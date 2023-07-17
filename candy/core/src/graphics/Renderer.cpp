#include <candy/graphics/Renderer.hpp>
#include <candy/graphics/Vulkan.hpp>
namespace Candy::Graphics
{
  using namespace Math;
  const std::vector<Math::Vector2> vertices = {
  {-0.5f, -0.5f},
  {0.5f, -0.5f},
  {0.5f, 0.5f},
  {-0.5f, 0.5f}
  };
  
  const std::vector<Math::Vector3> colors = {
  {1.0f, 0.0f, 0.0f},
  {0.0f, 1.0f, 0.0f},
  {0.0f, 0.0f, 1.0f},
  {1.0f, 1.0f, 1.0f}
  };
  
  const std::vector<uint32_t> indices = {
  0, 1, 2, 2, 3, 0
  };
  Renderer::Renderer(GraphicsContext* context) : target(context)
  {
    
    
    //Shader
    shader = Shader::Create("assets/shaders/temp/test.glsl");
    
    //Buffers
    vertexArray = VertexArray::Create();
    
    BufferLayout layout;
    layout.AddElement(ShaderDataType::Float2, "inPosition");
    layout.AddElement(ShaderDataType::Float3, "inColor");
    
    SharedPtr<VertexBuffer> vertexBuffer = VertexBuffer::Create(&target->frames[0].commandBuffer, layout, vertices.size());
    
    CANDY_CORE_INFO("HI");
    uint64_t totalSize = layout.CalculateTotalComponentCount(vertices.size());
    float data[totalSize];
    for (int i=0, a=0; i<totalSize; i+=5, a++)
    {
      data[i] = vertices[a].x;
      data[i+1] = vertices[a].y;
      
      data[i+2] = colors[a].x;
      data[i+3] = colors[a].y;
      data[i+4] = colors[a].z;
    }
    
    vertexBuffer->SetData(data);
    
    SharedPtr<IndexBuffer> indexBuffer = IndexBuffer::Create(&target->frames[0].commandBuffer, (uint32_t *) indices.data(), indices.size());
    
    vertexArray->AddVertexBuffer(vertexBuffer);
    vertexArray->SetIndexBuffer(indexBuffer);
    
    graphicsPipeline.Create(vertexArray, shader, *target->renderPass);
  
  }
  
  
  
  
  void Renderer::UpdatePushConstants()
  {
    static auto startTime = std::chrono::high_resolution_clock::now();
    
    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
    
    UniformBufferObject ubo{};
    
    ubo.model = Matrix4::Rotate(Matrix4::IDENTITY, time * Math::ToRadians(90.0f), Math::Vector3(0.0f, 0.0f, 1.0f));
    ubo.view = Matrix4::LookAt(Vector3(2.0f, 2.0f, 2.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f));
    ubo.proj = Matrix4::Perspective(Math::ToRadians(45.0f), (float)target->swapChain->extent.width / (float) target->swapChain->extent.height, 0.1f, 10.0f);
    
    ubo.proj[1,1] *= -1;
    
    
    GetCurrentFrame().commandBuffer.PushConstants(graphicsPipeline.Layout(), ShaderStage::VERTEX, sizeof(UniformBufferObject), &ubo);
    
  }
  
  
  void Renderer::Draw()
  {
  
// Only reset the fence if we are submitting work
    
    //wait until the gpu has finished rendering the last frame. Timeout of 1 second
    //CANDY_CORE_ASSERT(vkWaitForFences(Vulkan::LogicalDevice(), 1, &GetCurrentFrame().renderFence, VK_TRUE, UINT64_MAX) == VK_SUCCESS);
    CANDY_CORE_ASSERT(vkResetFences(Vulkan::LogicalDevice(), 1, &GetCurrentFrame().renderFence) == VK_SUCCESS);
    
    GetCurrentFrame().commandBuffer.Reset();
    
    
    
    
    GetCurrentFrame().commandBuffer.StartRecording(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);
    
    
    VkClearValue clearValue;
   
    clearValue.color = { { 0.0f, 0.0f, 0.0f, 1.0f } };
    
    
    VkClearValue depthClear;
    depthClear.depthStencil.depth = 1.f;
    
    
    VkRenderPassBeginInfo rpInfo = target->BeginRenderPass();
    
   
    rpInfo.clearValueCount = 2;
    
    VkClearValue clearValues[] = { clearValue, depthClear };
    
    rpInfo.pClearValues = &clearValues[0];
    GetCurrentFrame().commandBuffer.StartRenderPass(&rpInfo);
    GetCurrentFrame().commandBuffer.BindPipeline(graphicsPipeline.Pipeline());
    GetCurrentFrame().commandBuffer.SetViewport(target->swapChain->extent);
    GetCurrentFrame().commandBuffer.Bind(vertexArray);
    UpdatePushConstants();
    //draw_objects(cmd, _renderables.data(), _renderables.size());
    GetCurrentFrame().commandBuffer.DrawIndexed(vertexArray);
    
    
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
    
    //prepare present
    // this will put the image we just rendered to into the visible window.
    // we want to wait on the _renderSemaphore for that,
    // as its necessary that drawing commands have finished before the image is displayed to the user
    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.pSwapchains = &target->swapChain->swapChain;
    presentInfo.swapchainCount = 1;
    
    presentInfo.pWaitSemaphores = &GetCurrentFrame().renderSemaphore;
    presentInfo.waitSemaphoreCount = 1;
    
    presentInfo.pImageIndices = &target->swapChain->imageIndex;
    
    VkResult result = vkQueuePresentKHR(Vulkan::LogicalDevice().graphicsQueue, &presentInfo);
    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR)
    {
      target->RebuildSwapChain();
    }
    else
    {
      CANDY_CORE_ASSERT(result == VK_SUCCESS, "failed to present swap chain image!");
    }
    
    target->UpdateFrameIndex();
    //currentFrameIndex = (currentFrameIndex + 1) % FRAME_OVERLAP;
  }
  
  FrameData& Renderer::GetCurrentFrame(){return target->GetCurrentFrame();}
  
  
  void Renderer::Shutdown()
  {
    vkDeviceWaitIdle(Vulkan::LogicalDevice());
    
    
   target->swapChain->Clean();
    
    vertexArray->Clear();
    
    
    graphicsPipeline.Destroy();
    
    
    
  }
}