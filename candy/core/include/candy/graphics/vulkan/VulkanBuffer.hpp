#pragma once
#include <vulkan/vulkan.h>
#include "vma/vk_mem_alloc.h"
#include <CandyPch.hpp>
namespace Candy::Graphics
{
  enum BufferType
  {
    NONE=0,
    VERTEX,
    INDEX,
    UNIFORM,
    UNIFORM_DYNAMIC,
    STORAGE,
    STORAGE_DYNAMIC,
    STAGING,
    PIXEL,
    DUMMY,
  };
    class VulkanBuffer
    {
    protected:
      VkBuffer buffer=VK_NULL_HANDLE;
      VmaAllocation allocation=VK_NULL_HANDLE;
      uint64_t size=0;
      BufferType type;
    
        
    protected:
    
      
    public:
      VulkanBuffer(BufferType type);
      VulkanBuffer(uint64_t size, BufferType type);
      
    public:
      [[nodiscard]] uint64_t Size()const;
      operator VkBuffer()const;
      operator VkBuffer();
      VmaAllocation GetAllocation();
      [[nodiscard]] bool IsStatic()const;
      [[nodiscard]] bool IsDynamic()const;
      [[nodiscard]] BufferType GetType()const;
      
    public:
      static void CreateStagingBuffer(VkBuffer& buffer, uint64_t size, VmaAllocation* allocation);
      static void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VmaAllocation* allocation, VmaAllocationInfo* allocInfo=nullptr);
      static void DestroyBuffer(VkBuffer buffer, VmaAllocation allocation);
      static void DestroyBuffer(VulkanBuffer* vulkanBuffer);
      static VkDescriptorType TypeToVulkan(BufferType type);
      
    };
}