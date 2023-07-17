#include <candy/graphics/VertexBuffer.hpp>

#include <utility>
#include <candy/graphics/GraphicsContext.hpp>
#include <vma/vk_mem_alloc.h>
#include <candy/graphics/Vulkan.hpp>

namespace Candy::Graphics
{
    
    VertexBuffer::VertexBuffer(CommandBuffer* commandBuf, BufferLayout  bufferLayout, uint64_t countPerElement) : commandBuffer(commandBuf), layout(std::move(bufferLayout)), size(layout.CalculateSize(countPerElement))
    {
      
        VkBufferCreateInfo bufferInfo{};
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferInfo.size = size;
        VkBufferUsageFlags usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
        bufferInfo.usage = usage;
        bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        
        VmaAllocationCreateInfo allocInfo = {};
        allocInfo.usage = VMA_MEMORY_USAGE_CPU_TO_GPU;
        allocInfo.requiredFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
        
        
        
        CANDY_CORE_ASSERT(vmaCreateBuffer(Vulkan::Allocator(), &bufferInfo, &allocInfo, &buffer, &allocation, nullptr)==VK_SUCCESS, "Failed to create allocated buffer!");
        
        
    
    }
    
    VertexBuffer::VertexBuffer(CommandBuffer* commandBuf, float* vertices, uint64_t bufferSize) : commandBuffer(commandBuf), size(bufferSize)
    {
       
        
        VkBuffer stagingBuffer;
        VmaAllocation stagingBufferAllocation;
        
        CreateStagingBuffer(stagingBuffer, &stagingBufferAllocation);
        
       
        void* data;
        vmaMapMemory(Vulkan::Allocator(), stagingBufferAllocation, &data);
        memcpy(data, vertices, (size_t) bufferSize);
        vmaUnmapMemory(Vulkan::Allocator(), stagingBufferAllocation);
        
        
        VkBufferCreateInfo bufferInfo{};
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferInfo.size = size;
        VkBufferUsageFlags usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
        bufferInfo.usage = usage;
        bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        
        VmaAllocationCreateInfo allocInfo = {};
        allocInfo.usage = VMA_MEMORY_USAGE_CPU_TO_GPU;
        allocInfo.requiredFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
        
        
        
        CANDY_CORE_ASSERT(vmaCreateBuffer(Vulkan::Allocator(), &bufferInfo, &allocInfo, &buffer, &allocation, nullptr)==VK_SUCCESS, "Failed to create allocated buffer!");
        
        
        commandBuffer->CopyBuffer(stagingBuffer, buffer, size);
        
        
        vmaDestroyBuffer(Vulkan::Allocator(), stagingBuffer, stagingBufferAllocation);
        
        
        
    }
    VertexBuffer::~VertexBuffer()
    {
        vmaDestroyBuffer(Vulkan::Allocator(), buffer, allocation);
    }
    
    void VertexBuffer::CreateStagingBuffer(VkBuffer& buf, VmaAllocation* bufferAllocation)
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
    
    
    
    void VertexBuffer::SetData(float* vertices)
    {
        VkBuffer stagingBuffer;
        VmaAllocation stagingBufferAllocation;
        
        CreateStagingBuffer(stagingBuffer, &stagingBufferAllocation);
        
        void* data;
        vmaMapMemory(Vulkan::Allocator(), stagingBufferAllocation, &data);
        memcpy(data, vertices, (size_t) size);
        vmaUnmapMemory(Vulkan::Allocator(), stagingBufferAllocation);
        
        commandBuffer->CopyBuffer(stagingBuffer, buffer, size);
        
        vmaDestroyBuffer(Vulkan::Allocator(), stagingBuffer, stagingBufferAllocation);
    }
    void VertexBuffer::SetLayout(const BufferLayout& bufferLayout)
    {
        layout = bufferLayout;
    }
    [[nodiscard]] const BufferLayout& VertexBuffer::GetLayout()const
    {
        return layout;
    }
    
    uint64_t VertexBuffer::Size()const
    {
        return size;
    }
    
    VkVertexInputBindingDescription VertexBuffer::GetVertexBindingDescription()const
    {
        VkVertexInputBindingDescription bindingDescription{};
        bindingDescription.binding = 0;
        bindingDescription.stride = layout.GetStride();
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        
        return bindingDescription;
    }
    
    SharedPtr<VertexBuffer> VertexBuffer::Create(CommandBuffer* commandBuf, const BufferLayout& layout, uint64_t countPerElement)
    {
        return CreateSharedPtr<VertexBuffer>(commandBuf, layout, countPerElement);
    }
    
    
    SharedPtr<VertexBuffer> VertexBuffer::Create(CommandBuffer* commandBuf, float* vertices, uint64_t bufferSize)
    {
        return CreateSharedPtr<VertexBuffer>(commandBuf, vertices, bufferSize);
    }
    
    
    
    
}