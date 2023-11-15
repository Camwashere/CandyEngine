#pragma once
#include "candy/math/Vector.hpp"
#include <vma/vk_mem_alloc.h>
#include "ImageBase.hpp"
namespace Candy::Graphics
{
  class Image : public ImageBase
  {
  private:
    Math::Vector2u size;
    uint32_t mipLevels;
  };
}