#pragma once
#include "candy/graphics/shader/ShaderData.hpp"
#include <CandyPch.hpp>
#include "vma/vk_mem_alloc.h"
namespace Candy::Graphics
{
  class UniformBuffer
  {
  private:
    VkBuffer buffer;
    VmaAllocation allocation;
    //void* data;
    uint64_t size;
    //uint64_t paddedSize;
    //uint64_t originalSize;
    //uint64_t totalSize;
    
    
  public:
    explicit UniformBuffer(uint64_t originalObjectSize);
    //~UniformBuffer();
    
  public:
    operator VkBuffer()const;
    operator VkBuffer();
    
  public:
    void SetData(uint64_t dataSize, const void* data);
    void SetData(uint64_t offset, uint64_t size, const void* data);
    //void* GetData();
    void Destroy();
   
    
  public:
    static SharedPtr<UniformBuffer> Create(uint64_t size);
  };
}