#include <candy/graphics/shader/config/ShaderDynamicState.hpp>
#include <candy/graphics/RenderCommand.hpp>
#include <candy/math/Vector.hpp>
#include <candy/graphics/Color.hpp>
namespace Candy::Graphics
{
  
  bool DynamicState::ExecuteCommand()
  {
    switch (type)
    {
      case DynamicStateType::Viewport:
      {
        CANDY_CORE_ASSERT(std::holds_alternative<ViewportArgs>(this->args));
        auto& viewportArgs = std::get<ViewportArgs>(this->args);
        RenderCommand::SetViewport(viewportArgs.position, viewportArgs.size);
        return true;
      }
      case DynamicStateType::DepthTestStatic:
      {
        CANDY_CORE_ASSERT(std::holds_alternative<DepthTestStaticArgs>(this->args));
        auto& depthTestArgsStatic = std::get<DepthTestStaticArgs>(this->args);
        RenderCommand::SetDepthTestsEnabled(depthTestArgsStatic.enableDepthTest, depthTestArgsStatic.enableDepthBias, depthTestArgsStatic.enableDepthBounds);
        return true;
      }
      case DynamicStateType::DepthTestDynamic:
      {
        CANDY_CORE_ASSERT(std::holds_alternative<DepthTestDynamicArgs>(this->args));
        auto& depthTestArgs = std::get<DepthTestDynamicArgs>(this->args);
        RenderCommand::SetDepthTestsEnabled(depthTestArgs.enableDepthTest, depthTestArgs.biasSettings.enable, depthTestArgs.boundsSettings.enable);
        RenderCommand::SetDepthBias(depthTestArgs.biasSettings.clamp, depthTestArgs.biasSettings.constantFactor, depthTestArgs.biasSettings.slopeFactor);
        RenderCommand::SetDepthBounds(depthTestArgs.boundsSettings.min, depthTestArgs.boundsSettings.max);
        return true;
      }
      case DynamicStateType::BlendConstants:
      {
        CANDY_CORE_ASSERT(std::holds_alternative<BlendConstantArgs>(this->args));
        auto& blendConstantsArgs = std::get<BlendConstantArgs>(this->args);
        RenderCommand::SetBlendConstants(blendConstantsArgs.constants);
        return true;
      }
      case DynamicStateType::CullMode:
      {
        CANDY_CORE_ASSERT(std::holds_alternative<CullModeArgs>(this->args));
        auto& cullModeArgs = std::get<CullModeArgs>(this->args);
        RenderCommand::SetCullMode(ShaderEnums::CullModeToVulkan(cullModeArgs.mode));
        return true;
      }
      default:
        CANDY_CORE_ASSERT(false, "INVALID DYNAMIC STATE TYPE");
        return false;
      
    }
  }
  
}