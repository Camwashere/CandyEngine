#include "candy/graphics/shader/config/ShaderProfile.hpp"
#include <utility>
#include <candy/graphics/Renderer.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <candy/graphics/vulkan/DeletionQueue.hpp>
#include <candy/graphics/shader/ShaderLayout.hpp>
#include <candy/collections/GenericBuffer.hpp>
namespace Candy::Graphics
{
  
  struct SpecConstantData
  {
    Collections::GenericBuffer buffer;
    std::vector<VkSpecializationMapEntry> entries;
    int constantInputIndex=-1;
    VkSpecializationInfo specInfo{};
    VkPipelineShaderStageCreateInfo createInfo{};
  };
  ShaderConfiguration::ShaderConfiguration(uint32_t renderPassIndex) : settings(), renderPassIndex(renderPassIndex)
  {
  
  }
  ShaderConfiguration::ShaderConfiguration(ShaderConfigurationSettings  configSettings, uint32_t defaultRenderPassIndex) : settings(std::move(configSettings)),
  renderPassIndex(settings.customRenderPassIndex.has_value()? settings.customRenderPassIndex.value() : defaultRenderPassIndex)
  {
  
  }
  
  ShaderProfile::ShaderProfile(ShaderProfileSettings profileSettings) : settings(std::move(profileSettings))
  {
  
  }
  
  ShaderProfile::ShaderProfile(ShaderProfileSettings profileSettings, const std::vector<ShaderConfigurationSettings>& shaderConfigs) : settings(std::move(profileSettings))
  {
    if (shaderConfigs.empty())
    {
      configurations.emplace_back(ShaderConfigurationSettings(), settings.renderPassIndex);
    }
    else
    {
      for (const auto& config : shaderConfigs)
      {
        configurations.emplace_back(config, settings.renderPassIndex);
      }
    }
    
  }
  
  

  void ShaderProfile::Bake(const std::vector<VkPipelineShaderStageCreateInfo>& baseCreateInfos, const ShaderLayout& layout)
  {
    CANDY_PROFILE_FUNCTION();
    std::vector<SpecConstantData> configSpecConstantData = GetSpecializationConstantLayout(baseCreateInfos, layout);
    
    for (int i=0; i<configSpecConstantData.size(); i++)
    {
      if (configSpecConstantData[i].entries.empty())
      {
        continue;
      }
      configSpecConstantData[i].specInfo.mapEntryCount = configSpecConstantData[i].entries.size();
      configSpecConstantData[i].specInfo.pMapEntries = configSpecConstantData[i].entries.data();
      configSpecConstantData[i].specInfo.dataSize = configSpecConstantData[i].buffer.Size();
      configSpecConstantData[i].specInfo.pData = configSpecConstantData[i].buffer.Data();
      configSpecConstantData[i].createInfo.pSpecializationInfo = &configSpecConstantData[i].specInfo;
    }
    std::vector<std::vector<SpecConstantData>> profileSpecData;
    profileSpecData.resize(configurations.size());
    
    for (int i=0; i<configurations.size(); i++)
    {
      profileSpecData[i].resize(configSpecConstantData.size());
      for (int j=0; j<configSpecConstantData.size(); j++)
      {
        profileSpecData[i][j].createInfo = configSpecConstantData[j].createInfo;
        profileSpecData[i][j].entries = configSpecConstantData[j].entries;
        profileSpecData[i][j].constantInputIndex = configSpecConstantData[j].constantInputIndex;
        profileSpecData[i][j].specInfo.mapEntryCount = configSpecConstantData[j].entries.size();
        profileSpecData[i][j].specInfo.pMapEntries = profileSpecData[i][j].entries.data();
        profileSpecData[i][j].specInfo.dataSize = configSpecConstantData[j].buffer.Size();
        
        if (configurations[i].settings.constantInputs.empty())
        {
          profileSpecData[i][j].buffer = configSpecConstantData[j].buffer;
          profileSpecData[i][j].specInfo.pData = profileSpecData[i][j].buffer.Data();
          profileSpecData[i][j].createInfo.pSpecializationInfo = &profileSpecData[i][j].specInfo;
        }
        else
        {
          profileSpecData[i][j].buffer.AddBuffer(configurations[i].settings.constantInputs[profileSpecData[i][j].constantInputIndex].GetValue());
          profileSpecData[i][j].specInfo.pData = profileSpecData[i][j].buffer.Data();
          profileSpecData[i][j].createInfo.pSpecializationInfo = &profileSpecData[i][j].specInfo;
        }
      }
    }
    
    
    
    BakeInternal(profileSpecData, layout);
  }
  
