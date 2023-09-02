#include <candy/graphics/RenderCommand.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <candy/graphics/Renderer2D.hpp>
#include <candy/graphics/Renderer3D.hpp>
namespace Candy::Graphics
{
  
  void RenderCommand::InitSyncStructures()
  {
    VkFenceCreateInfo uploadFenceCreateInfo{};
    uploadFenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    
    
    CANDY_CORE_ASSERT(vkCreateFence(Vulkan::LogicalDevice(), &uploadFenceCreateInfo, nullptr, &uploadContext.uploadFence)==VK_SUCCESS);
    Vulkan::DeletionQueue().Push(uploadContext.uploadFence);
    //Vulkan::PushDeleter([=](){vkDestroyFence(Vulkan::LogicalDevice(), uploadContext.uploadFence, nullptr);});
  }
  VulkanBuffer* RenderCommand::dummyBuffer=nullptr;
  UploadContext RenderCommand::uploadContext;
  VkCommandBufferBeginInfo RenderCommand::CommandBufferBeginInfo(VkCommandBufferUsageFlags flags)
  {
    VkCommandBufferBeginInfo info{};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    info.pNext = nullptr;
    
    info.pInheritanceInfo = nullptr;
    info.flags = flags;
    return info;
  }
  VkSubmitInfo RenderCommand::SubmitInfo(VkCommandBuffer* cmd)
  {
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
    QueueFamilyIndices queueFamilyIndices = Vulkan::PhysicalDevice().FindQueueFamilies(Vulkan::GetCurrentContext().GetSurface());
    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();
    //create pool for upload context
    CANDY_CORE_ASSERT(vkCreateCommandPool(Vulkan::LogicalDevice(), &poolInfo, nullptr, &uploadContext.commandPool)==VK_SUCCESS);
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
    CANDY_CORE_ASSERT(vkAllocateCommandBuffers(Vulkan::LogicalDevice(), &allocInfo, &uploadContext.commandBuffer)==VK_SUCCESS);
  }
  void RenderCommand::Init()
  {
    InitSyncStructures();
    InitCommands();
    Renderer2D::Init();
    Renderer3D::Init();
    dummyBuffer = new VulkanBuffer(BufferType::DUMMY);
    
    
  }
  
  CommandBuffer& RenderCommand::GetCommandBuffer()
  {
    return Vulkan::GetCurrentCommandBuffer();
  }
  VkDescriptorSet RenderCommand::GetGlobalDescriptorSet()
  {
    return Vulkan::GetCurrentContext().GetCurrentFrame().GlobalDescriptor();
  }
  
  FrameData& RenderCommand::GetFrame()
  {
    return Vulkan::GetCurrentContext().GetCurrentFrame();
  }
  void RenderCommand::ImmediateSubmit(std::function<void(VkCommandBuffer cmd)>&& function)
  {
    VkCommandBuffer cmd = uploadContext.commandBuffer;
    
    //begin the command buffer recording. We will use this command buffer exactly once before resetting, so we tell vulkan that
    VkCommandBufferBeginInfo cmdBeginInfo = CommandBufferBeginInfo(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);
    
    CANDY_CORE_ASSERT(vkBeginCommandBuffer(cmd, &cmdBeginInfo)==VK_SUCCESS);
    
    //execute the function
    function(cmd);
    
    CANDY_CORE_ASSERT(vkEndCommandBuffer(cmd)==VK_SUCCESS);
    
    VkSubmitInfo submit = SubmitInfo(&cmd);
    
    
    //submit command buffer to the queue and execute it.
    // uploadFence will now block until the graphic commands finish execution
    CANDY_CORE_ASSERT(vkQueueSubmit(Vulkan::LogicalDevice().graphicsQueue, 1, &submit, uploadContext.uploadFence)==VK_SUCCESS);
    
    vkWaitForFences(Vulkan::LogicalDevice(), 1, &uploadContext.uploadFence, true, 9999999999);
    vkResetFences(Vulkan::LogicalDevice(), 1, &uploadContext.uploadFence);
    
    // reset the command buffers inside the command pool
    vkResetCommandPool(Vulkan::LogicalDevice(), uploadContext.commandPool, 0);
  }
  void RenderCommand::DrawEmpty(uint32_t count)
  {
    GetCommandBuffer().DrawEmpty(count, *dummyBuffer);
  }
  void RenderCommand::DrawIndexed(const SharedPtr<VertexArray>& vertexArray, int32_t instanceCount, int32_t instanceIndex)
  {
    //vertexArray->Bind();
    GetCommandBuffer().DrawIndexed(vertexArray, instanceCount, instanceIndex);
  
  }
  
