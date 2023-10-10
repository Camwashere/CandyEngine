#include "candy/graphics/shader/Shader.hpp"
#include "candy/graphics/shader/ShaderLibrary.hpp"
#include <filesystem>
#include "candy/graphics/shader/config/ShaderSettings.hpp"
#include <candy/graphics/shader/processing/ShaderPreProcessor.hpp>
#include <candy/graphics/shader/processing/ShaderPostProcessor.hpp>
#include "candy/graphics/Vulkan.hpp"
#include "candy/utils/FileUtils.hpp"
#include "shaderc/libshaderc/include/shaderc/shaderc.hpp"
#include "SPIRV-Cross/spirv_glsl.hpp"
#include <candy/graphics/RenderCommand.hpp>
#include <candy/graphics/shader/ShaderLibrary.hpp>
#include <candy/collections/GenericBuffer.hpp>
#include <candy/graphics/vulkan/DeletionQueue.hpp>
#include <utility>
#include <candy/graphics/Renderer.hpp>
#include <candy/graphics/vulkan/RenderPass.hpp>
using namespace Candy::Utils;
namespace Candy::Graphics
{
  
  static shaderc_shader_kind StageToShaderC(ShaderData::Stage stage)
  {
    switch (stage)
    {
      
      case ShaderData::Stage::Vertex: return shaderc_glsl_vertex_shader;
      case ShaderData::Stage::Fragment: return shaderc_glsl_fragment_shader;
      case ShaderData::Stage::Compute: return shaderc_glsl_compute_shader;
      case ShaderData::Stage::Geometry: return shaderc_glsl_geometry_shader;
      case ShaderData::Stage::TessellationControl: return shaderc_glsl_tess_control_shader;
      case ShaderData::Stage::TessellationEvaluation: return shaderc_glsl_tess_evaluation_shader;
      default:
      CANDY_CORE_ASSERT(false, "Unknown shader stage!");
        return (shaderc_shader_kind) 0;
    }
  }
  static VkShaderModule CreateShaderModule(const std::vector<uint32_t> &binary)
  {
    CANDY_PROFILE_FUNCTION();
    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = binary.size()*sizeof(uint32_t);
    createInfo.pCode = binary.data();
    VkShaderModule shaderModule;
    CANDY_VULKAN_CHECK(vkCreateShaderModule(Vulkan::LogicalDevice(), &createInfo, nullptr, &shaderModule));
    
    return shaderModule;
  }
  
  static std::vector<VkPipelineShaderStageCreateInfo> CreateShaderStageCreateInfos(const std::unordered_map<ShaderData::Stage, std::vector<uint32_t>>& spirvBinaries)
  {
    CANDY_PROFILE_FUNCTION();
    std::vector<VkPipelineShaderStageCreateInfo> ShaderStageCreateInfos;
    for (auto &&[stage, binaryCode]: spirvBinaries)
    {
      VkShaderModule shaderModule = CreateShaderModule(binaryCode);
      VkPipelineShaderStageCreateInfo shaderStageCreateInfo{};
      shaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
      shaderStageCreateInfo.stage = ShaderData::StageToVulkan(stage);
      shaderStageCreateInfo.module = shaderModule;
      shaderStageCreateInfo.pName = "main";
      
      ShaderStageCreateInfos.push_back(shaderStageCreateInfo);
    }
    return ShaderStageCreateInfos;
  }
  
  Shader::Shader(ShaderSettings shaderSettings) : settings(std::move(shaderSettings)), profile(settings.profileSettings, settings.configs)
  {
    CANDY_PROFILE_FUNCTION();

    ShaderPreProcessor preProcessor(settings.sourceFilePath);
    ShaderPostProcessor postProcessor(ShaderLibrary::GetCompilationSettings(), preProcessor.GetSourceStrings(), settings.sourceFilePath);
    
    postProcessor.BuildLayout(layout);
    spirvBinaries = postProcessor.spirvBinaries;
    
    // Extract name from filepath
    shaderName = Utils::FileUtils::ExtractNameFromFilePath(settings.sourceFilePath);
    
  }
  

  void Shader::Reload()
  {
    ShaderPreProcessor preProcessor(settings.sourceFilePath);
    ShaderPostProcessor postProcessor(ShaderLibrary::GetCompilationSettings(), preProcessor.GetSourceStrings(), settings.sourceFilePath);
    
    postProcessor.BuildLayout(layout);
    
    Bake();
  }
  
  void Shader::Bake()
  {
    CANDY_PROFILE_FUNCTION();
    
    std::vector<VkPipelineShaderStageCreateInfo> createInfos = CreateShaderStageCreateInfos(spirvBinaries);
    std::vector<VkShaderModule> shaderModules(createInfos.size());
    for (int i=0; i<createInfos.size(); i++)
    {
      shaderModules[i] = createInfos[i].module;
    }
    layout.BakePipelineLayout(profile.settings.renderPassIndex);
    BakeConfiguration(createInfos);
    for (int i=0; i<shaderModules.size(); i++)
    {
      vkDestroyShaderModule(Vulkan::LogicalDevice(), shaderModules[i], nullptr);
    }
  }
  void Shader::BakeConfiguration(const std::vector<VkPipelineShaderStageCreateInfo>& createInfos)
  {
    profile.Bake(createInfos, layout);
  }
  void Shader::Bind()
  {
    CANDY_PROFILE_FUNCTION();
    
    profile.Bind();
    layout.BindAllDescriptorSets(profile.GetActiveRenderPassIndex());
  }

