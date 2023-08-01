#include <candy/graphics/vulkan/Image.hpp>
#include <candy/graphics/Vulkan.hpp>
namespace Candy::Graphics
{
  Image::Image() : image(VK_NULL_HANDLE), format(VK_FORMAT_UNDEFINED), allocation(VK_NULL_HANDLE)
  {
    //Vulkan::PushDeleter([=, this](){Destroy();});
  }
  Image::Image(Math::Vector2u size, VkFormat imgFormat, VkImageTiling tiling, VkImageUsageFlags usageFlags, VkMemoryPropertyFlagBits requiredFlags, VmaAllocationCreateFlagBits allocationCreateFlags) : image(VK_NULL_HANDLE), format(imgFormat), allocation(VK_NULL_HANDLE)
  {
    Create(size, imgFormat, tiling, usageFlags, requiredFlags, allocationCreateFlags);
    //Vulkan::PushDeleter([=, this](){Destroy();});
  }
  
  
  
  void Image::Create(Math::Vector2u size, VkFormat imgFormat, VkImageTiling tiling, VkImageUsageFlags usageFlags, VkMemoryPropertyFlagBits requiredFlags, VmaAllocationCreateFlagBits allocationCreateFlags)
  {
    format = imgFormat;
    VkImageCreateInfo imageInfo{};
    imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imageInfo.imageType = VK_IMAGE_TYPE_2D;
    imageInfo.extent.width = size.width;
    imageInfo.extent.height = size.height;
    imageInfo.extent.depth = 1;
    imageInfo.mipLevels = 1;
    imageInfo.arrayLayers = 1;
    imageInfo.format = format;
    imageInfo.tiling = tiling;
    imageInfo.usage = usageFlags;
    imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    
    /* The samples flag is related to multisampling. This is only relevant for images that will be used as attachments, so stick to one sample.*/
    imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
    
    /* There are some optional flags for images that are related to sparse images.
     * Sparse images are images where only certain regions are actually backed by memory.
     * If you were using a 3D texture for a voxel terrain, for example, then you could use this to avoid allocating memory to store large volumes of "air" values */
    imageInfo.flags = 0; // Optional
    
    
    VmaAllocationCreateInfo allocCreateInfo{};
    VmaAllocationInfo allocInfo;
    allocCreateInfo.usage = VMA_MEMORY_USAGE_AUTO;
    allocCreateInfo.flags = allocationCreateFlags;
    allocCreateInfo.requiredFlags = requiredFlags;
    allocCreateInfo.priority = 1.0f;
    
    CANDY_CORE_ASSERT(vmaCreateImage(Vulkan::Allocator(), &imageInfo, &allocCreateInfo, &image, &allocation, &allocInfo) == VK_SUCCESS, "Failed to create image!");
    Vulkan::PushDeleter([=, this](){vmaDestroyImage(Vulkan::Allocator(), image, allocation);});
  }
  
  /*void Image::Destroy()
  {
    vmaDestroyImage(Vulkan::Allocator(), image, allocation);
  }*/
  
}