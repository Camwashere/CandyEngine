#include <candy/graphics/RenderCommand.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <candy/graphics/Renderer2D.hpp>
#include <candy/graphics/Renderer3D.hpp>
#include <candy/graphics/texture/TextureManager.hpp>
#include <candy/graphics/shader/ShaderLibrary.hpp>
namespace Candy::Graphics
{
  
  void RenderCommand::InitSyncStructures()
  {
    CANDY_PROFILE_FUNCTION();
    VkFenceCreateInfo uploadFenceCreateInfo{};
    uploadFenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    
    
    CANDY_VULKAN_CHECK(vkCreateFence(Vulkan::LogicalDevice(), &uploadFenceCreateInfo, nullptr, &uploadContext.uploadFence));
    Vulkan::DeletionQueue().Push(uploadContext.uploadFence);
    //Vulkan::PushDeleter([=](){vkDestroyFence(Vulkan::LogicalDevice(), uploadContext.uploadFence, nullptr);});
  }
  VulkanBuffer* RenderCommand::dummyBuffer=nullptr;
  UploadContext RenderCommand::uploadContext;
  VkCommandBufferBeginInfo RenderCommand::CommandBufferBeginInfo(VkCommandBufferUsageFlags flags)
  {
    CANDY_PROFILE_FUNCTION();
    VkCommandBufferBeginInfo info{};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    info.pNext = nullptr;
    
    info.pInheritanceInfo = nullptr;
    info.flags = flags;
    return info;
  }
  VkSubmitInfo RenderCommand::SubmitInfo(VkCommandBuffer* cmd)
  {
    CANDY_PROFILE_FUNCTION();
    VkSubmitInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    info.pNext = nullptr;
    
    info.waitSemaphoreCount = 0;
    info.pWaitSemaphores = nullptr;
    info.pWaitDstStageMask = nullptr;
    info.commandBufferCount = 1;
    info.pCommandBuffers = cmd;
    info.signalSemaphoreCount = 0;
    info.pSignalSemaphores = nullptr;
    
    return info;
  }
  
  void RenderCommand::InitCommands()
  {
    CANDY_PROFILE_FUNCTION();
    QueueFamilyIndices queueFamilyIndices = Vulkan::PhysicalDevice().FindQueueFamilies(Vulkan::GetCurrentContext().GetSurface());
    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();
    //create pool for upload context
    CANDY_VULKAN_CHECK(vkCreateCommandPool(Vulkan::LogicalDevice(), &poolInfo, nullptr, &uploadContext.commandPool));
    Vulkan::DeletionQueue().Push<VkCommandPool>(uploadContext.commandPool);
    //Vulkan::PushDeleter([=](){vkDestroyCommandPool(Vulkan::LogicalDevice(), uploadContext.commandPool, nullptr);});
    
    
    //allocate the default command buffer that we will use for the instant commands
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = uploadContext.commandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    //allocInfo.commandBufferCount = (uint32_t) commandBuffers.size();
    allocInfo.commandBufferCount=1;
    
    VkCommandBuffer cmd;
    CANDY_VULKAN_CHECK(vkAllocateCommandBuffers(Vulkan::LogicalDevice(), &allocInfo, &uploadContext.commandBuffer));
  }
  void RenderCommand::Init()
  {
    CANDY_PROFILE_FUNCTION();
    InitSyncStructures();
    InitCommands();
    TextureManager::Init();
    ShaderLibrarySettings settings = ShaderLibrarySettings::Load("config/shader/librarySettings.yml");
    if (! ShaderLibrary::Init(settings))
    {
      CANDY_CORE_ASSERT(false, "Failed to initialize shader library");
    }
    
    Renderer2D::Init();
    Renderer3D::Init();
    dummyBuffer = new VulkanBuffer(BufferType::DUMMY);
    
    
  }
  
  CommandBuffer& RenderCommand::GetCommandBuffer()
  {
    CANDY_PROFILE_FUNCTION();
    return Vulkan::GetCurrentCommandBuffer();
  }
  VkDescriptorSet RenderCommand::GetGlobalDescriptorSet()
  {
    CANDY_PROFILE_FUNCTION();
    return Vulkan::GetCurrentContext().GetCurrentFrame().GlobalDescriptor();
  }
  
