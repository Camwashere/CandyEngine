#pragma once
#include "CandyPch.hpp"
#include "vke/descriptor_allocator.h"
namespace Candy::Graphics
{
  class DescriptorAllocator
  {
  private:
    UniquePtr<vke::DescriptorAllocatorPool> pool;
    
  public:
    explicit DescriptorAllocator(const VkDevice& logicalDevice);
    
  public:
    vke::DescriptorAllocatorHandle GetHandle();
    bool Allocate(VkDescriptorSet* set, VkDescriptorSetLayout layout);
    void Flip();
    void Destroy();
  
  };
}