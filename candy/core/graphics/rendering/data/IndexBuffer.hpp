#pragma once

#include <Candy/CandyEngineBase.hpp>
namespace Candy::Graphics{
        class IndexBuffer {
        private:
            uint rendererID;
            uint count;
        public:
            IndexBuffer(uint *indices, uint count);
            ~IndexBuffer();
        
        public:
            void Bind() const;
            void Unbind() const;
            inline uint GetCount() const { return count; }
            
            static SharedPtr<IndexBuffer> Create(uint* indices, uint count);
        };
}



