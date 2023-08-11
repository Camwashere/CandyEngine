#include <candy/graphics/vulkan/VulkanBuffer.hpp>
#include <CandyPch.hpp>

#include <candy/graphics/Vulkan.hpp>
namespace Candy::Graphics
{
  uint64_t VulkanBuffer::Size()const{return size;}
  
  VmaAllocation VulkanBuffer::GetAllocation(){return allocation;}
  
  VulkanBuffer::operator VkBuffer()const{return buffer;}
  VulkanBuffer::operator VkBuffer(){return buffer;}
  
  VulkanBuffer::VulkanBuffer(BufferType bufferType) : type(bufferType)
  {
  
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
        
        
        CANDY_CORE_ASSERT(vmaCreateBuffer(Vulkan::Allocator(), &bufferInfo, &allocCreateInfo, &buffer, allocation, allocInfo)==VK_SUCCESS, "Failed to create allocated buffer!");
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