#pragma once
#include "CandyPch.hpp"
#include "BufferLayout.hpp"
#include "vma/vk_mem_alloc.h"
namespace Candy::Graphics
{
    class GraphicsContext;
    class CommandBuffer;
    
    class IndexBuffer
    {
    private:
        VkBuffer buffer=VK_NULL_HANDLE;
        VmaAllocation allocation=VK_NULL_HANDLE;
        
        CommandBuffer* commandBuffer;
        uint64_t count;
        uint64_t size=0;
        
    private:
        void CreateStagingBuffer(VkBuffer& buffer, VmaAllocation* allocation);
    
    
    public:
        IndexBuffer(CommandBuffer* commandBuf, uint32_t* indices, uint64_t count);
        ~IndexBuffer();
    
    public:
        operator VkBuffer()const{return buffer;}
        operator VkBuffer(){return buffer;}
    
    public:
        [[nodiscard]] uint64_t GetSize()const{return size;}
        [[nodiscard]] uint64_t GetCount()const{return count;}
        
        
    public:
        static SharedPtr<IndexBuffer> Create(CommandBuffer* commandBuf, uint32_t* indices, uint64_t count);
        
    private:
        friend class GraphicsContext;
        
        
        
    };
}