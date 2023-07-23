#include <candy/graphics/Renderer.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <candy/graphics/vulkan/VulkanBuffer.hpp>
#include <candy/graphics/vulkan/Image.hpp>
namespace Candy::Graphics
{
  using namespace Math;
  const std::vector<Math::Vector3> vertices = {
  {-0.5f, -0.5f, 0.0f},
  {0.5f, -0.5f, 0.0f},
  {0.5f, 0.5f, 0.0f},
  {-0.5f, 0.5f, 0.0f},
  
  // SECOND SQUARE
    {-0.5f, -0.5f, -0.5f},
    {0.5f, -0.5f, -0.5f},
    {0.5f, 0.5f, -0.5f},
    {-0.5f, 0.5f, -0.5f}
  };
  
  const std::vector<Math::Vector3> colors = {
  {1.0f, 0.0f, 0.0f},
  {0.0f, 1.0f, 0.0f},
  {0.0f, 0.0f, 1.0f},
  {1.0f, 1.0f, 1.0f},
  
  //SECOND SQUARE
  {1.0f, 0.0f, 0.0f},
  {0.0f, 1.0f, 0.0f},
  {0.0f, 0.0f, 1.0f},
  {1.0f, 1.0f, 1.0f}
  };
  
  const std::vector<Math::Vector2> uvs = {
    {1.0f, 0.0f},
    {0.0f, 0.0f},
    {0.0f, 1.0f},
    {1.0f, 1.0f},
    
    //SECOND SQUARE
    {1.0f, 0.0f},
    {0.0f, 0.0f},
    {0.0f, 1.0f},
    {1.0f, 1.0f}
  };
  
  const std::vector<uint32_t> indices = {
  0, 1, 2, 2, 3, 0,
  //SECOND SQUARE
  4, 5, 6, 6, 7, 4
  };
  Renderer::Renderer(GraphicsContext* context) : target(context)
  {
    
    //Shader
    shader = Shader::Create("assets/shaders/temp/test.glsl");
    texture.Load("assets/textures/statue.jpg", GetCurrentFrame().commandBuffer);
    textureImageView.Set(texture);
    texture.CreateSampler();
    
    //Buffers
    vertexArray = VertexArray::Create();
    
    BufferLayout layout;
    layout.AddElement(ShaderData::Type::Float3, "inPosition");
    layout.AddElement(ShaderData::Type::Float3, "inColor");
    layout.AddElement(ShaderData::Type::Float2, "inTexCoord");
    
    SharedPtr<VertexBuffer> vertexBuffer = VertexBuffer::Create(&target->frames[0].commandBuffer, layout, vertices.size());
    
    
    uint64_t totalSize = layout.CalculateTotalComponentCount(vertices.size());
    float data[totalSize];
    for (int i=0, a=0; i<totalSize; i+=8, a++)
    {
      data[i] = vertices[a].x;
      data[i+1] = vertices[a].y;
      data[i+2] = vertices[a].z;
      
      data[i+3] = colors[a].x;
      data[i+4] = colors[a].y;
      data[i+5] = colors[a].z;
      
      data[i+6] = uvs[a].x;
      data[i+7] = uvs[a].y;
    }
    
    vertexBuffer->SetData(data);
    
    SharedPtr<IndexBuffer> indexBuffer = IndexBuffer::Create(&target->frames[0].commandBuffer, (uint32_t *) indices.data(), indices.size());
    
    vertexArray->AddVertexBuffer(vertexBuffer);
    vertexArray->SetIndexBuffer(indexBuffer);
    CANDY_CORE_INFO("Uniform buffer obj size: {}", sizeof(UniformBufferObject));
    //pipeline.GetLayout().AddDescriptorSetLayout(descriptorSetLayout);
    pipeline.AddDynamicStates({VK_DYNAMIC_STATE_VIEWPORT,
                               VK_DYNAMIC_STATE_SCISSOR});
    
    pipeline.Bake(vertexArray, shader, *target->renderPass);
    
    CreateUniformBuffers();
    CreateDescriptorPool();
    CreateDescriptorSets();
    
    
  
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
    
    
    GetCurrentFrame().commandBuffer.PushConstants(pipeline.GetLayout(), ShaderStage::VERTEX, sizeof(UniformBufferObject), &ubo);
    
  }
  
  
  void Renderer::CreateDescriptorPool()
  {
    std::array<VkDescriptorPoolSize, 2> poolSizes{};
    poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    poolSizes[0].descriptorCount = static_cast<uint32_t>(FRAME_OVERLAP);
    poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    poolSizes[1].descriptorCount = static_cast<uint32_t>(FRAME_OVERLAP);
    
    VkDescriptorPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
    poolInfo.pPoolSizes = poolSizes.data();
    poolInfo.maxSets = static_cast<uint32_t>(FRAME_OVERLAP);
    
    
    CANDY_CORE_ASSERT(vkCreateDescriptorPool(Vulkan::LogicalDevice(), &poolInfo, nullptr, &descriptorPool) == VK_SUCCESS, "Failed to create descriptor pooL!");
    
  }
  
