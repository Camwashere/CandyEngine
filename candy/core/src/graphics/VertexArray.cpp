#include <candy/graphics/VertexArray.hpp>
#include <candy/graphics/Vulkan.hpp>
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
        indexBuffer;
        indexBuffer = nullptr;
    }
    void VertexArray::Bind()
    {
      Vulkan::GetCurrentCommandBuffer().Bind(this);
    
    
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
    std::vector<VkVertexInputBindingDescription> VertexArray::GetVertexBindingDescriptions()const
    {
        std::vector<VkVertexInputBindingDescription> descriptions{};
        for (const auto& buf : vertexBuffers)
        {
            descriptions.push_back(buf->GetVertexBindingDescription());
        }
        return descriptions;
    }
    
    std::vector<VkVertexInputAttributeDescription> VertexArray::GetVertexAttributeDescriptions()const
    {
        std::vector<VkVertexInputAttributeDescription> descriptions{};
        for (const auto& buf : vertexBuffers)
        {
            std::vector<VkVertexInputAttributeDescription> bufDescriptions = buf->GetLayout().GetAttributeDescriptions();
            for (const auto& desc : bufDescriptions)
            {
                descriptions.push_back(desc);
            }
        }
        return descriptions;
    }
    uint64_t VertexArray::GetVertexBindingDescriptionCount()const{return vertexBuffers.size();}
    uint64_t VertexArray::GetVertexAttributeDescriptionCount()const
    {
        uint64_t count=0;
        for(const auto& buffer : vertexBuffers)
        {
            count+=buffer->GetLayout().GetElements().size();
        }
        return count;
    }
    
    SharedPtr<VertexArray> VertexArray::Create()
    {
        return CreateSharedPtr<VertexArray>();
    }
}