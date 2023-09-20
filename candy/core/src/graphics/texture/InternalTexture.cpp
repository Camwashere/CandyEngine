#include <candy/graphics/texture/InternalTexture.hpp>
#include "stb/include/stb/stb_image.h"
#include "CandyPch.hpp"
#include <candy/graphics/vulkan/VulkanBuffer.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <utility>
#include <candy/graphics/RenderCommand.hpp>
namespace Candy::Graphics
{
  
  
  
  InternalTexture::InternalTexture(std::filesystem::path filepath) : path(std::move(filepath)), refCount(0)
  {
    if (!Load())
    {
      CANDY_CORE_ASSERT(false, "Failed to load texture from path!");
    }
    
    
    
  }
  
  InternalTexture::InternalTexture(const ImageFormat& imageFormat, const Math::Vector2u& imageSize) : format(imageFormat), size(imageSize), refCount(0)
  {
    
    //TODO Reserve gpu memory on object creation, so that it doesn't need to be recreated during SetData()
    /*image.Create(size, format.GetVulkanFormat(), VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT|VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT);
    imageView.Set(image);
    UpdateDescriptorImageInfo();*/
    
  }
  
  
  
  
  bool InternalTexture::Load()
  {
    CANDY_PROFILE_FUNCTION();
    int texWidth, texHeight, texChannels;
    
    stbi_uc* pixels = stbi_load(path.string().c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    if (! pixels)
    {
      CANDY_CORE_ASSERT(false, "Failed to load texture from path!");
      return false;
    }
    
    size.Set(static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight));
    format.SetChannels(texChannels);
    
    if (format.GetChannels() != 4)
    {
      CANDY_CORE_INFO("Format does not have 4 channels. Format channels: {0}, Bytes per pixel: {1}, Bytes per channel: {2}", format.GetChannels(), format.GetBytesPerPixel(), format.GetBytesPerChannel());
      format.SetChannels(4);
    }
    
    VkDeviceSize imageSize = size.x * size.y * format.GetChannels();
    
    VkBuffer stagingBuffer;
    VmaAllocation stagingBufferAllocation;
    VmaAllocationInfo stagingAllocInfo;
    VulkanBuffer::CreateBuffer(imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, &stagingBufferAllocation, &stagingAllocInfo);
    
    
    vmaMapMemory(Vulkan::Allocator(), stagingBufferAllocation, &stagingAllocInfo.pMappedData);
    memcpy(stagingAllocInfo.pMappedData, pixels, static_cast<size_t>(imageSize));
    vmaUnmapMemory(Vulkan::Allocator(), stagingBufferAllocation);
    
    stbi_image_free(pixels);
    
    image.Create(size, format.GetVulkanFormat(), VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT|VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT);
    //imageView.Set(image);
    
    
    Vulkan::TransitionImageLayout(image, format.GetVulkanFormat(), VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
    Vulkan::CopyBufferToImage(stagingBuffer, image, static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight));
    Vulkan::TransitionImageLayout(image, format.GetVulkanFormat(), VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    
    VulkanBuffer::DestroyBuffer(stagingBuffer, stagingBufferAllocation);
    return true;
  }
  
  void InternalTexture::SetData(void* data, uint32_t memorySize)
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_INFO("Memory size: {0}, Size in bytes: {1}", memorySize, GetTotalChannelCount());
    CANDY_CORE_ASSERT(memorySize == GetTotalChannelCount(), "Memory size does not match texture size! Cannot set data!");
    VkBuffer stagingBuffer;
    VmaAllocation stagingBufferAllocation;
    VmaAllocationInfo stagingAllocInfo;
    
    VulkanBuffer::CreateBuffer(memorySize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, &stagingBufferAllocation, &stagingAllocInfo);
    vmaMapMemory(Vulkan::Allocator(), stagingBufferAllocation, &stagingAllocInfo.pMappedData);
    memcpy(stagingAllocInfo.pMappedData, data, memorySize);
    vmaUnmapMemory(Vulkan::Allocator(), stagingBufferAllocation);
    image.Create(size, format.GetVulkanFormat(), VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT|VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT);
    
    RenderCommand::TransitionImageLayout(image, format.GetVulkanFormat(), VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
    RenderCommand::CopyBufferToImage(stagingBuffer, image, static_cast<uint32_t>(size.width), static_cast<uint32_t>(size.height));
    RenderCommand::TransitionImageLayout(image, format.GetVulkanFormat(), VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    
    //imageView.Set(image);
    VulkanBuffer::DestroyBuffer(stagingBuffer, stagingBufferAllocation);
    //UpdateDescriptorImageInfo();
  }
  void InternalTexture::AddRef()
  {
    refCount++;
  }
  int64_t InternalTexture::RemoveRef()
  {
    refCount--;
    return refCount;
  }
  
  void InternalTexture::ResetRef()
  {
    refCount=0;
  }
  
  int64_t InternalTexture::GetRefCount()const
  {
    return refCount;
  }
  size_t InternalTexture::GetTotalChannelCount()const
  {
    return size.width * size.height * format.GetChannels();
  }
  
  size_t InternalTexture::GetPixelCount()const
  {
    return size.width * size.height;
  }
  
  size_t InternalTexture::GetSizeInBytes()const
  {
    return GetTotalChannelCount() * format.GetBytesPerChannel();
    
  }
  const std::filesystem::path &InternalTexture::GetPath() const
  {
    return path;
  }
  
  
  
  Image &InternalTexture::GetImage()
  {
    return image;
  }
  
  const Image &InternalTexture::GetImage() const
  {
    return image;
  }
  
  /*ImageView &InternalTexture::GetImageView()
  {
    return imageView;
  }
  
  const ImageView &InternalTexture::GetImageView() const
  {
    return imageView;
  }
  
  VkSampler InternalTexture::GetSampler() const
  {
    return imageView.GetSampler();
  }*/
  
  uint32_t InternalTexture::GetWidth() const
  {
    return size.width;
  }
  
  uint32_t InternalTexture::GetHeight() const
  {
    return size.height;
  }
  
  Math::Vector2u InternalTexture::GetSize() const
  {
    return size;
  }
  
  bool InternalTexture::HasPath() const
  {
    return !path.empty();
  }
  
  /*const VkDescriptorImageInfo &InternalTexture::GetDescriptorImageInfo() const
  {
    return descriptorImageInfo;
  }*/
  
  const ImageFormat &InternalTexture::GetFormat() const
  {
    return format;
  }
  
  /*uint32_t InternalTexture::GetRefCount() const
  {
    return refCount;
  }*/
}