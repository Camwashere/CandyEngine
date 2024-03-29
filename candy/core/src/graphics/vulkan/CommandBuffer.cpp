#include <candy/graphics/vulkan/CommandBuffer.hpp>
#include <CandyPch.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <candy/graphics/GraphicsContext.hpp>
#include <candy/graphics/vulkan/DeletionQueue.hpp>
namespace Candy::Graphics
{
  
  
  CommandBuffer::CommandBuffer(uint32_t currentFrame)
  {
    //CreateCommandPool(surface);
    //CreateCommandBuffers();
    
  }
  
  
  void CommandBuffer::Init(VkSurfaceKHR surface)
  {
    CANDY_PROFILE_FUNCTION();
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
    CANDY_PROFILE_FUNCTION();
    QueueFamilyIndices queueFamilyIndices = Vulkan::LogicalDevice().GetQueueFamilyIndices();
    
    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();
    
    CANDY_VULKAN_CHECK(vkCreateCommandPool(Vulkan::LogicalDevice(), &poolInfo, nullptr, &commandPool));
    Vulkan::DeletionQueue().Push(commandPool);
    
  }
  
  void CommandBuffer::CreateCommandBuffers()
  {
    CANDY_PROFILE_FUNCTION();
    
    
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = commandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = (uint32_t) commandBuffers.size();
    
    
    
    
    CANDY_VULKAN_CHECK(vkAllocateCommandBuffers(Vulkan::LogicalDevice(), &allocInfo, commandBuffers.data()));
    
  }
  
