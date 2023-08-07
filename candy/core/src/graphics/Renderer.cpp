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
  void Renderer::AddWrite(VkWriteDescriptorSet write)
  {
    instance->writes.push_back(write);
  }
  void Renderer::AddWrites(std::vector<VkWriteDescriptorSet> writes)
  {
    instance->writes.insert(instance->writes.end(), writes.begin(), writes.end());
  }
  void Renderer::Submit(Material* material)
  {
    instance->materials.push_back(material);
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
    VkSurfaceFormatKHR surfaceFormat = instance->target->GetSurfaceFormat();
    instance->renderPass = CreateUniquePtr<RenderPass>(surfaceFormat.format);
  }
  
  
  void Renderer::BeginPass()
  {
    CANDY_CORE_ASSERT(vkResetFences(Vulkan::LogicalDevice(), 1, &GetCurrentFrame().renderFence) == VK_SUCCESS);
    RenderCommand::Reset();
    
    std::array<VkClearValue, 2> clearValues{};
    
    clearValues[0].color = { { 0.0f, 0.0f, 0.0f, 1.0f } };
    clearValues[1].depthStencil = {1.0f, 0};
    
    VkRenderPassBeginInfo rpInfo = BeginRenderPass();
    rpInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
    rpInfo.pClearValues = clearValues.data();
    
    GetCurrentFrame().commandBuffer.StartRenderPass(&rpInfo);
    /*for (auto& mat : instance->materials)
    {
      mat->Bind();
    }*/
    if (! instance->materials.empty())
    {
      instance->materials[0]->Bind();
    }
    
    SubmitWrites();
   
    RenderCommand::SetViewport(instance->target->swapChain->extent);
  }
  
  void Renderer::SubmitWrites()
  {
    if (! instance->writes.empty())
    {
      CANDY_CORE_INFO("SUBMITTING WRITES SIZE: {}", instance->writes.size());
      vkUpdateDescriptorSets(Vulkan::LogicalDevice(), instance->writes.size(), instance->writes.data(), 0, nullptr);
      instance->writes.clear();
    }
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