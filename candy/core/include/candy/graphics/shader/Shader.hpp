#pragma once
#include <string>
#include <unordered_map>
#include "CandyPch.hpp"
#include "candy/graphics/Color.hpp"
#include "ShaderData.hpp"
#include "vulkan/vulkan.h"
#include "processing/ShaderPreProcessor.hpp"
#include "processing/ShaderPostProcessor.hpp"
namespace Candy::Graphics
{
  
    class Shader
    {
    private:
        std::string shaderName;
        std::filesystem::path filepath;
        
        UniquePtr<ShaderPreProcessor> preProcessor;
        ShaderPostProcessor postProcessor;
        //bool optimize=false;
        //bool recompileOnLoad=true;
        //VkDescriptorSetLayout descriptorSetLayout;
        //std::unordered_map<ShaderData::Stage, std::vector<uint32_t>> spirvBinaries;
        std::vector<VkShaderModule> shaderModules;
        //std::vector<VkPushConstantRange> pushConstantRanges;
    
    private:
        //void CompileOrGetBinaries(const std::unordered_map<ShaderData::Stage, std::string>& sources);
        //void Reflect(ShaderData::Stage stage, std::vector<uint32_t> spirvBinary, std::vector<VkDescriptorSetLayoutBinding>& layoutBindings);
        
        VkShaderModule CreateShaderModule(ShaderData::Stage stage);
        std::vector<VkPipelineShaderStageCreateInfo> CreateShaderStageCreateInfos();
        
    
    public:
        explicit Shader(std::filesystem::path  shaderFilePath);
    
    public:
        const std::string& GetName()const{return shaderName;}
        const std::filesystem::path& GetFilepath()const{return filepath;}
        void DestroyShaderModules();
        uint32_t PushConstantRangeCount();
        const VkPushConstantRange* PushConstantRangeData();
        VkDescriptorSetLayout GetDescriptorSetLayout(){return postProcessor.descriptorLayout.GetLayout();}
        
    public:
      static std::vector<char> ReadSpvFileBinary(const std::string& filename);
      static SharedPtr<Shader> Create(const std::filesystem::path& shaderFilePath);
        
    private:
        friend class GraphicsContext;
        friend class GraphicsPipeline;
        friend class Pipeline;
        
       
    
    
   
        
        
        
    };
}