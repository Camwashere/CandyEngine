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
    
    void SetDataInternal(const void* vertices);
  
  public:
    VertexBuffer(const BufferLayout& layout, uint64_t countPerElement);
    VertexBuffer(float *vertices, uint64_t size);
    ~VertexBuffer();
  
  public:
    using VulkanBuffer::operator VkBuffer;
  
  public:

    
    template<typename T, typename...VECTOR_LIST>
    requires(IsVectorContainer<VECTOR_LIST> && ...)
    void SetData(const VECTOR_LIST&... vector)
    {
      std::vector<T> data = BufferLayout::Flatten<T>(layout, std::forward<const VECTOR_LIST&>(vector)...);
      for (int i=0; i<data.size(); i+=8)
      {
        Math::Vector3 vertex = {data[i], data[i+1], data[i+2]};
        Math::Vector3 normal = {data[i+3], data[i+4], data[i+5]};
        Math::Vector2 uv = {data[i+6], data[i+7]};
        CANDY_CORE_INFO("Vertex: {0}, Normal: {1}, UV: {2}", vertex, normal, uv);
      }
      SetDataInternal(data.data());
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
  

  
  
  
  
  
  
  
}