#include <gum/GumInstance.hpp>
#include "CandyPch.hpp"
#include <candy/graphics/Renderer.hpp>
namespace Candy::Gum
{
  using namespace Graphics;
  struct GumData
  {
    Version version=Version(0,0,1);
    GumConfig config;
    //GumContext context;
    
  };
  
  static GumData data;
  void GumInstance::Init(const std::filesystem::path& iniConfigPath)
  {
    //bool loadedConfig = data.config.Load(iniConfigPath);
   // CANDY_CORE_ASSERT(loadedConfig, "Failed to load Gum config");
    
  }
  void GumInstance::Shutdown()
  {
  
  }
  void GumInstance::BeginPass()
  {
    CANDY_PROFILE_FUNCTION();
    /*instance->currentPassIndex = uiPassIndex;
    GetCurrentFrame().commandBuffer.SetCurrentBuffer(uiPassIndex);
    RenderCommand::Reset();
    
    std::array<VkClearValue, 2> clearValues{};
    
    clearValues[0].color = {instance->clearColor.r, instance->clearColor.g, instance->clearColor.b, instance->clearColor.a};
    clearValues[1].depthStencil = {1.0f, 0};
    Vector2u size = {instance->target->swapChain->extent.width, instance->target->swapChain->extent.height};
    VkRenderPassBeginInfo rpInfo = GetUIPass().BeginPass(instance->target->swapChain->GetCurrentFrameBuffer(), size);
    rpInfo.clearValueCount = clearValues.size();
    rpInfo.pClearValues = clearValues.data();
    
    
    GetCurrentFrame().commandBuffer.StartRenderPass(&rpInfo);
    
    Math::Vector2u position = {0, 0};
    RenderCommand::SetViewport(position, size);*/
  }
  void GumInstance::EndPass()
  {
  
  }
  void GumInstance::Render()
  {
  
  }
  
  /*GumContext& GumInstance::GetContext()
  {
    return data.context;
  }*/
  Version GumInstance::GetVersion()
  {
    return data.version;
  }
}