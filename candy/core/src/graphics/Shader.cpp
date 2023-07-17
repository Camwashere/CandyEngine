#include <candy/graphics/Shader.hpp>
#include <candy/graphics/ShaderLibrary.hpp>
#include <filesystem>
#include <utility>
#include <candy/graphics/Vulkan.hpp>


namespace Candy::Graphics
{
    
    
    //static ShaderLibrary* shaderLibrary = new ShaderLibrary("assets/cache/shader", "assets/shaders/temp");
    namespace Utils {
        
        
        static std::filesystem::path GetCacheDirectory()
        {
          return "assets/cache/shader";
            //CANDY_CORE_ASSERT(shaderLibrary->IsValid(), "Shader library is not valid!");
            //return shaderLibrary->GetCacheDirectory();
        }
        
        
        
        
    }
    
    
    Shader::Shader(std::filesystem::path  shaderFilePath) : filepath(std::move(shaderFilePath))
    {
        CANDY_PROFILE_FUNCTION();
        
        
        std::string source = ShaderUtils::ReadFile(filepath);
        std::unordered_map<ShaderStage, std::string> shaderSources = ShaderUtils::PreProcess(source);
        //ShaderUtils::GetBinaries(vulkanSPIRV, shaderSources, filepath, shaderLibrary.GetCacheDirectory());
        ShaderUtils::CompileOrGetBinaries(vulkanSPIRV, shaderSources, filepath, Utils::GetCacheDirectory());
        //CompileOrGetBinaries(shaderSources);
        CreateProgram();
        
        // Extract name from filepath
        shaderName = ShaderUtils::ExtractNameFromFilePath(filepath);
        
        
    }
    
    std::vector<VkPipelineShaderStageCreateInfo> Shader::CreateShaderStageCreateInfos()
    {
        std::vector<VkPipelineShaderStageCreateInfo> shaderStageCreateInfos;
        for (auto&& [stage, binaryCode] : vulkanSPIRV)
        {
            VkShaderModule shaderModule = CreateShaderModule(stage);
            VkPipelineShaderStageCreateInfo shaderStageCreateInfo{};
            shaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
            shaderStageCreateInfo.stage = ShaderUtils::ShaderStageToVulkan(stage);
            shaderStageCreateInfo.module = shaderModule;
            shaderStageCreateInfo.pName = "main";
            
            shaderModules.push_back(shaderModule);
            shaderStageCreateInfos.push_back(shaderStageCreateInfo);
        }
        return shaderStageCreateInfos;
    }
    
    
    
    VkShaderModule Shader::CreateShaderModule(ShaderStage stage)
    {
        const auto& valuePair = vulkanSPIRV.find(stage);
        CANDY_CORE_ASSERT(valuePair != vulkanSPIRV.end(), "Shader binary not found! Cannot attempt to create shader module!");
        const auto& binary = valuePair->second;
        VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = binary.size()*sizeof(uint32_t);
        createInfo.pCode = binary.data();
        VkShaderModule shaderModule;
        CANDY_CORE_ASSERT(vkCreateShaderModule(Vulkan::LogicalDevice(), &createInfo, nullptr, &shaderModule) == VK_SUCCESS, "Failed to create shader module!");
        
        return shaderModule;
    }
    
    
    
    void Shader::CreateProgram()
    {
        /*GLuint program = glCreateProgram();
        
        std::vector<GLuint> shaderIDs;
        for (auto&& [stage, spirv] : m_OpenGLSPIRV)
        {
            GLuint shaderID = shaderIDs.emplace_back(glCreateShader(stage));
            glShaderBinary(1, &shaderID, GL_SHADER_BINARY_FORMAT_SPIR_V, spirv.data(), spirv.size() * sizeof(uint32_t));
            glSpecializeShader(shaderID, "main", 0, nullptr, nullptr);
            glAttachShader(program, shaderID);
        }
        
        glLinkProgram(program);
        
        GLint isLinked;
        glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
            
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, infoLog.data());
            HZ_CORE_ERROR("Shader linking failed ({0}):\n{1}", m_FilePath, infoLog.data());
            
            glDeleteProgram(program);
            
            for (auto id : shaderIDs)
                glDeleteShader(id);
        }
        
        for (auto id : shaderIDs)
        {
            glDetachShader(program, id);
            glDeleteShader(id);
        }
        
        m_RendererID = program;*/
    }
    
    
    
    
    
    /*void Shader::CompileOrGetBinaries(const std::unordered_map<ShaderStage, std::string> &sources)
    {
        shaderc::Compiler compiler;
        shaderc::CompileOptions options;
        options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_3);
        const bool optimize = true;
        if (optimize)
            options.SetOptimizationLevel(shaderc_optimization_level_performance);
        
        std::filesystem::path cacheDirectory = Utils::GetCacheDirectory();
        
        auto& shaderData = vulkanSPIRV;
        shaderData.clear();
        
        for (auto&& [stage, source] : sources)
        {
            std::filesystem::path shaderFilePath = filepath;
            std::filesystem::path cachedPath = cacheDirectory / (shaderFilePath.filename().string() + ShaderUtils::ShaderStageCachedVulkanFileExtension(stage));
            
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
                shaderc::SpvCompilationResult mod = compiler.CompileGlslToSpv(source, Utils::ShaderStageToShaderC(stage), filepath.string().c_str(), options);
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
        CANDY_CORE_INFO("PRE REFLECTION");
        
        for (auto&& [stage, data]: shaderData)
            Reflect(stage, data);
        
        
    
    }*/
    
    
    
    
    void Shader::DestroyShaderModules()
    {
        for (auto& shaderModule : shaderModules)
            vkDestroyShaderModule(Vulkan::LogicalDevice(), shaderModule, nullptr);
        shaderModules.clear();
    }
    
    SharedPtr<Shader> Shader::Create(std::filesystem::path shaderFilePath)
    {
        return CreateSharedPtr<Shader>(shaderFilePath);
    }
    
    
    
}