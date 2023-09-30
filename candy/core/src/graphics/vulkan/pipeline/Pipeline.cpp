#include <candy/graphics/vulkan/pipeline/Pipeline.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <utility>
namespace Candy::Graphics
{
  Pipeline::Pipeline(ShaderSettings  shaderSettings) : settings(std::move(shaderSettings)), activeConfig(0)
  {
  
  }
  
  
  
  VkPipelineInputAssemblyStateCreateInfo Pipeline::GetInputAssembly()
  {
    VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
    inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssembly.topology = ShaderSettings::TopologyToVulkan(settings.topologyType);
    inputAssembly.primitiveRestartEnable = VK_FALSE;
    return inputAssembly;
    
  }
  VkPipelineViewportStateCreateInfo  Pipeline::GetViewportState()
  {
    VkPipelineViewportStateCreateInfo viewportState = {};
    viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportState.viewportCount = 1;
    viewportState.scissorCount = 1;
    return viewportState;
  }
  VkPipelineRasterizationStateCreateInfo Pipeline::GetRasterizer(const PipelineConfigSettings& config)
  {
    VkPipelineRasterizationStateCreateInfo rasterizer = {};
    rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.depthClampEnable = VK_FALSE;
    rasterizer.rasterizerDiscardEnable = VK_FALSE;
    
    rasterizer.polygonMode = ShaderSettings::RenderModeToVulkan(config.renderMode);
    rasterizer.lineWidth = settings.lineWidth;
    
    rasterizer.cullMode = ShaderSettings::CullModeToVulkan(settings.cullMode);
    rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
    rasterizer.depthBiasEnable = VK_FALSE;
    
    return rasterizer;
  }
  VkPipelineMultisampleStateCreateInfo  Pipeline::GetMultisampling()
  {
    VkPipelineMultisampleStateCreateInfo multisampling = {};
    multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling.sampleShadingEnable = VK_FALSE;
    multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    return multisampling;
  }
  
  VkPipelineColorBlendAttachmentState Pipeline::GetColorBlendAttachment()
  {
    VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
    if (settings.alphaColorBlending)
    {
      colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
      colorBlendAttachment.blendEnable = VK_TRUE;
      colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
      colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
      colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
      colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
      colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
      colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;
    }
    else
    {
      colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
      colorBlendAttachment.blendEnable = VK_FALSE;
    }
    
    return colorBlendAttachment;
  }
  VkPipelineColorBlendStateCreateInfo Pipeline::GetColorBlending(VkPipelineColorBlendAttachmentState& colorBlendAttachment)
  {
    
    VkPipelineColorBlendStateCreateInfo colorBlending = {};
    colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlending.logicOpEnable = VK_FALSE;
    colorBlending.logicOp = VK_LOGIC_OP_COPY;
    colorBlending.attachmentCount = 1;
    colorBlending.pAttachments = &colorBlendAttachment;
    colorBlending.blendConstants[0] = 0.0f;
    colorBlending.blendConstants[1] = 0.0f;
    colorBlending.blendConstants[2] = 0.0f;
    colorBlending.blendConstants[3] = 0.0f;
    return colorBlending;
  }
  VkPipelineDepthStencilStateCreateInfo Pipeline::GetDepthStencil()
  {
    VkPipelineDepthStencilStateCreateInfo depthStencil = {};
    if (settings.depthTesting)
    {
      // Depth and stencil state
      depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
      depthStencil.depthTestEnable = VK_TRUE;
      depthStencil.depthWriteEnable = VK_TRUE;
      depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
      depthStencil.depthBoundsTestEnable = VK_FALSE;
      depthStencil.minDepthBounds = 0.0f; // Optional
      depthStencil.maxDepthBounds = 1.0f; // Optional
      depthStencil.stencilTestEnable = VK_FALSE;
      depthStencil.front = {}; // Optional
      depthStencil.back = {}; // Optional
    }
    else
    {
      // Depth and stencil state
      depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
      depthStencil.depthTestEnable = VK_TRUE;
      depthStencil.depthWriteEnable = VK_FALSE;
      depthStencil.depthCompareOp = VK_COMPARE_OP_ALWAYS;
      depthStencil.depthBoundsTestEnable = VK_FALSE;
      depthStencil.minDepthBounds = 0.0f; // Optional
      depthStencil.maxDepthBounds = 1.0f; // Optional
      depthStencil.stencilTestEnable = VK_FALSE;
      depthStencil.front = {}; // Optional
      depthStencil.back = {}; // Optional
    }
    return depthStencil;
  }
  
