#include <candy/graphics/shader/ShaderLayout.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <candy/utils/IDManager.hpp>
#include <candy/graphics/RenderCommand.hpp>
namespace Candy::Graphics
{
  std::string ShaderProperty::ToString()const
  {
    std::stringstream ss;
    //ss << "Name: " << name << ", Type: " << ShaderData::TypeToString(type) << ", Binding: " << binding << ", Set: " << set << ", Offset: " << offset << ", Size: " << size;
    return ss.str();
  }
  std::string ShaderLayoutProperty::ToString()const
  {
    std::stringstream ss;
    ss << "Name: " << name << (input? ", Input " : ", Output ") << ", Type: " << ShaderData::TypeToString(type) << ", Binding: " << binding << ", Set: " << set << ", Offset: " << offset << ", Stride: " << stride << ", Location: " << location << ", Input: " << input;
    return ss.str();
  }
  
  ShaderLayout::ShaderLayout()
  {
    pipeline.AddDynamicStates({VK_DYNAMIC_STATE_VIEWPORT,VK_DYNAMIC_STATE_SCISSOR});
  }
  
  void ShaderLayout::BakePipeline(VkRenderPass renderPass, const std::vector<VkPipelineShaderStageCreateInfo>& createInfos)
  {
    VkPipelineLayout pipelineLayout = BakePipelineLayout();
    pipeline.Bake(renderPass, GetVertexBindingDescriptions(), GetVertexAttributeDescriptions(), createInfos, pipelineLayout);
    //DestroyShaderModules();
    
  }
  
