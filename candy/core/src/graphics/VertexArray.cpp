#include <candy/graphics/VertexArray.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <candy/graphics/RenderCommand.hpp>
namespace Candy::Graphics
{
    
    VertexArray::VertexArray()
    = default;
    VertexArray::~VertexArray()
    = default;
    
    void VertexArray::Clear()
    {
        vertexBuffers.clear();
        vertexBufferOffsets.clear();
        indexBuffer = nullptr;
    }
    void VertexArray::Bind() const
    {
      RenderCommand::BindVertexArray(this);
    }
    void VertexArray::AddVertexBuffer(const SharedPtr<VertexBuffer> &buffer, uint64_t offset)
    {
        vertexBuffers.push_back(buffer);
        vertexBufferOffsets.push_back(offset);
    }
    void VertexArray::SetIndexBuffer(const SharedPtr<IndexBuffer>& buffer)
    {
        indexBuffer = buffer;
    }
 
    
    SharedPtr<VertexArray> VertexArray::Create()
    {
        return CreateSharedPtr<VertexArray>();
    }
}