  void ShaderProfile::BakeInternal(const std::vector<std::vector<SpecConstantData>>& profileCreateInfos, const ShaderLayout& shaderLayout)
  {
    
    struct ShaderProfileBakeData
    {
      VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
      VkPipelineViewportStateCreateInfo viewportState{};
      VkPipelineMultisampleStateCreateInfo multisampling{};
      VkPipelineDepthStencilStateCreateInfo depthStencil{};
      std::vector<VkPipelineColorBlendAttachmentState> colorBlendAttachments{};
      VkPipelineRasterizationStateCreateInfo rasterizer{};
      VkPipelineDynamicStateCreateInfo dynamicStates{};
      
    };
    
    ShaderProfileBakeData sharedData{};
    sharedData.inputAssembly = GetInputAssembly();
    sharedData.viewportState = GetViewportState();
    sharedData.multisampling = GetMultisampling();
    sharedData.depthStencil = GetDepthStencil();
    sharedData.colorBlendAttachments = GetColorBlendAttachments();
    std::vector<VkDynamicState> dynamicStates = GetDynamicStates();
    sharedData.dynamicStates.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    sharedData.dynamicStates.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
    sharedData.dynamicStates.pDynamicStates = dynamicStates.data();
    
    
    VkPipelineColorBlendStateCreateInfo colorBlending = {};
    colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlending.logicOpEnable = VK_FALSE;
    colorBlending.logicOp = VK_LOGIC_OP_COPY;
    colorBlending.attachmentCount = sharedData.colorBlendAttachments.size();
    colorBlending.pAttachments = sharedData.colorBlendAttachments.data();
    colorBlending.blendConstants[0] = settings.blendConstants[0];
    colorBlending.blendConstants[1] = settings.blendConstants[1];
    colorBlending.blendConstants[2] = settings.blendConstants[2];
    colorBlending.blendConstants[3] = settings.blendConstants[3];
    
    sharedData.rasterizer = GetRasterizer();
    
    VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
    vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    
    std::vector<VkVertexInputBindingDescription> bindingDescriptions = shaderLayout.GetVertexBindingDescriptions();
    std::vector<VkVertexInputAttributeDescription> attributeDescriptions = shaderLayout.GetVertexAttributeDescriptions();
    
    vertexInputInfo.vertexBindingDescriptionCount = bindingDescriptions.size();
    vertexInputInfo.vertexAttributeDescriptionCount = attributeDescriptions.size();
    vertexInputInfo.pVertexBindingDescriptions = bindingDescriptions.data();
    vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();
    
    VkPipelineLayout pipelineLayout = shaderLayout.GetPipelineLayout();
    
    std::vector<VkPipelineRasterizationStateCreateInfo> profileRasterizers{};
    
    
    profileRasterizers.resize(configurations.size());
    CANDY_CORE_ASSERT(!profileRasterizers.empty());
    for (int i=0; i<profileRasterizers.size(); i++)
    {
      profileRasterizers[i] = sharedData.rasterizer;
      if (configurations[i].settings.cullMode != CullMode::None)
      {
        profileRasterizers[i].cullMode = ShaderEnums::CullModeToVulkan(configurations[i].settings.cullMode);
      }
      if (configurations[i].settings.renderMode != PolygonRenderMode::None)
      {
        profileRasterizers[i].polygonMode = ShaderEnums::RenderModeToVulkan(configurations[i].settings.renderMode);
      }
      
      profileRasterizers[i].rasterizerDiscardEnable = configurations[i].settings.discardRasterizer;
    }
    
    std::vector<VkGraphicsPipelineCreateInfo> pipelineInfos;
    pipelineInfos.resize(configurations.size());
    
    
    std::vector<std::vector<VkPipelineShaderStageCreateInfo>> shaderStages{};
    shaderStages.resize(profileCreateInfos.size());
    for (int i=0; i<profileCreateInfos.size(); i++)
    {
      shaderStages[i].resize(profileCreateInfos[i].size());
      for (int j=0; j<profileCreateInfos[i].size(); j++)
      {
        shaderStages[i][j] = profileCreateInfos[i][j].createInfo;
      }
    }
    
    for (int i=0; i<pipelineInfos.size(); i++)
    {
      pipelineInfos[i].sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
      
      
      pipelineInfos[i].stageCount = shaderStages[i].size();
      pipelineInfos[i].pStages = shaderStages[i].data();
      
      
      pipelineInfos[i].pVertexInputState = &vertexInputInfo;
      
      
      pipelineInfos[i].pInputAssemblyState = &sharedData.inputAssembly;
      pipelineInfos[i].pViewportState = &sharedData.viewportState;
      
      pipelineInfos[i].pRasterizationState = &profileRasterizers[i];
      pipelineInfos[i].pMultisampleState = &sharedData.multisampling;
      pipelineInfos[i].pDepthStencilState = &sharedData.depthStencil;
      pipelineInfos[i].pColorBlendState = &colorBlending;
      pipelineInfos[i].pDynamicState = &sharedData.dynamicStates;
      
      
      pipelineInfos[i].layout = pipelineLayout;
      
      pipelineInfos[i].renderPass = Renderer::GetRenderPassHandle(settings.renderPassIndex);
      pipelineInfos[i].subpass = 0;
      
      pipelineInfos[i].basePipelineHandle = VK_NULL_HANDLE; // Optional
      pipelineInfos[i].basePipelineIndex = -1; // Optional
    }
    
    std::vector<VkPipeline> pipelines;
    pipelines.resize(pipelineInfos.size());
    CANDY_CORE_ASSERT((!pipelineInfos.empty()) && (pipelineInfos.size()==configurations.size()), "Pipeline info size mismatch!");
    CANDY_VULKAN_CHECK(vkCreateGraphicsPipelines(Vulkan::LogicalDevice(), VK_NULL_HANDLE, pipelineInfos.size(), pipelineInfos.data(), nullptr, pipelines.data()));
    
    for (int i=0; i<configurations.size(); i++)
    {
      configurations[i].pipeline = pipelines[i];
      Vulkan::DeletionQueue().Push(configurations[i].pipeline);
    }
    
    
  }
  
  
  std::vector<SpecConstantData> ShaderProfile::GetSpecializationConstantLayout(const std::vector<VkPipelineShaderStageCreateInfo>& createInfos, const ShaderLayout& layout)
  {
    std::vector<SpecConstantData> specConstantData(createInfos.size());
    
    for (int i = 0; i<createInfos.size(); i++)
    {
      size_t currentSize = 0;
      specConstantData[i].createInfo = createInfos[i];
      
      for (int specInputIndex=0; specInputIndex<settings.constantInputs.size(); specInputIndex++)
      {
        ShaderSpecializationConstant specConstant;
        SpecializationConstantInput specInput = settings.constantInputs[specInputIndex];
        if (layout.GetSpecConstant(specInput.GetName(), &specConstant))
        {
          if (specConstant.stage == ShaderData::VulkanToStage(createInfos[i].stage))
          {
            
            VkSpecializationMapEntry entry{};
            entry.constantID = specConstant.id;
            
            size_t typeSize = specInput.GetSize();
            entry.size = typeSize;
            entry.offset = currentSize;
            
            specConstantData[i].constantInputIndex=specInputIndex;
            specConstantData[i].buffer.AddBuffer(specInput.GetValue());
            
            
            currentSize += entry.size;
            specConstantData[i].entries.push_back(entry);
          }
        }
      }
    }
    return specConstantData;
  }
  
  
  void ShaderProfile::OnBind()const
  {
    for (auto state : settings.dynamicStates)
    {
      DynamicStateBind(state.type);
    }
    
  }
  
