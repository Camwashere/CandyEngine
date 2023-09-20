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
    CANDY_PROFILE_FUNCTION();
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
    CANDY_PROFILE_FUNCTION();
    VkBufferUsageFlags usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    
    VmaAllocationCreateInfo allocInfo = {};
    allocInfo.usage = VMA_MEMORY_USAGE_CPU_TO_GPU;
    allocInfo.requiredFlags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
    
    
    
    CANDY_VULKAN_CHECK(vmaCreateBuffer(Vulkan::Allocator(), &bufferInfo, &allocInfo, &buf, bufferAllocation, nullptr));
  }
  void VulkanBuffer::CreateStagingBuffer(VkBuffer& buffer, uint64_t size, VmaAllocation* bufferAllocation)
  {
    CANDY_PROFILE_FUNCTION();
    VkBufferUsageFlags usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    
    VmaAllocationCreateInfo allocInfo = {};
    allocInfo.usage = VMA_MEMORY_USAGE_CPU_TO_GPU;
    allocInfo.requiredFlags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
    
    
    
    CANDY_VULKAN_CHECK(vmaCreateBuffer(Vulkan::Allocator(), &bufferInfo, &allocInfo, &buffer, bufferAllocation, nullptr));
  }
    void VulkanBuffer::CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VmaAllocation* allocation, VmaAllocationInfo* allocInfo)
    {
      CANDY_PROFILE_FUNCTION();
        VkBufferCreateInfo bufferInfo{};
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferInfo.size = size;
        bufferInfo.usage = usage;
        bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        
        VmaAllocationCreateInfo allocCreateInfo = {};
        allocCreateInfo.flags = VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT | VMA_ALLOCATION_CREATE_MAPPED_BIT;
        allocCreateInfo.usage = VMA_MEMORY_USAGE_AUTO;
        allocCreateInfo.requiredFlags = properties;
      
      
      //CANDY_CORE_INFO("CREATED BUFFER SIZE: {0}", size);
      CANDY_VULKAN_CHECK(vmaCreateBuffer(Vulkan::Allocator(), &bufferInfo, &allocCreateInfo, &buffer, allocation, allocInfo));
    }
    
    void VulkanBuffer::DestroyBuffer(VkBuffer buffer, VmaAllocation allocation)
    {
      CANDY_PROFILE_FUNCTION();
        vmaDestroyBuffer(Vulkan::Allocator(), buffer, allocation);
    }
  void VulkanBuffer::DestroyBuffer(VulkanBuffer* vulkanBuffer)
  {
    CANDY_PROFILE_FUNCTION();
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