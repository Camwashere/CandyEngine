#include <candy/graphics/UniformBuffer.hpp>
#include <candy/graphics/vulkan/VulkanBuffer.hpp>
#include <candy/graphics/Vulkan.hpp>
namespace Candy::Graphics
{
  UniformBuffer::UniformBuffer(uint64_t bufferSize) : size(bufferSize)
  {
    VulkanBuffer::CreateBuffer(size, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, buffer, &allocation);
    vmaMapMemory(Vulkan::Allocator(), allocation, &data);
  }
  
  UniformBuffer::operator VkBuffer()const
  {
    return buffer;
  }
  UniformBuffer::operator VkBuffer()
  {
    return buffer;
  }
  
  void UniformBuffer::SetData(void* newData)
  {
    memcpy(data, newData, size);
    //vmaMapMemory(Vulkan::Allocator(), allocation, &data);
  }
  
  void UniformBuffer::Destroy()
  {
    vmaUnmapMemory(Vulkan::Allocator(), allocation);
    VulkanBuffer::DestroyBuffer(buffer, allocation);
  }
  
  SharedPtr<UniformBuffer> UniformBuffer::Create(uint64_t size)
  {
    return CreateSharedPtr<UniformBuffer>(size);
  }
}