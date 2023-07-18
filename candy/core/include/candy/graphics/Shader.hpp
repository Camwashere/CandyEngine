#pragma once
#include <string>
#include <unordered_map>
#include "CandyPch.hpp"
#include "Color.hpp"
#include "ShaderUtils.hpp"
#include "vulkan/vulkan.h"
namespace Candy::Graphics
{
    
    class Shader
    {
    
    private:
        std::string shaderName;
        std::filesystem::path filepath;
        
        std::unordered_map<ShaderStage, std::vector<uint32_t>> vulkanSPIRV;
        std::vector<VkShaderModule> shaderModules;
    
    private:
        //std::string ReadFile(const std::filesystem::path& path);
        //std::unordered_map<ShaderStage, std::string> PreProcess(const std::string& source);
        //void CompileOrGetBinaries(const std::unordered_map<ShaderStage, std::string>& sources);
        void CreateProgram();
        VkShaderModule CreateShaderModule(ShaderStage stage);
        std::vector<VkPipelineShaderStageCreateInfo> CreateShaderStageCreateInfos();
        //std::string ExtractNameFromFilePath(const std::filesystem::path& path);
    
    public:
        explicit Shader(std::filesystem::path  shaderFilePath);
    
    public:
        const std::string& GetName()const{return shaderName;}
        const std::filesystem::path& GetFilepath()const{return filepath;}
        void DestroyShaderModules();
        
    public:
        static SharedPtr<Shader> Create(std::filesystem::path shaderFilePath);
        
    private:
        friend class GraphicsContext;
        friend class GraphicsPipeline;
        friend class Pipeline;
        
       
    
    
   
        
        
        
    };
}