#include "candy/graphics/shader/Shader.hpp"
#include "candy/graphics/shader/ShaderLibrary.hpp"
#include <filesystem>
#include <utility>
#include "candy/graphics/Vulkan.hpp"
#include "candy/utils/FileUtils.hpp"
#include "shaderc/libshaderc/include/shaderc/shaderc.hpp"
#include "SPIRV-Cross/spirv_glsl.hpp"

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
      CANDY_CORE_INFO("GOT BINARIES");
      //CompileOrGetBinaries(preProcessor->GetSourceStrings());
        
      // Extract name from filepath
      shaderName = Utils::FileUtils::ExtractNameFromFilePath(filepath);
        
        
    }
    
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
            
            shaderModules.push_back(shaderModule);
            ShaderStageCreateInfos.push_back(ShaderStageCreateInfo);
        }
        return ShaderStageCreateInfos;
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
  
  
  uint32_t Shader::SetColor(const std::string& name, const Color& color)
  {
    return GetLayout().SetUniform(name, &color);
  }
  uint32_t Shader::SetVector4(const std::string& name, const Math::Vector4& vector)
  {
  
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
    
    /*void Shader::CompileOrGetBinaries(const std::unordered_map<ShaderData::Stage, std::string> &sources)
    {
        shaderc::Compiler compiler;
        shaderc::CompileOptions options;
        options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_3);
        
        if (optimize)
            options.SetOptimizationLevel(shaderc_optimization_level_performance);
        
        
        
        
        std::filesystem::path cacheDirectory = GetCacheDirectory();
        
        auto& shaderData = spirvBinaries;
        shaderData.clear();
        
        for (auto&& [stage, source] : sources)
        {
            std::filesystem::path shaderFilePath = filepath;
            std::filesystem::path cachedPath = cacheDirectory / (shaderFilePath.filename().string() + ShaderData::StageToCachedFileExtension(stage));
            
            std::ifstream in(cachedPath, std::ios::in | std::ios::binary);
            if (in.is_open() && !recompileOnLoad)
            {
                CANDY_CORE_INFO("ALREADY HAS SHADER CACHED");
                in.seekg(0, std::ios::end);
                auto size = in.tellg();
                in.seekg(0, std::ios::beg);
                
                auto& data = shaderData[stage];
                data.resize(size / sizeof(uint32_t));
                in.read((char*)data.data(), size);
            }
            else
            {
                CANDY_CORE_INFO("NO SHADER CACHED, COMPILING BINARIES");
                shaderc::SpvCompilationResult mod = compiler.CompileGlslToSpv(source, StageToShaderC(stage), filepath.string().c_str(), options);
                if (mod.GetCompilationStatus() != shaderc_compilation_status_success)
                {
                    CANDY_CORE_ERROR(mod.GetErrorMessage());
                    CANDY_CORE_ASSERT(false);
                }
                
                shaderData[stage] = std::vector<uint32_t>(mod.cbegin(), mod.cend());
                
                std::ofstream out(cachedPath, std::ios::out | std::ios::binary);
                if (out.is_open())
                {
                    auto& data = shaderData[stage];
                    out.write((char*)data.data(), data.size() * sizeof(uint32_t));
                    out.flush();
                    out.close();
                }
            }
        }
       
        std::vector<VkDescriptorSetLayoutBinding> layoutBindings{};
        for (auto&& [stage, data] : shaderData)
        {
            Reflect(stage, data, layoutBindings);
        }
      
      VkDescriptorSetLayoutCreateInfo layoutInfo{};
      layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
      layoutInfo.bindingCount = layoutBindings.size();
      layoutInfo.pBindings = layoutBindings.data();
      
      CANDY_CORE_ASSERT(vkCreateDescriptorSetLayout(Vulkan::LogicalDevice(), &layoutInfo, nullptr, &descriptorSetLayout) == VK_SUCCESS, "Failed to create descriptor set layout!");
      
        
        
    }*/
    
    /*void Shader::Reflect(ShaderData::Stage stage, std::vector<uint32_t> spirvBinary, std::vector<VkDescriptorSetLayoutBinding>& layoutBindings)
    {
      spirv_cross::CompilerGLSL compiler(std::move(spirvBinary));
      auto resources = compiler.get_shader_resources();
      
     
      
      for (auto& resource : resources.uniform_buffers)
      {
        CANDY_CORE_INFO("UNIFORM NAME: {}", resource.name);
        CANDY_CORE_INFO("UNIFORM SIZE: {}", compiler.get_declared_struct_size(compiler.get_type(resource.base_type_id)));
        auto memberNames = compiler.get_type(resource.base_type_id).member_name_cache;
        for (auto& memberName : memberNames)
        {
          CANDY_CORE_INFO("UNIFORM MEMBER NAME: {}", memberName);
        }
        uint32_t set = compiler.get_decoration(resource.id, spv::DecorationDescriptorSet);
        uint32_t binding = compiler.get_decoration(resource.id, spv::DecorationBinding);
        
        VkDescriptorSetLayoutBinding layoutBinding{};
        
        layoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        layoutBinding.descriptorCount = 1;
        layoutBinding.binding = binding;
        layoutBinding.stageFlags = ShaderData::StageToVulkan(stage);
        layoutBinding.pImmutableSamplers = nullptr;
        layoutBindings.push_back(layoutBinding);
        
      }
      
      for (auto& resource : resources.sampled_images)
      {
        VkDescriptorSetLayoutBinding samplerLayoutBinding{};
        uint32_t binding = compiler.get_decoration(resource.id, spv::DecorationBinding);
        samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        samplerLayoutBinding.descriptorCount = 1;
        samplerLayoutBinding.binding = binding;
        samplerLayoutBinding.stageFlags = ShaderData::StageToVulkan(stage);
        samplerLayoutBinding.pImmutableSamplers = nullptr;
        layoutBindings.push_back(samplerLayoutBinding);
      }
      VkPushConstantRange pushRange{};
      pushRange.stageFlags = ShaderData::StageToVulkan(stage);
      pushRange.offset = 0;
      
      
      uint32_t id = compiler.get_shader_resources().push_constant_buffers[0].id;
      uint32_t base_type_id = compiler.get_shader_resources().push_constant_buffers[0].base_type_id;
      uint32_t pcrSize=0;
      std::vector<spirv_cross::BufferRange> ranges = (std::vector<spirv_cross::BufferRange>)compiler.get_active_buffer_ranges(id);
      for (auto& range : ranges)
      {
        
        CANDY_CORE_INFO("MEMBER NAME {}", compiler.get_member_name(base_type_id, range.index));
        CANDY_CORE_INFO("Member: {0}, Offset: {1}, Size: {2}", range.index, range.offset, range.range);
        pcrSize += range.range;
      }
      pushRange.size = pcrSize;
      if (pushRange.size > 0)
      {
        pushConstantRanges.push_back(pushRange);
      }
      
      
    }*/
    
    
    
    
    void Shader::DestroyShaderModules()
    {
        for (auto& shaderModule : shaderModules)
            vkDestroyShaderModule(Vulkan::LogicalDevice(), shaderModule, nullptr);
        shaderModules.clear();
    }
  
  //uint32_t Shader::PushConstantRangeCount(){return postProcessor.pushConstantRanges.size();}
  //const VkPushConstantRange* Shader::PushConstantRangeData(){return postProcessor.pushConstantRanges.data();}
  
 /* std::vector<VkDescriptorSetLayout> Shader::GetDescriptorSetLayouts()
  {
      return GetLayout().GetDescriptorSetLayouts();
  
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