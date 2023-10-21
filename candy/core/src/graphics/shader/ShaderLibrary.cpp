#include "candy/graphics/shader/ShaderLibrary.hpp"
#include "CandyPch.hpp"
#include <candy/graphics/shader/Shader.hpp>
#include <candy/graphics/shader/ShaderLayout.hpp>
#include <filesystem>
#include <candy/graphics/Vulkan.hpp>
#include "candy/utils/IDManager.hpp"
#include "CandyEngine.hpp"
#include <candy/graphics/vulkan/descriptor/DescriptorBuilder.hpp>
#include <candy/graphics/GraphicsContext.hpp>
#include <candy/graphics/FrameResources.hpp>
#include <candy/project/ProjectManager.hpp>
#include <candy/graphics/shader/config/ShaderSettings.hpp>
#include "rapidyaml/src/ryml_std.hpp"
#include "rapidyaml/src/ryml.hpp"
namespace Candy::Graphics
{
  using namespace Utils;
  
  struct ShaderLibraryData
  {
    ShaderLibrarySettings settings;
    bool initialized=false;
    bool logInitialization=true;
    
    std::filesystem::path internalShaderDirectory;
    std::filesystem::path internalSourceDirectory;
    std::filesystem::path internalProfileDirectory;
    std::filesystem::path internalCacheDirectory;
    
    std::filesystem::path defaultLibSettingsPath;
    
    IDManager<uint32_t> idManager;
    std::unordered_map<std::string, uint32_t> nameToIDMap;
    std::vector<SharedPtr<Shader>> shaders;
    std::vector<ShaderSet> shaderSets;
  };
  
  static ShaderLibraryData data;
  
  
  
  bool ShaderLibrary::LoadLibrarySettings(ShaderLibrarySettings& settings, const std::filesystem::path& filepath)
  {
    CANDY_CORE_INFO("DESERIALIZING PROJECT");
    
    // read the file into a string
    std::ifstream fin(filepath);
    std::stringstream buffer;
    buffer << fin.rdbuf();
    std::string yaml_str = buffer.str();
    if (yaml_str.empty())
    {
      CANDY_CORE_ERROR("EMPTY YAML STRING WITH PATH: {}", filepath.string());
      CANDY_CORE_ASSERT(false);
      return false;
    }
    // parse the YAML string
    ryml::Tree tree = ryml::parse_in_arena(ryml::to_csubstr(yaml_str));
    ryml::NodeRef root = tree.rootref();
    
    auto libNode = root["ShaderLibrarySettings"];
    if (libNode.empty())
    {
      CANDY_CORE_ERROR("Failed to deserialize project file {0}. Empty Project Root Node", filepath.string());
      CANDY_CORE_ASSERT(false);
      return false;
    }
    
    
    auto compilationNode = libNode["CompilationSettings"];
    
    compilationNode["AutoMapping"] >> settings.compilationSettings.autoMapping;
    compilationNode["PreserveBindings"] >> settings.compilationSettings.preserveBindings;
    compilationNode["SuppressWarnings"] >> settings.compilationSettings.suppressWarnings;
    compilationNode["WarningsAsErrors"] >> settings.compilationSettings.warningsAsErrors;
    compilationNode["InvertY"] >> settings.compilationSettings.invertY;
    compilationNode["GenerateDebugInfo"] >> settings.compilationSettings.generateDebugInfo;
    compilationNode["Optimize"] >> settings.compilationSettings.optimize;
    compilationNode["RecompileOnLoad"] >> settings.compilationSettings.recompileOnLoad;
    compilationNode["GLSLVersion"] >> settings.compilationSettings.glslVersion;
    compilationNode["VulkanVersion"] >> settings.compilationSettings.vulkanVersion;
    
    //CANDY_CORE_ASSERT(settings.compilationSettings.invertY == true, "INVERT Y IS STILL FALSE");
    return true;
  }
  
