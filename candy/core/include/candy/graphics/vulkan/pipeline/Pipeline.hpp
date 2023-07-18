#pragma once
#include "vulkan/vulkan.h"
#include <vector>
#include "../../ShaderUtils.hpp"
#include "PipelineLayout.hpp"
#include "../../VertexArray.hpp"
#include "../../Shader.hpp"
#include "../RenderPass.hpp"
namespace Candy::Graphics
{
  
  
  
  class Pipeline
  {
  private:
    uint32_t id;
    PipelineLayout layout;
    VkPipeline pipeline=VK_NULL_HANDLE;
    std::vector<VkDynamicState> dynamicStates;
    VkPipelineInputAssemblyStateCreateInfo inputAssembly;
    VkPipelineViewportStateCreateInfo viewportState;
    VkPipelineRasterizationStateCreateInfo rasterizer;
    VkPipelineMultisampleStateCreateInfo multisampling;
    VkPipelineColorBlendAttachmentState colorBlendAttachment;
    VkPipelineColorBlendStateCreateInfo colorBlending;
    
  private:
    void InitInputAssembly();
    void InitViewportState();
    void InitRasterizer();
    void InitMultisampling();
    void InitColorBlending();
    
  
  public:
    explicit Pipeline();
    
  public:
    operator VkPipeline()const{return pipeline;}
    operator VkPipeline(){return pipeline;}
  
  public:
    void SetTopology(VkPrimitiveTopology topology, VkBool32 primitiveRestartEnable=VK_FALSE);
    void SetPolygonMode(VkPolygonMode polygonMode);
    void SetLineWidth(float width);
    void SetMultiSampling(VkSampleCountFlagBits sampleCount, VkBool32 enableSampleShading=VK_FALSE, VkBool32 enabledAlphaToCoverage=VK_FALSE, VkBool32 enabledAlphaToOne=VK_FALSE, VkPipelineMultisampleStateCreateFlags flags=0);
    void AddDynamicState(VkDynamicState state);
    void AddDynamicStates(std::initializer_list<VkDynamicState> states);
    void ClearDynamicStates();
  
  public:
    void RestoreDefaultSettings();
    void Bake(const SharedPtr<VertexArray>& vertexArray, const SharedPtr<Shader>& shader, const RenderPass& renderPass);
    PipelineLayout& GetLayout();
    void Destroy();
    
    [[nodiscard]] uint32_t GetID()const;
    
  private:
    friend class PipelineManager;
  };
}