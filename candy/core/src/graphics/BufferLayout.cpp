#include <candy/graphics/BufferLayout.hpp>
#include <string>
#include <utility>

namespace Candy::Graphics
{
    
    BufferElement::BufferElement(std::string elementName, ShaderData::Type dataType, uint32_t loc) : type(dataType), name(std::move(elementName)), location(loc)
    {
        //CANDY_CORE_INFO("BufferElement: {0} {1} {2}", name, ShaderData::TypeToString(type), location);
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
      CANDY_PROFILE_FUNCTION();
        CalculateOffsetsAndStride();
    }
    
    void BufferLayout::CalculateOffsetsAndStride()
    {
      CANDY_PROFILE_FUNCTION();
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
  void BufferLayout::Recalculate()
  {
    
    CalculateOffsetsAndStride();
  }
    void BufferLayout::AddElement(std::string elementName, ShaderData::Type dataType, uint32_t location)
    {
      CANDY_PROFILE_FUNCTION();
        BufferElement element(std::move(elementName), dataType, location);
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
  uint32_t BufferLayout::GetBinding()const
  {
        return binding;
  }
    const BufferElement& BufferLayout::GetElement(uint64_t index)const
    {
        return elements[index];
    }
   /* std::vector<VkVertexInputAttributeDescription> BufferLayout::GetAttributeDescriptions()const
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
        
    }*/
    uint32_t BufferLayout::GetStride()const
    {
        return stride;
    }
    
    size_t BufferLayout::GetElementCount()const
    {
        return elements.size();
    }
    
    /*VkVertexInputBindingDescription BufferLayout::GetBindingDescription()const
    {
        VkVertexInputBindingDescription desc{};
        desc.binding = binding;
        desc.stride = stride;
        desc.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        return desc;
    }*/
    
    const std::vector<BufferElement>& BufferLayout::GetElements()const{return elements;}
    
   
}
