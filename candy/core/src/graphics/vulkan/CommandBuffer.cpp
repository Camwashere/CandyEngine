#include <candy/graphics/vulkan/CommandBuffer.hpp>
#include <CandyPch.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <candy/graphics/GraphicsContext.hpp>

namespace Candy::Graphics
{
  
  
  CommandBuffer::CommandBuffer(uint32_t currentFrame)
  {
    //CreateCommandPool(surface);
    //CreateCommandBuffers();
    
  }
  
  
  void CommandBuffer::Init(VkSurfaceKHR surface)
  {
    CreateCommandPool(surface);
    CreateCommandBuffers();
    for (int i = 0; i<activeBuffers.size(); i++)
    {
      activeBuffers[i] = false;
    }
    //activeBuffers[2] = false;
  }
  
  void CommandBuffer::CreateCommandPool(VkSurfaceKHR surface)
  {
    QueueFamilyIndices queueFamilyIndices = Vulkan::PhysicalDevice().FindQueueFamilies(surface);
    
    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();
    
    CANDY_CORE_ASSERT(vkCreateCommandPool(Vulkan::LogicalDevice(), &poolInfo, nullptr, &commandPool) == VK_SUCCESS, "Failed to create command pool!");
    Vulkan::DeletionQueue().Push(commandPool);
    //Vulkan::PushDeleter([=, this](){vkDestroyCommandPool(Vulkan::LogicalDevice(), this->commandPool, nullptr);});
  }
  
  void CommandBuffer::CreateCommandBuffers()
  {
    //commandBuffers.resize(MAX_FRAMES_IN_FLIGHT);
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = commandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = (uint32_t) commandBuffers.size();
    //allocInfo.commandBufferCount=1;
    
    //CANDY_CORE_ASSERT(vkAllocateCommandBuffers(Vulkan::LogicalDevice(), &allocInfo, &commandBuffers[currentFrame]) == VK_SUCCESS, "Failed to allocate command buffers!");
    CANDY_CORE_ASSERT(vkAllocateCommandBuffers(Vulkan::LogicalDevice(), &allocInfo, commandBuffers.data()) == VK_SUCCESS, "Failed to allocate command buffers!");
    
  }
  
  void CommandBuffer::SetCurrentBuffer(uint8_t index)
  {
    CANDY_CORE_ASSERT(index<commandBuffers.size(), "Index out of range!");
    currentBuffer = index;
    activeBuffers[index]=true;
    
  }
  