  std::vector<VkDynamicState> Pipeline::GetDynamicStates()
  {
    std::vector<VkDynamicState> dynamicStates;
    dynamicStates.push_back(VK_DYNAMIC_STATE_VIEWPORT);
    dynamicStates.push_back(VK_DYNAMIC_STATE_SCISSOR);
    for (auto state : settings.dynamicStates)
    {
      dynamicStates.push_back(state);
    }
    return dynamicStates;
  }
  
  void Pipeline::Bake(VkRenderPass renderPass, const std::vector<VkVertexInputBindingDescription>& bindingDescriptions, const std::vector<VkVertexInputAttributeDescription>& attributeDescriptions,
                      const std::vector<VkPipelineShaderStageCreateInfo>& shaderStages, VkPipelineLayout pipelineLayout)
  {
    CANDY_PROFILE_FUNCTION();
    
    layout = pipelineLayout;
    configs.resize(settings.configs.size());
    
    VkPipelineInputAssemblyStateCreateInfo inputAssembly = GetInputAssembly();
    VkPipelineViewportStateCreateInfo viewportState = GetViewportState();
    
    VkPipelineMultisampleStateCreateInfo multisampling = GetMultisampling();
    VkPipelineDepthStencilStateCreateInfo depthStencil = GetDepthStencil();
    VkPipelineColorBlendAttachmentState colorBlendAttachment = GetColorBlendAttachment();
    VkPipelineColorBlendStateCreateInfo colorBlending = GetColorBlending(colorBlendAttachment);
    
    std::vector<VkDynamicState> dynamicStates = GetDynamicStates();
    
    VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
    vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    
    
    vertexInputInfo.vertexBindingDescriptionCount = bindingDescriptions.size();
    vertexInputInfo.vertexAttributeDescriptionCount = attributeDescriptions.size();
    vertexInputInfo.pVertexBindingDescriptions = bindingDescriptions.data();
    vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();
    
    
    
    
    VkPipelineDynamicStateCreateInfo dynamicState{};
    dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamicState.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
    dynamicState.pDynamicStates = dynamicStates.data();
    
    std::vector<VkPipelineRasterizationStateCreateInfo> rasterizers;
    rasterizers.resize(settings.configs.size());
    for (int i=0; i<rasterizers.size(); i++)
    {
      rasterizers[i] = GetRasterizer(settings.configs[i]);
    }
    std::vector<VkGraphicsPipelineCreateInfo> pipelineInfos;
    pipelineInfos.resize(settings.configs.size());
    
    for (int i=0; i<pipelineInfos.size(); i++)
    {
      pipelineInfos[i].sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
      
      
      pipelineInfos[i].stageCount = shaderStages.size();
      pipelineInfos[i].pStages = shaderStages.data();
      
      
      pipelineInfos[i].pVertexInputState = &vertexInputInfo;
      
      
      pipelineInfos[i].pInputAssemblyState = &inputAssembly;
      pipelineInfos[i].pViewportState = &viewportState;
      pipelineInfos[i].pRasterizationState = &rasterizers[i];
      pipelineInfos[i].pMultisampleState = &multisampling;
      pipelineInfos[i].pDepthStencilState = &depthStencil;
      pipelineInfos[i].pColorBlendState = &colorBlending;
      pipelineInfos[i].pDynamicState = &dynamicState;
      
      
      pipelineInfos[i].layout = layout;
      
      pipelineInfos[i].renderPass = renderPass;
      pipelineInfos[i].subpass = 0;
      
      pipelineInfos[i].basePipelineHandle = VK_NULL_HANDLE; // Optional
      pipelineInfos[i].basePipelineIndex = -1; // Optional
    }
    
    
    
    CANDY_VULKAN_CHECK(vkCreateGraphicsPipelines(Vulkan::LogicalDevice(), VK_NULL_HANDLE, pipelineInfos.size(), pipelineInfos.data(), nullptr, configs.data()));
    
    for (auto pipeline : configs)
    {
      Vulkan::DeletionQueue().Push(pipeline);
    }
   
    
    for (auto createInfo : shaderStages)
    {
      vkDestroyShaderModule(Vulkan::LogicalDevice(), createInfo.module, nullptr);
    }
    
  }
  
  Pipeline::operator VkPipeline()const
  {
    return configs[activeConfig];
  }
  Pipeline::operator VkPipeline()
  {
    return configs[activeConfig];
  }
  void Pipeline::SetActiveConfig(uint32_t config)
  {
    if (config < configs.size())
    {
      activeConfig = config;
    }
    else
    {
      activeConfig = 0;
    }
    
    
  }
  
  PipelineType Pipeline::GetType()const{return settings.pipelineType;}
  VkPipelineLayout Pipeline::GetLayout()const
  {
    return layout;
  }
}