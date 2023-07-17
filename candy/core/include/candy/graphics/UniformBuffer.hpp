#pragma once
#include "ShaderData.hpp"
#include "vma/vk_mem_alloc.h"
namespace Candy::Graphics
{
  class UniformBuffer
  {
  private:
    uint32_t binding;
    VkBuffer buffer;
    VmaAllocation allocation;
    void* data;
  };
}