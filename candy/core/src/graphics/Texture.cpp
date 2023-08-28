#include <candy/graphics/Texture.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <vulkan/vulkan.h>
#include <CandyPch.hpp>
#include <candy/graphics/vulkan/VulkanBuffer.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <utility>
#include <candy/graphics/RenderCommand.hpp>

namespace Candy::Graphics
{
  Texture::Texture()
  {

  
  }
  Texture::Texture(std::filesystem::path  filePath) : path(std::move(filePath))
  {
    Load(path);
  
  }
  Texture::Texture(const TextureSpecification& textureSpecification) : specification(textureSpecification)
  {
    CANDY_PROFILE_FUNCTION();
    
    
  }
  
  void Texture::SetData(void* data, uint32_t size)
  {
    uint32_t bpp = specification.format.GetChannels();
    CANDY_CORE_ASSERT(size == specification.size.width * specification.size.height * bpp, "Data must be entire texture!");
    //glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
    
    VkBuffer stagingBuffer;
    VmaAllocation stagingBufferAllocation;
    VmaAllocationInfo stagingAllocInfo;
    VulkanBuffer::CreateBuffer(size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, &stagingBufferAllocation, &stagingAllocInfo);
    
    
    vmaMapMemory(Vulkan::Allocator(), stagingBufferAllocation, &stagingAllocInfo.pMappedData);
    memcpy(stagingAllocInfo.pMappedData, data, static_cast<size_t>(size));
    vmaUnmapMemory(Vulkan::Allocator(), stagingBufferAllocation);
    image.Create(specification.size, GetVulkanFormat(), VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT|VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT);
    RenderCommand::TransitionImageLayout(image, specification.format.GetVulkanFormat(), VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
    RenderCommand::CopyBufferToImage(stagingBuffer, image, static_cast<uint32_t>(specification.size.width), static_cast<uint32_t>(specification.size.height));
    RenderCommand::TransitionImageLayout(image, specification.format.GetVulkanFormat(), VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    imageView.Set(image);
    VulkanBuffer::DestroyBuffer(stagingBuffer, stagingBufferAllocation);
    /*VulkanBuffer::CreateStagingBuffer(stagingBuffer, size, &stagingBufferAllocation);
    void* mappedData;
    vmaMapMemory(Vulkan::Allocator(), stagingBufferAllocation, &mappedData);
    memcpy(mappedData, data, size);
    
    RenderCommand::CopyBufferToImage(stagingBuffer, image, specification.size.width, specification.size.height);
    vmaUnmapMemory(Vulkan::Allocator(), stagingBufferAllocation);*/
  }
  void Texture::Bind(uint32_t slot)const
  {
    // imageInfo needs to hold the information to bind the texture
    VkDescriptorImageInfo imageInfo{};
    imageInfo.imageView = imageView; // VkImageView
    imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    imageInfo.sampler = GetSampler();

// The actual update info which takes imageInfo
    VkWriteDescriptorSet descriptorWrite{};
    descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET; // This must be VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET
    descriptorWrite.dstSet = Renderer::GetCurrentFrame().GetDescriptorSet(2); // Descriptor set to update
    descriptorWrite.dstBinding = slot; // Equivalent of binding/uniform location in shader
    descriptorWrite.descriptorCount = 1; // We are updating only one binding point
    descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER; // the descriptor type that fits your case
    descriptorWrite.pImageInfo = &imageInfo; // Pointer to the descriptor image info
    descriptorWrite.dstArrayElement = 0;
    


// Update the descriptor set
    vkUpdateDescriptorSets(Vulkan::LogicalDevice(), 1, &descriptorWrite, 0, nullptr);
  }
  void Texture::Bind(uint32_t slot, uint32_t arrayIndex)
  {
    // imageInfo needs to hold the information to bind the texture
    VkDescriptorImageInfo imageInfo{};
    imageInfo.imageView = imageView; // VkImageView
    imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    imageInfo.sampler = GetSampler();
    
    // The actual update info which takes imageInfo
    VkWriteDescriptorSet descriptorWrite{};
    descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET; // This must be VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET
    descriptorWrite.dstSet = Renderer::GetCurrentFrame().GetDescriptorSet(2); // Descriptor set to update
    descriptorWrite.dstBinding = slot; // Equivalent of binding/uniform location in shader
    descriptorWrite.descriptorCount = 1; // We are updating only one binding point
    descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER; // the descriptor type that fits your case
    descriptorWrite.pImageInfo = &imageInfo; // Pointer to the descriptor image info
    descriptorWrite.dstArrayElement = arrayIndex;



    // Update the descriptor set
    vkUpdateDescriptorSets(Vulkan::LogicalDevice(), 1, &descriptorWrite, 0, nullptr);
  }
  uint32_t Texture::GetWidth()const
  {
    return specification.size.width;
  }
  uint32_t Texture::GetHeight()const
  {
    return specification.size.height;
  }
  Math::Vector2u Texture::GetSize()const
  {
    return specification.size;
  }
  const TextureSpecification& Texture::GetSpecification()const
  {
    return specification;
  }
  const std::filesystem::path& Texture::GetPath()const
  {
    return path;
  }
  bool Texture::IsLoaded()const
  {
    return isLoaded;
  }
  
  uint64_t TextureSpecification::SizeInBytes()const
  {
    return size.x*size.y*format.GetBytesPerPixel();
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
    else
    {
      isLoaded=true;
    }
    specification.size.Set(static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight));
    specification.format.SetChannels(texChannels);
    /*specification.channels = texChannels;
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
    }*/
    if (specification.format.GetChannels() != 4)
    {
      CANDY_CORE_INFO("Format does not have 4 channels. Format channels: {0}, Bytes per pixel: {1}, Bytes per channel: {2}", specification.format.GetChannels(), specification.format.GetBytesPerPixel(), specification.format.GetBytesPerChannel());
      specification.format.SetChannels(4);
    }
    //VkDeviceSize imageSize = texWidth * texHeight * 4;
    
    VkDeviceSize imageSize = specification.size.x * specification.size.y * specification.format.GetChannels();
    
    VkBuffer stagingBuffer;
    VmaAllocation stagingBufferAllocation;
    VmaAllocationInfo stagingAllocInfo;
    VulkanBuffer::CreateBuffer(imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, &stagingBufferAllocation, &stagingAllocInfo);
    
    
    vmaMapMemory(Vulkan::Allocator(), stagingBufferAllocation, &stagingAllocInfo.pMappedData);
    memcpy(stagingAllocInfo.pMappedData, pixels, static_cast<size_t>(imageSize));
    vmaUnmapMemory(Vulkan::Allocator(), stagingBufferAllocation);
    stbi_image_free(pixels);

    image.Create(specification.size, GetVulkanFormat(), VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT|VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT);
    imageView.Set(image);
    
    /*Vulkan::TransitionImageLayout(image, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
    Vulkan::CopyBufferToImage(stagingBuffer, image, static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight));
    Vulkan::TransitionImageLayout(image, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);*/
    
    Vulkan::TransitionImageLayout(image, specification.format.GetVulkanFormat(), VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
    Vulkan::CopyBufferToImage(stagingBuffer, image, static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight));
    Vulkan::TransitionImageLayout(image, specification.format.GetVulkanFormat(), VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    
    VulkanBuffer::DestroyBuffer(stagingBuffer, stagingBufferAllocation);
    return true;
  }
  
  VkDescriptorImageInfo Texture::GetDescriptorImageInfo()const
  {
    VkDescriptorImageInfo imageInfo{};
    imageInfo.imageView = imageView; // VkImageView
    imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    imageInfo.sampler = GetSampler();
    return imageInfo;
  }
  VkFormat Texture::GetVulkanFormat()const
  {
    return specification.format.GetVulkanFormat();
    //return VK_FORMAT_R8G8B8A8_SRGB;
  }
  
  SharedPtr<Texture> Texture::Create(const std::filesystem::path& path)
  {
    return CreateSharedPtr<Texture>(path);
  }
  SharedPtr<Texture> Texture::Create(const TextureSpecification& spec)
  {
    return CreateSharedPtr<Texture>(spec);
  }
  

  
}