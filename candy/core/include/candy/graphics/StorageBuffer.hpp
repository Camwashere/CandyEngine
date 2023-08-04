#pragma once
#include "vulkan/VulkanBuffer.hpp"
namespace Candy::Graphics
{
  class StorageBuffer : public VulkanBuffer
  {
  private:
    uint64_t objectSize;
    uint64_t objectCount;
  public:
    
    explicit StorageBuffer(uint64_t objectSize, uint64_t objectCount);
  };
}