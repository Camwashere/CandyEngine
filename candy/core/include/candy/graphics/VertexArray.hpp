#pragma once
#include "CandyPch.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
namespace Candy::Graphics
{
    class VertexArray
    {
    private:
        std::vector<SharedPtr<VertexBuffer>> vertexBuffers;
        std::vector<uint64_t> vertexBufferOffsets;
        SharedPtr<IndexBuffer> indexBuffer;
        
    private:
    
        
    public:
        VertexArray();
        ~VertexArray();
        
    public:
        void AddVertexBuffer(const SharedPtr<VertexBuffer>& vertexBuffer, uint64_t offset=0);
        void SetIndexBuffer(const SharedPtr<IndexBuffer>& indexBuffer);
        void Clear();
        void Bind() const;
        [[nodiscard]] uint32_t GetVertexCount()const;
        [[nodiscard]] uint32_t GetIndexCount()const;
        
        
    public:
        static SharedPtr<VertexArray> Create();
        
    private:
        friend class CommandBuffer;
        friend class RenderCommand;
        friend class GraphicsContext;
    };

}