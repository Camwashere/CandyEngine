#include <candy/graphics/shader/config/ShaderEnums.hpp>
#include <candy/graphics/shader/config/ShaderDynamicState.hpp>
#include "CandyPch.hpp"

namespace Candy::Graphics
{
  VkPrimitiveTopology ShaderEnums::TopologyToVulkan(TopologyType value)
  {
    switch (value)
    {
      case TopologyType::Triangle:
        return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
      case TopologyType::Line:
        return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;
      case TopologyType::Point:
        return VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
      default:
        CANDY_CORE_ASSERT(false, "INVALID TOPOLOGY TYPE");
        return (VkPrimitiveTopology)0;
    }
  }
  VkPipelineBindPoint ShaderEnums::ShaderTypeToVulkan(ShaderType value)
  {
    switch(value)
    {
      case ShaderType::Graphics:
        return VK_PIPELINE_BIND_POINT_GRAPHICS;
      case ShaderType::Compute:
        return VK_PIPELINE_BIND_POINT_COMPUTE;
      default:
        CANDY_CORE_ASSERT(false, "Invalid pipeline type!");
        return (VkPipelineBindPoint)0;
      
    }
  }
  
  VkPolygonMode ShaderEnums::RenderModeToVulkan(PolygonRenderMode value)
  {
    switch (value)
    {
      case PolygonRenderMode::Shaded:
        return VK_POLYGON_MODE_FILL;
      case PolygonRenderMode::Wireframe:
        return VK_POLYGON_MODE_LINE;
      case PolygonRenderMode::Point:
        return VK_POLYGON_MODE_POINT;
      default:
        CANDY_CORE_ASSERT(false, "INVALID POLYGON TYPE");
        return (VkPolygonMode)0;
    }
  }
  
  VkCullModeFlags ShaderEnums::CullModeToVulkan(CullMode value)
  {
    switch (value)
    {
      case CullMode::Back:
        return VK_CULL_MODE_BACK_BIT;
      case CullMode::Front:
        return VK_CULL_MODE_FRONT_BIT;
      case CullMode::Both:
        return VK_CULL_MODE_FRONT_AND_BACK;
      default:
        CANDY_CORE_ASSERT(false, "INVALID CULL MODE");
        return (VkCullModeFlags)0;
    }
    
  }
  std::vector<VkDynamicState> ShaderEnums::DynamicStatesToVulkan(const std::vector<DynamicState>& states)
  {
    std::vector<DynamicStateType> types;
    for (auto state : states)
    {
      types.push_back(state.type);
    }
    
    return DynamicStatesToVulkan(types);
  }
  std::vector<VkDynamicState> ShaderEnums::DynamicStatesToVulkan(const std::vector<DynamicStateType>& states)
  {
    std::vector<VkDynamicState> vulkanStates;
    for (auto state : states)
    {
      switch (state)
      {
        case DynamicStateType::Viewport:
          vulkanStates.push_back(VK_DYNAMIC_STATE_VIEWPORT);
          vulkanStates.push_back(VK_DYNAMIC_STATE_SCISSOR);
          break;
        case DynamicStateType::DepthTestStatic:
          vulkanStates.push_back(VK_DYNAMIC_STATE_DEPTH_TEST_ENABLE);
          vulkanStates.push_back(VK_DYNAMIC_STATE_DEPTH_BIAS_ENABLE);
          vulkanStates.push_back(VK_DYNAMIC_STATE_DEPTH_BOUNDS_TEST_ENABLE);
          break;
        case DynamicStateType::DepthTestDynamic:
          vulkanStates.push_back(VK_DYNAMIC_STATE_DEPTH_TEST_ENABLE);
          vulkanStates.push_back(VK_DYNAMIC_STATE_DEPTH_BOUNDS_TEST_ENABLE);
          vulkanStates.push_back(VK_DYNAMIC_STATE_DEPTH_BIAS_ENABLE);
          vulkanStates.push_back(VK_DYNAMIC_STATE_DEPTH_BIAS);
          vulkanStates.push_back(VK_DYNAMIC_STATE_DEPTH_BOUNDS);
          break;
        case DynamicStateType::DepthWrite:
          vulkanStates.push_back(VK_DYNAMIC_STATE_DEPTH_WRITE_ENABLE);
          break;
        case DynamicStateType::BlendConstants:
          vulkanStates.push_back(VK_DYNAMIC_STATE_BLEND_CONSTANTS);
          break;
        case DynamicStateType::CullMode:
          vulkanStates.push_back(VK_DYNAMIC_STATE_CULL_MODE);
          break;
        
        default:
          CANDY_CORE_ASSERT(false, "INVALID DYNAMIC STATE TYPE");
          break;
      }
    }
    return vulkanStates;
  }
}