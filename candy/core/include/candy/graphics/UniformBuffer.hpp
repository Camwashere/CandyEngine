#pragma once
#include "candy/graphics/shader/ShaderData.hpp"
#include <CandyPch.hpp>
#include "vulkan/VulkanBuffer.hpp"
#include "vma/vk_mem_alloc.h"
namespace Candy::Graphics
{
  class UniformBuffer : public VulkanBuffer
  {
    
  public:
    UniformBuffer();
    explicit UniformBuffer(uint64_t originalObjectSize);
    
  public:
    using VulkanBuffer::operator VkBuffer;
    
  public:
    void SetData(uint64_t dataSize, const void* data);
    void SetData(uint64_t offset, uint64_t size, const void* data);
    
  public:
    static uint32_t MaxSize();
    static SharedPtr<UniformBuffer> Create();
    static SharedPtr<UniformBuffer> Create(uint64_t size);
  };
}