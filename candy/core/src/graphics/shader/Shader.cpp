#include "candy/graphics/shader/Shader.hpp"
#include "candy/graphics/shader/ShaderLibrary.hpp"
#include <filesystem>
#include <utility>
#include "candy/graphics/Vulkan.hpp"
#include "candy/utils/FileUtils.hpp"
#include "shaderc/libshaderc/include/shaderc/shaderc.hpp"
#include "SPIRV-Cross/spirv_glsl.hpp"
#include <candy/graphics/RenderCommand.hpp>

using namespace Candy::Utils;
namespace Candy::Graphics
{
  
  
  static std::filesystem::path GetCacheDirectory()
  {
    return "assets/cache/shader";
    //CANDY_CORE_ASSERT(shaderLibrary->IsValid(), "Shader library is not valid!");
    //return shaderLibrary->GetCacheDirectory();
  }
  
  static shaderc_shader_kind StageToShaderC(ShaderData::Stage stage)
  {
    switch (stage)
    {
      
      case ShaderData::Stage::Vertex:   return shaderc_glsl_vertex_shader;
      case ShaderData::Stage::Fragment: return shaderc_glsl_fragment_shader;
      case ShaderData::Stage::Compute: return shaderc_glsl_compute_shader;
      case ShaderData::Stage::Geometry: return shaderc_glsl_geometry_shader;
      case ShaderData::Stage::TessellationControl: return shaderc_glsl_tess_control_shader;
      case ShaderData::Stage::TessellationEvaluation: return shaderc_glsl_tess_evaluation_shader;
      default:
      CANDY_CORE_ASSERT(false, "Unknown shader stage!");
        return (shaderc_shader_kind)0;
    }
  }
    
    
    Shader::Shader(std::filesystem::path  shaderFilePath) : filepath(std::move(shaderFilePath))
    {
        CANDY_PROFILE_FUNCTION();
      
      preProcessor = ShaderPreProcessor::Create(filepath);
      postProcessor.CompileOrGetBinaries(preProcessor->GetSourceStrings(), filepath);
      
      //pipeline.AddDynamicStates({VK_DYNAMIC_STATE_VIEWPORT,VK_DYNAMIC_STATE_SCISSOR});
      
        
      // Extract name from filepath
      shaderName = Utils::FileUtils::ExtractNameFromFilePath(filepath);
      
      GetLayout().BakePipeline(Renderer::GetRenderPass(), CreateShaderStageCreateInfos());
      //BakePipeline(Renderer::GetRenderPass());
        
    }
  
