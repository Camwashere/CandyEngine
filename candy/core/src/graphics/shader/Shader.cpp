#include "candy/graphics/shader/Shader.hpp"
#include "candy/graphics/shader/ShaderLibrary.hpp"
#include <filesystem>
#include <utility>
#include "candy/graphics/Vulkan.hpp"
#include "candy/utils/FileUtils.hpp"
#include "shaderc/libshaderc/include/shaderc/shaderc.hpp"
#include "SPIRV-Cross/spirv_glsl.hpp"
#include <candy/graphics/RenderCommand.hpp>
#include <candy/graphics/shader/ShaderLibrary.hpp>
#include <candy/collections/GenericBuffer.hpp>

using namespace Candy::Utils;
namespace Candy::Graphics
{
  
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
    
    
    Shader::Shader(const ShaderSettings&  settings) : postProcessor(settings)
    {
        CANDY_PROFILE_FUNCTION();
      
      preProcessor = ShaderPreProcessor::Create(settings.filepath);
      postProcessor.CompileOrGetBinaries(preProcessor->GetSourceStrings(), settings.filepath);
      
      
        
      // Extract name from filepath
      shaderName = Utils::FileUtils::ExtractNameFromFilePath(settings.filepath);
      
    }
  
    struct SpecConstantData
    {
      Collections::GenericBuffer buffer;
      std::vector<VkSpecializationMapEntry> entries;
      VkSpecializationInfo specInfo{};
    };
  void Shader::Bake()
  {
    CANDY_PROFILE_FUNCTION();
    std::vector<VkPipelineShaderStageCreateInfo> createInfos = CreateShaderStageCreateInfos();
    std::vector<SpecConstantData> specConstantData(createInfos.size());
    
    for (int i=0; i<createInfos.size(); i++)
    {
      size_t currentSize=0;
      
      for(const auto& specInput : GetLayout().settings.constantInputs)
      {
        ShaderSpecializationConstant specConstant;
        if (GetLayout().GetSpecConstant(specInput.GetName(), &specConstant))
        {
          if (specConstant.stage == ShaderData::VulkanToStage(createInfos[i].stage))
          {
            
            VkSpecializationMapEntry entry{};
            entry.constantID = specConstant.id;
            
            //size_t typeSize = ShaderData::TypeSize(specConstant.type);
            size_t typeSize = specInput.GetSize();
            entry.size = typeSize;
            entry.offset = currentSize;
            
            //CANDY_CORE_CRITICAL("Entry size: {0}, Entry offset: {1}", entry.size, entry.offset);
            specConstantData[i].buffer.AddBuffer(specInput.GetValue());
            
            
            currentSize += entry.size;
            specConstantData[i].entries.push_back(entry);
            
            
          }
        }
        
      }
      
      if (! specConstantData[i].entries.empty())
      {
        
        specConstantData[i].specInfo.mapEntryCount = (uint32_t)specConstantData[i].entries.size();
        specConstantData[i].specInfo.pMapEntries = specConstantData[i].entries.data();
        specConstantData[i].specInfo.dataSize = specConstantData[i].buffer.Size();
        specConstantData[i].specInfo.pData = specConstantData[i].buffer.Data();
        //CANDY_CORE_CRITICAL("Post: Data size: {0}, Entry count: {1}", specConstantData[i].specInfo.dataSize, specConstantData[i].specInfo.mapEntryCount);
        
        
        
        
        createInfos[i].pSpecializationInfo = &specConstantData[i].specInfo;
      }
      else
      {
        createInfos[i].pSpecializationInfo=nullptr;
      }
    }
    /*for (auto& createInfo : createInfos)
    {
      size_t currentSize=0;
      
      
      
      Collections::GenericBuffer buffer;
      std::vector<VkSpecializationMapEntry> entries{};
      for(const auto& specInput : GetLayout().settings.constantInputs)
      {
        ShaderSpecializationConstant specConstant;
        if (GetLayout().GetSpecConstant(specInput.GetName(), &specConstant))
        {
          if (specConstant.stage == ShaderData::VulkanToStage(createInfo.stage))
          {
            VkSpecializationMapEntry entry{};
            entry.constantID = specConstant.id;
            
            //size_t typeSize = ShaderData::TypeSize(specConstant.type);
            size_t typeSize = specInput.GetSize();
            entry.size = typeSize;
            entry.offset = currentSize;
            
            CANDY_CORE_CRITICAL("Entry size: {0}, Entry offset: {1}", entry.size, entry.offset);
            buffer.AddBuffer(specInput.GetValue());
            
            
            currentSize += entry.size;
            entries.push_back(entry);
            
          }
        }
        
      }
      VkSpecializationInfo specInfo{};
      if (! entries.empty())
      {
        
        specInfo.mapEntryCount = (uint32_t)entries.size();
        specInfo.pMapEntries = entries.data();
        specInfo.dataSize = buffer.Size();
        specInfo.pData = buffer.Data();
        CANDY_CORE_CRITICAL("Post: Data size: {0}, Entry count: {1}", specInfo.dataSize, specInfo.mapEntryCount);
        
        for (size_t i=0; i<specInfo.mapEntryCount; ++i)
        {
          CANDY_CORE_CRITICAL("Entry size: {0}, Entry offset: {1}", specInfo.pMapEntries[i].size, specInfo.pMapEntries[i].offset);
        }
        
        
        createInfo.pSpecializationInfo = &specInfo;
      }
      else
      {
        createInfo.pSpecializationInfo=nullptr;
      }
    }*/
    
    //CANDY_CORE_INFO("Baking pipeline");
    GetLayout().BakePipeline(createInfos);
    //CANDY_CORE_INFO("Baked pipeline");
    
  }
  void Shader::Bind()
  {
    CANDY_PROFILE_FUNCTION();
    RenderCommand::BindPipeline(GetLayout().pipeline);
  }
  