  VkPipelineLayout ShaderLayout::BakePipelineLayout()
  {
    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    VkPipelineLayout pipelineLayout;
    
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    
    
    auto descriptorSetLayouts = BakeDescriptorSetLayouts();
    //CANDY_CORE_INFO("DESCRIPTOR SET VECTOR SIZE: {}", descriptorSetLayouts.size());
    for (auto d : descriptorSetLayouts)
    {
      if (d==VK_NULL_HANDLE)
      {
        CANDY_CORE_ERROR("NULL DESCRIPTOR SET LAYOUT HANDLE");
      }
    }
    pipelineLayoutInfo.setLayoutCount = descriptorSetLayouts.size();
    pipelineLayoutInfo.pSetLayouts = descriptorSetLayouts.data();
    
    auto pushConstantRanges = GetPushConstantRanges();
    //CANDY_CORE_INFO("Push Constant Range Count: {0}", pushConstantRanges.size());
    pipelineLayoutInfo.pushConstantRangeCount = pushConstantRanges.size(); // Optional
    pipelineLayoutInfo.pPushConstantRanges = pushConstantRanges.data(); // Optional
    
    CANDY_CORE_ASSERT(vkCreatePipelineLayout(Vulkan::LogicalDevice(), &pipelineLayoutInfo, nullptr, &pipelineLayout) == VK_SUCCESS, "Failed to create pipeline layout!");
    Vulkan::DeletionQueue().Push(pipelineLayout);
    return pipelineLayout;
  }
  std::vector<VkDescriptorSetLayout> ShaderLayout::BakeDescriptorSetLayouts()
  {
    std::vector<VkDescriptorSetLayout> layouts;
    layouts.resize(FRAME_OVERLAP);
    
    for (int i=0; i<FRAME_OVERLAP; i++)
    {
      DescriptorBuilder builder = DescriptorBuilder::Begin();
      
      
      for (const auto& block : uniformBlockProperties)
      {
        builder.AddBinding(block.binding, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, ShaderData::StageToVulkan(block.stage));
        //builder.BindBuffer(block.binding, &bufferInfo, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, ShaderData::StageToVulkan(block.stage));
      }
      for (const auto& block : uniformImageProperties)
      {
        //CANDY_CORE_INFO("IMAGE BINDING: {}", block.binding);
        builder.AddBinding(block.binding, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, ShaderData::StageToVulkan(block.stage));
        //builder.BindImage(block.binding, &imageInfo, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, ShaderData::StageToVulkan(block.stage));
      }
      
      builder.BuildLayout(&Vulkan::GetCurrentContext().GetFrame(i).globalDescriptor, layouts[i]);
      
      //Vulkan::PushDeleter([=, this](){vkDestroyDescriptorSetLayout(Vulkan::LogicalDevice(), layouts[i], nullptr);});
    }
    return layouts;
    
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
  void ShaderLayout::CalculateProperties()
  {
    Utils::IDManager<uint32_t> parentIDManager;
    Utils::IDManager<uint32_t> propertyIDManager;
    for (const auto& block : uniformBlockProperties)
    {
      ShaderParentProperty parentProperty{};
      parentProperty.name = block.name;
      parentProperty.id = parentIDManager.Assign();
      parentProperty.binding = block.binding;
      uint32_t offset = 0;
      parentProperties.push_back(parentProperty);
      for (const auto& value : block.properties)
      {
        ShaderProperty property{};
        property.name = value.name;
        property.id = propertyIDManager.Assign();
        property.type = value.type;
        property.parentBlockID = parentProperty.id;
        property.size = ShaderData::TypeSize(property.type);
        property.offset = offset;
        offset += property.size;
        propertyMap[property.name] = properties.size();
        properties.push_back(property);
      }
    }
    Utils::IDManager<uint32_t> imageIDManager;
    for (const auto& image : uniformImageProperties)
    {
      ShaderParentProperty parentProperty{};
      parentProperty.name = image.name;
      parentProperty.id = imageIDManager.Assign();
      parentProperty.binding = image.binding;
      imageProperties.push_back(parentProperty);
    }
    
    Utils::IDManager<uint32_t> pushConstantIDManager;
    for (const auto& block : pushConstantBlockProperties)
    {
      for (const auto& push : block.properties)
      {
        ShaderPushProperty property{};
        property.id = pushConstantIDManager.Assign();
        property.name = push.name;
        property.stage = block.stage;
        property.type = push.type;
        property.size = push.size;
        property.offset = push.offset;
        pushPropertyMap[property.name] = pushProperties.size();
        pushProperties.push_back(property);
      }
    }
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
  uint32_t ShaderLayout::PushConstant(const std::string& name, const void* data)
  {
    auto it = pushPropertyMap.find(name);
    if (it != pushPropertyMap.end())
    {
      uint32_t id = it->second;
      PushConstant(id, data);
      return id;
    }
    CANDY_CORE_ASSERT(false, "Push constant name not found");
    return 0;
  }
  void ShaderLayout::PushConstant(uint32_t id, const void* data)
  {
    CANDY_CORE_ASSERT(id < pushProperties.size(), "Push constant id out of range");
    auto& prop = pushProperties[id];
    
    RenderCommand::PushConstants(pipeline.GetLayout(), prop.stage, prop.offset, prop.size, data);
  }
  uint32_t ShaderLayout::SetUniform(const std::string& name, const void* data)
  {
    auto it = propertyMap.find(name);
    if (it != propertyMap.end())
    {
      uint32_t id = it->second;
      SetUniform(id, data);
      return id;
    }
    CANDY_CORE_ERROR("Uniform name: {0} was not found", name);
    CANDY_CORE_ASSERT(false);
    return 0;
  }
  void ShaderLayout::SetUniform(uint32_t id, const void* data)
  {
    CANDY_CORE_ASSERT(id < properties.size(), "Uniform id out of range");
    auto& prop = properties[id];
    auto& parent = parentProperties[prop.parentBlockID];
    
    RenderCommand::SetUniform(pipeline, prop.offset, prop.size, data);
  }
  uint32_t ShaderLayout::GetLayoutVertexStride()const
  {
    return layoutVertexStride;
  }
  
  VkPipeline ShaderLayout::GetPipeline()const{return pipeline;}
  VkPipelineLayout ShaderLayout::GetPipelineLayout()const{return pipeline.GetLayout();}

}