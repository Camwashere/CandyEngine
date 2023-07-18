#include <candy/graphics/vulkan/CommandBuffer.hpp>
#include <CandyPch.hpp>
#include <candy/graphics/Vulkan.hpp>
namespace Candy::Graphics
{
   
    
    CommandBuffer::CommandBuffer(uint32_t currentFrame)
    {
        //CreateCommandPool(surface);
        //CreateCommandBuffers();
    }
    
    CommandBuffer::~CommandBuffer()
    {
        //Destroy();
    }
  
  void CommandBuffer::Init(VkSurfaceKHR surface)
  {
      CreateCommandPool(surface);
      CreateCommandBuffers();
  }
    void CommandBuffer::CreateCommandPool(VkSurfaceKHR surface)
    {
        QueueFamilyIndices queueFamilyIndices = Vulkan::PhysicalDevice().FindQueueFamilies(surface);
        
        VkCommandPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
        poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();
        
        CANDY_CORE_ASSERT(vkCreateCommandPool(Vulkan::LogicalDevice(), &poolInfo, nullptr, &commandPool) == VK_SUCCESS, "Failed to create command pool!");
    }
    
    void CommandBuffer::CreateCommandBuffers()
    {
        //commandBuffers.resize(MAX_FRAMES_IN_FLIGHT);
        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.commandPool = commandPool;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        //allocInfo.commandBufferCount = (uint32_t) commandBuffers.size();
        allocInfo.commandBufferCount=1;
        
        //CANDY_CORE_ASSERT(vkAllocateCommandBuffers(Vulkan::LogicalDevice(), &allocInfo, &commandBuffers[currentFrame]) == VK_SUCCESS, "Failed to allocate command buffers!");
      CANDY_CORE_ASSERT(vkAllocateCommandBuffers(Vulkan::LogicalDevice(), &allocInfo, &mainCommandBuffer) == VK_SUCCESS, "Failed to allocate command buffers!");
        
    }
    
    void CommandBuffer::CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size)
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
        
        VkBufferCopy copyRegion{};
        copyRegion.srcOffset = 0; // Optional
        copyRegion.dstOffset = 0; // Optional
        copyRegion.size = size;
        vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);
        
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
      CANDY_CORE_ASSERT(vkResetCommandBuffer(mainCommandBuffer, 0)==VK_SUCCESS, "Failed to reset command buffer!");
    }
    void CommandBuffer::StartRecording(VkCommandBufferUsageFlags flags)
    {
      Reset();
      VkCommandBufferBeginInfo cmdBeginInfo{};
      cmdBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
      cmdBeginInfo.flags = flags;
      cmdBeginInfo.pInheritanceInfo = nullptr;
      
      CANDY_CORE_ASSERT(vkBeginCommandBuffer(mainCommandBuffer, &cmdBeginInfo)==VK_SUCCESS);
    }
    /*void CommandBuffer::StartRecording(uint32_t currentFrame)
    {
      //mainCommandBuffer = commandBuffers[currentFrame];
        Reset();
        
        VkCommandBufferBeginInfo beginInfo{};
        
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = 0;
        beginInfo.pInheritanceInfo = nullptr;
        
        CANDY_CORE_ASSERT(vkBeginCommandBuffer(mainCommandBuffer, &beginInfo) == VK_SUCCESS, "Failed to begin recording command buffer!");
    };*/
    
    void CommandBuffer::StartRenderPass(const VkRenderPassBeginInfo* renderPassInfo)
    {
        vkCmdBeginRenderPass(mainCommandBuffer, renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
    }
    
    void CommandBuffer::BindPipeline(VkPipeline pipeline)
    {
        vkCmdBindPipeline(mainCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
    }
    void CommandBuffer::SetViewport(VkExtent2D extent)
    {
        VkViewport viewport{};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = static_cast<float>(extent.width);
        viewport.height = static_cast<float>(extent.height);
        viewport.minDepth=0.0f;
        viewport.maxDepth=1.0f;
        
        
        VkRect2D scissor{};
        scissor.offset = {0, 0};
        scissor.extent = extent;
        
        vkCmdSetViewport(mainCommandBuffer, 0, 1, &viewport);
        vkCmdSetScissor(mainCommandBuffer, 0, 1, &scissor);
    }
    
    void CommandBuffer::BindVertexBuffers(const std::vector<VkBuffer>& vertexBuffers)
    {
        VkDeviceSize* offsets;
        memset(offsets, 0, vertexBuffers.size() * sizeof(VkDeviceSize));
        
        vkCmdBindVertexBuffers(mainCommandBuffer, 0, vertexBuffers.size(), vertexBuffers.data(), offsets);
    }
    void CommandBuffer::BindIndexBuffer(const IndexBuffer& indexBuffer)
    {
        vkCmdBindIndexBuffer(mainCommandBuffer, indexBuffer, 0, VK_INDEX_TYPE_UINT32);
    }
    
    
    void CommandBuffer::Bind(const SharedPtr<VertexArray>& vertexArray)
    {
        VkBuffer data[vertexArray->vertexBuffers.size()];
        for (int i = 0; i < vertexArray->vertexBuffers.size(); i++)
        {
            data[i] = *vertexArray->vertexBuffers[i];
        }
        
        
        vkCmdBindVertexBuffers(mainCommandBuffer, 0, vertexArray->vertexBuffers.size(), data, vertexArray->vertexBufferOffsets.data());
        vkCmdBindIndexBuffer(mainCommandBuffer, *vertexArray->indexBuffer, 0, VK_INDEX_TYPE_UINT32);
    }
    void CommandBuffer::DrawIndexed(const SharedPtr<VertexArray>& vertexArray)
    {
        vkCmdDrawIndexed(mainCommandBuffer, static_cast<uint32_t>(vertexArray->indexBuffer->GetCount()), 1, 0, 0, 0);
    }
    void CommandBuffer::EndRenderPass()
    {
        vkCmdEndRenderPass(mainCommandBuffer);
    }
    
    void CommandBuffer::EndRecording()
    {
        CANDY_CORE_ASSERT(vkEndCommandBuffer(mainCommandBuffer) == VK_SUCCESS, "Failed to record command buffer!");
    }
    
    void CommandBuffer::EndAll()
    {
      EndRenderPass();
      EndRecording();
    }
  
  void CommandBuffer::PushConstants(VkPipelineLayout layout, ShaderStage shaderStage, uint32_t dataSize, const void* data)
  {
    vkCmdPushConstants(mainCommandBuffer, layout, Shader::StageToVulkan(shaderStage), 0, dataSize, data);
  }
  
  void CommandBuffer::Destroy()
  {
    vkDestroyCommandPool(Vulkan::LogicalDevice(), commandPool, nullptr);
  }
}