  void Shader::Commit()
  {
    CANDY_PROFILE_FUNCTION();
    GetLayout().BindAll();

  }
  
    std::vector<VkPipelineShaderStageCreateInfo> Shader::CreateShaderStageCreateInfos()
    {
      CANDY_PROFILE_FUNCTION();
        std::vector<VkPipelineShaderStageCreateInfo> ShaderStageCreateInfos;
        for (auto&& [stage, binaryCode] : postProcessor.spirvBinaries)
        {
            VkShaderModule shaderModule = CreateShaderModule(stage);
            VkPipelineShaderStageCreateInfo shaderStageCreateInfo{};
            shaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
            shaderStageCreateInfo.stage = ShaderData::StageToVulkan(stage);
            shaderStageCreateInfo.module = shaderModule;
            shaderStageCreateInfo.pName = "main";

            ShaderStageCreateInfos.push_back(shaderStageCreateInfo);
        }
        return ShaderStageCreateInfos;
    }
  
  const std::string& Shader::GetName()const
  {
      return shaderName;
  }
  const std::filesystem::path& Shader::GetFilepath()const
  {
      return GetLayout().GetSettings().filepath;
  }
  const ShaderSettings& Shader::GetSettings()const{return GetLayout().GetSettings();}
  VkPipeline Shader::GetPipeline()const{return GetLayout().GetPipeline();}
  VkPipelineLayout Shader::GetPipelineLayout()const{return GetLayout().GetPipelineLayout();}
  uint32_t Shader::GetPushID(const std::string& name)const
  {
    return GetLayout().GetPushID(name);
  }
  uint32_t Shader::PushInt(const std::string& name, int value)
  {
    
      return GetLayout().PushConstant(name, &value);
  }
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
  void Shader::PushInt(uint32_t id, int value)
  {
    GetLayout().PushConstant(id, &value);
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
      CANDY_PROFILE_FUNCTION();
        const auto& valuePair = postProcessor.spirvBinaries.find(stage);
        CANDY_CORE_ASSERT(valuePair != postProcessor.spirvBinaries.end(), "Shader binary not found! Cannot attempt to create shader module!");
        const auto& binary = valuePair->second;
        VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = binary.size()*sizeof(uint32_t);
        createInfo.pCode = binary.data();
        VkShaderModule shaderModule;
      CANDY_VULKAN_CHECK(vkCreateShaderModule(Vulkan::LogicalDevice(), &createInfo, nullptr, &shaderModule));
        
        return shaderModule;
    }


  

  std::vector<VkPushConstantRange> Shader::GetPushConstantRanges()
  {
    CANDY_PROFILE_FUNCTION();
      return GetLayout().GetPushConstantRanges();
  
  }
  std::vector<char> Shader::ReadSpvFileBinary(const std::string& filename)
  {
    CANDY_PROFILE_FUNCTION();
    std::ifstream file(filename, std::ios::ate | std::ios::binary);
    CANDY_CORE_ASSERT(file.is_open(), "Failed to open file!");
    
    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);
    
    file.seekg(0);
    file.read(buffer.data(), fileSize);
    file.close();
    
    return buffer;
  }
  
    
    SharedPtr<Shader> Shader::Create(const ShaderSettings& settings)
    {
      CANDY_PROFILE_FUNCTION();
      SharedPtr<Shader> shader = CreateSharedPtr<Shader>(settings);
      ShaderLibrary::AddShader(shader);
      return shader;
    }
  
    
    
    
}