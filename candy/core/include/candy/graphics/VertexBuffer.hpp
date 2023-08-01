#pragma once
#include "CandyPch.hpp"
#include "BufferLayout.hpp"

#include "vma/vk_mem_alloc.h"
namespace Candy::Graphics
{
    class GraphicsContext;
    class CommandBuffer;
    
    class VertexBuffer
    {
    private:
        VkBuffer buffer=VK_NULL_HANDLE;
        VmaAllocation allocation=VK_NULL_HANDLE;
        //CommandBuffer* commandBuffer;
        BufferLayout layout;
        uint64_t size=0;
        
    private:
        void CreateStagingBuffer(VkBuffer& buffer, VmaAllocation* allocation);
        //void Destroy();
        
        
    public:
        VertexBuffer(BufferLayout  layout, uint64_t countPerElement);
        VertexBuffer(float* vertices, uint64_t size);
        ~VertexBuffer();
        
    public:
        operator VkBuffer()const{return buffer;}
        operator VkBuffer(){return buffer;}
        
    public:
      
      void SetData(float* data);
      void SetLayout(const BufferLayout& bufferLayout);
      [[nodiscard]] const BufferLayout& GetLayout()const;
      [[nodiscard]] uint64_t Size()const;
      [[nodiscard]] VkVertexInputBindingDescription GetVertexBindingDescription()const;
      
        
        
        
    public:
        static SharedPtr<VertexBuffer> Create(const BufferLayout& layout, uint64_t countPerElement);
        static SharedPtr<VertexBuffer> Create(float* vertices, uint64_t bufferSize);
        
    private:
        friend class GraphicsContext;
        
    
    
    };
}