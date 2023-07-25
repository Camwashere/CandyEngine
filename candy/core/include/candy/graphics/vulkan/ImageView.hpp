#pragma once
#include <vulkan/vulkan.h>
#include "../Texture.hpp"
namespace Candy::Graphics
{
  class ImageView
  {
  private:
    VkImageView imageView;
    
  public:
    ImageView();
    explicit ImageView(Texture& texture, VkImageAspectFlags aspectFlags = VK_IMAGE_ASPECT_COLOR_BIT);
    ImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags = VK_IMAGE_ASPECT_COLOR_BIT);
    
  public:
    operator VkImageView(){return imageView;}
    operator VkImageView()const{return imageView;}
    
  public:
    void Set(Texture& texture, VkImageAspectFlags aspectFlags = VK_IMAGE_ASPECT_COLOR_BIT);
    void Set(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags = VK_IMAGE_ASPECT_COLOR_BIT);
    [[nodiscard]] bool IsValid()const;
    void Destroy();
  };
}