  void ShaderProfile::DynamicStateBind(DynamicStateType type) const
  {
    switch (type)
    {
      case DynamicStateType::DepthTestStatic:
      {
        RenderCommand::SetDepthTestsEnabled(settings.depthStencil.depthBufferReading, settings.depthBias.enable, settings.depthBounds.enable);
        break;
      }
      case DynamicStateType::DepthTestDynamic:
      {
        RenderCommand::SetDepthTestsEnabled(settings.depthStencil.depthBufferReading, settings.depthBias.enable, settings.depthBounds.enable);
        RenderCommand::SetDepthBias(settings.depthBias.clamp, settings.depthBias.constantFactor, settings.depthBias.slopeFactor);
        RenderCommand::SetDepthBounds(settings.depthBounds.min, settings.depthBounds.max);
        break;
      }
      case DynamicStateType::BlendConstants:
      {
        RenderCommand::SetBlendConstants(settings.blendConstants);
        break;
      }
      case DynamicStateType::CullMode:
      {
        RenderCommand::SetCullMode(ShaderEnums::CullModeToVulkan(settings.cullMode));
        break;
      }
      default:
        break;
      
    }
  }
  
  void ShaderProfile::Bind()const
  {
    RenderCommand::BindPipeline(GetBindPoint(), configurations[activeConfig].pipeline);
    OnBind();
  }
  uint32_t ShaderProfile::GetActiveRenderPassIndex()const
  {
    return configurations[activeConfig].renderPassIndex;
  }
  VkPipeline ShaderProfile::GetActivePipeline()const
  {
    return configurations[activeConfig].pipeline;
  }
  VkPipelineBindPoint ShaderProfile::GetBindPoint()const
  {
    return ShaderEnums::ShaderTypeToVulkan(settings.shaderType);
  }
  
