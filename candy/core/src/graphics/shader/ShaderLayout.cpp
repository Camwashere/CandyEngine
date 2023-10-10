#include <candy/graphics/shader/ShaderLayout.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <candy/utils/IDManager.hpp>
#include <candy/graphics/RenderCommand.hpp>
#include <utility>
#include <candy/graphics/shader/ShaderLibrary.hpp>
#include <candy/graphics/Renderer.hpp>
#include <candy/graphics/vulkan/DeletionQueue.hpp>
#include <candy/graphics/vulkan/RenderPass.hpp>
namespace Candy::Graphics
{
  using namespace Math;
  ShaderLayout::ShaderLayout()
  {
    CANDY_PROFILE_FUNCTION();
    materialBufferSize=0;
    globalBufferSize=0;
    sets.emplace_back();
    
  }
  void ShaderLayout::BindAllDescriptorSets(uint32_t renderPassIndex)
  {
    CANDY_PROFILE_FUNCTION();
    std::vector<uint32_t> dynamicOffsets{0, 0};
    RenderCommand::BindDescriptorSets(pipelineLayout, 0, {Renderer::GetCurrentFrame().GlobalDescriptor()}, dynamicOffsets);
    for (size_t i=1; i<sets.size(); i++)
    {
      BindDescriptorSet(renderPassIndex, i);
    }
  }
  void ShaderLayout::BindDescriptorSet(uint32_t renderPassIndex, uint32_t set)
  {
    CANDY_PROFILE_FUNCTION();
    if (sets[set].IsEmpty())
    {
      
      return;
    }
    RenderCommand::BindDescriptorSets(pipelineLayout, set, {Renderer::GetCurrentFrame().GetDescriptorSet(set, renderPassIndex)}, sets[set].offsets);
   
  }
 /* void ShaderLayout::BakePipeline(const std::vector<VkPipelineShaderStageCreateInfo>& createInfos)
  {
    CANDY_PROFILE_FUNCTION();
    VkPipelineLayout pipelineLayout = BakePipelineLayout();
    
    pipeline.Bake(Renderer::GetRenderPass(settings.renderPassIndex), GetVertexBindingDescriptions(), GetVertexAttributeDescriptions(), createInfos, pipelineLayout);
  }*/
  
