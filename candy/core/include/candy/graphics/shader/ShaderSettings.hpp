#pragma once
#include <filesystem>
#include <vulkan/vulkan.h>
#include <vector>
namespace Candy::Graphics
{
  struct ShaderSettings
  {
    enum class PipelineType
    {
      None=0,
      Graphics,
      Compute,
      RayTracing,
    };
    enum class TopologyType
    {
      TRIANGLE,
      LINE,
      LINE_STRIP,
      POINT
    };
    enum class PolygonType
    {
      FILL,
      LINE,
      POINT,
    };
    enum class CullMode
    {
      NONE=0,
      FRONT,
      BACK,
      BOTH,
    };
    std::filesystem::path filepath;
    uint8_t renderPassIndex;
    PipelineType pipelineType=PipelineType::Graphics;
    TopologyType topologyType=TopologyType::TRIANGLE;
    PolygonType polygonType = PolygonType::FILL;
    CullMode cullMode = CullMode::BACK;
    float lineWidth=1.0f;
    
    bool depthTesting=true;
    bool alphaColorBlending=false;
    std::vector<VkDynamicState> dynamicStates{};
    
    static VkPipelineBindPoint PipelineTypeToVulkan(PipelineType value);
    static VkPrimitiveTopology  TopologyToVulkan(TopologyType value);
    static VkPolygonMode PolygonToVulkan(PolygonType value);
    static VkCullModeFlags CullModeToVulkan(CullMode value);
    
  };
}