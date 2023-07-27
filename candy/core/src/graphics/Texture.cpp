#include <candy/graphics/Texture.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <vulkan/vulkan.h>
#include <CandyPch.hpp>
#include <candy/graphics/vulkan/VulkanBuffer.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <utility>

namespace Candy::Graphics
{
  
  Texture::Texture()
  {
    //Vulkan::PushDeleter([=, this](){Destroy();});
  
  }
  Texture::Texture(std::filesystem::path  filePath) : path(std::move(filePath))
  {
    //Vulkan::PushDeleter([=, this](){Destroy();});
  
  }
  Texture::Texture(const TextureSpecification& textureSpecification)
  {
    //Vulkan::PushDeleter([=, this](){Destroy();});
  }
  
  
 /* void Texture::CreateSampler()
  {
    VkSamplerCreateInfo samplerInfo{};
    samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    samplerInfo.magFilter = VK_FILTER_LINEAR;
    samplerInfo.minFilter = VK_FILTER_LINEAR;
    samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    samplerInfo.anisotropyEnable = VK_TRUE;
    
    VkPhysicalDeviceProperties properties{};
    vkGetPhysicalDeviceProperties(Vulkan::PhysicalDevice(), &properties);
    
    samplerInfo.maxAnisotropy = properties.limits.maxSamplerAnisotropy;
    samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
    samplerInfo.unnormalizedCoordinates = VK_FALSE;
    samplerInfo.compareEnable = VK_FALSE;
    samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
    samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
    samplerInfo.mipLodBias = 0.0f;
    samplerInfo.minLod = 0.0f;
    samplerInfo.maxLod = 0.0f;
    
    CANDY_CORE_ASSERT(vkCreateSampler(Vulkan::LogicalDevice(), &samplerInfo, nullptr, &sampler) == VK_SUCCESS, "Failed to create texture sampler!");
  }*/
  
  uint64_t TextureSpecification::ImageSize()const
  {
    return size.x*size.y*channels;
  }
  
  bool Texture::Load(const std::filesystem::path& texturePath)
  {
    path = texturePath;
    int texWidth, texHeight, texChannels;
    
    stbi_uc* pixels = stbi_load(path.string().c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    if (! pixels)
    {
      CANDY_CORE_ASSERT(false, "Failed to load texture from path!");
      return false;
    }
    specification.size.Set(static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight));
    specification.channels = texChannels;
    switch(specification.channels)
    {
      case 3:
        specification.format.layout = ColorLayout::RGB;
        specification.format.dataType = ColorDataType::UNSIGNED_BYTE;
        break;
      case 4:
        specification.format.layout = ColorLayout::RGBA;
        specification.format.dataType = ColorDataType::UNSIGNED_BYTE;
        break;
      default:
        specification.format.layout = ColorLayout::NONE;
        specification.format.dataType = ColorDataType::NONE;
    }
    
    VkDeviceSize imageSize = texWidth * texHeight * 4;
    
    VkBuffer stagingBuffer;
    VmaAllocation stagingBufferAllocation;
    VmaAllocationInfo stagingAllocInfo;
    VulkanBuffer::CreateBuffer(imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, &stagingBufferAllocation, &stagingAllocInfo);
    
    
    vmaMapMemory(Vulkan::Allocator(), stagingBufferAllocation, &stagingAllocInfo.pMappedData);
    memcpy(stagingAllocInfo.pMappedData, pixels, static_cast<size_t>(imageSize));
    vmaUnmapMemory(Vulkan::Allocator(), stagingBufferAllocation);
    stbi_image_free(pixels);
    
    
    /*VkImageCreateInfo imageInfo{};
    imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imageInfo.imageType = VK_IMAGE_TYPE_2D;
    imageInfo.extent.width = specification.size.width;
    imageInfo.extent.height = specification.size.height;
    imageInfo.extent.depth = 1;
    imageInfo.mipLevels = 1;
    imageInfo.arrayLayers = 1;
    imageInfo.format = GetVulkanFormat();
    imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
    imageInfo.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
    imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;*/
    
    /* The samples flag is related to multisampling. This is only relevant for images that will be used as attachments, so stick to one sample.*/
    //imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
    
    /* There are some optional flags for images that are related to sparse images.
     * Sparse images are images where only certain regions are actually backed by memory.
     * If you were using a 3D texture for a voxel terrain, for example, then you could use this to avoid allocating memory to store large volumes of "air" values */
    //imageInfo.flags = 0; // Optional
    
    
   /* VmaAllocationCreateInfo allocCreateInfo{};
    VmaAllocationInfo allocInfo;
    allocCreateInfo.usage = VMA_MEMORY_USAGE_AUTO;
    
    allocCreateInfo.flags = VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT;
    allocCreateInfo.requiredFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
    allocCreateInfo.priority = 1.0f;*/
    image.Create(specification.size, GetVulkanFormat(), VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT|VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT);
    //CANDY_CORE_ASSERT(vmaCreateImage(Vulkan::Allocator(), &imageInfo, &allocCreateInfo, &image, &allocation, &allocInfo) == VK_SUCCESS, "Failed to create image!");
    //vmaAllocateMemoryForImage(Vulkan::Allocator(), image, &allocCreateInfo, &allocation, &allocInfo);
    
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
    
    //vmaBindImageMemory(Vulkan::Allocator(), allocation, image);
    
    Vulkan::TransitionImageLayout(image, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
    Vulkan::CopyBufferToImage(stagingBuffer, image, static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight));
    Vulkan::TransitionImageLayout(image, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    
    VulkanBuffer::DestroyBuffer(stagingBuffer, stagingBufferAllocation);
    return true;
  }
  VkFormat Texture::GetVulkanFormat()const
  {
    return VK_FORMAT_R8G8B8A8_SRGB;
  }
  
  void Texture::Destroy()
  {
    image.Destroy();
    //vmaDestroyImage(Vulkan::Allocator(), image, allocation);
    
    //vkDestroySampler(Vulkan::LogicalDevice(), sampler, nullptr);
  }
  
}