  void CommandBuffer::SetCurrentBuffer(uint8_t index)
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_ASSERT(index<commandBuffers.size(), "Index out of range!");
    currentBuffer = index;
    activeBuffers[index]=true;
    
  }
  void CommandBuffer::CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size, VkDeviceSize srcOffset, VkDeviceSize dstOffset)
  {
    CANDY_PROFILE_FUNCTION();
    
   
  }
  void CommandBuffer::CopyBufferImmediate(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size)
  {
    CANDY_PROFILE_FUNCTION();
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
    CANDY_PROFILE_FUNCTION();
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
    CANDY_PROFILE_FUNCTION();
    vkEndCommandBuffer(commandBuffer);
    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;
    
    vkQueueSubmit(Vulkan::LogicalDevice().graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(Vulkan::LogicalDevice().graphicsQueue);
    
    vkFreeCommandBuffers(Vulkan::LogicalDevice(), commandPool, 1, &commandBuffer);
    
  }
  
  
  
  void CommandBuffer::Reset()
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_VULKAN_CHECK(vkResetCommandBuffer(commandBuffers[currentBuffer], 0));
    activeBuffers[currentBuffer] = false;
  }
  
  void CommandBuffer::ResetUtility()
  {
    CANDY_PROFILE_FUNCTION();
    
    /*CANDY_VULKAN_CHECK(vkResetCommandBuffer(utilityBuffer, 0));
    
    
    VkCommandBufferBeginInfo cmdBeginInfo{};
    cmdBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    cmdBeginInfo.flags = 0;
    cmdBeginInfo.pInheritanceInfo = nullptr;
    
    CANDY_VULKAN_CHECK(vkBeginCommandBuffer(utilityBuffer, &cmdBeginInfo));*/
    
    
  }
  
  void CommandBuffer::StartRecording(VkCommandBufferUsageFlags flags)
  {
    CANDY_PROFILE_FUNCTION();
    Reset();
    VkCommandBufferBeginInfo cmdBeginInfo{};
    cmdBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    cmdBeginInfo.flags = flags;
    cmdBeginInfo.pInheritanceInfo = nullptr;
    
    CANDY_VULKAN_CHECK(vkBeginCommandBuffer(GetCurrentBuffer(), &cmdBeginInfo));
    activeBuffers[currentBuffer] = true;
  }
  
  
  void CommandBuffer::StartRenderPass(const VkRenderPassBeginInfo *renderPassInfo)
  {
    CANDY_PROFILE_FUNCTION();
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
  
  VkCommandBuffer& CommandBuffer::GetOverlayBuffer()
  {
    return commandBuffers[1];
  }
  
  VkCommandBuffer &CommandBuffer::GetSelectionBuffer()
  {
    return commandBuffers[2];
  }
  
  VkCommandBuffer &CommandBuffer::GetUIBuffer()
  {
    return commandBuffers[3];
  }
  /*VkCommandBuffer& CommandBuffer::GetUtilityBuffer()
  {
    return utilityBuffer;
  }*/
  const std::array<VkCommandBuffer, 4>& CommandBuffer::GetBuffers()
  {
    return commandBuffers;
  }
  std::vector<VkCommandBuffer> CommandBuffer::GetActiveBuffers()
  {
    CANDY_PROFILE_FUNCTION();
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
    CANDY_PROFILE_FUNCTION();
    vkCmdBindPipeline(GetCurrentBuffer(), VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
  }
  
  void CommandBuffer::BindComputePipeline(VkPipeline pipeline)
  {
    CANDY_PROFILE_FUNCTION();
    vkCmdBindPipeline(GetCurrentBuffer(), VK_PIPELINE_BIND_POINT_COMPUTE, pipeline);
  }
  
  void CommandBuffer::SetViewport(VkExtent2D extent)
  {
    CANDY_PROFILE_FUNCTION();
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
    CANDY_PROFILE_FUNCTION();
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
    CANDY_PROFILE_FUNCTION();
    vkCmdSetLineWidth(GetCurrentBuffer(), value);
  }
  
  
  void CommandBuffer::BindVertexBuffers(const std::vector<VkBuffer> &vertexBuffers)
  {
    CANDY_PROFILE_FUNCTION();
    VkDeviceSize *offsets;
    memset(offsets, 0, vertexBuffers.size()*sizeof(VkDeviceSize));
    
    vkCmdBindVertexBuffers(GetCurrentBuffer(), 0, vertexBuffers.size(), vertexBuffers.data(), offsets);
  }
  
  void CommandBuffer::BindIndexBuffer(const IndexBuffer &indexBuffer)
  {
    CANDY_PROFILE_FUNCTION();
    vkCmdBindIndexBuffer(GetCurrentBuffer(), indexBuffer, 0, VK_INDEX_TYPE_UINT32);
    
  }
  
  /*void CommandBuffer::BindDescriptorSet(VkPipelineLayout layout, VkDescriptorSet descriptorSet, const uint32_t* uniformOffset)
  {
      vkCmdBindDescriptorSets(GetCurrentBuffer(), VK_PIPELINE_BIND_POINT_GRAPHICS, layout, 0, 1, &descriptorSet, 1, uniformOffset);
  }*/
  
  void CommandBuffer::BindDescriptorSets(VkPipelineLayout layout, uint32_t firstSet, const std::vector<VkDescriptorSet> &descriptorSets, const std::vector<uint32_t> &uniformOffsets)
  {
    CANDY_PROFILE_FUNCTION();
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
    CANDY_PROFILE_FUNCTION();
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
    CANDY_PROFILE_FUNCTION();
// Bind the dummy buffer
    size_t offset = 0;
    vkCmdBindVertexBuffers(GetCurrentBuffer(), 0, 1, &dummyBuffer, &offset);
    vkCmdDraw(GetCurrentBuffer(), count, 1, 0, 0);
  }
  void CommandBuffer::DrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance)
  {
    CANDY_PROFILE_FUNCTION();
    vkCmdDrawIndexed(GetCurrentBuffer(), indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
  }
  void CommandBuffer::DrawIndexed(const SharedPtr<VertexArray> &vertexArray, int32_t instanceCount, int32_t instanceIndex)
  {
    CANDY_PROFILE_FUNCTION();
    vkCmdDrawIndexed(GetCurrentBuffer(), static_cast<uint32_t>(vertexArray->indexBuffer->GetCount()), instanceCount, 0, 0, instanceIndex);
  }
  void CommandBuffer::DrawLines(const SharedPtr<VertexArray>& vertexArray, uint32_t count)
  {
    CANDY_PROFILE_FUNCTION();
    vertexArray->Bind();
    vkCmdDraw(GetCurrentBuffer(), count, 1, 0, 0);
  }
  void CommandBuffer::EndRenderPass(uint8_t index)
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_ASSERT(index<commandBuffers.size());
    if (activeBuffers[index])
    {
      vkCmdEndRenderPass(commandBuffers[index]);
    }
    //vkCmdEndRenderPass(commandBuffers[index]);
  }
  
  void CommandBuffer::EndRenderPasses()
  {
    CANDY_PROFILE_FUNCTION();
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
    CANDY_PROFILE_FUNCTION();
    CANDY_VULKAN_CHECK(vkEndCommandBuffer(commandBuffers[index]));
    /*CANDY_CORE_ASSERT(vkEndCommandBuffer(commandBuffers[index]) == VK_SUCCESS, "Failed to end record command buffer!");
    activeBuffers[index]=false;*/
  }
  
  void CommandBuffer::EndRecordings()
  {
    CANDY_PROFILE_FUNCTION();
    for (int i=0; i<commandBuffers.size(); i++)
    {
      if (activeBuffers[i])
      {
        CANDY_VULKAN_CHECK(vkEndCommandBuffer(commandBuffers[i]));
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
    CANDY_PROFILE_FUNCTION();
    EndRenderPass(index);
    EndRecording(index);
  }
  
  void CommandBuffer::EndUtility()
  {
    //CANDY_VULKAN_CHECK(vkEndCommandBuffer(utilityBuffer));
  }
  
  void CommandBuffer::EndAll()
  {
    CANDY_PROFILE_FUNCTION();
    EndRenderPasses();
    EndRecordings();
    EndUtility();
  }
  
  void CommandBuffer::PushConstants(VkPipelineLayout layout, ShaderData::Stage shaderStage, uint32_t dataSize, const void *data)
  {
    CANDY_PROFILE_FUNCTION();
    vkCmdPushConstants(GetCurrentBuffer(), layout, ShaderData::StageToVulkan(shaderStage), 0, dataSize, data);
  }
  
  void CommandBuffer::PushConstants(VkPipelineLayout layout, ShaderData::Stage shaderStage, uint32_t offset, uint32_t dataSize, const void *data)
  {
    CANDY_PROFILE_FUNCTION();
    vkCmdPushConstants(GetCurrentBuffer(), layout, ShaderData::StageToVulkan(shaderStage), offset, dataSize, data);
  }
  
  
}