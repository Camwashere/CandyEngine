#pragma once
#include <candy/graphics/vulkan/VulkanImage.hpp>
#include <candy/graphics/vulkan/VulkanImageView.hpp>
#include <candy/graphics/FrameBuffer.hpp>
namespace Candy::Graphics
{
  struct ImageResource
  {
    VulkanImage image;
    VulkanImageView imageView;
  };
  struct RenderTarget
  {
    std::vector<ImageResource> imageResources;
    FrameBuffer frameBuffer;
    
    
  };
}