#include <candy/graphics/vulkan/VulkanBuffer.hpp>
#include <CandyPch.hpp>

#include <candy/graphics/Vulkan.hpp>
namespace Candy::Graphics
{
    void VulkanBuffer::CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VmaAllocation* allocation)
    {
        VkBufferCreateInfo bufferInfo{};
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferInfo.size = size;
        bufferInfo.usage = usage;
        bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        
        VmaAllocationCreateInfo allocInfo = {};
        allocInfo.usage = VMA_MEMORY_USAGE_CPU_TO_GPU;
        allocInfo.requiredFlags = properties;
        
        
        
        CANDY_CORE_ASSERT(vmaCreateBuffer(Vulkan::Allocator(), &bufferInfo, &allocInfo, &buffer, allocation, nullptr)==VK_SUCCESS, "Failed to create allocated buffer!");
    }
    
    void VulkanBuffer::DestroyBuffer(VkBuffer buffer, VmaAllocation allocation)
    {
        vmaDestroyBuffer(Vulkan::Allocator(), buffer, allocation);
    }

}