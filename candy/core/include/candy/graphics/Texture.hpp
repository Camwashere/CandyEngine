#pragma once
#include <vulkan/vulkan.h>
#include <vma/vk_mem_alloc.h>
namespace Candy::Graphics
{
  class Texture
  {
  private:
    VkImage image;
    VmaAllocation allocation;
    void CreateTextureImage();
  
  };
}