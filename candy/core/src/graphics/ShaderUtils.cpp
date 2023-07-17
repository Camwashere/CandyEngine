#include <candy/graphics/ShaderUtils.hpp>
#include <CandyPch.hpp>


#define CANDY_USING_SHADERC


#ifdef CANDY_USING_SHADERC
#include <shaderc/shaderc.hpp>
#endif

#include <spirv_cross/spirv_cross.hpp>
#include <spirv_glsl.hpp>
namespace Candy::Graphics
{
    #ifdef CANDY_USING_SHADERC
    static shaderc_shader_kind ShaderStageToShaderC(ShaderStage stage)
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
    #endif
    
    
    ShaderStage ShaderUtils::ShaderStageFromString(const std::string& type)
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
    
    VkShaderStageFlagBits ShaderUtils::ShaderStageToVulkan(ShaderStage stage)
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
    
    const char* ShaderUtils::ShaderStageToString(ShaderStage stage)
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
    
    
    
    
    
    
    const char* ShaderUtils::ShaderStageCachedVulkanFileExtension(ShaderStage stage)
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
    
    
    std::vector<char> ShaderUtils::ReadSpvFileBinary(const std::string& filename)
    {
        std::ifstream file(filename, std::ios::ate | std::ios::binary);
        
        if (!file.is_open())
        {
            throw std::runtime_error("failed to open file!");
        }
        
        size_t fileSize = (size_t)file.tellg();
        std::vector<char> buffer(fileSize);
        
        file.seekg(0);
        file.read(buffer.data(), fileSize);
        file.close();
        
        return buffer;
    }
    
    std::string ShaderUtils::ExtractNameFromFilePath(const std::filesystem::path& path)
    {
        // Extract name from filepath
        auto lastSlash = path.string().find_last_of("/\\");
        lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
        auto lastDot = path.string().rfind('.');
        auto count = lastDot == std::string::npos ? path.string().size() - lastSlash : lastDot - lastSlash;
        return path.string().substr(lastSlash, count);
        
    }
    
    
    std::string ShaderUtils::ReadFile(const std::filesystem::path &path)
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
    
    std::unordered_map<ShaderStage, std::string> ShaderUtils::PreProcess(const std::string &source)
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
            CANDY_CORE_ASSERT(ShaderStageFromString(type), "Invalid shader type specified");
            
            size_t nextLinePos = source.find_first_not_of("\r\n", eol); //Start of shader code after shader type declaration line
            CANDY_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");
            pos = source.find(typeToken, nextLinePos); //Start of next shader type declaration line
            
            shaderSources[ShaderStageFromString(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
        }
        
        return shaderSources;
    }
    
    bool ShaderUtils::HasBinaries(const std::unordered_map<ShaderStage, std::string> &sources, const std::filesystem::path& cacheDirectory, const std::filesystem::path& shaderFilePath)
    {
        for (const auto& [stage, source] : sources)
        {
            
            std::filesystem::path cachedPath = cacheDirectory / (shaderFilePath.filename().string() + ShaderUtils::ShaderStageCachedVulkanFileExtension(stage));
            
            std::ifstream in(cachedPath, std::ios::in | std::ios::binary);
            if (!in.is_open())
            {
                return false;
            }
            
        }
        return true;
    }
    void ShaderUtils::GetBinaries(std::unordered_map<ShaderStage, std::vector<uint32_t>>& binaries, const std::unordered_map<ShaderStage, std::string> &sources, const std::filesystem::path& filepath, const std::filesystem::path& cacheDirectory)
    {
        
        
        
        for (auto&& [stage, source] : sources)
        {
            std::filesystem::path cachedPath = cacheDirectory / (filepath.filename().string() + ShaderUtils::ShaderStageCachedVulkanFileExtension(stage));
            
            std::ifstream in(cachedPath, std::ios::in | std::ios::binary);
            CANDY_CORE_ASSERT(in.is_open(), "Unable to get shader binaries!");
            in.seekg(0, std::ios::end);
            auto size = in.tellg();
            in.seekg(0, std::ios::beg);
            
            auto& data = binaries[stage];
            data.resize(size / sizeof(uint32_t));
            in.read((char*)data.data(), size);
            
        }
    }
    
    
    
    void ShaderUtils::CompileOrGetBinaries(std::unordered_map<ShaderStage, std::vector<uint32_t>>& shaderData, const std::unordered_map<ShaderStage, std::string> &sources, const std::filesystem::path& filepath, const std::filesystem::path& cacheDirectory)
    {
        
        #ifdef CANDY_USING_SHADERC
        shaderc::Compiler compiler;
        shaderc::CompileOptions options;
        options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_3);
        const bool optimize = true;
        if (optimize)
            options.SetOptimizationLevel(shaderc_optimization_level_performance);
        
        
        shaderData.clear();
        for (auto&& [stage, source] : sources)
        {
           
            std::filesystem::path cachedPath = cacheDirectory / (filepath.filename().string() + ShaderUtils::ShaderStageCachedVulkanFileExtension(stage));
            
            std::ifstream in(cachedPath, std::ios::in | std::ios::binary);
            if (in.is_open())
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
                shaderc::SpvCompilationResult mod = compiler.CompileGlslToSpv(source, ShaderStageToShaderC(stage), filepath.string().c_str(), options);
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
        
        /*for (auto&& [stage, data] : shaderData)
        {
          Reflect(stage, data, filepath);
        }*/
        #else
        GetBinaries(shaderData, sources, filepath, cacheDirectory);
        #endif
        
    }
  
  void ShaderUtils::Reflect(ShaderStage stage, const std::vector<uint32_t>& shaderData, const std::filesystem::path& filepath)
  {
    spirv_cross::CompilerGLSL compiler(shaderData);
    CANDY_CORE_INFO("CREATED REFLECT COMPILER");
    //spirv_cross::Compiler compiler(shaderData);
    spirv_cross::ShaderResources resources = compiler.get_shader_resources();
    CANDY_CORE_INFO("GOT SHADER RESOURCES");
    
    CANDY_CORE_TRACE("OpenGLShader::Reflect - {0} {1}", ShaderUtils::ShaderStageToString(stage), filepath);
    CANDY_CORE_TRACE("    {0} uniform buffers", resources.uniform_buffers.size());
    CANDY_CORE_TRACE("    {0} resources", resources.sampled_images.size());
    
    CANDY_CORE_TRACE("Uniform buffers:");
    if (resources.uniform_buffers.empty())
    {
      CANDY_CORE_INFO("Uniform buffers empty");
      return;
    }
    for (const auto& resource : resources.uniform_buffers)
    {
      const auto& bufferType = compiler.get_type(resource.base_type_id);
      uint32_t bufferSize = compiler.get_declared_struct_size(bufferType);
      uint32_t binding = compiler.get_decoration(resource.id, spv::DecorationBinding);
      int memberCount = bufferType.member_types.size();
      
      CANDY_CORE_TRACE("  {0}", resource.name);
      CANDY_CORE_TRACE("    Size = {0}", bufferSize);
      CANDY_CORE_TRACE("    Binding = {0}", binding);
      CANDY_CORE_TRACE("    Members = {0}", memberCount);
    }
  }
}