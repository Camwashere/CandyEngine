#pragma once

#include "CandyPch.hpp"
#include "BufferLayout.hpp"
#include "vulkan/VulkanBuffer.hpp"
#include "vma/vk_mem_alloc.h"


namespace Candy::Graphics
{
  class GraphicsContext;
  
  class CommandBuffer;
  
  class VertexBuffer : public VulkanBuffer
  {
  private:
    BufferLayout layout;
    uint32_t count;
  
  private:
    void SetDataInternal(const void* vertices);
  
  public:
    explicit VertexBuffer(const BufferLayout& layout);
    VertexBuffer(const BufferLayout& layout, uint64_t countPerElement);
    VertexBuffer(float *vertices, uint64_t size);
    ~VertexBuffer();
  
  public:
    using VulkanBuffer::operator VkBuffer;
  
  public:

    void SetData(const void* data, uint32_t size);
    template<typename T, typename...VECTOR_LIST>
    requires(IsVectorContainer<VECTOR_LIST> && ...)
    void SetData(const VECTOR_LIST&... vector)
    {
      std::vector<T> data = BufferLayout::Flatten<T>(layout, std::forward<const VECTOR_LIST&>(vector)...);
      SetDataInternal(data.data());
    }
    
    void SetLayout(const BufferLayout &bufferLayout);
    [[nodiscard]] const BufferLayout &GetLayout() const;
    [[nodiscard]] VkVertexInputBindingDescription GetVertexBindingDescription() const;
    uint32_t GetCount()const;
  
  public:
    
    static SharedPtr<VertexBuffer> Create(const BufferLayout &layout, uint64_t countPerElement);
    static SharedPtr<VertexBuffer> Create(float *vertices, uint64_t bufferSize);
    static SharedPtr<VertexBuffer> Create(const BufferLayout& layout);
  
  private:
    friend class GraphicsContext;
  };
  

  
  
  
  
  
  
  
}