  void RenderCommand::DrawLines(const SharedPtr<VertexArray>& vertexArray, uint32_t count)
  {
    GetCommandBuffer().DrawLines(vertexArray, count);
  }
  void RenderCommand::BindPipeline(const Pipeline& pipeline)
  {
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
    GetCommandBuffer().BindVertexArray(vertexArray);
  }
  void RenderCommand::SetClearColor(Color color)
  {
    Renderer::SetClearColor(color);
  }
  void RenderCommand::SetClearColor(float r, float g, float b)
  {
    SetClearColor({r, g, b});
  }
  void RenderCommand::SetLineWidth(float value)
  {
    GetCommandBuffer().SetLineWidth(value);
  }
  
  void RenderCommand::BindDescriptorSets(const Pipeline& pipeline, uint32_t firstSet, const std::vector<VkDescriptorSet>& descriptorSets, const std::vector<uint32_t>& uniformOffsets)
  {
    GetCommandBuffer().BindDescriptorSets(pipeline.GetLayout(), firstSet, descriptorSets, uniformOffsets);
  }
  
  void RenderCommand::SetViewport(VkExtent2D extent)
  {
    GetCommandBuffer().SetViewport(extent);
  }
  void RenderCommand::SetViewport(const Math::Vector2u& size)
  {
    GetCommandBuffer().SetViewport(VkExtent2D{size.x, size.y});
  }
  void RenderCommand::SetViewport(uint32_t width, uint32_t height)
  {
    GetCommandBuffer().SetViewport(VkExtent2D{width, height});
  }
  void RenderCommand::SetViewport(const Math::Vector2u& position, const Math::Vector2u& size)
  {
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
    GetCommandBuffer().SetViewport(viewport);
  }
  void RenderCommand::SetUniform(uint32_t offset, uint32_t size, const void* data)
  {
    GetFrame().uniformBuffer->SetData(offset, size, data);
    //uint32_t paddedOffset = Vulkan::PhysicalDevice().PadUniformBufferSize(size);
    //BindDescriptorSet(pipeline, GetGlobalDescriptorSet(), offset);
    
  }
  void RenderCommand::CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height)
  {
    GetFrame().commandBuffer.CopyBufferToImage(buffer, image, width, height);
  }
  void RenderCommand::CopyImageToBuffer(VkImage image, VkBuffer buffer, uint32_t width, uint32_t height)
  {
    GetFrame().commandBuffer.CopyImageToBuffer(image, buffer, width, height);
  }
  void RenderCommand::TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout)
  {
    GetFrame().commandBuffer.TransitionImageLayout(image, format, oldLayout, newLayout);
  }
  void RenderCommand::PushConstants(VkPipelineLayout pipelineLayout, ShaderData::Stage stage, uint32_t dataSize, const void* data)
  {
    GetFrame().commandBuffer.PushConstants(pipelineLayout, stage, dataSize, data);
  }
  void RenderCommand::PushConstants(VkPipelineLayout pipelineLayout, ShaderData::Stage stage, uint32_t offset, uint32_t dataSize, const void* data)
  {
    GetFrame().commandBuffer.PushConstants(pipelineLayout, stage, offset, dataSize, data);
  }
  
  void RenderCommand::Reset()
  {
    GetFrame().commandBuffer.Reset();
    GetFrame().commandBuffer.StartRecording(VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT);
  }
  
  void RenderCommand::Submit()
  {
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
    
    
    CANDY_CORE_ASSERT(vkQueueSubmit(Vulkan::LogicalDevice().graphicsQueue, 1, &submitInfo, GetFrame().renderFence)==VK_SUCCESS);
  }
}