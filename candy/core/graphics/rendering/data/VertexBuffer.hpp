#pragma once


#include <Candy/CandyEngineBase.hpp>
#include "BufferLayout.hpp"
namespace Candy::Graphics {
        class VertexBuffer {
        private:
            uint32 rendererID;
            BufferLayout layout;
        public:
            VertexBuffer(uint32 size);
            VertexBuffer(float *vertices, uint32 size);
            ~VertexBuffer();
        
        public:
            void Bind() const;
            void Unbind() const;
            void SetData(const void* data, uint32 size);
            const BufferLayout& GetLayout()const{return layout;}
            void SetLayout(const BufferLayout& bufferLayout){ layout = bufferLayout;}
            
            static SharedPtr<VertexBuffer> Create(uint32 size);
            static SharedPtr<VertexBuffer> Create(float* vertices, uint32 size);
            
        };
}

