#include <candy/graphics/StorageBuffer.hpp>
#include <candy/graphics/Vulkan.hpp>
namespace Candy::Graphics
{
  StorageBuffer::StorageBuffer(uint64_t objSize, uint64_t objCount) : VulkanBuffer(objSize*objCount, BufferType::STORAGE_DYNAMIC), objectSize(objSize), objectCount(objCount)
  {
    
    VulkanBuffer::CreateBuffer(size, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, buffer, &allocation);
    Vulkan::DeletionQueue().Push(this);
  }
  void StorageBuffer::SetData(const void* data, uint64_t dataSize)
  {
    CANDY_CORE_ASSERT(dataSize <= size, "DATA SIZE IS BIGGER THAN BUFFER SIZE");
    void* mappedData;
    vmaMapMemory(Vulkan::Allocator(), allocation, &mappedData);
    memcpy(mappedData, data, dataSize);
    vmaUnmapMemory(Vulkan::Allocator(), allocation);
  }
  
  
  SharedPtr<StorageBuffer> StorageBuffer::Create(uint64_t objectSize, uint64_t objectCount)
  {
    return CreateSharedPtr<StorageBuffer>(objectSize, objectCount);
  }
}