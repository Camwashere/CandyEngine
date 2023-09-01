#pragma once
#include "vulkan/vulkan.h"
#include <vector>

namespace Candy::Graphics
{
  
  enum class PipelineType
  {
    Graphics=0,
    Compute,
    RayTracing,
    None,
  };
  
  class Pipeline
  {
  private:
    uint32_t id;
    PipelineType type;
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
    
   
    
  
  public:
    explicit Pipeline(PipelineType type=PipelineType::Graphics);
    
  public:
    operator VkPipeline()const{return pipeline;}
    operator VkPipeline(){return pipeline;}
  
  public:
    void SetTopology(VkPrimitiveTopology topology, VkBool32 primitiveRestartEnable=VK_FALSE);
    void SetPolygonMode(VkPolygonMode polygonMode);
    void SetLineWidth(float width);
    void SetMultiSampling(VkSampleCountFlagBits sampleCount, VkBool32 enableSampleShading=VK_FALSE, VkBool32 enabledAlphaToCoverage=VK_FALSE, VkBool32 enabledAlphaToOne=VK_FALSE, VkPipelineMultisampleStateCreateFlags flags=0);
    void AddDynamicState(VkDynamicState state);
    void SetDepthTesting(bool enabled);
    void SetAlphaColorBlending(bool enabled);
    void AddDynamicStates(std::initializer_list<VkDynamicState> states);
    void ClearDynamicStates();
  
  public:
    void RestoreDefaultSettings();
    void Bake(VkRenderPass renderPass, const std::vector<VkVertexInputBindingDescription>& bindingDescriptions, const std::vector<VkVertexInputAttributeDescription>& attributeDescriptions,
              const std::vector<VkPipelineShaderStageCreateInfo>& shaderStages, VkPipelineLayout pipelineLayout);
    
    [[nodiscard]] uint32_t GetID()const;
    [[nodiscard]] PipelineType GetType()const;
    [[nodiscard]] VkPipelineLayout GetLayout()const;
    
  public:
    static VkPipelineBindPoint TypeToVulkan(PipelineType type);
    
 
  };
}