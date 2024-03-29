#include <candy/graphics/IndexBuffer.hpp>
#include <candy/graphics/GraphicsContext.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <candy/graphics/RenderCommand.hpp>
#include <candy/graphics/vulkan/DeletionQueue.hpp>
namespace Candy::Graphics
{
  IndexBuffer::IndexBuffer(uint64_t indexCount) : VulkanBuffer(sizeof(uint32_t)*indexCount, BufferType::INDEX), count(indexCount)
  {
    CANDY_PROFILE_FUNCTION();
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    VkBufferUsageFlags usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    
    VmaAllocationCreateInfo allocInfo = {};
    allocInfo.usage = VMA_MEMORY_USAGE_CPU_TO_GPU;
    allocInfo.requiredFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
    
    CANDY_VULKAN_CHECK(vmaCreateBuffer(Vulkan::Allocator(), &bufferInfo, &allocInfo, &buffer, &allocation, nullptr));
    
    Vulkan::DeletionQueue().Push(this);
  }
    IndexBuffer::IndexBuffer(uint32_t* indices, uint64_t indexCount) : VulkanBuffer(sizeof(uint32_t)*indexCount, BufferType::INDEX), count(indexCount)
    {
      CANDY_PROFILE_FUNCTION();

        VkBufferCreateInfo bufferInfo{};
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferInfo.size = size;
        VkBufferUsageFlags usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
        bufferInfo.usage = usage;
        bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        
        VmaAllocationCreateInfo allocInfo = {};
        allocInfo.usage = VMA_MEMORY_USAGE_CPU_TO_GPU;
        allocInfo.requiredFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
      
      CANDY_VULKAN_CHECK(vmaCreateBuffer(Vulkan::Allocator(), &bufferInfo, &allocInfo, &buffer, &allocation, nullptr));
      
        Vulkan::DeletionQueue().Push(this);
        
        SetDataInternal(indices);
      
    }
    
   
  
  void IndexBuffer::SetData(uint32_t* indices, uint64_t indexCount)
  {
    CANDY_PROFILE_FUNCTION();
    count = indexCount;
    size = sizeof(uint32_t)*count;
    SetDataInternal(indices);
    
  }
  void IndexBuffer::SetData(const uint32_t* indices, uint64_t indexCount)
  {
    CANDY_PROFILE_FUNCTION();
    count = indexCount;
    size = sizeof(uint32_t)*count;
    SetDataInternal(indices);
  }
  void IndexBuffer::SetDataInternal(const void* indices)
  {
    CANDY_PROFILE_FUNCTION();
    
    void *data;
    vmaMapMemory(Vulkan::Allocator(), allocation, &data);
    memcpy(data, indices, (size_t) size);
    vmaFlushAllocation(Vulkan::Allocator(), allocation, 0, VK_WHOLE_SIZE);
    vmaUnmapMemory(Vulkan::Allocator(), allocation);
    
  }
    SharedPtr<IndexBuffer> IndexBuffer::Create(uint64_t count)
    {
      return CreateSharedPtr<IndexBuffer>(count);
    }
    SharedPtr<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint64_t count)
    {
        return CreateSharedPtr<IndexBuffer>(indices, count);
    }
}