  void ShaderLayout::BakePipelineLayout(uint32_t renderPassIndex)
  {
    CANDY_PROFILE_FUNCTION();
    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    //VkPipelineLayout pipelineLayout;
    
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    
    
    //auto descriptorSetLayouts = BakeDescriptorSetLayouts();
    auto descriptorSetLayouts = ShaderLibrary::BakeDescriptorSetLayouts(renderPassIndex);
    
    
    pipelineLayoutInfo.setLayoutCount = descriptorSetLayouts.size();
    pipelineLayoutInfo.pSetLayouts = descriptorSetLayouts.data();
    
    auto pushConstantRanges = GetPushConstantRanges();
    pipelineLayoutInfo.pushConstantRangeCount = pushConstantRanges.size(); // Optional
    pipelineLayoutInfo.pPushConstantRanges = pushConstantRanges.data(); // Optional
    
    
    CANDY_VULKAN_CHECK(vkCreatePipelineLayout(Vulkan::LogicalDevice(), &pipelineLayoutInfo, nullptr, &pipelineLayout));
    Vulkan::DeletionQueue().Push(pipelineLayout);
    //return pipelineLayout;
  }
  
  
  VkDescriptorType ShaderLayout::GetDescriptorType(size_t setIndex)
  {
    CANDY_PROFILE_FUNCTION();
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
    CANDY_PROFILE_FUNCTION();
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
    CANDY_PROFILE_FUNCTION();
    std::vector<VkVertexInputBindingDescription> descriptions{};
    VkVertexInputBindingDescription d{};
    d.binding = vertexLayout.GetBinding();
    d.stride = vertexLayout.GetStride();
    d.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    
    descriptions.push_back(d);
    return descriptions;
  }
  std::vector<VkVertexInputAttributeDescription> ShaderLayout::GetVertexAttributeDescriptions()const
  {
    CANDY_PROFILE_FUNCTION();
    std::vector<VkVertexInputAttributeDescription> descriptions{};
    
    for (const auto& e : vertexLayout)
    {
      VkVertexInputAttributeDescription desc{};
      
      desc.binding = vertexLayout.GetBinding();
      desc.format = ShaderData::TypeToVulkan(e.type);
      desc.location = e.location;
      desc.offset = e.offset;
      
      descriptions.push_back({e.location, 0, ShaderData::TypeToVulkan(e.type), e.offset});
    }
    return descriptions;
  }
  void ShaderLayout::AddSpecConstant(const ShaderSpecializationConstant& specConstant)
  {
    CANDY_PROFILE_FUNCTION();
    ShaderSpecializationConstant s = specConstant;
    specConstantMap[s.name] = specConstants.size();
    specConstants.push_back(s);
  }
  bool ShaderLayout::HasSpecConstant(const std::string& name)const
  {
    CANDY_PROFILE_FUNCTION();
    return specConstantMap.find(name) != specConstantMap.end();
  }
  bool ShaderLayout::GetSpecConstant(const std::string& name, ShaderSpecializationConstant* specConstant)const
  {
    CANDY_PROFILE_FUNCTION();
    const auto& it = specConstantMap.find(name);
    if (it != specConstantMap.end())
    {
      *specConstant = specConstants[it->second];
      return true;
    }
   
    return false;
  }
  uint32_t ShaderLayout::AddBlock(const ShaderBlock& block)
  {
    CANDY_PROFILE_FUNCTION();
    ShaderBlock b = block;
    if (b.set >= sets.size())
    {
      sets.resize(b.set+1);
    }
    if (b.set == MATERIAL_SET)
    {
      materialBufferSize += b.size;
    }
    else if (b.set == GLOBAL_SET)
    {
      globalBufferSize += b.size;
    }
    return sets[b.set].AddBlock(b);
    
  }
  void ShaderLayout::AddPushBlock(const ShaderPushBlock& block)
  {
    CANDY_PROFILE_FUNCTION();
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
    CANDY_PROFILE_FUNCTION();
    property->parentID = pushBlockID;
    property->id = pushProperties.size();
    pushProperties.push_back(property);
    pushPropertyMap[property->name] = property->id;
  
  }
  void ShaderLayout::AddTexture(const ShaderTexture& texture)
  {
    CANDY_PROFILE_FUNCTION();
    ShaderTexture t = texture;
    if (t.set >= sets.size())
    {
      sets.resize(t.set+1);
    }
    sets[t.set].AddTexture(t);
  }

  void ShaderLayout::AddVertexInput(const std::string& name, ShaderData::Type type, uint32_t location)
  {
    CANDY_PROFILE_FUNCTION();
    vertexLayout.AddElement(name, type, location);
  }
  uint32_t ShaderLayout::GetPushID(const std::string& name)const
  {
    CANDY_PROFILE_FUNCTION();
    const auto& it = pushPropertyMap.find(name);
    CANDY_CORE_ASSERT(it != pushPropertyMap.end(), "Push constant name not found");
    return it->second;
  }
  uint32_t ShaderLayout::PushConstant(const std::string& name, const void* data)
  {
    CANDY_PROFILE_FUNCTION();
    const auto& it = pushPropertyMap.find(name);
    CANDY_CORE_ASSERT(it != pushPropertyMap.end());
    auto id = it->second;
    PushConstant(id, data);
    return id;
  }
  void ShaderLayout::PushConstant(uint32_t id, const void* data)
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_ASSERT(id < pushProperties.size());
    
    ShaderPushProperty* prop = pushProperties[id];
    RenderCommand::PushConstants(pipelineLayout, ShaderData::Stage::All, prop->offset, prop->size, data);
  }
  uint32_t ShaderLayout::SetUniform(const std::string& name, const void* data)
  {
    CANDY_PROFILE_FUNCTION();
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
    CANDY_PROFILE_FUNCTION();
    const auto& set = sets[0];
    const auto& prop = set.GetProperty(key);
    
    RenderCommand::SetUniform(prop.GlobalOffset(), prop.size, data);
  }
  
  
  //VkPipeline ShaderLayout::GetPipeline()const{return pipeline;}
  //VkPipelineLayout ShaderLayout::GetPipelineLayout()const{return pipeline.GetLayout();}

}