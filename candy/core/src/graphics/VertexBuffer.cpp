#include <candy/graphics/VertexBuffer.hpp>

#include <candy/graphics/GraphicsContext.hpp>
#include <vma/vk_mem_alloc.h>
#include <candy/graphics/Vulkan.hpp>
#include <candy/graphics/RenderCommand.hpp>
#include <candy/graphics/vulkan/DeletionQueue.hpp>

namespace Candy::Graphics
{
  VertexBuffer::VertexBuffer(const BufferLayout &bufferLayout) : VulkanBuffer(BufferType::VERTEX), layout(bufferLayout)
  {
    CANDY_PROFILE_FUNCTION();
    size = Vulkan::PhysicalDevice().GetMaxAllocationSize()/2;
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
   
    bufferInfo.usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    
    VmaAllocationCreateInfo allocInfo = {};
    allocInfo.usage = VMA_MEMORY_USAGE_CPU_TO_GPU;
    allocInfo.requiredFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
    
    
    
    CANDY_VULKAN_CHECK(vmaCreateBuffer(Vulkan::Allocator(), &bufferInfo, &allocInfo, &buffer, &allocation, nullptr));
    Vulkan::DeletionQueue().Push(this);
  }
  
  VertexBuffer::VertexBuffer(const BufferLayout &bufferLayout, uint64_t countPerElement) : VulkanBuffer(bufferLayout.CalculateSize(countPerElement), BufferType::VERTEX), layout(bufferLayout)
  {
    CANDY_PROFILE_FUNCTION();
    count = countPerElement;
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    
    
    VmaAllocationCreateInfo allocInfo = {};
    allocInfo.usage = VMA_MEMORY_USAGE_CPU_TO_GPU;
    
    allocInfo.requiredFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
    
    
    CANDY_VULKAN_CHECK(vmaCreateBuffer(Vulkan::Allocator(), &bufferInfo, &allocInfo, &buffer, &allocation, nullptr));
    Vulkan::DeletionQueue().Push(this);
  }
  
  VertexBuffer::VertexBuffer(float *vertices, uint64_t bufferSize) : VulkanBuffer(bufferSize, BufferType::VERTEX)
  {
    CANDY_PROFILE_FUNCTION();
    
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    
    VmaAllocationCreateInfo allocInfo = {};
    allocInfo.usage = VMA_MEMORY_USAGE_CPU_TO_GPU;
    allocInfo.requiredFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
    
    
    CANDY_VULKAN_CHECK(vmaCreateBuffer(Vulkan::Allocator(), &bufferInfo, &allocInfo, &buffer, &allocation, nullptr));

    Vulkan::DeletionQueue().Push(this);
    
    SetDataInternal(vertices);
  }
  
  VertexBuffer::~VertexBuffer() = default;
  
  
  void VertexBuffer::SetDataInternal(const void *vertices)
  {
    CANDY_PROFILE_FUNCTION();
    
    void* data;
    vmaMapMemory(Vulkan::Allocator(), allocation, &data); // Map the buffer memory
    memcpy(data, vertices, (size_t) size); // Copy the vertices data into the mapped memory
    
    // Guarantee that the write operations completed before it's used
    vmaFlushAllocation(Vulkan::Allocator(), allocation, 0, VK_WHOLE_SIZE);
    vmaUnmapMemory(Vulkan::Allocator(), allocation); // Unmap the buffer memory
  }
  
  void VertexBuffer::SetData(const void* data, uint32_t dataSize)
  {
    CANDY_PROFILE_FUNCTION();
    size = dataSize;
    SetDataInternal(data);
  }
  void VertexBuffer::SetLayout(const BufferLayout &bufferLayout)
  {
    layout = bufferLayout;
  }
  
  [[nodiscard]] const BufferLayout &VertexBuffer::GetLayout() const
  {
    return layout;
  }

  
  VkVertexInputBindingDescription VertexBuffer::GetVertexBindingDescription() const
  {
    CANDY_PROFILE_FUNCTION();
    VkVertexInputBindingDescription bindingDescription{};
    bindingDescription.binding = 0;
    bindingDescription.stride = layout.GetStride();
    bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    
    
    return bindingDescription;
  }
  uint32_t VertexBuffer::GetCount()const
  {
    return count;
  }
  SharedPtr<VertexBuffer> VertexBuffer::Create(const BufferLayout &layout, uint64_t countPerElement)
  {
    return CreateSharedPtr<VertexBuffer>(layout, countPerElement);
  }
  
  
  SharedPtr<VertexBuffer> VertexBuffer::Create(float *vertices, uint64_t bufferSize)
  {
    return CreateSharedPtr<VertexBuffer>(vertices, bufferSize);
  }
  
  SharedPtr<VertexBuffer> VertexBuffer::Create(const BufferLayout &layout)
  {
    return CreateSharedPtr<VertexBuffer>(layout);
  }
  
  
}