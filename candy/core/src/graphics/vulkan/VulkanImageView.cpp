#include <candy/graphics/vulkan/VulkanImageView.hpp>
#include <candy/graphics/Vulkan.hpp>
#include "candy/graphics/texture/Texture.hpp"
#include <candy/graphics/vulkan/DeletionQueue.hpp>
namespace Candy::Graphics
{
  VulkanImageView::VulkanImageView() : imageView(VK_NULL_HANDLE)
  {
  
  }
  
  VulkanImageView::VulkanImageView(const VulkanImage& image, VkImageAspectFlags aspectFlags) : imageView(VK_NULL_HANDLE)
  {
    CANDY_PROFILE_FUNCTION();
    VkImageViewCreateInfo viewInfo{};
    viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    viewInfo.image = image;
    viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    viewInfo.format = image.GetFormatHandle();
    viewInfo.subresourceRange.aspectMask = aspectFlags;
    viewInfo.subresourceRange.baseMipLevel = 0;
    viewInfo.subresourceRange.levelCount = 1;
    viewInfo.subresourceRange.baseArrayLayer = 0;
    viewInfo.subresourceRange.layerCount = 1;
    
    
    CANDY_VULKAN_CHECK(vkCreateImageView(Vulkan::LogicalDevice(), &viewInfo, nullptr, &imageView));
    Vulkan::DeletionQueue().Push(this);
    
  }
  
  
  void VulkanImageView::CreateSampler()
  {
    CANDY_PROFILE_FUNCTION();
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
    
    CANDY_VULKAN_CHECK(vkCreateSampler(Vulkan::LogicalDevice(), &samplerInfo, nullptr, &sampler));
  }
  
  void VulkanImageView::Set(const VulkanImage& image, VkImageAspectFlags aspectFlags)
  {
    CANDY_PROFILE_FUNCTION();
    VkImageViewCreateInfo viewInfo{};
    viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    viewInfo.image = image;
    viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    
    viewInfo.format = image.GetFormatHandle();
    viewInfo.subresourceRange.aspectMask = aspectFlags;
    viewInfo.subresourceRange.baseMipLevel = 0;
    viewInfo.subresourceRange.levelCount = 1;
    viewInfo.subresourceRange.baseArrayLayer = 0;
    viewInfo.subresourceRange.layerCount = 1;
    
    CANDY_VULKAN_CHECK(vkCreateImageView(Vulkan::LogicalDevice(), &viewInfo, nullptr, &imageView));
    
    CreateSampler();
    Vulkan::DeletionQueue().Push(this);
    
  }
  void VulkanImageView::SetSwapChainImage(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags)
  {
    CANDY_PROFILE_FUNCTION();
    VkImageViewCreateInfo viewInfo{};
    viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    viewInfo.image = image;
    viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    viewInfo.format = format;
    viewInfo.subresourceRange.aspectMask = aspectFlags;
    viewInfo.subresourceRange.baseMipLevel = 0;
    viewInfo.subresourceRange.levelCount = 1;
    viewInfo.subresourceRange.baseArrayLayer = 0;
    viewInfo.subresourceRange.layerCount = 1;
    
    CANDY_VULKAN_CHECK(vkCreateImageView(Vulkan::LogicalDevice(), &viewInfo, nullptr, &imageView));
    CreateSampler();
    Vulkan::DeletionQueue().Push(this);
  }
  
  bool VulkanImageView::IsValid()const
  {
    return imageView != VK_NULL_HANDLE;
  }
  
 
}