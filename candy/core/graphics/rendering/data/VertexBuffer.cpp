#include "VertexBuffer.hpp"
#include "VertexBuffer.hpp"
#include "../GraphicsContext.hpp"
#include "../Renderer.hpp"
namespace Candy::Graphics {
        VertexBuffer::VertexBuffer(uint32 size)
        {
            glCreateBuffers(1, &rendererID);
            glBindBuffer(GL_ARRAY_BUFFER, rendererID);
            glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
        }
        VertexBuffer::VertexBuffer(float* vertices, uint32 size) {
            glGenBuffers(1, &rendererID);
            glBindBuffer(GL_ARRAY_BUFFER, rendererID);
            glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
            
        }
        
        VertexBuffer::~VertexBuffer() {
            glDeleteBuffers(1, &rendererID);
        }
        
        void VertexBuffer::Bind() const {
            glBindBuffer(GL_ARRAY_BUFFER, rendererID);
        }
        
        void VertexBuffer::Unbind() const {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
        
        void VertexBuffer::SetData(const void* data, uint32 size)
        {
            glBindBuffer(GL_ARRAY_BUFFER, rendererID);
            glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
        }
        SharedPtr<VertexBuffer> VertexBuffer::Create(uint32 size)
        {
            switch (Renderer::GetAPI())
            {
                case RendererAPI::API::None: return nullptr;
                case RendererAPI::API::OpenGL: return CreateSharedPtr<VertexBuffer>(size);
                default:
                    std::cerr << "Unknown renderer api" << std::endl;
                    return nullptr;
            }
            
        }
        SharedPtr<VertexBuffer> VertexBuffer::Create(float* vertices, uint32 size)
        {
            switch (Renderer::GetAPI())
            {
                case RendererAPI::API::None: return nullptr;
                case RendererAPI::API::OpenGL: return CreateSharedPtr<VertexBuffer>(vertices, size);
                default:
                    std::cerr << "Unknown renderer api" << std::endl;
                    return nullptr;
            }
        }
}

