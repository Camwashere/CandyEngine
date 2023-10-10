#pragma once
#include <candy/graphics/shader/config/ShaderEnums.hpp>
#include <candy/graphics/Color.hpp>
#include <optional>
namespace Candy::Graphics
{
  
  struct DepthBiasSettings
  {
    bool enable=false;
    float clamp=0.0f;
    float constantFactor=0.0f;
    float slopeFactor=0.0f;
  };
  struct DepthBoundsSettings
  {
    bool enable=false;
    float min=0.0f;
    float max=1.0f;
  };
  struct ShaderDepthStencilSettings
  {
    bool depthBufferReading = true;
    bool depthBufferWriting = true;
    VkCompareOp depthCompareOp = VK_COMPARE_OP_LESS;
    bool stencilTest=false;
    VkStencilOpState front{};
    VkStencilOpState back{};
  };
  
  struct ShaderBlendAttachmentConfig
  {
    /// NOTE: Setting enabled color channels to NONE is same as disabling blending
    ColorChannels enabledChannels = ColorChannels::NONE;
    bool enableBlending=false;
    VkBlendFactor srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
    VkBlendFactor dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
    VkBlendOp colorBlendOp = VK_BLEND_OP_ADD;
    VkBlendFactor srcAlphaBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
    VkBlendFactor dstAlphaBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    VkBlendOp alphaBlendOp = VK_BLEND_OP_ADD;
  };
  
  class SpecializationConstantInput;
  class DynamicState;
  
  
  struct ShaderConfigurationSettings
  {
    std::optional<uint32_t> customRenderPassIndex;
    bool discardRasterizer=false;
    PolygonRenderMode renderMode=PolygonRenderMode::None;
    CullMode cullMode = CullMode::None;
    std::vector<SpecializationConstantInput> constantInputs;
  };
  
  
  struct ShaderProfileSettings
  {
    uint32_t renderPassIndex=0;
    PolygonRenderMode renderMode=PolygonRenderMode::Shaded;
    TopologyType topologyType=TopologyType::Triangle;
    bool primitiveRestart=false;
    bool discardRasterizer=false;
    ShaderType shaderType=ShaderType::Graphics;
    CullMode cullMode = CullMode::Back;
    DepthBiasSettings depthBias{};
    DepthBoundsSettings depthBounds{};
    std::vector<SpecializationConstantInput> constantInputs;
    Color blendConstants = {0, 0, 0, 0};
    std::vector<ShaderBlendAttachmentConfig> blendAttachments;
    ShaderDepthStencilSettings depthStencil{};
    std::vector<DynamicState> dynamicStates;
    
    void SetDepthStencil(bool depthTestEnabled)
    {
      depthStencil={};
      
      if (depthTestEnabled)
      {
        // Depth and stencil state
        
        depthStencil.depthBufferReading = true;
        depthStencil.depthBufferWriting = true;
        depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
        depthStencil.stencilTest = false;
        depthStencil.front = {}; // Optional
        depthStencil.back = {}; // Optional
      }
      else
      {
        // Depth and stencil state
        depthStencil.depthBufferReading = true;
        depthStencil.depthBufferWriting = false;
        depthStencil.depthCompareOp = VK_COMPARE_OP_ALWAYS;
        depthStencil.stencilTest = false;
        depthStencil.front = {}; // Optional
        depthStencil.back = {}; // Optional
      }
      
    }
    void AddBlendAttachment(bool alphaColorBlending)
    {
      ShaderBlendAttachmentConfig colorBlendAttachment{};
      if (alphaColorBlending)
      {
        colorBlendAttachment.enabledChannels = ColorChannels::RGBA;
        colorBlendAttachment.enableBlending = true;
        colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
        colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
        colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
        colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
        colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
        colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;
      }
      else
      {
        colorBlendAttachment.enabledChannels = ColorChannels::RGBA;
        colorBlendAttachment.enableBlending = false;
      }
      blendAttachments.push_back(colorBlendAttachment);
    }
  };
}