  void Shader::Bind()
  {
    RenderCommand::BindPipeline(GetLayout().pipeline);
    //Vulkan::GetCurrentCommandBuffer().BindPipeline(pipeline);
  }
  /*void Shader::BakePipeline(VkRenderPass renderPass)
  {
    VkPipelineLayout pipelineLayout = BakePipelineLayout();
    GetLayout().BakePipeline(renderPass, CreateShaderStageCreateInfos());
    //DestroyShaderModules();
  
  }
  
  VkPipelineLayout Shader::BakePipelineLayout()
  {
    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    VkPipelineLayout pipelineLayout;
    
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    
    
    auto descriptorSetLayouts = BakeDescriptorSetLayouts();
    //CANDY_CORE_INFO("DESCRIPTOR SET VECTOR SIZE: {}", descriptorSetLayouts.size());
    for (auto d : descriptorSetLayouts)
    {
      if (d==VK_NULL_HANDLE)
      {
        CANDY_CORE_ERROR("NULL DESCRIPTOR SET LAYOUT HANDLE");
      }
    }
    pipelineLayoutInfo.setLayoutCount = descriptorSetLayouts.size();
    pipelineLayoutInfo.pSetLayouts = descriptorSetLayouts.data();
    
    auto pushConstantRanges = GetPushConstantRanges();
    //CANDY_CORE_INFO("Push Constant Range Count: {0}", pushConstantRanges.size());
    pipelineLayoutInfo.pushConstantRangeCount = pushConstantRanges.size(); // Optional
    pipelineLayoutInfo.pPushConstantRanges = pushConstantRanges.data(); // Optional
    
    CANDY_CORE_ASSERT(vkCreatePipelineLayout(Vulkan::LogicalDevice(), &pipelineLayoutInfo, nullptr, &pipelineLayout) == VK_SUCCESS, "Failed to create pipeline layout!");
    Vulkan::DeletionQueue().Push(pipelineLayout);
    return pipelineLayout;
  }
  std::vector<VkDescriptorSetLayout> Shader::BakeDescriptorSetLayouts()
  {
    std::vector<VkDescriptorSetLayout> layouts;
    layouts.resize(FRAME_OVERLAP);
    
    for (int i=0; i<FRAME_OVERLAP; i++)
    {
      DescriptorBuilder builder = DescriptorBuilder::Begin();
      
      
      for (const auto& block : GetLayout().uniformBlockProperties)
      {
        builder.AddBinding(block.binding, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, ShaderData::StageToVulkan(block.stage));
        //builder.BindBuffer(block.binding, &bufferInfo, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, ShaderData::StageToVulkan(block.stage));
      }
      for (const auto& block : GetLayout().uniformImageProperties)
      {
        //CANDY_CORE_INFO("IMAGE BINDING: {}", block.binding);
        builder.AddBinding(block.binding, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, ShaderData::StageToVulkan(block.stage));
        //builder.BindImage(block.binding, &imageInfo, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, ShaderData::StageToVulkan(block.stage));
      }
      
      builder.BuildLayout(&Vulkan::GetCurrentContext().GetFrame(i).globalDescriptor, layouts[i]);
      
      //Vulkan::PushDeleter([=, this](){vkDestroyDescriptorSetLayout(Vulkan::LogicalDevice(), layouts[i], nullptr);});
    }
    return layouts;
    
  }*/
    std::vector<VkPipelineShaderStageCreateInfo> Shader::CreateShaderStageCreateInfos()
    {
        std::vector<VkPipelineShaderStageCreateInfo> ShaderStageCreateInfos;
        for (auto&& [stage, binaryCode] : postProcessor.spirvBinaries)
        {
            VkShaderModule shaderModule = CreateShaderModule(stage);
            VkPipelineShaderStageCreateInfo ShaderStageCreateInfo{};
            ShaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
            ShaderStageCreateInfo.stage = ShaderData::StageToVulkan(stage);
            ShaderStageCreateInfo.module = shaderModule;
            ShaderStageCreateInfo.pName = "main";
            
            //shaderModules.push_back(shaderModule);
            ShaderStageCreateInfos.push_back(ShaderStageCreateInfo);
        }
        return ShaderStageCreateInfos;
    }
  VkPipeline Shader::GetPipeline()const{return GetLayout().GetPipeline();}
  VkPipelineLayout Shader::GetPipelineLayout()const{return GetLayout().GetPipelineLayout();}
  uint32_t Shader::PushFloat(const std::string& name, float value)
  {
    return GetLayout().PushConstant(name, &value);
  }
  uint32_t Shader::PushVector2(const std::string& name, const Math::Vector2& vector)
  {
    return GetLayout().PushConstant(name, &vector);
  }
  uint32_t Shader::PushVector3(const std::string& name, const Math::Vector3& vector)
  {
    return GetLayout().PushConstant(name, &vector);
  }
  uint32_t Shader::PushVector4(const std::string& name, const Math::Vector4& vector)
  {
    return GetLayout().PushConstant(name, &vector);
  }
  uint32_t Shader::PushMatrix(const std::string& name, const Math::Matrix4& matrix)
  {
    return GetLayout().PushConstant(name, &matrix);
  }
  
