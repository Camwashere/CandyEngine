#include "UniformBuffer.hpp"
#include "../Renderer.hpp"
#include "glad/glad.h"
namespace Candy::Graphics {
    UniformBuffer::UniformBuffer(uint32 size, uint32 binding)
    {
        glCreateBuffers(1, &rendererID);
        glNamedBufferData(rendererID, size, nullptr, GL_DYNAMIC_DRAW);
        glBindBufferBase(GL_UNIFORM_BUFFER, binding, rendererID);
    }
    UniformBuffer::~UniformBuffer()
    {
        glDeleteBuffers(1, &rendererID);
    }
    
    void UniformBuffer::SetData(const void* data, uint32 size, uint32 offset)
    {
        glNamedBufferSubData(rendererID, offset, size, data);
    }
    
    SharedPtr<UniformBuffer> UniformBuffer::Create(uint32 size, uint32 binding)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:    CANDY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return CreateSharedPtr<UniformBuffer>(size, binding);
        }
        
        CANDY_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }
}