  void CommandBuffer::CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size)
  {
    VkCommandBuffer commandBuffer = BeginSingleTimeCommands();
    
    VkBufferCopy copyRegion{};
    copyRegion.srcOffset = 0; // Optional
    copyRegion.dstOffset = 0; // Optional
    copyRegion.size = size;
    vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);
    
    EndSingleTimeCommands(commandBuffer);
    
    
  }
  
  VkCommandBuffer CommandBuffer::BeginSingleTimeCommands()
  {
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = commandPool;
    allocInfo.commandBufferCount = 1;
    
    
    VkCommandBuffer commandBuffer;
    vkAllocateCommandBuffers(Vulkan::LogicalDevice(), &allocInfo, &commandBuffer);
    
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    
    vkBeginCommandBuffer(commandBuffer, &beginInfo);
    
    return commandBuffer;
  }
  
  void CommandBuffer::EndSingleTimeCommands(VkCommandBuffer commandBuffer)
  {
    vkEndCommandBuffer(commandBuffer);
    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;
    
    vkQueueSubmit(Vulkan::LogicalDevice().graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(Vulkan::LogicalDevice().graphicsQueue);
    
    vkFreeCommandBuffers(Vulkan::LogicalDevice(), commandPool, 1, &commandBuffer);
    
  }
  
  void CommandBuffer::TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout)
  {
    
    VkCommandBuffer commandBuffer = BeginSingleTimeCommands();
    
    VkImageMemoryBarrier barrier{};
    barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    barrier.oldLayout = oldLayout;
    barrier.newLayout = newLayout;
    
    barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    
    barrier.image = image;
    
    barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    barrier.subresourceRange.baseMipLevel = 0;
    barrier.subresourceRange.levelCount = 1;
    barrier.subresourceRange.baseArrayLayer = 0;
    barrier.subresourceRange.layerCount = 1;
    
    VkPipelineStageFlags sourceStage;
    VkPipelineStageFlags destinationStage;
    if (newLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL || GraphicsContext::IsDepthOnlyFormat(format))
    {
      barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
      
      if (GraphicsContext::HasStencilComponent(format))
      {
        barrier.subresourceRange.aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;
      }
    }
    else
    {
      barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    }
    if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL)
    {
      barrier.srcAccessMask = 0;
      barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
      
      sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
      destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    }
    else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL)
    {
      barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
      barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
      
      sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
      destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    }
    else if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL)
    {
      barrier.srcAccessMask = 0;
      barrier.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT|VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
      
      sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
      destinationStage = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
    }
    else if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL)
    {
      barrier.srcAccessMask = 0;
      barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
      
      sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
      destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT; // OR VK_PIPELINE_STAGE_VERTEX_SHADER_BIT, depending on usage
    }
    else if (oldLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL)
    {
      barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
      barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
      
      sourceStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
      destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    }
    else
    {
      CANDY_CORE_ASSERT(false, "Unsupported layout transition!");
      
    }
    
    vkCmdPipelineBarrier(commandBuffer, sourceStage, destinationStage, 0, 0, nullptr, 0, nullptr, 1, &barrier);
    
    
    EndSingleTimeCommands(commandBuffer);
  }
  
  
  void CommandBuffer::CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height)
  {
    VkCommandBuffer commandBuffer = BeginSingleTimeCommands();
    
    VkBufferImageCopy region{};
    region.bufferOffset = 0;
    region.bufferRowLength = 0;
    region.bufferImageHeight = 0;
    
    region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    region.imageSubresource.mipLevel = 0;
    region.imageSubresource.baseArrayLayer = 0;
    region.imageSubresource.layerCount = 1;
    
    region.imageOffset = {0, 0, 0};
    region.imageExtent = {width, height, 1};
    
    vkCmdCopyBufferToImage(commandBuffer, buffer, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);
    
    EndSingleTimeCommands(commandBuffer);
  }
  
  void CommandBuffer::CopyImageToBuffer(VkImage image, VkBuffer buffer, uint32_t width, uint32_t height)
  {
    VkCommandBuffer commandBuffer = BeginSingleTimeCommands();
    
    VkBufferImageCopy region{};
    region.bufferOffset = 0;
    region.bufferRowLength = 0; // Specifying 0 means tightly packed
    region.bufferImageHeight = 0; // Specifying 0 means tightly packed
    
    region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    region.imageSubresource.mipLevel = 0;
    region.imageSubresource.baseArrayLayer = 0;
    region.imageSubresource.layerCount = 1;
    
    region.imageOffset = {0, 0, 0};
    region.imageExtent = {width, height, 1};
    
    vkCmdCopyImageToBuffer(commandBuffer, image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, buffer, 1, &region);
    
    EndSingleTimeCommands(commandBuffer);
    
    commandBuffer = BeginSingleTimeCommands();

// Copy from image to buffer
    
    VkBufferMemoryBarrier barrier{};
    barrier.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
    barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT; // We have written to the buffer
    barrier.dstAccessMask = VK_ACCESS_HOST_READ_BIT; // Prepare for host read access
    barrier.buffer = buffer; // Buffer where the data was copied
    barrier.size = VK_WHOLE_SIZE; // Apply to entire buffer
    barrier.offset = 0;
    
    vkCmdPipelineBarrier(
    commandBuffer,
    VK_PIPELINE_STAGE_TRANSFER_BIT, // After the transfer stage
    VK_PIPELINE_STAGE_HOST_BIT, // Before the host operation
    0,
    0, nullptr,
    1, &barrier, // Buffer memory barrier
    0, nullptr
    );
    EndSingleTimeCommands(commandBuffer);
  }
  void CommandBuffer::CopyImageToBuffer(VkImage image, VkBuffer buffer, int x, int y, uint32_t width, uint32_t height)
  {
    VkCommandBuffer commandBuffer = BeginSingleTimeCommands();
    
    VkBufferImageCopy region{};
    region.bufferOffset = 0;
    region.bufferRowLength = 0; // Specifying 0 means tightly packed
    region.bufferImageHeight = 0; // Specifying 0 means tightly packed
    
    region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    region.imageSubresource.mipLevel = 0;
    region.imageSubresource.baseArrayLayer = 0;
    region.imageSubresource.layerCount = 1;
    
    region.imageOffset = {x, y, 0};
    region.imageExtent = {width, height, 1};
    
    
    vkCmdCopyImageToBuffer(commandBuffer, image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, buffer, 1, &region);
    
    EndSingleTimeCommands(commandBuffer);
    
    commandBuffer = BeginSingleTimeCommands();

// Copy from image to buffer
    
    VkBufferMemoryBarrier barrier{};
    barrier.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
    barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT; // We have written to the buffer
    barrier.dstAccessMask = VK_ACCESS_HOST_READ_BIT; // Prepare for host read access
    barrier.buffer = buffer; // Buffer where the data was copied
    barrier.size = VK_WHOLE_SIZE; // Apply to entire buffer
    barrier.offset = 0;
    
    vkCmdPipelineBarrier(
    commandBuffer,
    VK_PIPELINE_STAGE_TRANSFER_BIT, // After the transfer stage
    VK_PIPELINE_STAGE_HOST_BIT, // Before the host operation
    0,
    0, nullptr,
    1, &barrier, // Buffer memory barrier
    0, nullptr
    );
    EndSingleTimeCommands(commandBuffer);
  }
  
  void CommandBuffer::Reset()
  {
    CANDY_CORE_ASSERT(vkResetCommandBuffer(commandBuffers[currentBuffer], 0) == VK_SUCCESS, "Failed to reset command buffer!");
    activeBuffers[currentBuffer] = false;
  }
  
  void CommandBuffer::StartRecording(VkCommandBufferUsageFlags flags)
  {
    
    Reset();
    VkCommandBufferBeginInfo cmdBeginInfo{};
    cmdBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    cmdBeginInfo.flags = flags;
    cmdBeginInfo.pInheritanceInfo = nullptr;
    
    CANDY_CORE_ASSERT(vkBeginCommandBuffer(GetCurrentBuffer(), &cmdBeginInfo) == VK_SUCCESS);
    activeBuffers[currentBuffer] = true;
  }
  
  
  void CommandBuffer::StartRenderPass(const VkRenderPassBeginInfo *renderPassInfo)
  {
    vkCmdBeginRenderPass(GetCurrentBuffer(), renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
    activeBuffers[currentBuffer]=true;
  }
  
  VkCommandBuffer &CommandBuffer::GetCurrentBuffer()
  {
    return commandBuffers[currentBuffer];
  }
  
  VkCommandBuffer &CommandBuffer::GetViewportBuffer()
  {
    return commandBuffers[0];
  }
  
  VkCommandBuffer &CommandBuffer::GetSelectionBuffer()
  {
    return commandBuffers[1];
  }
  
  VkCommandBuffer &CommandBuffer::GetUIBuffer()
  {
    return commandBuffers[2];
  }
  
  const std::array<VkCommandBuffer, 4>& CommandBuffer::GetBuffers()
  {
    return commandBuffers;
  }
  std::vector<VkCommandBuffer> CommandBuffer::GetActiveBuffers()
  {
    std::vector<VkCommandBuffer> buffers;
    for (size_t i = 0; i < commandBuffers.size(); i++)
    {
      if (activeBuffers[i])
      {
        buffers.push_back(commandBuffers[i]);
      }
    }
    return buffers;
  }
  size_t CommandBuffer::GetBufferCount() const
  {
    //return GetBuffers().size();
    return commandBuffers.size();
  }
  
  void CommandBuffer::BindGraphicsPipeline(VkPipeline pipeline)
  {
    vkCmdBindPipeline(GetCurrentBuffer(), VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
  }
  
  void CommandBuffer::BindComputePipeline(VkPipeline pipeline)
  {
    vkCmdBindPipeline(GetCurrentBuffer(), VK_PIPELINE_BIND_POINT_COMPUTE, pipeline);
  }
  
  void CommandBuffer::SetViewport(VkExtent2D extent)
  {
    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = static_cast<float>(extent.width);
    viewport.height = static_cast<float>(extent.height);
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    
    
    VkRect2D scissor{};
    scissor.offset = {0, 0};
    scissor.extent = extent;
    
    vkCmdSetViewport(GetCurrentBuffer(), 0, 1, &viewport);
    vkCmdSetScissor(GetCurrentBuffer(), 0, 1, &scissor);
  }
  
  
  void CommandBuffer::SetViewport(VkViewport viewport)
  {
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    VkRect2D scissor{};
    scissor.offset.x = viewport.x;
    scissor.offset.y = viewport.y;
    scissor.extent = VkExtent2D(static_cast<uint32_t>(viewport.width), static_cast<uint32_t>(viewport.height));
    
    vkCmdSetViewport(GetCurrentBuffer(), 0, 1, &viewport);
    vkCmdSetScissor(GetCurrentBuffer(), 0, 1, &scissor);
  }
  
  void CommandBuffer::SetLineWidth(float value)
  {
    vkCmdSetLineWidth(GetCurrentBuffer(), value);
  }
  
  
  void CommandBuffer::BindVertexBuffers(const std::vector<VkBuffer> &vertexBuffers)
  {
    VkDeviceSize *offsets;
    memset(offsets, 0, vertexBuffers.size()*sizeof(VkDeviceSize));
    
    vkCmdBindVertexBuffers(GetCurrentBuffer(), 0, vertexBuffers.size(), vertexBuffers.data(), offsets);
  }
  
  void CommandBuffer::BindIndexBuffer(const IndexBuffer &indexBuffer)
  {
    vkCmdBindIndexBuffer(GetCurrentBuffer(), indexBuffer, 0, VK_INDEX_TYPE_UINT32);
    
  }
  
  /*void CommandBuffer::BindDescriptorSet(VkPipelineLayout layout, VkDescriptorSet descriptorSet, const uint32_t* uniformOffset)
  {
      vkCmdBindDescriptorSets(GetCurrentBuffer(), VK_PIPELINE_BIND_POINT_GRAPHICS, layout, 0, 1, &descriptorSet, 1, uniformOffset);
  }*/
  
  void CommandBuffer::BindDescriptorSets(VkPipelineLayout layout, uint32_t firstSet, const std::vector<VkDescriptorSet> &descriptorSets, const std::vector<uint32_t> &uniformOffsets)
  {
    //CANDY_CORE_INFO("descriptorSets.size()={0}, uniformOffsets.size()={1}", descriptorSets.size(), uniformOffsets.size());
    if (uniformOffsets.empty())
    {
      vkCmdBindDescriptorSets(GetCurrentBuffer(), VK_PIPELINE_BIND_POINT_GRAPHICS, layout, firstSet, descriptorSets.size(), descriptorSets.data(), 0, nullptr);
    }
    else
    {
      vkCmdBindDescriptorSets(GetCurrentBuffer(), VK_PIPELINE_BIND_POINT_GRAPHICS, layout, firstSet, descriptorSets.size(), descriptorSets.data(), uniformOffsets.size(), uniformOffsets.data());
    }
    
  }
  
  
  void CommandBuffer::BindVertexArray(const VertexArray *vertexArray)
  {
    
    VkBuffer data[vertexArray->vertexBuffers.size()];
    for (int i = 0; i<vertexArray->vertexBuffers.size(); i++)
    {
      data[i] = *vertexArray->vertexBuffers[i];
    }
    vkCmdBindVertexBuffers(GetCurrentBuffer(), 0, vertexArray->vertexBuffers.size(), data, vertexArray->vertexBufferOffsets.data());
    if (vertexArray->indexBuffer)
    {
      vkCmdBindIndexBuffer(GetCurrentBuffer(), *vertexArray->indexBuffer, 0, VK_INDEX_TYPE_UINT32);
    }
    
  }
  
  void CommandBuffer::DrawEmpty(uint32_t count, VkBuffer dummyBuffer)
  {
// Bind the dummy buffer
    size_t offset = 0;
    vkCmdBindVertexBuffers(GetCurrentBuffer(), 0, 1, &dummyBuffer, &offset);
    vkCmdDraw(GetCurrentBuffer(), count, 1, 0, 0);
  }
  
  void CommandBuffer::DrawIndexed(const SharedPtr<VertexArray> &vertexArray, int32_t instanceCount, int32_t instanceIndex)
  {
    vkCmdDrawIndexed(GetCurrentBuffer(), static_cast<uint32_t>(vertexArray->indexBuffer->GetCount()), instanceCount, 0, 0, instanceIndex);
  }
  void CommandBuffer::DrawLines(const SharedPtr<VertexArray>& vertexArray, uint32_t count)
  {
    vertexArray->Bind();
    vkCmdDraw(GetCurrentBuffer(), count, 1, 0, 0);
  }
  void CommandBuffer::EndRenderPass(uint8_t index)
  {
    CANDY_CORE_ASSERT(index<commandBuffers.size());
    if (activeBuffers[index])
    {
      vkCmdEndRenderPass(commandBuffers[index]);
    }
    //vkCmdEndRenderPass(commandBuffers[index]);
  }
  
  void CommandBuffer::EndRenderPasses()
  {
    for (int i = 0; i<commandBuffers.size(); i++)
    {
      if (activeBuffers[i])
      {
        vkCmdEndRenderPass(commandBuffers[i]);
      }
      
      
    }
    
    //vkCmdEndRenderPass(GetCurrentBuffer());
  }
  
  void CommandBuffer::EndRecording(uint8_t index)
  {
    CANDY_CORE_ASSERT(vkEndCommandBuffer(commandBuffers[index]) == VK_SUCCESS, "Failed to end record command buffer!");
    /*CANDY_CORE_ASSERT(vkEndCommandBuffer(commandBuffers[index]) == VK_SUCCESS, "Failed to end record command buffer!");
    activeBuffers[index]=false;*/
  }
  
  void CommandBuffer::EndRecordings()
  {
    for (int i=0; i<commandBuffers.size(); i++)
    {
      if (activeBuffers[i])
      {
        CANDY_CORE_ASSERT(vkEndCommandBuffer(commandBuffers[i]) == VK_SUCCESS, "Failed to record command buffer!");
      }
    }
    //activeBuffers={false, false, false};
    /*for (int i=0; i<commandBuffers.size(); i++)
    {
      CANDY_CORE_ASSERT(vkEndCommandBuffer(commandBuffers[i]) == VK_SUCCESS, "Failed to record command buffer!");
    }*/
    
  }
  
  void CommandBuffer::End(uint8_t index)
  {
    EndRenderPass(index);
    EndRecording(index);
  }
  
  
  void CommandBuffer::EndAll()
  {
    EndRenderPasses();
    EndRecordings();
  }
  
  void CommandBuffer::PushConstants(VkPipelineLayout layout, ShaderData::Stage shaderStage, uint32_t dataSize, const void *data)
  {
    vkCmdPushConstants(GetCurrentBuffer(), layout, ShaderData::StageToVulkan(shaderStage), 0, dataSize, data);
  }
  
  void CommandBuffer::PushConstants(VkPipelineLayout layout, ShaderData::Stage shaderStage, uint32_t offset, uint32_t dataSize, const void *data)
  {
    vkCmdPushConstants(GetCurrentBuffer(), layout, ShaderData::StageToVulkan(shaderStage), offset, dataSize, data);
  }
  
  /*void CommandBuffer::Destroy()
  {
    vkDestroyCommandPool(Vulkan::LogicalDevice(), commandPool, nullptr);
  }*/
}