#include <candy/graphics/vulkan/ImageView.hpp>
#include <candy/graphics/Vulkan.hpp>
namespace Candy::Graphics
{
  ImageView::ImageView() : imageView(VK_NULL_HANDLE)
  {
    //Vulkan::PushDeleter([=, this](){Destroy();});
  }
  ImageView::ImageView(Texture& texture, VkImageAspectFlags aspectFlags) : imageView(VK_NULL_HANDLE)
  {
    Set(texture, aspectFlags);
    //Vulkan::PushDeleter([=, this](){Destroy();});
  }
  ImageView::ImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags) : imageView(VK_NULL_HANDLE)
  {
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
    
    
    CANDY_CORE_ASSERT(vkCreateImageView(Vulkan::LogicalDevice(), &viewInfo, nullptr, &imageView) == VK_SUCCESS, "Failed to create image view!");
    //Vulkan::PushDeleter([=, this](){Destroy();});
  }
  
  void ImageView::CreateSampler()
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
  }
  void ImageView::Set(Texture& texture, VkImageAspectFlags aspectFlags)
  {
    Set(texture.GetImage(), texture.GetVulkanFormat(), aspectFlags);
  }
  void ImageView::Set(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags)
  {
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
    
    CANDY_CORE_ASSERT(vkCreateImageView(Vulkan::LogicalDevice(), &viewInfo, nullptr, &imageView) == VK_SUCCESS, "Failed to create image view!");
    CreateSampler();
  }
  bool ImageView::IsValid()const
  {
    return imageView != VK_NULL_HANDLE;
  }
  
  void ImageView::Destroy()
  {
    vkDestroyImageView(Vulkan::LogicalDevice(), imageView, nullptr);
    imageView = VK_NULL_HANDLE;
    vkDestroySampler(Vulkan::LogicalDevice(), sampler, nullptr);
  }
}