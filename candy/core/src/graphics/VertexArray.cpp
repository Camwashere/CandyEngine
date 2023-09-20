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
      CANDY_PROFILE_FUNCTION();
        vertexBuffers.clear();
        vertexBufferOffsets.clear();
        indexBuffer = nullptr;
    }
  uint32_t VertexArray::GetVertexCount()const
  {
    CANDY_PROFILE_FUNCTION();
    uint32_t count=0;
    if(vertexBuffers.empty())
      return count;
    
    
    for (const auto& vertexBuffer : vertexBuffers)
    {
      count += vertexBuffer->GetCount();
    }
    return count;
  }
  
  uint32_t VertexArray::GetIndexCount()const
  {
    CANDY_PROFILE_FUNCTION();
      if (indexBuffer)
      {
        return indexBuffer->GetCount();
      }
      return 0;
  }
    void VertexArray::Bind() const
    {
      CANDY_PROFILE_FUNCTION();
      RenderCommand::BindVertexArray(this);
    }
    void VertexArray::AddVertexBuffer(const SharedPtr<VertexBuffer> &buffer, uint64_t offset)
    {
      CANDY_PROFILE_FUNCTION();
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