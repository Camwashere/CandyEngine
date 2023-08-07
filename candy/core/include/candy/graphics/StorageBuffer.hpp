#pragma once
#include "vulkan/VulkanBuffer.hpp"
#include <CandyPch.hpp>
namespace Candy::Graphics
{
  class StorageBuffer : public VulkanBuffer
  {
  private:
    uint64_t objectSize;
    uint64_t objectCount;
    
    
  public:
    explicit StorageBuffer(uint64_t objectSize, uint64_t objectCount);
    
    void Bind(void** data);
    void Unbind();
    
    static SharedPtr<StorageBuffer> Create(uint64_t objectSize, uint64_t objectCount);
  };
}