  const std::string &Shader::GetName() const
  {
    return shaderName;
  }
  
  const std::filesystem::path &Shader::GetFilepath() const
  {
    return settings.sourceFilePath;
  }

  
  ShaderLayout &Shader::GetLayout() {return layout;}
  
  [[nodiscard]] const ShaderLayout &Shader::GetLayout() const {return layout;}
  
  [[nodiscard]] BufferLayout Shader::GetBufferLayout() const {return layout.vertexLayout;}
  
  [[nodiscard]] size_t Shader::GetMaterialBufferSize() const {return layout.materialBufferSize;}
  
  [[nodiscard]] size_t Shader::GetGlobalBufferSize() const {return layout.globalBufferSize;}
  
  
  uint32_t Shader::GetPushID(const std::string &name) const
  {
    return layout.GetPushID(name);
  }
  
  uint32_t Shader::PushInt(const std::string &name, int value)
  {
    
    return layout.PushConstant(name, &value);
  }
  
  uint32_t Shader::PushFloat(const std::string &name, float value)
  {
    return layout.PushConstant(name, &value);
  }
  
  uint32_t Shader::PushVector2(const std::string &name, const Math::Vector2 &vector)
  {
    return layout.PushConstant(name, &vector);
  }
  
  uint32_t Shader::PushVector3(const std::string &name, const Math::Vector3 &vector)
  {
    return layout.PushConstant(name, &vector);
  }
  
  uint32_t Shader::PushVector4(const std::string &name, const Math::Vector4 &vector)
  {
    return layout.PushConstant(name, &vector);
  }
  
  uint32_t Shader::PushMatrix(const std::string &name, const Math::Matrix4 &matrix)
  {
    return layout.PushConstant(name, &matrix);
  }
  
  void Shader::PushInt(uint32_t valueID, int value)
  {
    layout.PushConstant(valueID, &value);
  }
  
  void Shader::PushFloat(uint32_t valueID, float value)
  {
    layout.PushConstant(valueID, &value);
  }
  
  void Shader::PushVector2(uint32_t valueID, const Math::Vector2 &vector)
  {
    layout.PushConstant(valueID, &vector);
  }
  
  void Shader::PushVector3(uint32_t valueID, const Math::Vector3 &vector)
  {
    layout.PushConstant(valueID, &vector);
  }
  
  void Shader::PushVector4(uint32_t valueID, const Math::Vector4 &vector)
  {
    layout.PushConstant(valueID, &vector);
  }
  
  void Shader::PushMatrix(uint32_t valueID, const Math::Matrix4 &matrix)
  {
    layout.PushConstant(valueID, &matrix);
  }
  
  
  uint32_t Shader::SetFloat(const std::string &name, float value)
  {
    return layout.SetUniform(name, &value);
  }
  
  uint32_t Shader::SetVector2(const std::string &name, const Math::Vector2 &vector)
  {
    return layout.SetUniform(name, &vector);
  }
  
  uint32_t Shader::SetVector3(const std::string &name, const Math::Vector3 &vector)
  {
    return layout.SetUniform(name, &vector);
  }
  
  uint32_t Shader::SetVector4(const std::string &name, const Math::Vector4 &vector)
  {
    return layout.SetUniform(name, &vector);
  }
  
  uint32_t Shader::SetColor(const std::string &name, const Color &color)
  {
    return layout.SetUniform(name, &color);
  }
  
  uint32_t Shader::SetMatrix(const std::string &name, const Math::Matrix4 &matrix)
  {
    return layout.SetUniform(name, &matrix);
  }
  
  void Shader::SetFloat(uint32_t valueID, float value)
  {
    layout.SetUniform(valueID, &value);
  }
  
  void Shader::SetVector2(uint32_t valueID, const Math::Vector2 &vector)
  {
    layout.SetUniform(valueID, &vector);
  }
  
  void Shader::SetVector3(uint32_t valueID, const Math::Vector3 &vector)
  {
    layout.SetUniform(valueID, &vector);
  }
  
  void Shader::SetVector4(uint32_t valueID, const Math::Vector4 &vector)
  {
    layout.SetUniform(valueID, &vector);
  }
  
  void Shader::SetColor(uint32_t valueID, const Color &color)
  {
    layout.SetUniform(valueID, &color);
  }
  
  void Shader::SetMatrix(uint32_t valueID, const Math::Matrix4 &matrix)
  {
    layout.SetUniform(valueID, &matrix);
  }
  
  
  
  
  std::vector<VkPushConstantRange> Shader::GetPushConstantRanges()
  {
    CANDY_PROFILE_FUNCTION();
    return layout.GetPushConstantRanges();
    
  }
  
  std::vector<char> Shader::ReadSpvFileBinary(const std::string &filename)
  {
    CANDY_PROFILE_FUNCTION();
    std::ifstream file(filename, std::ios::ate|std::ios::binary);
    CANDY_CORE_ASSERT(file.is_open(), "Failed to open file!");
    
    size_t fileSize = (size_t) file.tellg();
    std::vector<char> buffer(fileSize);
    
    file.seekg(0);
    file.read(buffer.data(), fileSize);
    file.close();
    
    return buffer;
  }
  
  
  SharedPtr<Shader> Shader::Create(const ShaderSettings &settings)
  {
    CANDY_PROFILE_FUNCTION();
    SharedPtr<Shader> shader = CreateSharedPtr<Shader>(settings);
    ShaderLibrary::AddShader(shader);
    return shader;
  }
  
  
}