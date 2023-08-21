#pragma once
#include "vulkan/VulkanBuffer.hpp"
#include <candy/math/Vector.hpp>
namespace Candy::Graphics
{
  class PixelBuffer : public VulkanBuffer
  {
  private:
    int* pixels;
    void* data;
    Math::Vector2u imageSize;
  public:
    PixelBuffer(const Math::Vector2u& imageSize);
    ~PixelBuffer();
    
  public:
    int ReadPixel(int x, int y);
    [[nodiscard]] Math::Vector2u GetImageSize()const;
    void CopyImage(VkImage image, int x, int y);
    int GetPixel(int x, int y);
  
  };
}