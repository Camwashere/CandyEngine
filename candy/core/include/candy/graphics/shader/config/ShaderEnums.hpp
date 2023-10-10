#pragma once
#include <vulkan/vulkan.h>
#include <vector>
namespace Candy::Graphics
{
  enum class ShaderType
  {
    None=0,
    Graphics,
    Compute,
    RayTracing,
  };
  enum class TopologyType
  {
    None=0,
    Triangle,
    Line,
    Point,
  };
  
  enum PolygonRenderMode
  {
    None=0,
    Shaded,
    Wireframe,
    Point,
  };
  
  enum class CullMode
  {
    None=0,
    Front,
    Back,
    Both,
  };
  
  enum class WindingOrder
  {
    None=0,
    Clockwise,
    CounterClockwise,
  };
  
  enum class DynamicStateType
  {
    Viewport,
    DepthTestStatic,
    DepthTestDynamic,
    DepthWrite,
    BlendConstants,
    CullMode,
  };
  class DynamicState;
  struct ShaderEnums
  {
    static VkPrimitiveTopology TopologyToVulkan(TopologyType value);
    static VkPipelineBindPoint ShaderTypeToVulkan(ShaderType value);
    static VkPolygonMode RenderModeToVulkan(PolygonRenderMode value);
    static VkCullModeFlags CullModeToVulkan(CullMode value);
    static std::vector<VkDynamicState> DynamicStatesToVulkan(const std::vector<DynamicState>& states);
    static std::vector<VkDynamicState> DynamicStatesToVulkan(const std::vector<DynamicStateType>& states);
  };
}