  std::vector<VkDynamicState> ShaderProfile::GetDynamicStates()const
  {
    std::vector<VkDynamicState> dynamicStates;
    dynamicStates.push_back(VK_DYNAMIC_STATE_VIEWPORT);
    dynamicStates.push_back(VK_DYNAMIC_STATE_SCISSOR);
    
    std::vector<VkDynamicState> customDynamicStates = ShaderEnums::DynamicStatesToVulkan(settings.dynamicStates);
    
    for (const auto& state : customDynamicStates)
    {
      dynamicStates.push_back(state);
    }
    return dynamicStates;
  }
  VkPipelineRasterizationStateCreateInfo ShaderProfile::GetRasterizer()const
  {
    VkPipelineRasterizationStateCreateInfo rasterizer{};
    rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.depthClampEnable = VK_FALSE;
    rasterizer.rasterizerDiscardEnable = settings.discardRasterizer;
    rasterizer.polygonMode = ShaderEnums::RenderModeToVulkan(settings.renderMode);
    rasterizer.lineWidth = 1.0f;
    rasterizer.cullMode = ShaderEnums::CullModeToVulkan(settings.cullMode);
    //rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
    rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
    rasterizer.depthBiasEnable = settings.depthBias.enable;
    rasterizer.depthBiasClamp = settings.depthBias.clamp;
    rasterizer.depthBiasConstantFactor = settings.depthBias.constantFactor;
    rasterizer.depthBiasSlopeFactor = settings.depthBias.slopeFactor;
    return rasterizer;
  }
  VkPipelineMultisampleStateCreateInfo ShaderProfile::GetMultisampling()const
  {
    VkPipelineMultisampleStateCreateInfo multisampling = {};
    multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling.sampleShadingEnable = VK_FALSE;
    multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    return multisampling;
  }
  
