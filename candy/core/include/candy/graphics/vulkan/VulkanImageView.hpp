#pragma once
#include <vulkan/vulkan.h>
//#include "../Texture.hpp"
namespace Candy::Graphics
{
  class Texture;
  class VulkanImage;
}
namespace Candy::Graphics
{
  class VulkanImageView
  {
  private:
    VkImageView imageView;
    VkSampler sampler;
    
  public:
    VulkanImageView();
    //explicit VulkanImageView(Texture& texture, VkImageAspectFlags aspectFlags = VK_IMAGE_ASPECT_COLOR_BIT);
    VulkanImageView(const VulkanImage& image, VkImageAspectFlags aspectFlags = VK_IMAGE_ASPECT_COLOR_BIT);
    //VulkanImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags = VK_IMAGE_ASPECT_COLOR_BIT);
    //~VulkanImageView();
    
  public:
    operator VkImageView(){return imageView;}
    operator VkImageView()const{return imageView;}
    
  public:
    void CreateSampler();
    void SetSwapChainImage(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags = VK_IMAGE_ASPECT_COLOR_BIT);
    //void Set(Texture& texture, VkImageAspectFlags aspectFlags = VK_IMAGE_ASPECT_COLOR_BIT);
    void Set(const VulkanImage& image, VkImageAspectFlags aspectFlags = VK_IMAGE_ASPECT_COLOR_BIT);
    //void Set(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags = VK_IMAGE_ASPECT_COLOR_BIT);
    [[nodiscard]] bool IsValid()const;
    [[nodiscard]] VkSampler GetSampler()const{return sampler;}
    //void Destroy();
  };
}