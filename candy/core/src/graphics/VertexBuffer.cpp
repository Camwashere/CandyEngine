#include <candy/graphics/VertexBuffer.hpp>

#include <utility>
#include <candy/graphics/GraphicsContext.hpp>
#include <vma/vk_mem_alloc.h>
#include <candy/graphics/Vulkan.hpp>

namespace Candy::Graphics
{
  
  VertexBuffer::VertexBuffer(BufferLayout bufferLayout, uint64_t countPerElement) : VulkanBuffer(bufferLayout.CalculateSize(countPerElement)), layout(std::move(bufferLayout))
  {
    
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    VkBufferUsageFlags usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT|VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    
    VmaAllocationCreateInfo allocInfo = {};
    allocInfo.usage = VMA_MEMORY_USAGE_CPU_TO_GPU;
    allocInfo.requiredFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
    
    
    CANDY_CORE_ASSERT(vmaCreateBuffer(Vulkan::Allocator(), &bufferInfo, &allocInfo, &buffer, &allocation, nullptr) == VK_SUCCESS, "Failed to create allocated buffer!");
    Vulkan::DeletionQueue().Push(this);
  }
  
  VertexBuffer::VertexBuffer(float *vertices, uint64_t bufferSize) : VulkanBuffer(bufferSize)
  {
    
    
    VkBuffer stagingBuffer;
    VmaAllocation stagingBufferAllocation;
    
    CreateStagingBuffer(stagingBuffer, &stagingBufferAllocation);
    
    
    void *data;
    vmaMapMemory(Vulkan::Allocator(), stagingBufferAllocation, &data);
    memcpy(data, vertices, (size_t) bufferSize);
    vmaUnmapMemory(Vulkan::Allocator(), stagingBufferAllocation);
    
    
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    VkBufferUsageFlags usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT|VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    
    VmaAllocationCreateInfo allocInfo = {};
    allocInfo.usage = VMA_MEMORY_USAGE_CPU_TO_GPU;
    allocInfo.requiredFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
    
    
    CANDY_CORE_ASSERT(vmaCreateBuffer(Vulkan::Allocator(), &bufferInfo, &allocInfo, &buffer, &allocation, nullptr) == VK_SUCCESS, "Failed to create allocated buffer!");
    
    Vulkan::CopyBuffer(stagingBuffer, buffer, size);
    
    
    vmaDestroyBuffer(Vulkan::Allocator(), stagingBuffer, stagingBufferAllocation);
    Vulkan::DeletionQueue().Push(this);
  }
  
  VertexBuffer::~VertexBuffer()
  = default;

  
  template<IsPrimitive T>
  void VertexBuffer::SetDataInternal(T* vertices)
  {
    VkBuffer stagingBuffer;
    VmaAllocation stagingBufferAllocation;
    
    CreateStagingBuffer(stagingBuffer, &stagingBufferAllocation);
    
    void *data;
    vmaMapMemory(Vulkan::Allocator(), stagingBufferAllocation, &data);
    memcpy(data, vertices, (size_t) size);
    vmaUnmapMemory(Vulkan::Allocator(), stagingBufferAllocation);
    Vulkan::CopyBuffer(stagingBuffer, buffer, size);
    
    vmaDestroyBuffer(Vulkan::Allocator(), stagingBuffer, stagingBufferAllocation);
  }
  template<typename T>
  void VertexBuffer::SetData(T *vertices)
  {
    CANDY_CORE_ASSERT(false, "Unsupported vertex buffer data type!");
  }
  
  template<>
  void VertexBuffer::SetData<float>(float* vertices)
  {
    SetDataInternal(vertices);
  }
  
  template<>
  void VertexBuffer::SetData<double>(double* vertices)
  {
    SetDataInternal(vertices);
  }
  
  void VertexBuffer::SetLayout(const BufferLayout &bufferLayout)
  {
    layout = bufferLayout;
  }
  
  [[nodiscard]] const BufferLayout &VertexBuffer::GetLayout() const
  {
    return layout;
  }
  
  /*uint64_t VertexBuffer::Size()const
  {
      return size;
  }*/
  
  VkVertexInputBindingDescription VertexBuffer::GetVertexBindingDescription() const
  {
    VkVertexInputBindingDescription bindingDescription{};
    bindingDescription.binding = 0;
    bindingDescription.stride = layout.GetStride();
    bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    
    
    return bindingDescription;
  }
  
  SharedPtr<VertexBuffer> VertexBuffer::Create(const BufferLayout &layout, uint64_t countPerElement)
  {
    return CreateSharedPtr<VertexBuffer>(layout, countPerElement);
  }
  
  
  SharedPtr<VertexBuffer> VertexBuffer::Create(float *vertices, uint64_t bufferSize)
  {
    return CreateSharedPtr<VertexBuffer>(vertices, bufferSize);
  }
  
  
}