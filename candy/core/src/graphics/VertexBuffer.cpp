#include <candy/graphics/VertexBuffer.hpp>

#include <utility>
#include <candy/graphics/GraphicsContext.hpp>
#include <vma/vk_mem_alloc.h>
#include <candy/graphics/Vulkan.hpp>
#include <candy/graphics/RenderCommand.hpp>

namespace Candy::Graphics
{
  VertexBuffer::VertexBuffer(const BufferLayout &bufferLayout) : VulkanBuffer(BufferType::VERTEX), layout(bufferLayout)
  {
    CANDY_PROFILE_FUNCTION();
    size = Vulkan::PhysicalDevice().GetMaxAllocationSize()/2;
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    VkBufferUsageFlags usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT|VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    bufferInfo.usage = usage;
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
    VkBufferUsageFlags usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT|VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    bufferInfo.usage = usage;
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
    
    VkBuffer stagingBuffer;
    VmaAllocation stagingBufferAllocation;
    
    CreateStagingBuffer(stagingBuffer, &stagingBufferAllocation);
    
    count = bufferSize/sizeof(float);
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
    
    
    CANDY_VULKAN_CHECK(vmaCreateBuffer(Vulkan::Allocator(), &bufferInfo, &allocInfo, &buffer, &allocation, nullptr));
    
    RenderCommand::CopyBufferImmediate(stagingBuffer, buffer, size);
    
    
    vmaDestroyBuffer(Vulkan::Allocator(), stagingBuffer, stagingBufferAllocation);
    Vulkan::DeletionQueue().Push(this);
  }
  
  VertexBuffer::~VertexBuffer() = default;
  
  
  void VertexBuffer::SetDataInternal(const void *vertices)
  {
    CANDY_PROFILE_FUNCTION();
    VkBuffer stagingBuffer;
    VmaAllocation stagingBufferAllocation;
    
    CreateStagingBuffer(stagingBuffer, &stagingBufferAllocation);
    
    void *data;
    vmaMapMemory(Vulkan::Allocator(), stagingBufferAllocation, &data);
    memcpy(data, vertices, (size_t) size);
    vmaUnmapMemory(Vulkan::Allocator(), stagingBufferAllocation);
    RenderCommand::CopyBufferImmediate(stagingBuffer, buffer, size);
    
    vmaDestroyBuffer(Vulkan::Allocator(), stagingBuffer, stagingBufferAllocation);
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
  
  /*uint64_t VertexBuffer::Size()const
  {
      return size;
  }*/
  
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