  FrameData& RenderCommand::GetFrame()
  {
    CANDY_PROFILE_FUNCTION();
    return Vulkan::GetCurrentContext().GetCurrentFrame();
  }
  void RenderCommand::ImmediateSubmit(std::function<void(VkCommandBuffer cmd)>&& function)
  {
    CANDY_PROFILE_FUNCTION();
    VkCommandBuffer cmd = uploadContext.commandBuffer;
    
    //begin the command buffer recording. We will use this command buffer exactly once before resetting, so we tell vulkan that
    VkCommandBufferBeginInfo cmdBeginInfo = CommandBufferBeginInfo(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);
    
    CANDY_VULKAN_CHECK(vkBeginCommandBuffer(cmd, &cmdBeginInfo));
    
    //execute the function
    function(cmd);
    
    CANDY_VULKAN_CHECK(vkEndCommandBuffer(cmd));
    
    VkSubmitInfo submit = SubmitInfo(&cmd);
    
    
    //submit command buffer to the queue and execute it.
    // uploadFence will now block until the graphic commands finish execution
    CANDY_VULKAN_CHECK(vkQueueSubmit(Vulkan::LogicalDevice().graphicsQueue, 1, &submit, uploadContext.uploadFence));
    
    vkWaitForFences(Vulkan::LogicalDevice(), 1, &uploadContext.uploadFence, true, 9999999999);
    vkResetFences(Vulkan::LogicalDevice(), 1, &uploadContext.uploadFence);
    
    // reset the command buffers inside the command pool
    vkResetCommandPool(Vulkan::LogicalDevice(), uploadContext.commandPool, 0);
  }
  void RenderCommand::DrawEmpty(uint32_t count)
  {
    CANDY_PROFILE_FUNCTION();
    GetCommandBuffer().DrawEmpty(count, *dummyBuffer);
  }
  void RenderCommand::DrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance)
  {
    CANDY_PROFILE_FUNCTION();
    GetCommandBuffer().DrawIndexed(indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
  }
  void RenderCommand::DrawIndexed(const SharedPtr<VertexArray>& vertexArray, int32_t instanceCount, int32_t instanceIndex)
  {
    CANDY_PROFILE_FUNCTION();
    //vertexArray->Bind();
    GetCommandBuffer().DrawIndexed(vertexArray, instanceCount, instanceIndex);
  
  }
  
  void RenderCommand::DrawLines(const SharedPtr<VertexArray>& vertexArray, uint32_t count)
  {
    CANDY_PROFILE_FUNCTION();
    GetCommandBuffer().DrawLines(vertexArray, count);
  }
  void RenderCommand::BindPipeline(const Pipeline& pipeline)
  {
    CANDY_PROFILE_FUNCTION();
    switch(pipeline.GetType())
    {
      case ShaderSettings::PipelineType::Graphics:
        GetCommandBuffer().BindGraphicsPipeline(pipeline);
        break;
      case ShaderSettings::PipelineType::Compute:
        GetCommandBuffer().BindComputePipeline(pipeline);
        break;
      default:
        CANDY_CORE_ASSERT(false, "Unknown pipeline type");
    }
  
  }
  
  void RenderCommand::BindVertexArray(const VertexArray* vertexArray)
  {
    CANDY_PROFILE_FUNCTION();
    GetCommandBuffer().BindVertexArray(vertexArray);
  }
  void RenderCommand::SetClearColor(Color color)
  {
    CANDY_PROFILE_FUNCTION();
    Renderer::SetClearColor(color);
  }
  void RenderCommand::SetClearColor(float r, float g, float b)
  {
    CANDY_PROFILE_FUNCTION();
    SetClearColor({r, g, b});
  }
  void RenderCommand::SetLineWidth(float value)
  {
    CANDY_PROFILE_FUNCTION();
    GetCommandBuffer().SetLineWidth(value);
  }
  
  void RenderCommand::BindDescriptorSets(const Pipeline& pipeline, uint32_t firstSet, const std::vector<VkDescriptorSet>& descriptorSets, const std::vector<uint32_t>& uniformOffsets)
  {
    CANDY_PROFILE_FUNCTION();
    GetCommandBuffer().BindDescriptorSets(pipeline.GetLayout(), firstSet, descriptorSets, uniformOffsets);
  }
  
  void RenderCommand::SetViewport(VkExtent2D extent)
  {
    CANDY_PROFILE_FUNCTION();
    GetCommandBuffer().SetViewport(extent);
  }
  void RenderCommand::SetViewport(const Math::Vector2u& size)
  {
    CANDY_PROFILE_FUNCTION();
    GetCommandBuffer().SetViewport(VkExtent2D{size.x, size.y});
  }
  void RenderCommand::SetViewport(uint32_t width, uint32_t height)
  {
    CANDY_PROFILE_FUNCTION();
    GetCommandBuffer().SetViewport(VkExtent2D{width, height});
  }
  void RenderCommand::SetViewport(const Math::Vector2u& position, const Math::Vector2u& size)
  {
    CANDY_PROFILE_FUNCTION();
    VkViewport viewport{};
    viewport.x = position.x;
    viewport.y = position.y;
    viewport.width = size.width;
    viewport.height = size.height;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    GetCommandBuffer().SetViewport(viewport);
  }
  void RenderCommand::SetViewport(VkViewport viewport)
  {
    CANDY_PROFILE_FUNCTION();
    GetCommandBuffer().SetViewport(viewport);
  }
  void RenderCommand::SetUniform(uint32_t offset, uint32_t size, const void* data)
  {
    CANDY_PROFILE_FUNCTION();
    GetFrame().uniformBuffer->SetData(offset, size, data);
    //uint32_t paddedOffset = Vulkan::PhysicalDevice().PadUniformBufferSize(size);
    //BindDescriptorSet(pipeline, GetGlobalDescriptorSet(), offset);
    
  }
  void RenderCommand::CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size)
  {
    GetCommandBuffer().CopyBuffer(srcBuffer, dstBuffer, size);
  }
  void RenderCommand::CopyBufferImmediate(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size)
  {
    CANDY_PROFILE_FUNCTION();
    ImmediateSubmit([=](VkCommandBuffer cmd)
                    {
                      VkBufferCopy copyRegion{};
                      copyRegion.srcOffset = 0; // Optional
                      copyRegion.dstOffset = 0; // Optional
                      copyRegion.size = size;
                      vkCmdCopyBuffer(cmd, srcBuffer, dstBuffer, 1, &copyRegion);
                    });
                    
    //GetCommandBuffer().CopyBufferImmediate(srcBuffer, dstBuffer, size);
    /*CommandBuffer* cmd = &Vulkan::GetCurrentContext().GetCurrentFrame().commandBuffer;
    
    VkCommandBuffer commandBuffer = cmd->BeginSingleTimeCommands();
    
    VkBufferCopy copyRegion{};
    copyRegion.srcOffset = 0; // Optional
    copyRegion.dstOffset = 0; // Optional
    copyRegion.size = size;
    vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);
    
    cmd->EndSingleTimeCommands(commandBuffer);*/
  }
  void RenderCommand::CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height)
  {
    CANDY_PROFILE_FUNCTION();
    GetFrame().commandBuffer.CopyBufferToImage(buffer, image, width, height);
  }
  void RenderCommand::CopyImageToBuffer(VkImage image, VkBuffer buffer, uint32_t width, uint32_t height)
  {
    CANDY_PROFILE_FUNCTION();
    GetFrame().commandBuffer.CopyImageToBuffer(image, buffer, width, height);
  }
  void RenderCommand::TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout)
  {
    CANDY_PROFILE_FUNCTION();
    GetFrame().commandBuffer.TransitionImageLayout(image, format, oldLayout, newLayout);
  }
  void RenderCommand::PushConstants(VkPipelineLayout pipelineLayout, ShaderData::Stage stage, uint32_t dataSize, const void* data)
  {
    CANDY_PROFILE_FUNCTION();
    GetFrame().commandBuffer.PushConstants(pipelineLayout, stage, dataSize, data);
  }
  void RenderCommand::PushConstants(VkPipelineLayout pipelineLayout, ShaderData::Stage stage, uint32_t offset, uint32_t dataSize, const void* data)
  {
    CANDY_PROFILE_FUNCTION();
    GetFrame().commandBuffer.PushConstants(pipelineLayout, stage, offset, dataSize, data);
  }
  
  void RenderCommand::Reset()
  {
    CANDY_PROFILE_FUNCTION();
    GetCommandBuffer().Reset();
    GetCommandBuffer().StartRecording(VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT);
  }
  
  void RenderCommand::ResetUtility()
  {
    CANDY_PROFILE_FUNCTION();
    GetCommandBuffer().ResetUtility();
  }
  
  
  /*VkSubmitInfo submitInfo{};
  submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submitInfo.commandBufferCount = 1;
  submitInfo.pCommandBuffers = &commandBuffer;
  
  vkQueueSubmit(Vulkan::LogicalDevice().graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
  vkQueueWaitIdle(Vulkan::LogicalDevice().graphicsQueue);*/
  void RenderCommand::Submit()
  {
    CANDY_PROFILE_FUNCTION();
    GetCommandBuffer().EndAll();
    //GetCommandBuffer().EndRecording();
    std::vector<VkCommandBuffer> activeBuffers = GetCommandBuffer().GetActiveBuffers();
    
    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount=activeBuffers.size();
    submitInfo.pCommandBuffers = activeBuffers.data();
    
    
    
    VkPipelineStageFlags waitStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    
    submitInfo.pWaitDstStageMask = &waitStage;
    
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = &GetFrame().presentSemaphore;
    
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = &GetFrame().renderSemaphore;
    
    
    CANDY_VULKAN_CHECK(vkQueueSubmit(Vulkan::LogicalDevice().graphicsQueue, 1, &submitInfo, GetFrame().renderFence));
  }
}