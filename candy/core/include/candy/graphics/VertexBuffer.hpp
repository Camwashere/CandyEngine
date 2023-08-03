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
  
  private:
    template<IsPrimitive T>
    void SetDataInternal(T *vertices);
  
  public:
    VertexBuffer(BufferLayout layout, uint64_t countPerElement);
    VertexBuffer(float *vertices, uint64_t size);
    ~VertexBuffer();
  
  public:
    using VulkanBuffer::operator VkBuffer;
  
  public:
    template<typename T>
    void SetData(T *vertices);
    
    template<typename T, typename...VECTOR_LIST>
    requires(IsVectorContainer<VECTOR_LIST> && ...)
    void SetData(const VECTOR_LIST &... vector)
    {
      std::vector<T> data = BufferLayout::Flatten<T>(layout, std::forward<const VECTOR_LIST &>(vector)...);
      SetData(data.data());
    }
    
    void SetLayout(const BufferLayout &bufferLayout);
    [[nodiscard]] const BufferLayout &GetLayout() const;
    [[nodiscard]] VkVertexInputBindingDescription GetVertexBindingDescription() const;
  
  public:
    static SharedPtr<VertexBuffer> Create(const BufferLayout &layout, uint64_t countPerElement);
    static SharedPtr<VertexBuffer> Create(float *vertices, uint64_t bufferSize);
  
  private:
    friend class GraphicsContext;
  };
  
  template<>
  void VertexBuffer::SetData<float>(float *vertices);
  template<>
  void VertexBuffer::SetData<double>(double *vertices);
  
  
  
  
  
}