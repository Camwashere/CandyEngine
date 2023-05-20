#pragma once

#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "BufferLayout.hpp"
#include <Candy/CandyEngineBase.hpp>
#include <vector>
namespace Candy::Graphics{
        class VertexArray {
        private:
            uint32 rendererID;
            uint32 vertexBufferIndex=0;
            std::vector<SharedPtr<VertexBuffer>> vertexBuffers;
            SharedPtr<IndexBuffer> indexBuffer;
        public:
            VertexArray();
            ~VertexArray();
        
        public:
            void Bind() const;
            void Unbind() const;
            void AddVertexBuffer(const SharedPtr<VertexBuffer> &vertexBuffer);
            void SetIndexBuffer(const SharedPtr<IndexBuffer>& indexBufferValue);
            
            const std::vector<SharedPtr<VertexBuffer>>& GetVertexBuffers()const{return vertexBuffers;}
            const SharedPtr<IndexBuffer>& GetIndexBuffer()const{return indexBuffer;}
            
            static SharedPtr<VertexArray> Create();
        };
}




