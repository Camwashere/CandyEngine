#pragma once
#include <candy/graphics/shader/config/ShaderEnums.hpp>
#include <candy/math/Vector.hpp>
#include <candy/graphics/shader/config/ShaderProfileSettings.hpp>
#include <candy/base/Assert.hpp>
namespace Candy::Graphics
{
  /*case DynamicStateType::DepthTestStatic:
  vulkanStates.push_back(VK_DYNAMIC_STATE_DEPTH_TEST_ENABLE_EXT);
  vulkanStates.push_back(VK_DYNAMIC_STATE_DEPTH_BIAS_ENABLE);
  vulkanStates.push_back(VK_DYNAMIC_STATE_DEPTH_BOUNDS_TEST_ENABLE_EXT);
  break;
  case DynamicStateType::DepthTestDynamic:
  vulkanStates.push_back(VK_DYNAMIC_STATE_DEPTH_TEST_ENABLE_EXT);
  vulkanStates.push_back(VK_DYNAMIC_STATE_DEPTH_BOUNDS_TEST_ENABLE_EXT);
  vulkanStates.push_back(VK_DYNAMIC_STATE_DEPTH_BIAS_ENABLE);
  vulkanStates.push_back(VK_DYNAMIC_STATE_DEPTH_BIAS);
  vulkanStates.push_back(VK_DYNAMIC_STATE_DEPTH_BOUNDS);
  break;
  case DynamicStateType::DepthWrite:
  vulkanStates.push_back(VK_DYNAMIC_STATE_DEPTH_WRITE_ENABLE);
  break;*/
  struct ViewportArgs
  {
    Math::Vector2u position;
    Math::Vector2u size;
  };
  struct DepthTestStaticArgs
  {
    bool enableDepthTest;
    bool enableDepthBias;
    bool enableDepthBounds;
  };
  struct DepthTestDynamicArgs
  {
    bool enableDepthTest=false;
    DepthBiasSettings biasSettings;
    DepthBoundsSettings boundsSettings;
  };
  struct DepthWriteArgs
  {
    bool enableDepthWrite;
  };
  struct BlendConstantArgs
  {
    Math::Vector4 constants;
  };
  struct CullModeArgs
  {
    CullMode mode;
  };
  using DynamicStateArgs = std::variant<ViewportArgs, DepthTestStaticArgs, DepthTestDynamicArgs, DepthWriteArgs, BlendConstantArgs, CullModeArgs>;
  struct DynamicState
  {
    DynamicStateType type;
    DynamicStateArgs args;
    
    bool ExecuteCommand();
    
    
    
  private:
    template<typename T>
    auto& GetArgs()
    {
      CANDY_CORE_ASSERT(std::holds_alternative<ViewportArgs>(this->args));
      return std::get<ViewportArgs>(this->args);
    }
    
  };
}