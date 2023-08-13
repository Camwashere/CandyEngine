#include <candy/graphics/shader/ShaderLayout.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <candy/utils/IDManager.hpp>
#include <candy/graphics/RenderCommand.hpp>
namespace Candy::Graphics
{

  ShaderLayout::ShaderLayout()
  {
    sets.emplace_back();
    pipeline.AddDynamicStates({VK_DYNAMIC_STATE_VIEWPORT,VK_DYNAMIC_STATE_SCISSOR});
  }
  void ShaderLayout::BindAll()
  {
    //CANDY_CORE_INFO("SETS SIZE: {}", sets.size());
    for (size_t i=0; i<sets.size(); i++)
    {
      Bind(i);
    }
  }
  void ShaderLayout::Bind(uint32_t set)
  {
    RenderCommand::BindDescriptorSets(pipeline, set, {Renderer::GetCurrentFrame().GetDescriptorSet(set)}, sets[set].offsets);
  }
  void ShaderLayout::BakePipeline(VkRenderPass renderPass, const std::vector<VkPipelineShaderStageCreateInfo>& createInfos)
  {
    VkPipelineLayout pipelineLayout = BakePipelineLayout();
    pipeline.Bake(renderPass, GetVertexBindingDescriptions(), GetVertexAttributeDescriptions(), createInfos, pipelineLayout);
    
  }
  
  VkPipelineLayout ShaderLayout::BakePipelineLayout()
  {
    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    VkPipelineLayout pipelineLayout;
    
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    
    
    auto descriptorSetLayouts = BakeDescriptorSetLayouts();
    
    
    pipelineLayoutInfo.setLayoutCount = descriptorSetLayouts.size();
    pipelineLayoutInfo.pSetLayouts = descriptorSetLayouts.data();
    
    auto pushConstantRanges = GetPushConstantRanges();
    pipelineLayoutInfo.pushConstantRangeCount = pushConstantRanges.size(); // Optional
    pipelineLayoutInfo.pPushConstantRanges = pushConstantRanges.data(); // Optional
    
    CANDY_CORE_ASSERT(vkCreatePipelineLayout(Vulkan::LogicalDevice(), &pipelineLayoutInfo, nullptr, &pipelineLayout) == VK_SUCCESS, "Failed to create pipeline layout!");
    Vulkan::DeletionQueue().Push(pipelineLayout);
    return pipelineLayout;
  }
  std::vector<VkDescriptorSetLayout> ShaderLayout::BakeDescriptorSetLayouts()
  {
    std::vector<VkDescriptorSetLayout> layouts;
    //int LAYOUT_NUM = 2;
    size_t LAYOUT_NUM = sets.size();
    layouts.resize(LAYOUT_NUM);
    
    for (size_t i=0; i<LAYOUT_NUM; i++)
    {
      DescriptorBuilder builder = DescriptorBuilder::Begin();
      for (const auto& block : sets[i].blocks)
      {
        builder.AddBinding(block.binding, GetDescriptorType(i), ShaderData::StageToVulkan(block.stage));
      }
      for (const auto& tex : sets[i].textures)
      {
        builder.AddBinding(tex.binding, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, ShaderData::StageToVulkan(tex.stage));
      }
      layouts[i] = builder.BuildLayout();
      for (int f=0; f<FRAME_OVERLAP; f++)
      {
        CANDY_CORE_ASSERT(builder.AllocateDescriptorSet(&Vulkan::GetCurrentContext().GetFrame(f).GetDescriptorSet(i), layouts[i]), "Failed to allocate descriptor set!");
      }
    }
    return layouts;
    
  }
  
  VkDescriptorType ShaderLayout::GetDescriptorType(size_t setIndex)
  {
    switch(setIndex)
    {
      case 0:
        return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
      case 1:
        return VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;
      default:
        CANDY_CORE_ASSERT(false, "Invalid descriptor set index!");
        return VK_DESCRIPTOR_TYPE_MAX_ENUM;
    }
  }
  


