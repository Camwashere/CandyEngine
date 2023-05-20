#include "IndexBuffer.hpp"

#include "../GraphicsContext.hpp"
#include "../Renderer.hpp"
namespace Candy::Graphics {
        IndexBuffer::IndexBuffer(uint *indices, uint count) : count(count) {
            //ASSERT(sizeof(unsigned int) == sizeof(GLuint));
            glCreateBuffers(1, &rendererID);
            glBindBuffer(GL_ARRAY_BUFFER, rendererID);
            glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint), indices, GL_STATIC_DRAW);
            
        }
        
        IndexBuffer::~IndexBuffer() {
            glDeleteBuffers(1, &rendererID);
        }
        
        void IndexBuffer::Bind() const {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
        }
        
        void IndexBuffer::Unbind() const {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
        
        SharedPtr<IndexBuffer> IndexBuffer::Create(uint* indices, uint count)
        {
            switch(Renderer::GetAPI())
            {
                case RendererAPI::API::None : std::cerr << "No renderer api" << std::endl; return nullptr;
                case RendererAPI::API::OpenGL : return CreateSharedPtr<IndexBuffer>(indices, count);
            }
            std::cerr << "Error could not find API" << std::endl;
            return nullptr;
        }
}
