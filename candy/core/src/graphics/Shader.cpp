#include <candy/graphics/Shader.hpp>
#include <candy/graphics/ShaderLibrary.hpp>
#include <filesystem>
#include <utility>
#include <candy/graphics/Vulkan.hpp>
#include <candy/utils/FileUtils.hpp>
#include <shaderc/shaderc.hpp>
#include <spirv_glsl.hpp>

using namespace Candy::Utils;
namespace Candy::Graphics
{
  
  
  static std::filesystem::path GetCacheDirectory()
  {
    return "assets/cache/shader";
    //CANDY_CORE_ASSERT(shaderLibrary->IsValid(), "Shader library is not valid!");
    //return shaderLibrary->GetCacheDirectory();
  }
  
  static shaderc_shader_kind StageToShaderC(ShaderStage stage)
  {
    switch (stage)
    {
      
      case VERTEX:   return shaderc_glsl_vertex_shader;
      case FRAGMENT: return shaderc_glsl_fragment_shader;
      case COMPUTE: return shaderc_glsl_compute_shader;
      case GEOMETRY: return shaderc_glsl_geometry_shader;
      default:
      CANDY_CORE_ASSERT(false, "Unknown shader stage!");
        CANDY_CORE_INFO("BA");
        return (shaderc_shader_kind)0;
    }
  }
    
    
    Shader::Shader(std::filesystem::path  shaderFilePath) : filepath(std::move(shaderFilePath))
    {
        CANDY_PROFILE_FUNCTION();
        
        
        std::string source = ReadFile(filepath);
        std::unordered_map<ShaderStage, std::string> shaderSources = PreProcess(source);
        CompileOrGetBinaries(shaderSources);
        
        // Extract name from filepath
        shaderName = Utils::FileUtils::ExtractNameFromFilePath(filepath);
        
        
    }
    
    std::vector<VkPipelineShaderStageCreateInfo> Shader::CreateShaderStageCreateInfos()
    {
        std::vector<VkPipelineShaderStageCreateInfo> shaderStageCreateInfos;
        for (auto&& [stage, binaryCode] : spirvBinaries)
        {
            VkShaderModule shaderModule = CreateShaderModule(stage);
            VkPipelineShaderStageCreateInfo shaderStageCreateInfo{};
            shaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
            shaderStageCreateInfo.stage = StageToVulkan(stage);
            shaderStageCreateInfo.module = shaderModule;
            shaderStageCreateInfo.pName = "main";
            
            shaderModules.push_back(shaderModule);
            shaderStageCreateInfos.push_back(shaderStageCreateInfo);
        }
        return shaderStageCreateInfos;
    }
    
    
    
    VkShaderModule Shader::CreateShaderModule(ShaderStage stage)
    {
        const auto& valuePair = spirvBinaries.find(stage);
        CANDY_CORE_ASSERT(valuePair != spirvBinaries.end(), "Shader binary not found! Cannot attempt to create shader module!");
        const auto& binary = valuePair->second;
        VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = binary.size()*sizeof(uint32_t);
        createInfo.pCode = binary.data();
        VkShaderModule shaderModule;
        CANDY_CORE_ASSERT(vkCreateShaderModule(Vulkan::LogicalDevice(), &createInfo, nullptr, &shaderModule) == VK_SUCCESS, "Failed to create shader module!");
        
        return shaderModule;
    }
  
