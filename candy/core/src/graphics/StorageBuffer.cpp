#include <candy/graphics/StorageBuffer.hpp>
#include <candy/graphics/Vulkan.hpp>
namespace Candy::Graphics
{
  StorageBuffer::StorageBuffer(uint64_t objSize, uint64_t objCount) : VulkanBuffer(objSize*objCount), objectSize(objSize), objectCount(objCount)
  {
    VMA_MEMORY_USAGE_CPU_TO_GPU;
    VulkanBuffer::CreateBuffer(size, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, buffer, &allocation);
    Vulkan::DeletionQueue().Push(this);
  }
  
  SharedPtr<StorageBuffer> StorageBuffer::Create(uint64_t objectSize, uint64_t objectCount)
  {
    return CreateSharedPtr<StorageBuffer>(objectSize, objectCount);
  }
}