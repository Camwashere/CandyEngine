#include <candy/graphics/shader/ShaderLayout.hpp>
#include <candy/graphics/Vulkan.hpp>
namespace Candy::Graphics
{
  std::string ShaderProperty::ToString()const
  {
    std::stringstream ss;
    ss << "Name: " << name << ", Type: " << ShaderData::TypeToString(type) << ", Binding: " << binding << ", Set: " << set << ", Offset: " << offset << ", Size: " << size;
    return ss.str();
  }
  std::string ShaderLayoutProperty::ToString()const
  {
    std::stringstream ss;
    ss << "Name: " << name << (input? ", Input " : ", Output ") << ", Type: " << ShaderData::TypeToString(type) << ", Binding: " << binding << ", Set: " << set << ", Offset: " << offset << ", Stride: " << stride << ", Location: " << location << ", Input: " << input;
    return ss.str();
  }
  void ShaderLayout::CalculateOffsetsAndStride()
  {
    std::uint64_t offset=0;
    uint32_t stride=0;
    for (auto& element : inputLayoutProperties)
    {
      if (element.stage == ShaderData::Stage::Vertex)
      {
        element.offset = offset;
        uint64_t elementSize = ShaderData::TypeSize(element.type);
        offset += elementSize;
        stride += elementSize;
      }
      
    }
    layoutVertexStride = stride;
  
  }
  size_t ShaderLayout::MaxSetCount()const
  {
    uint32_t maxSet=0;
    for(const auto& block : uniformBlockProperties)
    {
      if (block.set > maxSet)
      {
        maxSet = block.set;
      }
    }
    for (const auto& block : uniformImageProperties)
    {
      if (block.set > maxSet)
      {
        maxSet = block.set;
      }
    }
    return maxSet+1;
  }
 /* std::vector<VkDescriptorSetLayout> ShaderLayout::GetDescriptorSetLayouts()
  {
    
    std::vector<VkDescriptorSetLayout> layouts;
    DescriptorBuilder builder = DescriptorBuilder::Begin();
    
    
    std::vector<VkDescriptorSetLayoutBinding> bindings;
    for (int i=0; i<FRAME_OVERLAP; i++)
    {
      VkDescriptorBufferInfo bufferInfo{};
      bufferInfo.buffer = *Vulkan::GetCurrentContext().GetFrame(i).uniformBuffer;
      bufferInfo.offset = 0;
      bufferInfo.range = sizeof(Color);
      
      
      VkDescriptorImageInfo imageInfo{};
      imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
      imageInfo.imageView = textureImageView;
      imageInfo.sampler = textureImageView.GetSampler();
      for (const auto& block : uniformBlockProperties)
      {
        builder.BindBuffer(block.binding, &bufferInfo, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, ShaderData::StageToVulkan(block.stage));
        *//*VkDescriptorSetLayoutBinding binding{};
        binding.binding = block.binding;
        binding.stageFlags = ShaderData::StageToVulkan(block.stage);
        binding.pImmutableSamplers = nullptr;
        binding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
        
        binding.descriptorCount = 1;
        bindings.push_back(binding);*//*
        
      }
      for (const auto& block : uniformImageProperties)
      {
        builder.BindImage(block.binding, nullptr, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, ShaderData::StageToVulkan(block.stage));
        *//*VkDescriptorSetLayoutBinding binding{};
        binding.binding = block.binding;
        binding.stageFlags = ShaderData::StageToVulkan(block.stage);
        binding.pImmutableSamplers = nullptr;
        binding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        binding.descriptorCount = 1;
        bindings.push_back(binding);*//*
        //bindings.push_back(binding);
      }
      VkDescriptorSetLayout layout;
      builder.Build(&Vulkan::GetCurrentContext().GetFrame(i).globalDescriptor, layout);
      layouts.push_back(layout);
    }
    
    
   
    return layouts;
  
  }*/
  std::vector<VkPushConstantRange> ShaderLayout::GetPushConstantRanges()
  {
    std::vector<VkPushConstantRange> pushConstantRanges;
    for (const auto& block : pushConstantBlockProperties)
    {
      VkPushConstantRange range{};
      range.size = 0;
      range.offset = block.offset;
      range.stageFlags = ShaderData::StageToVulkan(block.stage);
      for(const auto& prop : block.properties)
      {
        range.size += prop.size;
      }
      pushConstantRanges.push_back(range);
    }
    return pushConstantRanges;
  }
  std::vector<VkVertexInputBindingDescription> ShaderLayout::GetVertexBindingDescriptions()const
  {
    std::vector<VkVertexInputBindingDescription> descriptions{};
    descriptions.push_back({0, layoutVertexStride, VK_VERTEX_INPUT_RATE_VERTEX});
    return descriptions;
  }
  std::vector<VkVertexInputAttributeDescription> ShaderLayout::GetVertexAttributeDescriptions()const
  {
    std::vector<VkVertexInputAttributeDescription> descriptions{};
    for (const auto& buf : inputLayoutProperties)
    {
      if (buf.stage == ShaderData::Stage::Vertex)
      {
        descriptions.push_back({buf.location, buf.binding, ShaderData::TypeToVulkan(buf.type), buf.offset});
      }
    }
    return descriptions;
  }
  
  
  void ShaderLayout::AddPushConstantBlockProperty(const ShaderPushConstantBlockProperty& prop)
  {
    pushConstantBlockProperties.push_back(prop);
  }
  void ShaderLayout::AddUniformBlockProperty(const ShaderUniformBlockProperty& prop)
  {
    uniformBlockProperties.push_back(prop);
  }
  void ShaderLayout::AddUniformImageProperty(const ShaderUniformImageProperty& prop)
  {
    uniformImageProperties.push_back(prop);
  }
  void ShaderLayout::AddInputLayoutProperty(const std::string& name, ShaderData::Stage stage, ShaderData::Type type, std::uint32_t binding, std::uint32_t set, std::uint32_t offset, std::uint32_t stride, std::uint32_t location)
  {
    AddLayoutProperty(name, true, stage,  type, binding, set, offset, stride, location);
  }
  void ShaderLayout::AddOutputLayoutProperty(const std::string& name, ShaderData::Stage stage, ShaderData::Type type, std::uint32_t binding, std::uint32_t set, std::uint32_t offset, std::uint32_t stride, std::uint32_t location)
  {
    AddLayoutProperty(name, false, stage,  type, binding, set, offset, stride, location);
  }
  void ShaderLayout::AddLayoutProperty(const std::string& name, bool isInput, ShaderData::Stage stage, ShaderData::Type type, std::uint32_t binding, std::uint32_t set, std::uint32_t offset, std::uint32_t stride, std::uint32_t location)
  {
    if (isInput)
    {
      inputLayoutProperties.push_back({name, stage, type, binding, set, offset, stride, location, isInput});
    }
    else
    {
      outputLayoutProperties.push_back({name, stage, type, binding, set, offset, stride, location, isInput});
    }
    
    
  
  }
  
  uint32_t ShaderLayout::GetLayoutVertexStride()const
  {
    return layoutVertexStride;
  }

}