#pragma once
#include <candy/graphics/vulkan/Image.hpp>
#include <candy/graphics/vulkan/ImageView.hpp>
#include <candy/graphics/FrameBuffer.hpp>
namespace Candy::Graphics
{
  struct ImageResource
  {
    Image image;
    ImageView imageView;
  };
  struct RenderTarget
  {
    std::vector<ImageResource> imageResources;
    FrameBuffer frameBuffer;
    
    
  };
}