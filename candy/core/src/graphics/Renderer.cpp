#include <candy/graphics/Renderer.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <candy/graphics/vulkan/VulkanBuffer.hpp>
#include <candy/app/Application.hpp>
#include <candy/graphics/RenderCommand.hpp>
namespace Candy::Graphics
{
  using namespace Math;
  
  
  
  Renderer::Renderer() : target(nullptr)
  {
    //writes.resize(10);
  }
  
  Renderer* Renderer::instance = nullptr;
  
  
  
  /*void Renderer::Submit(Material* material)
  {
    instance->materials.push_back(material);
  }*/
  void Renderer::Init()
  {
    Renderer::instance = new Renderer();
    
  }
  void Renderer::Start()
  {
    instance->target->SwapBuffers();
    Renderer::BeginViewportPass();
  }
 
  void Renderer::SetTarget(GraphicsContext* target)
  {
    instance->target = target;
    VkSurfaceFormatKHR surfaceFormat = instance->target->GetSurfaceFormat();
    instance->renderPasses[viewportPassIndex] = CreateUniquePtr<RenderPass>(surfaceFormat.format, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    instance->renderPasses[uiPassIndex] = CreateUniquePtr<RenderPass>(surfaceFormat.format, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);
  }
  void Renderer::BeginViewportPass()
  {
    CANDY_CORE_ASSERT(vkResetFences(Vulkan::LogicalDevice(), 1, &GetCurrentFrame().renderFence) == VK_SUCCESS);
    GetCurrentFrame().commandBuffer.SetCurrentBuffer(0);
    RenderCommand::Reset();
    
    std::array<VkClearValue, 2> clearValues{};
    
    
    clearValues[0].color = {0.0f, 0.3f, 0.0f, 1.0f};
    clearValues[1].depthStencil = {1.0f, 0};
    Vector2u size = {instance->target->swapChain->extent.width, instance->target->swapChain->extent.height};
    VkRenderPassBeginInfo rpInfo = GetViewportPass().BeginPass(GetCurrentFrame().viewportFrameBuffer, size);
    rpInfo.clearValueCount = clearValues.size();
    rpInfo.pClearValues = clearValues.data();
    
    
    GetCurrentFrame().commandBuffer.StartRenderPass(&rpInfo);
    
    Math::Vector2u position = {0, 0};
    RenderCommand::SetViewport(position, size);
  }
  void Renderer::BeginUIPass()
  {
    GetCurrentFrame().commandBuffer.SetCurrentBuffer(1);
    RenderCommand::Reset();
    
    std::array<VkClearValue, 2> clearValues{};
    
    clearValues[0].color = {0.0f, 0.3f, 0.0f, 1.0f};
    clearValues[1].depthStencil = {1.0f, 0};
    Vector2u size = {instance->target->swapChain->extent.width, instance->target->swapChain->extent.height};
    VkRenderPassBeginInfo rpInfo = GetUIPass().BeginPass(instance->target->swapChain->GetCurrentFrameBuffer(), size);
    rpInfo.clearValueCount = clearValues.size();
    rpInfo.pClearValues = clearValues.data();
    
    
    GetCurrentFrame().commandBuffer.StartRenderPass(&rpInfo);
    
    Math::Vector2u position = {0, 0};
    RenderCommand::SetViewport(position, size);
  }

  
  void Renderer::BeginScene(const Camera& camera)
  {
  
  }
  void Renderer::EndScene()
  {
  
  }

  void Renderer::SetClearColor(Color color)
  {
    GetViewportPass().SetClearColor(color);
  }
  void Renderer::EndViewportPass()
  {
  
  }
  void Renderer::EndPass()
  {
    RenderCommand::Submit();
  }
  RenderPass& Renderer::GetCurrentPass()
  {
    return *instance->renderPasses[instance->currentPassIndex];
  }
  RenderPass& Renderer::GetUIPass()
  {
    return *instance->renderPasses[uiPassIndex];
  }

  RenderPass& Renderer::GetViewportPass()
  {
    return *instance->renderPasses[viewportPassIndex];
  }
  
  FrameData& Renderer::GetCurrentFrame(){return instance->target->GetCurrentFrame();}
  FrameData& Renderer::GetFrame(uint32_t index){return instance->target->GetFrame(index);}
  


  

}