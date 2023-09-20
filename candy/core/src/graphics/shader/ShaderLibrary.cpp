#include "candy/graphics/shader/ShaderLibrary.hpp"
#include "CandyPch.hpp"
#include <utility>
#include <filesystem>
#include <candy/graphics/Vulkan.hpp>
#include "candy/utils/IDManager.hpp"
namespace Candy::Graphics
{
  using namespace Utils;
  
  struct ShaderLibraryData
  {
    /*std::filesystem::path internalCacheDirectory;
    std::filesystem::path internalSourceDirectory;
    std::filesystem::path projectCacheDirectory;
    std::filesystem::path projectSourceDirectory;
    
    ShaderCompilationSettings compilationSettings{};*/
    ShaderLibrarySettings settings;
    bool initialized=false;
    bool logInitialization=true;
    
    IDManager<uint32_t> idManager;
    std::unordered_map<std::string, uint32_t> nameToIDMap;
    std::vector<SharedPtr<Shader>> shaders;
    std::vector<ShaderSet> shaderSets;
  };
  
  static ShaderLibraryData data;
  
  std::string ShaderLibrary::DirectoryTypeToString(DirectoryType type)
  {
    switch (type)
    {
      case InternalCache:
        return "InternalCache";
      case InternalSource:
        return "InternalSource";
      case ProjectCache:
        return "ProjectCache";
      case ProjectSource:
        return "ProjectSource";
      case InternalDirs:
        return "InternalDirectories";
      case ProjectDirs:
        return "ProjectDirectories";
      case CacheDirs:
        return "CacheDirectories";
      case SourceDirs:
        return "SourceDirectories";
      case AllDirs:
        return "AllDirectories";
      default:
        return "Unknown";
    }
  }
  
  static bool CheckOrInitDirectory(const std::filesystem::path& path, bool createIfNeeded, ShaderLibrary::DirectoryType type)
  {
    CANDY_PROFILE_FUNCTION();
    if (std::filesystem::exists(path))
    {
      if (data.logInitialization)
      {
        CANDY_CORE_INFO("{0} with path: {1} exists!", ShaderLibrary::DirectoryTypeToString(type), path.string());
      }
      
      return true;
    }
    else
    {
      if (createIfNeeded)
      {
        if (std::filesystem::create_directories(path))
        {
          if (data.logInitialization)
          {
            CANDY_CORE_INFO("{0} with path {1} created!", ShaderLibrary::DirectoryTypeToString(type), path.string());
          }
          return true;
        }
        else
        {
          CANDY_CORE_ERROR("Failed to create {0} with path {1}!", ShaderLibrary::DirectoryTypeToString(type), path.string());
          return false;
        }
        
      }
      else
      {
        CANDY_CORE_ERROR("{0} with path {1} does not exist and create directories has been set to false", ShaderLibrary::DirectoryTypeToString(type), path.string());
        return false;
      }
    }
  }
  
  bool ShaderLibrary::Init(const ShaderLibrarySettings& libSettings, bool createDirectoriesIfNeeded)
  {
    CANDY_PROFILE_FUNCTION();
    data.settings = libSettings;
    
    data.initialized = CheckOrInitDirectory(data.settings.internalCacheDirectory, createDirectoriesIfNeeded, DirectoryType::InternalCache) &&
    CheckOrInitDirectory(data.settings.internalSourceDirectory, createDirectoriesIfNeeded, DirectoryType::InternalSource) &&
    CheckOrInitDirectory(data.settings.projectCacheDirectory, createDirectoriesIfNeeded, DirectoryType::ProjectCache) &&
    CheckOrInitDirectory(data.settings.projectSourceDirectory, createDirectoriesIfNeeded, DirectoryType::ProjectSource);
    
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
  void ShaderLibrary::Reload()
  {
    CANDY_PROFILE_FUNCTION();
      for (const auto& set : data.shaderSets)
      {
        CANDY_CORE_INFO("Set: {0}, bindings: {1}", set.GetSet(), set.blocks.size() + set.textures.size());
      }
      
      for (auto& shader : data.shaders)
      {
        shader->Bake();
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
    const int FRAME_OVERLAP = 2;
    std::vector<VkDescriptorSetLayout> layouts;
    
    size_t LAYOUT_NUM = data.shaderSets.size();
    layouts.resize(LAYOUT_NUM);
    //bool skipObject=renderPassIndex == Renderer::GetOverlayPassIndex();
    
    for (size_t i = 0; i<LAYOUT_NUM; i++)
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
      for (int f = 0; f<FRAME_OVERLAP; f++)
      {
        bool alloc = builder.AllocateDescriptorSet(&Vulkan::GetCurrentContext().GetFrame(f).GetDescriptorSet(i, renderPassIndex), layouts[i]);
        CANDY_CORE_ASSERT(alloc, "Failed to allocate descriptor set!");
      }
    }
    return layouts;
  }
  
  const std::filesystem::path& ShaderLibrary::GetInternalCacheDirectory()
  {
    return data.settings.internalCacheDirectory;
  }
  const std::filesystem::path& ShaderLibrary::GetInternalSourceDirectory()
  {
    return data.settings.internalSourceDirectory;
  }
  const std::filesystem::path& ShaderLibrary::GetProjectCacheDirectory()
  {
    return data.settings.projectCacheDirectory;
  }
  const std::filesystem::path& ShaderLibrary::GetProjectSourceDirectory()
  {
    return data.settings.projectSourceDirectory;
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