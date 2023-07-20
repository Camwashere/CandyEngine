#include <candy/graphics/vulkan/VulkanBuffer.hpp>
#include <CandyPch.hpp>

#include <candy/graphics/Vulkan.hpp>
namespace Candy::Graphics
{
    void VulkanBuffer::CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VmaAllocation* allocation, VmaAllocationInfo* allocInfo)
    {
        VkBufferCreateInfo bufferInfo{};
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferInfo.size = size;
        bufferInfo.usage = usage;
        bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        
        VmaAllocationCreateInfo allocCreateInfo = {};
        allocCreateInfo.flags = VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT | VMA_ALLOCATION_CREATE_MAPPED_BIT;
        allocCreateInfo.usage = VMA_MEMORY_USAGE_AUTO;
        allocCreateInfo.requiredFlags = properties;
        
        
        CANDY_CORE_ASSERT(vmaCreateBuffer(Vulkan::Allocator(), &bufferInfo, &allocCreateInfo, &buffer, allocation, allocInfo)==VK_SUCCESS, "Failed to create allocated buffer!");
    }
    
    void VulkanBuffer::DestroyBuffer(VkBuffer buffer, VmaAllocation allocation)
    {
        vmaDestroyBuffer(Vulkan::Allocator(), buffer, allocation);
    }

}