#pragma once
#include <vulkan/vulkan.h>
#include "vma/vk_mem_alloc.h"
namespace Candy::Graphics
{
    class VulkanBuffer
    {
    protected:
      VkBuffer buffer=VK_NULL_HANDLE;
      VmaAllocation allocation=VK_NULL_HANDLE;
      uint64_t size=0;
    
        
    protected:
      void CreateStagingBuffer(VkBuffer& buffer, VmaAllocation* allocation)const;
      
    public:
      VulkanBuffer()=default;
      VulkanBuffer(uint64_t size);
      
    public:
      [[nodiscard]] uint64_t Size()const;
      operator VkBuffer()const;
      operator VkBuffer();
      VmaAllocation GetAllocation();
      
    public:
      static void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VmaAllocation* allocation, VmaAllocationInfo* allocInfo=nullptr);
      static void DestroyBuffer(VkBuffer buffer, VmaAllocation allocation);
    };
}