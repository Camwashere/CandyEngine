#include <candy/graphics/UniformBuffer.hpp>
#include <candy/graphics/vulkan/VulkanBuffer.hpp>
#include <candy/graphics/Vulkan.hpp>
namespace Candy::Graphics
{
  UniformBuffer::UniformBuffer(uint64_t origSize) : VulkanBuffer(origSize)
  {
    VulkanBuffer::CreateBuffer(size, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, buffer, &allocation);
    Vulkan::DeletionQueue().Push(this);
    //Vulkan::PushDeleter([=, this](){vmaDestroyBuffer(Vulkan::Allocator(), buffer, allocation);});
  }
  
  /*UniformBuffer::operator VkBuffer()const
  {
    return buffer;
  }
  UniformBuffer::operator VkBuffer()
  {
    return buffer;
  }*/
  
  void UniformBuffer::SetData(uint64_t dataSize, const void* newData)
  {
    char* sceneData;
    vmaMapMemory(Vulkan::Allocator(), allocation, (void**)&sceneData);
    //sceneData += Vulkan::PhysicalDevice().PadUniformBufferSize(sizeof(Color)) * Vulkan::GetCurrentContext().GetCurrentFrameIndex();
    memcpy(sceneData, newData, dataSize);
    vmaUnmapMemory(Vulkan::Allocator(), allocation);
  }
  
  void UniformBuffer::SetData(uint64_t offset, uint64_t dataSize, const void* data)
  {
    char* sceneData;
    vmaMapMemory(Vulkan::Allocator(), allocation, (void**)&sceneData);
    memcpy(sceneData+offset, data, dataSize);
    vmaUnmapMemory(Vulkan::Allocator(), allocation);
  }
  
  
  
  
  
  /*void UniformBuffer::Destroy()
  {
    //vmaUnmapMemory(Vulkan::Allocator(), allocation);
    VulkanBuffer::DestroyBuffer(buffer, allocation);
  }*/
  
  
  
  SharedPtr<UniformBuffer> UniformBuffer::Create(uint64_t size)
  {
    return CreateSharedPtr<UniformBuffer>(size);
  }
}