  VkPipelineViewportStateCreateInfo ShaderProfile::GetViewportState()const
  {
    VkPipelineViewportStateCreateInfo viewportState = {};
    viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportState.viewportCount = 1;
    viewportState.scissorCount = 1;
    return viewportState;
  }
  
  VkPipelineInputAssemblyStateCreateInfo ShaderProfile::GetInputAssembly()const
  {
    VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
    inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssembly.topology = ShaderEnums::TopologyToVulkan(settings.topologyType);
    inputAssembly.primitiveRestartEnable = settings.primitiveRestart;
    return inputAssembly;
  }
  VkPipelineDepthStencilStateCreateInfo ShaderProfile::GetDepthStencil()const
  {
    VkPipelineDepthStencilStateCreateInfo depthStencil = {};
    // Depth and stencil state
    depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    depthStencil.depthTestEnable = settings.depthStencil.depthBufferReading;
    depthStencil.depthWriteEnable = settings.depthStencil.depthBufferWriting;
    depthStencil.depthCompareOp = settings.depthStencil.depthCompareOp;
    depthStencil.depthBoundsTestEnable = settings.depthBounds.enable;
    depthStencil.minDepthBounds = settings.depthBounds.min;
    depthStencil.maxDepthBounds = settings.depthBounds.max;
    depthStencil.stencilTestEnable = settings.depthStencil.stencilTest;
    depthStencil.front = settings.depthStencil.front;
    depthStencil.back = settings.depthStencil.back;
    return depthStencil;
  }
  
  
  
  std::vector<VkPipelineColorBlendAttachmentState> ShaderProfile::GetColorBlendAttachments()const
  {
    std::vector<VkPipelineColorBlendAttachmentState> colorBlendAttachments;
    if (settings.blendAttachments.empty())
    {
      VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
      colorBlendAttachment.colorWriteMask = static_cast<VkColorComponentFlags>(ColorChannels::RGBA);
      colorBlendAttachment.blendEnable = VK_FALSE;
      colorBlendAttachments.push_back(colorBlendAttachment);
      return colorBlendAttachments;
    }
    for (const auto& attachmentConfig : settings.blendAttachments)
    {
      VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
      if (attachmentConfig.enableBlending)
      {
        colorBlendAttachment.colorWriteMask = static_cast<VkColorComponentFlags>(attachmentConfig.enabledChannels);
        colorBlendAttachment.blendEnable = attachmentConfig.enableBlending;
        
        colorBlendAttachment.srcColorBlendFactor = attachmentConfig.srcColorBlendFactor;
        colorBlendAttachment.dstColorBlendFactor = attachmentConfig.dstColorBlendFactor;
        colorBlendAttachment.colorBlendOp = attachmentConfig.colorBlendOp;
        colorBlendAttachment.srcAlphaBlendFactor = attachmentConfig.srcAlphaBlendFactor;
        colorBlendAttachment.dstAlphaBlendFactor = attachmentConfig.dstAlphaBlendFactor;
        colorBlendAttachment.alphaBlendOp = attachmentConfig.alphaBlendOp;
      }
      else
      {
        colorBlendAttachment.colorWriteMask = static_cast<VkColorComponentFlags>(attachmentConfig.enabledChannels);
        colorBlendAttachment.blendEnable = VK_FALSE;
      }
      colorBlendAttachments.push_back(colorBlendAttachment);
    }
    return colorBlendAttachments;
    
  }
}