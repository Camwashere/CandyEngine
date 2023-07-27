#pragma once
#include <vulkan/vulkan.h>
#include <vma/vk_mem_alloc.h>
#include <candy/math/Vector.hpp>
namespace Candy::Graphics
{
  class Image
  {
  private:
    VkImage image;
    VkFormat format;
    VmaAllocation allocation;
    
    
  public:
    Image();
    Image(Math::Vector2u size, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usageFlags, VkMemoryPropertyFlagBits requiredFlags, VmaAllocationCreateFlagBits allocationCreateFlags);
    //~Image();
  public:
    operator VkImage()const{return image;}
    operator VkImage(){return image;}
    
  public:
    void Create(Math::Vector2u size, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usageFlags, VkMemoryPropertyFlagBits requiredFlags, VmaAllocationCreateFlagBits allocationCreateFlags);
    VkImage GetImageHandle(){return image;}
    VkFormat GetFormatHandle(){return format;}
    void Destroy();
    
    
    
  };
}