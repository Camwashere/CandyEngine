#pragma once
#include <string>
#include <unordered_map>
#include "CandyPch.hpp"
#include "candy/graphics/Color.hpp"
#include "vulkan/vulkan.h"
namespace Candy::Graphics
{
  enum ShaderStage
  {
    NONE = 0,
    VERTEX = 1,
    FRAGMENT = 2,
    COMPUTE = 3,
    GEOMETRY = 4,
    TESSELATION_CONTROL=5,
    TESSELATION_EVALUATION=6,
  };
    class Shader
    {
    
    private:
        std::string shaderName;
        std::filesystem::path filepath;
        
        
        bool optimize=false;
        bool recompileOnLoad=true;
        VkDescriptorSetLayout descriptorSetLayout;
        std::unordered_map<ShaderStage, std::vector<uint32_t>> spirvBinaries;
        std::vector<VkShaderModule> shaderModules;
        std::vector<VkPushConstantRange> pushConstantRanges;
    
    private:
        std::string ReadFile(const std::filesystem::path& path);
        std::unordered_map<ShaderStage, std::string> PreProcess(const std::string& source);
        void CompileOrGetBinaries(const std::unordered_map<ShaderStage, std::string>& sources);
        void Reflect(ShaderStage stage, std::vector<uint32_t> spirvBinary, std::vector<VkDescriptorSetLayoutBinding>& layoutBindings);
        
        VkShaderModule CreateShaderModule(ShaderStage stage);
        std::vector<VkPipelineShaderStageCreateInfo> CreateShaderStageCreateInfos();
        
    
    public:
        explicit Shader(std::filesystem::path  shaderFilePath);
    
    public:
        const std::string& GetName()const{return shaderName;}
        const std::filesystem::path& GetFilepath()const{return filepath;}
        void DestroyShaderModules();
        uint32_t PushConstantRangeCount();
        const VkPushConstantRange* PushConstantRangeData();
        VkDescriptorSetLayout GetDescriptorSetLayout(){return descriptorSetLayout;}
        
    public:
      static ShaderStage StageFromString(const std::string& stage);
      static const char* StageCachedFileExtension(ShaderStage stage);
      static const char* StageToString(ShaderStage stage);
      static std::vector<char> ReadSpvFileBinary(const std::string& filename);
      static ShaderStage VulkanToStage(VkShaderStageFlagBits stage);
      static VkShaderStageFlagBits StageToVulkan(ShaderStage stage);
      static SharedPtr<Shader> Create(const std::filesystem::path& shaderFilePath);
        
    private:
        friend class GraphicsContext;
        friend class GraphicsPipeline;
        friend class Pipeline;
        
       
    
    
   
        
        
        
    };
}