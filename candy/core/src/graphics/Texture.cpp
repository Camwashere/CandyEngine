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

  
  }
  Texture::Texture(std::filesystem::path  filePath) : path(std::move(filePath))
  {
    Load(path);
  
  }
  Texture::Texture(const TextureSpecification& textureSpecification)
  {
  }
  

  
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

    image.Create(specification.size, GetVulkanFormat(), VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT|VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT);
    
    
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
  

  
}