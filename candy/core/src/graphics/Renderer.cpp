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
  
  }
  
  VkPipelineLayout Renderer::GetPipelineLayout()
  {
    if (!instance->materials.empty())
    {
      return instance->materials[0]->GetShader()->GetPipelineLayout();
    }
    return VK_NULL_HANDLE;
  }
  Renderer* Renderer::instance = nullptr;
  
  void Renderer::Submit(Material* material)
  {
    instance->materials.push_back(material);
    //instance->pipeline.Bake(material, *instance->renderPass);
  }
  void Renderer::Init()
  {
    Renderer::instance = new Renderer();
  }
  void Renderer::Start()
  {
    instance->target->SwapBuffers();
    Renderer::BeginPass();
  }
 
  void Renderer::SetTarget(GraphicsContext* target)
  {
    instance->target = target;
    /*SwapChainSupportDetails swapChainSupport = Vulkan::PhysicalDevice().QuerySwapChainSupport(target->surface);
    VkSurfaceFormatKHR surfaceFormat = Vulkan::ChooseSwapSurfaceFormat(swapChainSupport.formats);
    instance->renderPass = CreateUniquePtr<RenderPass>(surfaceFormat.format);*/
  }
  
  void Renderer::InitRenderPass(VkSurfaceKHR surface)
  {
    SwapChainSupportDetails swapChainSupport = Vulkan::PhysicalDevice().QuerySwapChainSupport(surface);
    VkSurfaceFormatKHR surfaceFormat = Vulkan::ChooseSwapSurfaceFormat(swapChainSupport.formats);
    instance->renderPass = CreateUniquePtr<RenderPass>(surfaceFormat.format);
  }
  void Renderer::BeginPass()
  {
    CANDY_CORE_ASSERT(vkResetFences(Vulkan::LogicalDevice(), 1, &GetCurrentFrame().renderFence) == VK_SUCCESS);
    RenderCommand::Reset();
    //GetCurrentFrame().commandBuffer.Reset();
    
    //GetCurrentFrame().commandBuffer.StartRecording(VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT);
    
    std::array<VkClearValue, 2> clearValues{};
    
    clearValues[0].color = { { 0.0f, 0.0f, 0.0f, 1.0f } };
    clearValues[1].depthStencil = {1.0f, 0};
    
    VkRenderPassBeginInfo rpInfo = BeginRenderPass();
    rpInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
    rpInfo.pClearValues = clearValues.data();
    
    GetCurrentFrame().commandBuffer.StartRenderPass(&rpInfo);
    if (! instance->materials.empty())
    {
      instance->materials[0]->Bind();
    }
    //GetCurrentFrame().commandBuffer.BindPipeline(instance->pipeline);
    RenderCommand::SetViewport(instance->target->swapChain->extent);
  }
  VkRenderPassBeginInfo Renderer::BeginRenderPass()
  {
      return instance->renderPass->BeginPass(instance->target->swapChain->GetCurrentFrameBuffer(), instance->target->swapChain->extent);
  }
  void Renderer::EndPass()
  {
    RenderCommand::Submit();
    
  }
  
  VkRenderPass Renderer::GetRenderPass()
  {
    return *instance->renderPass;
  }
  
  FrameData& Renderer::GetCurrentFrame(){return instance->target->GetCurrentFrame();}
  


  

}