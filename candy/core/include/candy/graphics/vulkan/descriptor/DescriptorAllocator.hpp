#pragma once
#include "CandyPch.hpp"
#include <vulkan/vulkan.h>
#include "DescriptorAllocatorPool.hpp"
namespace Candy::Graphics
{
  
  class DescriptorAllocator
  {
  private:
    UniquePtr<DescriptorAllocatorPool> pool;
    
  public:
    explicit DescriptorAllocator();
    
  public:
    DescriptorAllocatorHandle GetHandle();
    bool Allocate(VkDescriptorSet* set, VkDescriptorSetLayout layout);
    void Flip(uint32_t frameIndex);
    void Reset();
    //void Destroy();
  
  };
}