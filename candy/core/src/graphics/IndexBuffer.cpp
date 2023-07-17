#include <candy/graphics/IndexBuffer.hpp>
#include <candy/graphics/GraphicsContext.hpp>
#include <candy/graphics/Vulkan.hpp>
namespace Candy::Graphics
{
    IndexBuffer::IndexBuffer(CommandBuffer* commandBuf, uint32_t* indices, uint64_t indexCount) : commandBuffer(commandBuf), count(indexCount), size(sizeof(uint32_t)*count)
    {
        CANDY_CORE_INFO("CREATING INDEX BUFFER");
        
        VkBuffer stagingBuffer;
        VmaAllocation stagingBufferAllocation;
        CreateStagingBuffer(stagingBuffer, &stagingBufferAllocation);
        
        void* data;
        vmaMapMemory(Vulkan::Allocator(), stagingBufferAllocation, &data);
        memcpy(data, indices, (size_t) size);
        vmaUnmapMemory(Vulkan::Allocator(), stagingBufferAllocation);
        
        
        
        VkBufferCreateInfo bufferInfo{};
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferInfo.size = size;
        VkBufferUsageFlags usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
        bufferInfo.usage = usage;
        bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        
        VmaAllocationCreateInfo allocInfo = {};
        allocInfo.usage = VMA_MEMORY_USAGE_CPU_TO_GPU;
        allocInfo.requiredFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
        
        CANDY_CORE_ASSERT(vmaCreateBuffer(Vulkan::Allocator(), &bufferInfo, &allocInfo, &buffer, &allocation, nullptr)==VK_SUCCESS, "Failed to create index buffer!");
        
        commandBuffer->CopyBuffer(stagingBuffer, buffer, size);
        
        vmaDestroyBuffer(Vulkan::Allocator(), stagingBuffer, stagingBufferAllocation);
    }
    
    IndexBuffer::~IndexBuffer()
    {
        vmaDestroyBuffer(Vulkan::Allocator(), buffer, allocation);
    }
    
    void IndexBuffer::CreateStagingBuffer(VkBuffer& buf, VmaAllocation* bufferAllocation)
    {
        VkBufferUsageFlags usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
        VkBufferCreateInfo bufferInfo{};
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferInfo.size = size;
        bufferInfo.usage = usage;
        bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        
        VmaAllocationCreateInfo allocInfo = {};
        allocInfo.usage = VMA_MEMORY_USAGE_CPU_TO_GPU;
        allocInfo.requiredFlags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
        
        
        
        CANDY_CORE_ASSERT(vmaCreateBuffer(Vulkan::Allocator(), &bufferInfo, &allocInfo, &buf, bufferAllocation, nullptr)==VK_SUCCESS, "Failed to create vertex staging buffer!");
    }
    
    SharedPtr<IndexBuffer> IndexBuffer::Create(CommandBuffer* commandBuf, uint32_t* indices, uint64_t count)
    {
        return CreateSharedPtr<IndexBuffer>(commandBuf, indices, count);
    }
}