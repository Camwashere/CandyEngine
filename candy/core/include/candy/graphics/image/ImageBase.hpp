#pragma once
#include <vma/vk_mem_alloc.h>
#include "ImageFormat.hpp"
namespace Candy::Graphics
{
  class ImageBase
  {
  private:
    const uint32_t id;
  protected:
    VkImage image;
    ImageFormat format;
    VmaAllocation allocation;
    
    
  public:
    [[nodiscard]] uint32_t GetID()const;
    
  };
}