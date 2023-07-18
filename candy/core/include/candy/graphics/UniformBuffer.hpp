#pragma once
#include "ShaderData.hpp"
#include <CandyPch.hpp>
#include "vma/vk_mem_alloc.h"
namespace Candy::Graphics
{
  class UniformBuffer
  {
  private:
    VkBuffer buffer;
    VmaAllocation allocation;
    void* data;
    uint64_t size;
    
    
  public:
    explicit UniformBuffer(uint64_t size);
    
  public:
    operator VkBuffer()const;
    operator VkBuffer();
    
  public:
    void SetData(void* data);
    void Destroy();
    
  public:
    static SharedPtr<UniformBuffer> Create(uint64_t size);
  };
}