  void Renderer::CreateDescriptorSets()
  {
    std::vector<VkDescriptorSetLayout> layouts(FRAME_OVERLAP, shader->GetDescriptorSetLayout());
    VkDescriptorSetAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = descriptorPool;
    allocInfo.descriptorSetCount = static_cast<uint32_t>(FRAME_OVERLAP);
    allocInfo.pSetLayouts = layouts.data();
    
    
    
    descriptorSets.resize(FRAME_OVERLAP);
    
    
    CANDY_CORE_ASSERT(vkAllocateDescriptorSets(Vulkan::LogicalDevice(), &allocInfo, descriptorSets.data()) == VK_SUCCESS, "Failed to allocate descriptor sets!");
    
    for (size_t i=0; i<FRAME_OVERLAP; i++)
    {
      VkDescriptorBufferInfo bufferInfo{};
      bufferInfo.buffer = *uniformBuffers[i];
      bufferInfo.offset = 0;
      bufferInfo.range = sizeof(UniformBufferObject);
      
      VkDescriptorImageInfo imageInfo{};
      imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
      imageInfo.imageView = textureImageView;
      imageInfo.sampler = texture.GetSampler();
      
      std::array<VkWriteDescriptorSet, 2> descriptorWrites{};
      
      descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
      descriptorWrites[0].dstSet = descriptorSets[i];
      descriptorWrites[0].dstBinding = 0;
      descriptorWrites[0].dstArrayElement = 0;
      descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
      descriptorWrites[0].descriptorCount = 1;
      descriptorWrites[0].pBufferInfo = &bufferInfo;
      
      descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
      descriptorWrites[1].dstSet = descriptorSets[i];
      descriptorWrites[1].dstBinding = 1;
      descriptorWrites[1].dstArrayElement = 0;
      descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
      descriptorWrites[1].descriptorCount = 1;
      descriptorWrites[1].pImageInfo = &imageInfo;
        
      vkUpdateDescriptorSets(Vulkan::LogicalDevice(), static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
    }
    
    
  }

  
  void Renderer::CreateUniformBuffers()
  {
    VkDeviceSize bufferSize = sizeof(UniformBufferObject);
    
    uniformBuffers.resize(FRAME_OVERLAP);
    
    for (size_t i = 0; i < FRAME_OVERLAP; i++)
    {
      uniformBuffers[i] = UniformBuffer::Create(bufferSize);
    }
    
  }
  
  void Renderer::UpdateUniformBuffer()
  {
    Color color = Color::blue;
    uniformBuffers[target->currentFrameIndex]->SetData(&color[0]);
  }
  void Renderer::Draw()
  {
    
    CANDY_CORE_ASSERT(vkResetFences(Vulkan::LogicalDevice(), 1, &GetCurrentFrame().renderFence) == VK_SUCCESS);
    
    GetCurrentFrame().commandBuffer.Reset();
    GetCurrentFrame().commandBuffer.StartRecording(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);
    
    std::array<VkClearValue, 2> clearValues{};
    
    clearValues[0].color = { { 0.0f, 0.0f, 0.0f, 1.0f } };
    clearValues[1].depthStencil = {1.0f, 0};
    
    VkRenderPassBeginInfo rpInfo = target->BeginRenderPass();
    rpInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
    rpInfo.pClearValues = clearValues.data();
    
    GetCurrentFrame().commandBuffer.StartRenderPass(&rpInfo);
    GetCurrentFrame().commandBuffer.BindPipeline(pipeline);
    GetCurrentFrame().commandBuffer.SetViewport(target->swapChain->extent);
    GetCurrentFrame().commandBuffer.Bind(vertexArray);
    UpdatePushConstants();
    UpdateUniformBuffer();
    GetCurrentFrame().commandBuffer.BindDescriptorSets(pipeline.GetLayout(), descriptorSets[target->currentFrameIndex]);
    
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
  }
  
  FrameData& Renderer::GetCurrentFrame(){return target->GetCurrentFrame();}
  
  
  void Renderer::Shutdown()
  {
    vkDeviceWaitIdle(Vulkan::LogicalDevice());
    
    
   target->swapChain->Clean();
   textureImageView.Destroy();
   texture.Destroy();
    for (size_t i = 0; i < FRAME_OVERLAP; i++)
    {
      uniformBuffers[i]->Destroy();
    }
    vkDestroyDescriptorPool(Vulkan::LogicalDevice(), descriptorPool, nullptr);
    vkDestroyDescriptorSetLayout(Vulkan::LogicalDevice(), shader->GetDescriptorSetLayout(), nullptr);
    
    vertexArray->Clear();
    
    pipeline.Destroy();
    
  }
}