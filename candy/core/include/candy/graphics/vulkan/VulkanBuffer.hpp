#pragma once
#include <vulkan/vulkan.h>
#include "vma/vk_mem_alloc.h"
namespace Candy::Graphics
{
    class VulkanBuffer
    {
        
    
        
    public:
        static void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VmaAllocation* allocation);
        static void DestroyBuffer(VkBuffer buffer, VmaAllocation allocation);
    };
}