  std::vector<VkPushConstantRange> ShaderLayout::GetPushConstantRanges()
  {
    std::vector<VkPushConstantRange> pushConstantRanges;
    for (const auto& block : pushBlocks)
    {
      VkPushConstantRange range{};
      range.size = 0;
      range.offset = block.offset;
      range.stageFlags = ShaderData::StageToVulkan(ShaderData::Stage::All);
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
    
    descriptions.push_back({vertexLayout.GetBinding(), vertexLayout.GetStride(), VK_VERTEX_INPUT_RATE_VERTEX});
    return descriptions;
  }
  std::vector<VkVertexInputAttributeDescription> ShaderLayout::GetVertexAttributeDescriptions()const
  {
    std::vector<VkVertexInputAttributeDescription> descriptions{};
    
    for (const auto& e : vertexLayout)
    {
      //CANDY_CORE_INFO("NAME: {0}, LOCATION: {1}, TYPE: {2}, OFFSET: {3}", e.name, e.location, ShaderData::TypeToString(e.type), e.offset);
      descriptions.push_back({e.location, 0, ShaderData::TypeToVulkan(e.type), e.offset});
    }
    return descriptions;
  }
  uint32_t ShaderLayout::AddBlock(const ShaderBlock& block)
  {
    ShaderBlock b = block;
    if (b.set >= sets.size())
    {
      sets.resize(b.set+1);
    }
    return sets[b.set].AddBlock(b);
    
  }
  void ShaderLayout::AddPushBlock(const ShaderPushBlock& block)
  {
    ShaderPushBlock b = block;
    b.id = pushBlocks.size();
    pushBlocks.push_back(b);
    pushBlockMap[b.name] = b.id;
    ShaderPushBlock& blockRef = pushBlocks.back();
    for (auto& p : blockRef.properties)
    {
      AddPushProperty(blockRef.id, &p);
    }
  }
  void ShaderLayout::AddPushProperty(uint32_t pushBlockID, ShaderPushProperty* property)
  {
    property->parentID = pushBlockID;
    property->id = pushProperties.size();
    pushProperties.push_back(property);
    pushPropertyMap[property->name] = property->id;
  
  }
  void ShaderLayout::AddTexture(const ShaderTexture& texture)
  {
    ShaderTexture t = texture;
    if (t.set >= sets.size())
    {
      sets.resize(t.set+1);
    }
    sets[t.set].AddTexture(t);
  }

  void ShaderLayout::AddVertexInput(const std::string& name, ShaderData::Type type, uint32_t location)
  {
    vertexLayout.AddElement(name, type, location);
  }

  uint32_t ShaderLayout::PushConstant(const std::string& name, const void* data)
  {
    const auto& it = pushPropertyMap.find(name);
    if (it != pushPropertyMap.end())
    {
      auto id = it->second;
      PushConstant(id, data);
      return id;
    }
    CANDY_CORE_ASSERT(false, "Push constant name not found");
    return {};
  }
  void ShaderLayout::PushConstant(uint32_t id, const void* data)
  {
    CANDY_CORE_ASSERT(id < pushBlocks.size());
    
    auto& prop = pushProperties[id];
    RenderCommand::PushConstants(pipeline.GetLayout(), ShaderData::Stage::All, prop->offset, prop->size, data);
  }
  uint32_t ShaderLayout::SetUniform(const std::string& name, const void* data)
  {
    const auto& it = sets[0].propertyMap.find(name);
    if (it != sets[0].propertyMap.end())
    {
      uint32_t id = it->second;
      SetUniform(id, data);
      return id;
    }
    CANDY_CORE_ERROR("Uniform name: {0} was not found", name);
    CANDY_CORE_ASSERT(false);
    return {};
  }
  void ShaderLayout::SetUniform(uint32_t key, const void* data)
  {
    const auto& set = sets[0];
    const auto& prop = set.GetProperty(key);
    
    RenderCommand::SetUniform(prop.GlobalOffset(), prop.size, data);
    //RenderCommand::BindDescriptorSets(pipeline, {Vulkan::GetCurrentContext().GetCurrentFrame().GlobalDescriptor()}, set.offsets);
  }
  
  
  VkPipeline ShaderLayout::GetPipeline()const{return pipeline;}
  VkPipelineLayout ShaderLayout::GetPipelineLayout()const{return pipeline.GetLayout();}

}