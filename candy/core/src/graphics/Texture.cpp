#include <candy/graphics/Texture.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <vulkan/vulkan.h>
#include <CandyPch.hpp>
#include <candy/graphics/vulkan/VulkanBuffer.hpp>
#include <candy/graphics/Vulkan.hpp>
namespace Candy::Graphics
{
  void Texture::CreateTextureImage()
  {
    int texWidth, texHeight, texChannels;
    stbi_uc* pixels = stbi_load("assets/textures/statue.jpg", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    uint64_t imageSize = texWidth * texHeight * 4;
    
    CANDY_CORE_ASSERT(pixels, "Failed to load texture image!");
    
    VkBuffer stagingBuffer;
    VmaAllocation stagingBufferAllocation;
    
    
    VulkanBuffer::CreateBuffer(imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, &stagingBufferAllocation);
    
    void* data;
    vmaMapMemory(Vulkan::Allocator(), stagingBufferAllocation, &data);
    memcpy(data, pixels, static_cast<size_t>(imageSize));
    vmaUnmapMemory(Vulkan::Allocator(), stagingBufferAllocation);
    stbi_image_free(pixels);
    
    
    VkImageCreateInfo imageInfo{};
    imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imageInfo.imageType = VK_IMAGE_TYPE_2D;
    imageInfo.extent.width = static_cast<uint32_t>(texWidth);
    imageInfo.extent.height = static_cast<uint32_t>(texHeight);
    imageInfo.extent.depth = 1;
    imageInfo.mipLevels = 1;
    imageInfo.arrayLayers = 1;
    
    imageInfo.format = VK_FORMAT_R8G8B8A8_SRGB;
    imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
    
    imageInfo.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
    
    imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    
    /* The samples flag is related to multisampling. This is only relevant for images that will be used as attachments, so stick to one sample.*/
    imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
    
    /* There are some optional flags for images that are related to sparse images.
     * Sparse images are images where only certain regions are actually backed by memory.
     * If you were using a 3D texture for a voxel terrain, for example, then you could use this to avoid allocating memory to store large volumes of "air" values */
    imageInfo.flags = 0; // Optional
    
    
    VmaAllocationCreateInfo allocCreateInfo{};
    VmaAllocationInfo allocInfo;
  
    CANDY_CORE_ASSERT(vmaCreateImage(Vulkan::Allocator(), &imageInfo, &allocCreateInfo, &image, &allocation, &allocInfo) == VK_SUCCESS, "Failed to create image!");
    vmaAllocateMemoryForImage(Vulkan::Allocator(), image, &allocCreateInfo, &allocation, &allocInfo);
    
   //TODO FIGURE OUT HOW TO TRANSLATE THIS SHIT TO VMA
    /*VkMemoryRequirements memRequirements;
    vkGetImageMemoryRequirements(device, image, &memRequirements);
    
    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties);
    
    if (vkAllocateMemory(device, &allocInfo, nullptr, &imageMemory) != VK_SUCCESS) {
      throw std::runtime_error("failed to allocate image memory!");
    }
    
    vkBindImageMemory(device, image, imageMemory, 0);*/
    
    vmaBindImageMemory(Vulkan::Allocator(), allocation, image);
  }
}