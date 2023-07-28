#include <candy/graphics/Renderer.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <candy/graphics/vulkan/VulkanBuffer.hpp>
#include <candy/app/Application.hpp>
namespace Candy::Graphics
{
  using namespace Math;
  
  Renderer::Renderer() : target(nullptr)
  {
    pipeline.AddDynamicStates({VK_DYNAMIC_STATE_VIEWPORT,VK_DYNAMIC_STATE_SCISSOR});
  }

  
  Renderer Renderer::instance;
  
  void Renderer::Submit(Material* material)
  {
    instance.pipeline.Bake(material, *instance.target->renderPass);
  }
  void Renderer::Start()
  {
    instance.target->SwapBuffers();
    Renderer::BeginPass();
  }
 
  void Renderer::SetTarget(GraphicsContext* target)
  {
    instance.target = target;
  }
  void Renderer::BeginPass()
  {
    CANDY_CORE_ASSERT(vkResetFences(Vulkan::LogicalDevice(), 1, &GetCurrentFrame().renderFence) == VK_SUCCESS);
    
    GetCurrentFrame().commandBuffer.Reset();
    GetCurrentFrame().commandBuffer.StartRecording(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);
    
    std::array<VkClearValue, 2> clearValues{};
    
    clearValues[0].color = { { 0.0f, 0.0f, 0.0f, 1.0f } };
    clearValues[1].depthStencil = {1.0f, 0};
    
    VkRenderPassBeginInfo rpInfo = instance.target->BeginRenderPass();
    rpInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
    rpInfo.pClearValues = clearValues.data();
    
    GetCurrentFrame().commandBuffer.StartRenderPass(&rpInfo);
    GetCurrentFrame().commandBuffer.BindPipeline(instance.pipeline);
    GetCurrentFrame().commandBuffer.SetViewport(instance.target->swapChain->extent);
  }
  
  void Renderer::EndPass()
  {
    GetCurrentFrame().commandBuffer.EndRenderPass();
    GetCurrentFrame().commandBuffer.EndRecording();
    
    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount=1;
    submitInfo.pCommandBuffers = &GetCurrentFrame().commandBuffer.mainCommandBuffer;
    VkPipelineStageFlags waitStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    
    submitInfo.pWaitDstStageMask = &waitStage;
    
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = &GetCurrentFrame().presentSemaphore;
    
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = &GetCurrentFrame().renderSemaphore;
    
    
    CANDY_CORE_ASSERT(vkQueueSubmit(Vulkan::LogicalDevice().graphicsQueue, 1, &submitInfo, GetCurrentFrame().renderFence)==VK_SUCCESS);
  }
  

  void Renderer::BindDescriptorSets(uint32_t uniformOffset)
  {
    //uint32_t uniformOffset = paddedOffset * instance.target->currentFrameIndex;
    GetCurrentFrame().commandBuffer.BindDescriptorSets(instance.pipeline.GetLayout(), GetCurrentFrame().globalDescriptor, &uniformOffset);
  }
  
  void Renderer::SetUniform(uint32_t offset, uint32_t size, const void* data)
  {
    GetCurrentFrame().uniformBuffer->SetData(offset, size, data);
    //uint32_t paddedOffset = Vulkan::PhysicalDevice().PadUniformBufferSize(size);
    BindDescriptorSets(offset);
  
  }
  void Renderer::DrawIndexed(const SharedPtr<VertexArray>& vertexArray)
  {
    GetCurrentFrame().commandBuffer.DrawIndexed(vertexArray);
  }
  FrameData& Renderer::GetCurrentFrame(){return instance.target->GetCurrentFrame();}
  
  void Renderer::PushConstants(ShaderData::Stage stage, uint32_t dataSize, const void* data)
  {
    GetCurrentFrame().commandBuffer.PushConstants(instance.pipeline.GetLayout(), stage, dataSize, data);
  }
  void Renderer::PushConstants(ShaderData::Stage stage, uint32_t offset, uint32_t dataSize, const void* data)
  {
    GetCurrentFrame().commandBuffer.PushConstants(instance.pipeline.GetLayout(), stage, offset, dataSize, data);
  }
  void Renderer::Shutdown()
  {
    //vkDeviceWaitIdle(Vulkan::LogicalDevice());
    
    
   //instance.target->swapChain->Clean();
   /*textureImageView.Destroy();
   texture.Destroy();
   uniformBuffer->Destroy();
    for (size_t i = 0; i < FRAME_OVERLAP; i++)
    {
      //uniformBuffers[i]->Destroy();
    }
    //descriptorAllocator.Destroy();
    //descriptorLayoutCache.Destroy();
    //vkDestroyDescriptorPool(Vulkan::LogicalDevice(), descriptorPool, nullptr);
    vkDestroyDescriptorSetLayout(Vulkan::LogicalDevice(), shader->GetDescriptorSetLayout(), nullptr);
    
    vertexArray->Clear();*/
    
    instance.pipeline.Destroy();
    
    CANDY_CORE_INFO("SHUTDOWN RENDERER");
    
  }
}