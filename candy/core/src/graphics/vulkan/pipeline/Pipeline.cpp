#include <candy/graphics/vulkan/pipeline/Pipeline.hpp>
#include <candy/graphics/Vulkan.hpp>
namespace Candy::Graphics
{
  Pipeline::Pipeline(PipelineType pipelineType) : id(0), type(pipelineType)
  {
    
    InitInputAssembly();
    InitViewportState();
    InitRasterizer();
    InitMultisampling();
    InitColorBlending();
    //Vulkan::PushDeleter([=, this](){vkDestroyPipeline(Vulkan::LogicalDevice(), pipeline, nullptr);});
  }
  
  void Pipeline::InitInputAssembly()
  {
    inputAssembly = {};
    inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    inputAssembly.primitiveRestartEnable = VK_FALSE;
  }
  void Pipeline::InitViewportState()
  {
    viewportState = {};
    viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportState.viewportCount = 1;
    viewportState.scissorCount = 1;
  }
  void Pipeline::InitRasterizer()
  {
    rasterizer = {};
    rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.depthClampEnable = VK_FALSE;
    rasterizer.rasterizerDiscardEnable = VK_FALSE;
    rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
    rasterizer.lineWidth = 1.0f;
    rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
    rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
    rasterizer.depthBiasEnable = VK_FALSE;
  }
  void Pipeline::InitMultisampling()
  {
    multisampling = {};
    multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling.sampleShadingEnable = VK_FALSE;
    multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
  }
  void Pipeline::InitColorBlending()
  {
    colorBlendAttachment = {};
    colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    colorBlendAttachment.blendEnable = VK_FALSE;
    
    colorBlending = {};
    colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlending.logicOpEnable = VK_FALSE;
    colorBlending.logicOp = VK_LOGIC_OP_COPY;
    colorBlending.attachmentCount = 1;
    colorBlending.pAttachments = &colorBlendAttachment;
    colorBlending.blendConstants[0] = 0.0f;
    colorBlending.blendConstants[1] = 0.0f;
    colorBlending.blendConstants[2] = 0.0f;
    colorBlending.blendConstants[3] = 0.0f;
  }
  
  void Pipeline::SetTopology(VkPrimitiveTopology topology, VkBool32 primitiveRestartEnable)
  {
    inputAssembly.topology = topology;
    inputAssembly.primitiveRestartEnable = primitiveRestartEnable;
  }
  void Pipeline::SetPolygonMode(VkPolygonMode polygonMode)
  {
    rasterizer.polygonMode = polygonMode;
  }
  void Pipeline::SetLineWidth(float width)
  {
    rasterizer.lineWidth = width;
  }
  void Pipeline::SetMultiSampling(VkSampleCountFlagBits sampleCount, VkBool32 enableSampleShading, VkBool32 enabledAlphaToCoverage, VkBool32 enabledAlphaToOne, VkPipelineMultisampleStateCreateFlags flags)
  {
    multisampling.rasterizationSamples = sampleCount;
    multisampling.sampleShadingEnable = enableSampleShading;
    multisampling.alphaToCoverageEnable = enabledAlphaToCoverage;
    multisampling.alphaToOneEnable = enabledAlphaToOne;
    multisampling.flags = flags;
  }
  
  void Pipeline::AddDynamicState(VkDynamicState state)
  {
    dynamicStates.push_back(state);
  }
  void Pipeline::AddDynamicStates(std::initializer_list<VkDynamicState> states)
  {
    for(auto state : states)
      dynamicStates.push_back(state);
  }
  void Pipeline::ClearDynamicStates()
  {
    dynamicStates.clear();
  }
  
  void Pipeline::RestoreDefaultSettings()
  {
    InitInputAssembly();
    InitViewportState();
    InitRasterizer();
    InitMultisampling();
    InitColorBlending();
    dynamicStates.clear();
  }
  void Pipeline::Bake(VkRenderPass renderPass, const std::vector<VkVertexInputBindingDescription>& bindingDescriptions, const std::vector<VkVertexInputAttributeDescription>& attributeDescriptions,
                      const std::vector<VkPipelineShaderStageCreateInfo>& shaderStages, VkPipelineLayout pipelineLayout)
  {
    //shader->BakePipelineLayout();
    layout = pipelineLayout;
    VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
    vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    
    
    
    
    //auto bindingDescriptions = shader->GetLayout().GetVertexBindingDescriptions();
    //auto attributeDescriptions = shader->GetLayout().GetVertexAttributeDescriptions();
    
    vertexInputInfo.vertexBindingDescriptionCount = bindingDescriptions.size();
    vertexInputInfo.vertexAttributeDescriptionCount = attributeDescriptions.size();
    vertexInputInfo.pVertexBindingDescriptions = bindingDescriptions.data();
    vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();
    
    // Depth and stencil state
    VkPipelineDepthStencilStateCreateInfo depthStencil{};
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
    
    VkPipelineDynamicStateCreateInfo dynamicState{};
    dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamicState.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
    dynamicState.pDynamicStates = dynamicStates.data();
    
    //material->BakePipelineLayout();
    //layout.Bake(shader);
    
    //std::vector<VkPipelineShaderStageCreateInfo> shaderStages = shader->CreateShaderStageCreateInfos();
    
    VkGraphicsPipelineCreateInfo pipelineInfo{};
    pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineInfo.stageCount = shaderStages.size();
    pipelineInfo.pStages = shaderStages.data();
    
    pipelineInfo.pVertexInputState = &vertexInputInfo;
    pipelineInfo.pInputAssemblyState = &inputAssembly;
    pipelineInfo.pViewportState = &viewportState;
    pipelineInfo.pRasterizationState = &rasterizer;
    pipelineInfo.pMultisampleState = &multisampling;
    pipelineInfo.pDepthStencilState = &depthStencil;
    pipelineInfo.pColorBlendState = &colorBlending;
    pipelineInfo.pDynamicState = &dynamicState;
    
    
    pipelineInfo.layout = layout;
    
    pipelineInfo.renderPass = renderPass;
    pipelineInfo.subpass = 0;
    
    pipelineInfo.basePipelineHandle = VK_NULL_HANDLE; // Optional
    pipelineInfo.basePipelineIndex = -1; // Optional
    
    CANDY_CORE_ASSERT(vkCreateGraphicsPipelines(Vulkan::LogicalDevice(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &pipeline) == VK_SUCCESS, "Failed to create graphics pipeline!");
    //Vulkan::PushDeleter([=, this](){ vkDestroyPipeline(Vulkan::LogicalDevice(), pipeline, nullptr); });
    Vulkan::DeletionQueue().Push(pipeline);
    
    for (auto createInfo : shaderStages)
    {
      //createInfo.module
      vkDestroyShaderModule(Vulkan::LogicalDevice(), createInfo.module, nullptr);
    }
    //shader->DestroyShaderModules();
  }

  
  uint32_t Pipeline::GetID()const{return id;}
  PipelineType Pipeline::GetType()const{return type;}
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-type"
  VkPipelineBindPoint Pipeline::TypeToVulkan(PipelineType type)
  {
    switch(type)
    {
      case PipelineType::Graphics:
        return VK_PIPELINE_BIND_POINT_GRAPHICS;
        case PipelineType::Compute:
        return VK_PIPELINE_BIND_POINT_COMPUTE;
        default:
        CANDY_CORE_ASSERT(false, "Invalid pipeline type!");
        
    }
  }
#pragma GCC diagnostic pop
  VkPipelineLayout Pipeline::GetLayout()const
  {
    return layout;
  }
}