  void Shader::PushFloat(uint32_t id, float value)
  {
    GetLayout().PushConstant(id, &value);
  }
  void Shader::PushVector2(uint32_t id, const Math::Vector2& vector)
  {
    GetLayout().PushConstant(id, &vector);
  }
  void Shader::PushVector3(uint32_t id, const Math::Vector3& vector)
  {
    GetLayout().PushConstant(id, &vector);
  }
  void Shader::PushVector4(uint32_t id, const Math::Vector4& vector)
  {
    GetLayout().PushConstant(id, &vector);
  }
  void Shader::PushMatrix(uint32_t id, const Math::Matrix4& matrix)
  {
    GetLayout().PushConstant(id, &matrix);
  }
  
  
  
  uint32_t Shader::SetFloat(const std::string& name, float value)
  {
    return GetLayout().SetUniform(name, &value);
  }
  uint32_t Shader::SetVector2(const std::string& name, const Math::Vector2& vector)
  {
    return GetLayout().SetUniform(name, &vector);
  }
  uint32_t Shader::SetVector3(const std::string& name, const Math::Vector3& vector)
  {
    return GetLayout().SetUniform(name, &vector);
  }
  uint32_t Shader::SetVector4(const std::string& name, const Math::Vector4& vector)
  {
    return GetLayout().SetUniform(name, &vector);
  }
  uint32_t Shader::SetColor(const std::string& name, const Color& color)
  {
    return GetLayout().SetUniform(name, &color);
  }
  uint32_t Shader::SetMatrix(const std::string& name, const Math::Matrix4& matrix)
  {
    return GetLayout().SetUniform(name, &matrix);
  }
  
  void Shader::SetFloat(uint32_t id, float value)
  {
    GetLayout().SetUniform(id, &value);
  }
  void Shader::SetVector2(uint32_t id, const Math::Vector2& vector)
  {
    GetLayout().SetUniform(id, &vector);
  }
  void Shader::SetVector3(uint32_t id, const Math::Vector3& vector)
  {
    GetLayout().SetUniform(id, &vector);
  }
  void Shader::SetVector4(uint32_t id, const Math::Vector4& vector)
  {
    GetLayout().SetUniform(id, &vector);
  }
  void Shader::SetColor(uint32_t id, const Color& color)
  {
    GetLayout().SetUniform(id, &color);
  }
  void Shader::SetMatrix(uint32_t id, const Math::Matrix4& matrix)
  {
    GetLayout().SetUniform(id, &matrix);
  }
  
    VkShaderModule Shader::CreateShaderModule(ShaderData::Stage stage)
    {
        const auto& valuePair = postProcessor.spirvBinaries.find(stage);
        CANDY_CORE_ASSERT(valuePair != postProcessor.spirvBinaries.end(), "Shader binary not found! Cannot attempt to create shader module!");
        const auto& binary = valuePair->second;
        VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = binary.size()*sizeof(uint32_t);
        createInfo.pCode = binary.data();
        VkShaderModule shaderModule;
        CANDY_CORE_ASSERT(vkCreateShaderModule(Vulkan::LogicalDevice(), &createInfo, nullptr, &shaderModule) == VK_SUCCESS, "Failed to create shader module!");
        
        return shaderModule;
    }

    
    
    
    
    /*void Shader::DestroyShaderModules()
    {
        for (auto& shaderModule : shaderModules)
            vkDestroyShaderModule(Vulkan::LogicalDevice(), shaderModule, nullptr);
        shaderModules.clear();
    }*/
  

  std::vector<VkPushConstantRange> Shader::GetPushConstantRanges()
  {
      return GetLayout().GetPushConstantRanges();
  
  }
  std::vector<char> Shader::ReadSpvFileBinary(const std::string& filename)
  {
    std::ifstream file(filename, std::ios::ate | std::ios::binary);
    CANDY_CORE_ASSERT(file.is_open(), "Failed to open file!");
    
    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);
    
    file.seekg(0);
    file.read(buffer.data(), fileSize);
    file.close();
    
    return buffer;
  }
 
  
  
    
    SharedPtr<Shader> Shader::Create(const std::filesystem::path& shaderFilePath)
    {
        return CreateSharedPtr<Shader>(shaderFilePath);
    }
    
    
    
}