  std::string Shader::ReadFile(const std::filesystem::path& path)
  {
    CANDY_PROFILE_FUNCTION();
    
    std::string result;
    std::ifstream in(path, std::ios::in | std::ios::binary); // ifstream closes itself due to RAII
    if (in)
    {
      in.seekg(0, std::ios::end);
      auto size = in.tellg();
      if (size != -1)
      {
        result.resize(size);
        in.seekg(0, std::ios::beg);
        in.read(&result[0], size);
      }
      else
      {
        CANDY_CORE_ERROR("Could not read from file '{0}'", path);
      }
    }
    else
    {
      CANDY_CORE_ERROR("Could not open file '{0}'", path);
    }
    
    return result;
  }
  std::unordered_map<ShaderStage, std::string> Shader::PreProcess(const std::string& source)
  {
    CANDY_PROFILE_FUNCTION();
    
    std::unordered_map<ShaderStage, std::string> shaderSources;
    
    const char* typeToken = "#type";
    size_t typeTokenLength = strlen(typeToken);
    size_t pos = source.find(typeToken, 0); //Start of shader type declaration line
    while (pos != std::string::npos)
    {
      size_t eol = source.find_first_of("\r\n", pos); //End of shader type declaration line
      CANDY_CORE_ASSERT(eol != std::string::npos, "Syntax error");
      size_t begin = pos + typeTokenLength + 1; //Start of shader type name (after "#type " keyword)
      std::string type = source.substr(begin, eol - begin);
      CANDY_CORE_ASSERT(StageFromString(type), "Invalid shader type specified");
      
      size_t nextLinePos = source.find_first_not_of("\r\n", eol); //Start of shader code after shader type declaration line
      CANDY_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");
      pos = source.find(typeToken, nextLinePos); //Start of next shader type declaration line
      
      shaderSources[StageFromString(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
    }
    
    return shaderSources;
  }
  
  
    
    
    
    
    
    
    
    void Shader::CompileOrGetBinaries(const std::unordered_map<ShaderStage, std::string> &sources)
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
            std::filesystem::path cachedPath = cacheDirectory / (shaderFilePath.filename().string() + StageCachedFileExtension(stage));
            
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
      
        
        
    }
    
    void Shader::Reflect(ShaderStage stage, std::vector<uint32_t> spirvBinary, std::vector<VkDescriptorSetLayoutBinding>& layoutBindings)
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
        layoutBinding.stageFlags = StageToVulkan(stage);
        layoutBinding.pImmutableSamplers = nullptr;
        layoutBindings.push_back(layoutBinding);
        
      }
      VkPushConstantRange pushRange{};
      pushRange.stageFlags = StageToVulkan(stage);
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
      
      
    }
    
    
    
    
    void Shader::DestroyShaderModules()
    {
        for (auto& shaderModule : shaderModules)
            vkDestroyShaderModule(Vulkan::LogicalDevice(), shaderModule, nullptr);
        shaderModules.clear();
    }
  
  uint32_t Shader::PushConstantRangeCount(){return pushConstantRanges.size();}
  const VkPushConstantRange* Shader::PushConstantRangeData(){return pushConstantRanges.data();}
  
  ShaderStage Shader::StageFromString(const std::string& type)
  {
    if (type == "vertex" || type == "vert")
      return VERTEX;
    if (type == "fragment" || type == "pixel" || type == "frag")
      return FRAGMENT;
    if (type == "geometry" || type == "geom")
      return GEOMETRY;
    if (type == "compute" || type == "comp")
      return COMPUTE;
    
    CANDY_CORE_ASSERT(false, "Unknown shader type!");
    return ShaderStage::NONE;
  }
  const char* Shader::StageCachedFileExtension(ShaderStage stage)
  {
    switch (stage)
    {
      case VERTEX:    return ".cached_vulkan.vert";
      case FRAGMENT:  return ".cached_vulkan.frag";
      case GEOMETRY:  return ".cached_vulkan.geometry";
      case COMPUTE:   return ".cached_vulkan.compute";
      default:
      CANDY_CORE_ASSERT(false, "Unknown shader stage!");
        return nullptr;
    }
  }
  const char* Shader::StageToString(ShaderStage stage)
  {
    switch (stage)
    {
      case VERTEX:   return "VERTEX";
      case FRAGMENT: return "FRAGMENT";
      case GEOMETRY: return "GEOMETRY";
      case COMPUTE: return "COMPUTE";
      default:
      CANDY_CORE_ASSERT(false, "Unknown shader stage!");
        return nullptr;
    }
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
  VkShaderStageFlagBits Shader::StageToVulkan(ShaderStage stage)
  {
    switch (stage)
    {
      case VERTEX: return VK_SHADER_STAGE_VERTEX_BIT;
      case FRAGMENT: return VK_SHADER_STAGE_FRAGMENT_BIT;
      case COMPUTE: return VK_SHADER_STAGE_COMPUTE_BIT;
      case GEOMETRY: return VK_SHADER_STAGE_GEOMETRY_BIT;
      case TESSELATION_CONTROL: return VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
      case TESSELATION_EVALUATION: return VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
      default:
      CANDY_CORE_ASSERT(false, "Unknown shader stage!");
        return (VkShaderStageFlagBits)0;
    }
  }
  
  ShaderStage Shader::VulkanToStage(VkShaderStageFlagBits stage)
  {
    switch(stage)
    {
      case VK_SHADER_STAGE_VERTEX_BIT: return VERTEX;
      case VK_SHADER_STAGE_FRAGMENT_BIT: return FRAGMENT;
      case VK_SHADER_STAGE_COMPUTE_BIT: return COMPUTE;
      case VK_SHADER_STAGE_GEOMETRY_BIT: return GEOMETRY;
      case VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT: return TESSELATION_CONTROL;
      case VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT: return TESSELATION_EVALUATION;
      default:
        CANDY_CORE_ASSERT(false, "Unknown shader stage!");
        return NONE;
    }
  }
    
    SharedPtr<Shader> Shader::Create(const std::filesystem::path& shaderFilePath)
    {
        return CreateSharedPtr<Shader>(shaderFilePath);
    }
    
    
    
}