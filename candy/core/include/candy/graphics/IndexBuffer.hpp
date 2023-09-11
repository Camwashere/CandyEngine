#pragma once
#include "CandyPch.hpp"
#include "BufferLayout.hpp"
#include "vulkan/VulkanBuffer.hpp"
#include "vma/vk_mem_alloc.h"
namespace Candy::Graphics
{
    class GraphicsContext;
    class CommandBuffer;
    
    class IndexBuffer : public VulkanBuffer
    {
    private:
        uint64_t count;
        
    private:
      void SetDataInternal(const void* indices);
        
    public:
      explicit IndexBuffer(uint64_t count);
        IndexBuffer(uint32_t* indices, uint64_t count);
        ~IndexBuffer();
        
    public:
      void SetData(uint32_t* indices, uint64_t indexCount);
    
    public:
        using VulkanBuffer::operator VkBuffer;
    
    public:
       
        [[nodiscard]] uint64_t GetCount()const{return count;}
        
        
    public:
      static SharedPtr<IndexBuffer> Create(uint64_t count);
        static SharedPtr<IndexBuffer> Create(uint32_t* indices, uint64_t count);
        
    private:
        friend class GraphicsContext;
        
        
        
    };
}