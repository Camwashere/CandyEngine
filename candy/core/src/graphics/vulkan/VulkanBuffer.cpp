#include <candy/graphics/vulkan/VulkanBuffer.hpp>
#include <CandyPch.hpp>

#include <candy/graphics/Vulkan.hpp>
namespace Candy::Graphics
{
  const char* String_VkResult(VkResult errorCode) {
    switch (errorCode)
    {
#define STR(r) case VK_ ## r: return #r
      STR(SUCCESS);
      STR(NOT_READY);
      STR(TIMEOUT);
      STR(EVENT_SET);
      STR(EVENT_RESET);
      STR(INCOMPLETE);
      STR(ERROR_OUT_OF_HOST_MEMORY);
      STR(ERROR_OUT_OF_DEVICE_MEMORY);
      STR(ERROR_INITIALIZATION_FAILED);
      STR(ERROR_DEVICE_LOST);
      STR(ERROR_MEMORY_MAP_FAILED);
      STR(ERROR_LAYER_NOT_PRESENT);
      STR(ERROR_EXTENSION_NOT_PRESENT);
      STR(ERROR_FEATURE_NOT_PRESENT);
      STR(ERROR_INCOMPATIBLE_DRIVER);
      STR(ERROR_TOO_MANY_OBJECTS);
      STR(ERROR_FORMAT_NOT_SUPPORTED);
      STR(ERROR_FRAGMENTED_POOL);
      STR(ERROR_UNKNOWN);
#undef STR
      default: return "UNKNOWN_ERROR";
    }
  }
  uint64_t VulkanBuffer::Size()const{return size;}
  
  VmaAllocation VulkanBuffer::GetAllocation(){return allocation;}
  
  VulkanBuffer::operator VkBuffer()const{return buffer;}
  VulkanBuffer::operator VkBuffer(){return buffer;}
  
  VulkanBuffer::VulkanBuffer(BufferType bufferType) : type(bufferType)
  {
    switch(type)
    {
      case BufferType::DUMMY:
        size = sizeof(float);
        VkBufferCreateInfo bufferInfo = { VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO };
        bufferInfo.size = sizeof(float);  // Can be anything as long as non-zero
        bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;

// Define the allocation
        VmaAllocationCreateInfo allocationInfo = {};
        allocationInfo.usage = VMA_MEMORY_USAGE_GPU_ONLY;

// Create the buffer

        vmaCreateBuffer(Vulkan::Allocator(), &bufferInfo, &allocationInfo, &buffer, &allocation, nullptr);
        Vulkan::DeletionQueue().Push(this);
        break;
    }
  
  }
  
  VulkanBuffer::VulkanBuffer(uint64_t bufferSize, BufferType bufferType) : size(bufferSize), type(bufferType)
  {
  
  }
  
  bool VulkanBuffer::IsStatic()const
  {
    switch(type)
    {
      case UNIFORM_DYNAMIC:
      case STORAGE_DYNAMIC:
        return false;
      default:
        return true;
    }
  }
  bool VulkanBuffer::IsDynamic()const
  {
    switch(type)
    {
      case UNIFORM_DYNAMIC:
      case STORAGE_DYNAMIC:
        return true;
      default:
        return false;
    }
  }
  BufferType VulkanBuffer::GetType()const
  {
    return type;
  }
  void VulkanBuffer::CreateStagingBuffer(VkBuffer& buf, VmaAllocation* bufferAllocation)const
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
    
    
    
    CANDY_CORE_ASSERT(vmaCreateBuffer(Vulkan::Allocator(), &bufferInfo, &allocInfo, &buf, bufferAllocation, nullptr)==VK_SUCCESS, "Failed to create index staging buffer!");
  }
  void VulkanBuffer::CreateStagingBuffer(VkBuffer& buffer, uint64_t size, VmaAllocation* bufferAllocation)
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
    
    
    
    CANDY_CORE_ASSERT(vmaCreateBuffer(Vulkan::Allocator(), &bufferInfo, &allocInfo, &buffer, bufferAllocation, nullptr)==VK_SUCCESS, "Failed to create index staging buffer!");
  }
    void VulkanBuffer::CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VmaAllocation* allocation, VmaAllocationInfo* allocInfo)
    {
        VkBufferCreateInfo bufferInfo{};
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferInfo.size = size;
        bufferInfo.usage = usage;
        bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        
        VmaAllocationCreateInfo allocCreateInfo = {};
        allocCreateInfo.flags = VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT | VMA_ALLOCATION_CREATE_MAPPED_BIT;
        allocCreateInfo.usage = VMA_MEMORY_USAGE_AUTO;
        allocCreateInfo.requiredFlags = properties;
      
      VkResult result = vmaCreateBuffer(Vulkan::Allocator(), &bufferInfo, &allocCreateInfo, &buffer, allocation, allocInfo);
      //CANDY_CORE_INFO("CREATED BUFFER SIZE: {0}", size);
        CANDY_CORE_ASSERT(result==VK_SUCCESS, String_VkResult(result));
    }
    
    void VulkanBuffer::DestroyBuffer(VkBuffer buffer, VmaAllocation allocation)
    {
        vmaDestroyBuffer(Vulkan::Allocator(), buffer, allocation);
    }
  void VulkanBuffer::DestroyBuffer(VulkanBuffer* vulkanBuffer)
  {
    vmaDestroyBuffer(Vulkan::Allocator(), *vulkanBuffer, vulkanBuffer->allocation);
  }
  
  VkDescriptorType VulkanBuffer::TypeToVulkan(BufferType type)
  {
    switch(type)
    {
      case UNIFORM:
        return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
      case UNIFORM_DYNAMIC:
        return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
      case STORAGE:
        return VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
      case STORAGE_DYNAMIC:
        return VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;
        return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
      default:
        CANDY_CORE_ASSERT(false, "INVALID BUFFER TYPE, CANNOT CONVERT TO VULKAN!");
        return (VkDescriptorType)0;
    }
  }
  

}