  bool ShaderLibrary::Init()
  {
    CANDY_PROFILE_FUNCTION();
    data.defaultLibSettingsPath = CandyEngine::GetInternalConfigDirectory() / "shader" / "librarySettings.yml";
    bool loadedSettings = LoadLibrarySettings(data.settings, data.defaultLibSettingsPath);
    CANDY_CORE_ASSERT(loadedSettings);
    data.internalShaderDirectory = CandyEngine::GetInternalAssetsDirectory() / "shaders";
    data.internalSourceDirectory = data.internalShaderDirectory / "sources";
    data.internalProfileDirectory = data.internalShaderDirectory / "profiles";
    data.internalCacheDirectory = data.internalShaderDirectory / "cache";
    
   
    
    
    data.initialized = std::filesystem::exists(data.internalShaderDirectory);
    
    if (data.initialized)
    {
      data.shaderSets.resize(3);
    }
    
    return data.initialized;
    
    
    
  }
  
  
  void ShaderLibrary::AddShader(const SharedPtr<Shader>& shader)
  {
    CANDY_PROFILE_FUNCTION();
      for (const auto& set : shader->GetLayout().sets)
      {
        auto& libSet = data.shaderSets[set.GetSet()];
        for (const auto& block : set.blocks)
        {
          if (!libSet.HasBlockBinding(block.binding))
          {
            libSet.AddBlock(block);
          }
        }
        for (const auto& tex : set.textures)
        {
          if (!libSet.HasTextureBinding(tex.binding))
          {
            libSet.AddTexture(tex);
          }
        }
      }
      data.shaders.push_back(shader);
  }
  void ShaderLibrary::Bake()
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_INFO("Baking shaders");
    for (auto& shader : data.shaders)
    {
      shader->Bake();
    }
    CANDY_CORE_INFO("Baked shaders");
  }
  void ShaderLibrary::Reload()
  {
    CANDY_PROFILE_FUNCTION();
      
    
      for (auto& shader : data.shaders)
      {
        shader->Reload();
      }
      
      
        
  }
  VkDescriptorType GetDescriptorType(size_t setIndex)
  {
    CANDY_PROFILE_FUNCTION();
    switch(setIndex)
    {
      case 0:
        return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
      case 1:
        return VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;
      default:
      CANDY_CORE_ASSERT(false, "Invalid descriptor set index!");
        return VK_DESCRIPTOR_TYPE_MAX_ENUM;
    }
  }
  
  std::vector<VkDescriptorSetLayout> ShaderLibrary::BakeDescriptorSetLayouts(uint8_t renderPassIndex)
  {
    CANDY_PROFILE_FUNCTION();
    
    std::vector<VkDescriptorSetLayout> layouts;
    
    //size_t LAYOUT_NUM = data.shaderSets.size();
    layouts.resize(data.shaderSets.size());
    //bool skipObject=renderPassIndex == Renderer::GetOverlayPassIndex();
    
    for (size_t i = 0; i<data.shaderSets.size(); i++)
    {
      DescriptorBuilder builder = DescriptorBuilder::Begin();
      
      
      
      for (const auto &block: data.shaderSets[i].blocks)
      {
        
        builder.AddBinding(block.binding, GetDescriptorType(i), ShaderData::StageToVulkan(block.stage));
      }
      for (const auto &tex: data.shaderSets[i].textures)
      {
        builder.AddBinding(tex.binding, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, ShaderData::StageToVulkan(tex.stage), tex.arraySize);
      }
      layouts[i] = builder.BuildLayout();
      for (int f = 0; f<Vulkan::GetFramesInFlight(); f++)
      {
        bool alloc = builder.AllocateDescriptorSet(&Vulkan::GetCurrentContext().GetFrame(f).GetDescriptorSet(i, renderPassIndex), layouts[i]);
        CANDY_CORE_ASSERT(alloc, "Failed to allocate descriptor set!");
      }
    }
    return layouts;
  }
  
  const std::filesystem::path& ShaderLibrary::GetInternalCacheDirectory()
  {
    return data.internalCacheDirectory;
  }
  const std::filesystem::path& ShaderLibrary::GetInternalSourceDirectory()
  {
    return data.internalSourceDirectory;
  }
  const std::filesystem::path& ShaderLibrary::GetInternalProfileDirectory()
  {
    return data.internalProfileDirectory;
  }
  
  
  const ShaderCompilationSettings& ShaderLibrary::GetCompilationSettings()
  {
    return data.settings.compilationSettings;
  }
  
  bool ShaderLibrary::IsInitialized()
  {
    return data.initialized;
  }
  
}