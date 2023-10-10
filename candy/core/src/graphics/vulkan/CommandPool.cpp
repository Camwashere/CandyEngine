#include <candy/graphics/vulkan/CommandPool.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <candy/graphics/vulkan/DeletionQueue.hpp>
#include "CandyPch.hpp"
namespace Candy::Graphics
{
  CommandPool::CommandPool() = default;
  CommandPool::CommandPool(VkSurfaceKHR surface, CommandPoolType poolType, uint32_t bufferCount)
  {
    Init(surface, poolType, bufferCount);
  }
  
  static VkCommandPoolCreateFlags PoolTypeToVulkan(CommandPoolType type)
  {
    switch (type)
    {
      case CommandPoolType::OneTime:
        return VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
        break;
      case CommandPoolType::ShortLived:
        return VK_COMMAND_POOL_CREATE_TRANSIENT_BIT | VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
        break;
      case CommandPoolType::LongLived:
        return VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
        break;
      default:
        return 0;
    }
  }
  static VkCommandBufferUsageFlags PoolTypeToVulkanUsage(CommandPoolType type)
  {
    switch (type)
    {
      case CommandPoolType::OneTime:
        return VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
        break;
      case CommandPoolType::ShortLived:
        return VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
        break;
      case CommandPoolType::LongLived:
        return VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT;
        break;
      default:
        return 0;
    }
  }
  void CommandPool::Init(VkSurfaceKHR surface, CommandPoolType poolType, uint32_t bufferCount, bool startSignaled)
  {
    CANDY_PROFILE_FUNCTION();
    type = poolType;
    QueueFamilyIndices queueFamilyIndices = Vulkan::LogicalDevice().GetQueueFamilyIndices();
    
    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.flags = PoolTypeToVulkan(type);
    poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();
    
    CANDY_VULKAN_CHECK(vkCreateCommandPool(Vulkan::LogicalDevice(), &poolInfo, nullptr, &pool));
    Vulkan::DeletionQueue().Push(pool);
    
    if (bufferCount>0)
    {
      buffers.resize(bufferCount);
      VkCommandBufferAllocateInfo allocInfo{};
      allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
      allocInfo.commandPool = pool;
      allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
      allocInfo.commandBufferCount = bufferCount;
      vkAllocateCommandBuffers(Vulkan::LogicalDevice(), &allocInfo, buffers.data());
    }
    
    
    VkFenceCreateInfo fenceCreateInfo{};
    fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    // Use signaled flag for swapchain images, no flag for anything else
    fenceCreateInfo.flags = startSignaled? VK_FENCE_CREATE_SIGNALED_BIT : 0;
    
    
    
    vkCreateFence(Vulkan::LogicalDevice(), &fenceCreateInfo, nullptr, &fence);
    
    //vkResetFences(Vulkan::LogicalDevice(), 1, &fence);
    
    Vulkan::DeletionQueue().Push(fence);
  }
  
  VkCommandBuffer CommandPool::GetCommandBuffer(uint32_t index)
  {
    return buffers[index];
  }
  VkCommandBuffer CommandPool::BeginCommandBuffer(uint32_t index)
  {
    VkCommandBufferBeginInfo info{};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    info.pNext = nullptr;
    
    info.pInheritanceInfo = nullptr;
    info.flags = PoolTypeToVulkanUsage(type);
    
    
    VkCommandBuffer buffer = buffers[index];
    
    CANDY_VULKAN_CHECK(vkBeginCommandBuffer(buffer, &info));
    return buffer;
  }
  
  
  VkResult CommandPool::ResetPool(bool releaseResources)
  {
    return vkResetCommandPool(Vulkan::LogicalDevice(), pool, releaseResources);
  }
  VkResult CommandPool::ResetBuffer(uint32_t index, bool releaseResources)
  {
    CANDY_CORE_ASSERT(index < buffers.size());
    return vkResetCommandBuffer(buffers[index], releaseResources);
  }
  VkResult CommandPool::ResetBuffers(bool releaseResources)
  {
    for (auto buffer : buffers)
    {
      VkResult result = vkResetCommandBuffer(buffer, releaseResources);
      if (result != VK_SUCCESS)
      {
        return result;
      }
    
    }
    return VK_SUCCESS;
  }
  
  VkResult CommandPool::EndRecording()
  {
    for (auto buffer : buffers)
    {
      VkResult result = vkEndCommandBuffer(buffer);
      if (result != VK_SUCCESS)
      {
        return result;
      }
    }
    return VK_SUCCESS;
  }
  
  VkResult CommandPool::WaitFence(uint64_t timeout)
  {
    CANDY_VULKAN_CHECK(vkWaitForFences(Vulkan::LogicalDevice(), 1, &fence, VK_TRUE, timeout));
    return vkResetFences(Vulkan::LogicalDevice(), 1, &fence);
  }
  
}