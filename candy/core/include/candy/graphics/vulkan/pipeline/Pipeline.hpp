#pragma once
#include "vulkan/vulkan.h"
#include <vector>
#include <candy/graphics/shader/ShaderSettings.hpp>
namespace Candy::Graphics
{
  
  
  
  class Pipeline
  {
  private:
    ShaderSettings settings;
    std::vector<VkPipeline> configs;
    uint32_t activeConfig;
    VkPipelineLayout layout = VK_NULL_HANDLE;
    
    
  private:
    VkPipelineInputAssemblyStateCreateInfo GetInputAssembly();
    VkPipelineViewportStateCreateInfo GetViewportState();
    VkPipelineRasterizationStateCreateInfo GetRasterizer(const PipelineConfigSettings& config);
    VkPipelineMultisampleStateCreateInfo GetMultisampling();
    VkPipelineColorBlendAttachmentState GetColorBlendAttachment();
    VkPipelineColorBlendStateCreateInfo GetColorBlending(VkPipelineColorBlendAttachmentState& attachment);
    VkPipelineDepthStencilStateCreateInfo GetDepthStencil();
    
    std::vector<VkDynamicState> GetDynamicStates();
    
  public:
    explicit Pipeline(ShaderSettings  settings);
    
    operator VkPipeline()const;
    operator VkPipeline();
    
  public:
    void Bake(VkRenderPass renderPass, const std::vector<VkVertexInputBindingDescription>& bindingDescriptions, const std::vector<VkVertexInputAttributeDescription>& attributeDescriptions,
              const std::vector<VkPipelineShaderStageCreateInfo>& shaderStages, VkPipelineLayout pipelineLayout);
    
    [[nodiscard]] PipelineType GetType()const;
    [[nodiscard]] VkPipelineLayout GetLayout()const;
    void SetActiveConfig(uint32_t config);
  };
  /*class Pipeline
  {
  private:
    uint32_t id;
    
    ShaderSettings settings;
    VkPipeline pipeline=VK_NULL_HANDLE;
    VkPipelineLayout layout = VK_NULL_HANDLE;
    std::vector<VkDynamicState> dynamicStates;
    VkPipelineInputAssemblyStateCreateInfo inputAssembly;
    VkPipelineViewportStateCreateInfo viewportState;
    VkPipelineRasterizationStateCreateInfo rasterizer;
    VkPipelineMultisampleStateCreateInfo multisampling;
    VkPipelineColorBlendAttachmentState colorBlendAttachment;
    VkPipelineColorBlendStateCreateInfo colorBlending;
    VkPipelineDepthStencilStateCreateInfo depthStencil;
    
  private:
    void InitInputAssembly();
    void InitViewportState();
    void InitRasterizer();
    void InitMultisampling();
    void InitColorBlending();
    void InitDepthTesting();
    void InitDynamicStates();
    
   
    
  
  public:
    explicit Pipeline(const ShaderSettings& settings);
    
  public:
    operator VkPipeline()const{return pipeline;}
    operator VkPipeline(){return pipeline;}
  
  public:
    void SetTopology(VkPrimitiveTopology topology, VkBool32 primitiveRestartEnable=VK_FALSE);
    void SetPolygonMode(VkPolygonMode polygonMode);
    void SetLineWidth(float width);
    void SetMultiSampling(VkSampleCountFlagBits sampleCount, VkBool32 enableSampleShading=VK_FALSE, VkBool32 enabledAlphaToCoverage=VK_FALSE, VkBool32 enabledAlphaToOne=VK_FALSE, VkPipelineMultisampleStateCreateFlags flags=0);
    void AddDynamicState(VkDynamicState state);
    void SetInputAssembly(ShaderSettings::TopologyType topologyType);
    void SetDepthTesting(bool enabled);
    void SetAlphaColorBlending(bool enabled);
    void AddDynamicStates(std::initializer_list<VkDynamicState> states);
    void ClearDynamicStates();
  
  public:
    void RestoreDefaultSettings();
    void Bake(VkRenderPass renderPass, const std::vector<VkVertexInputBindingDescription>& bindingDescriptions, const std::vector<VkVertexInputAttributeDescription>& attributeDescriptions,
              const std::vector<VkPipelineShaderStageCreateInfo>& shaderStages, VkPipelineLayout pipelineLayout);
    
    [[nodiscard]] uint32_t GetID()const;
    [[nodiscard]] ShaderSettings::PipelineType GetType()const;
    [[nodiscard]] VkPipelineLayout GetLayout()const;
    
 
    
 
  };*/
}