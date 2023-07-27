#include <candy/graphics/BufferLayout.hpp>
#include <string>
#include <utility>

namespace Candy::Graphics
{
    
    BufferElement::BufferElement(ShaderData::Type dataType, std::string elementName) : type(dataType), name(std::move(elementName))
    {
    
    }
    
    uint64_t BufferElement::Size()const
    {
        return ShaderData::TypeSize(type);
    }
    uint64_t BufferElement::GetComponentCount()const
    {
        return ShaderData::ShaderData::ComponentCount(type);
    }
    VkFormat BufferElement::GetFormat()const
    {
        
        return ShaderData::ShaderData::TypeToVulkan(type);
    }
    
    uint64_t BufferElement::CalculateSize(uint64_t count)const
    {
        return Size() * count;
    }
    
    
    BufferLayout::BufferLayout(std::initializer_list<BufferElement> bufferElements) : elements(bufferElements)
    {
        CalculateOffsetsAndStride();
    }
    
    void BufferLayout::CalculateOffsetsAndStride()
    {
        std::uint64_t offset=0;
        stride=0;
        for (auto& element : elements)
        {
            element.offset = offset;
            uint64_t elementSize = element.Size();
            offset += elementSize;
            stride += elementSize;
        }
    }
    
    void BufferLayout::AddElement(ShaderData::Type type, const std::string& name)
    {
        BufferElement element(type, name);
        size_t size = element.Size();
        uint64_t offset = 0;
        if (!elements.empty())
        {
            offset = elements.back().offset + elements.back().Size();
        }
        element.offset = offset;
        
        stride += size;
        elements.push_back(element);
    }
    
    const BufferElement& BufferLayout::GetElement(uint64_t index)const
    {
        return elements[index];
    }
    std::vector<VkVertexInputAttributeDescription> BufferLayout::GetAttributeDescriptions()const
    {
        std::vector<VkVertexInputAttributeDescription> attributeDescriptions{};
        
        for (const auto& element : elements)
        {
            VkVertexInputAttributeDescription attributeDescription;
            attributeDescription.binding = binding;
            attributeDescription.location = attributeDescriptions.size();
            attributeDescription.format = element.GetFormat();
            attributeDescription.offset = element.offset;
            
            attributeDescriptions.push_back(attributeDescription);
        }
        return attributeDescriptions;
        
    }
    uint32_t BufferLayout::GetStride()const
    {
        return stride;
    }
    
    size_t BufferLayout::GetElementCount()const
    {
        return elements.size();
    }
    
    VkVertexInputBindingDescription BufferLayout::GetBindingDescription()const
    {
        VkVertexInputBindingDescription desc{};
        desc.binding = binding;
        desc.stride = stride;
        desc.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        return desc;
    }
    
    const std::vector<BufferElement>& BufferLayout::GetElements()const{return elements;}
    
   
}
