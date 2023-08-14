#include "candy/graphics/vulkan/descriptor/DescriptorBuilder.hpp"
#include "candy/graphics/Vulkan.hpp"
namespace Candy::Graphics
{
  DescriptorBuilder DescriptorBuilder::Begin(){
    
    DescriptorBuilder builder;
    
    builder.cache = &Vulkan::GetDescriptorLayoutCache();
    builder.alloc = &Vulkan::GetDescriptorAllocator();
    return builder;
  }
  
  DescriptorBuilder& DescriptorBuilder::BindBuffer(uint32_t binding, VkDescriptorBufferInfo* bufferInfo, VkDescriptorType type, VkShaderStageFlags stageFlags)
  {
    //create the descriptor binding for the layout
    VkDescriptorSetLayoutBinding newBinding{};
    
    newBinding.descriptorCount = 1;
    newBinding.descriptorType = type;
    newBinding.pImmutableSamplers = nullptr;
    newBinding.stageFlags = stageFlags;
    newBinding.binding = binding;
    bindings.push_back(newBinding);
    
    //create the descriptor write
    VkWriteDescriptorSet newWrite{};
    newWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    newWrite.pNext = nullptr;
    newWrite.descriptorCount = 1;
    newWrite.descriptorType = type;
    newWrite.pBufferInfo = bufferInfo;
    newWrite.dstBinding = binding;
    
    
    
    writes.push_back(newWrite);
    return *this;
  }
  DescriptorBuilder& DescriptorBuilder::BindImage(uint32_t binding,  VkDescriptorImageInfo* imageInfo, VkDescriptorType type, VkShaderStageFlags stageFlags)
  {
    VkDescriptorSetLayoutBinding newBinding{};
    
    newBinding.descriptorCount = 1;
    newBinding.descriptorType = type;
    newBinding.pImmutableSamplers = nullptr;
    newBinding.stageFlags = stageFlags;
    newBinding.binding = binding;
    
    bindings.push_back(newBinding);
    
    VkWriteDescriptorSet newWrite{};
    newWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    newWrite.pNext = nullptr;
    
    newWrite.descriptorCount = 1;
    newWrite.descriptorType = type;
    newWrite.pImageInfo = imageInfo;
    newWrite.dstBinding = binding;
    
    writes.push_back(newWrite);
    return *this;
  }
  
  DescriptorBuilder& DescriptorBuilder::AddBinding(uint32_t binding, VkDescriptorType type, VkShaderStageFlags stageFlags)
  {
    VkDescriptorSetLayoutBinding newBinding{};
    
    newBinding.descriptorCount = 1;
    newBinding.descriptorType = type;
    newBinding.pImmutableSamplers = nullptr;
    newBinding.stageFlags = stageFlags;
    newBinding.binding = binding;
    
    bindings.push_back(newBinding);
    return *this;
  }
  
  DescriptorBuilder& DescriptorBuilder::AddImageWrite(uint32_t binding,  const VkDescriptorImageInfo* imageInfo, VkDescriptorType type)
  {
    VkWriteDescriptorSet newWrite{};
    newWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    newWrite.pNext = nullptr;
    
    newWrite.descriptorCount = 1;
    newWrite.descriptorType = type;
    newWrite.pImageInfo = imageInfo;
    newWrite.dstBinding = binding;
    
    writes.push_back(newWrite);
    return *this;
  }
  DescriptorBuilder& DescriptorBuilder::AddBufferWrite(uint32_t binding,  const VkDescriptorBufferInfo* bufferInfo, VkDescriptorType type)
  {
    VkWriteDescriptorSet newWrite{};
    newWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    newWrite.pNext = nullptr;
    
    newWrite.descriptorCount = 1;
    newWrite.descriptorType = type;
    newWrite.pBufferInfo = bufferInfo;
    newWrite.dstBinding = binding;
    
    writes.push_back(newWrite);
    return *this;
  }
  DescriptorBuilder& DescriptorBuilder::AddImageWrite(uint32_t binding,  const VkDescriptorImageInfo* imageInfo, VkDescriptorType type, uint32_t set)
  {
    VkWriteDescriptorSet newWrite{};
    newWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    newWrite.pNext = nullptr;
    
    newWrite.descriptorCount = 1;
    newWrite.descriptorType = type;
    newWrite.pImageInfo = imageInfo;
    newWrite.dstBinding = binding;
    newWrite.dstSet = Renderer::GetCurrentFrame().GetDescriptorSet(set);
    writes.push_back(newWrite);
    return *this;
  }
  DescriptorBuilder& DescriptorBuilder::AddBufferWrite(uint32_t binding,  const VkDescriptorBufferInfo* bufferInfo, VkDescriptorType type, uint32_t set)
  {
    VkWriteDescriptorSet newWrite{};
    newWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    newWrite.pNext = nullptr;
    
    newWrite.descriptorCount = 1;
    newWrite.descriptorType = type;
    newWrite.pBufferInfo = bufferInfo;
    newWrite.dstBinding = binding;
    newWrite.dstSet = Renderer::GetCurrentFrame().GetDescriptorSet(set);
    
    writes.push_back(newWrite);
    return *this;
  }
  
  VkDescriptorSetLayout DescriptorBuilder::BuildLayout()
  {
    VkDescriptorSetLayoutCreateInfo layoutInfo{};
    layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    layoutInfo.pNext = nullptr;
    
    layoutInfo.pBindings = bindings.data();
    layoutInfo.bindingCount = bindings.size();
    
    return cache->CreateDescriptorSetLayout(&layoutInfo);
    
  }
  
  bool DescriptorBuilder::AllocateDescriptorSet(VkDescriptorSet* set, VkDescriptorSetLayout layout)
  {
    bool success = alloc->Allocate(set, layout);
    if (!success)
    {
      CANDY_CORE_ERROR("Failed to allocate descriptor set!");
      return false;
    };
    return true;
  }
  bool DescriptorBuilder::Build(VkDescriptorSet* set, VkDescriptorSetLayout& layout){
    //build layout first
    layout = BuildLayout();
    if (!AllocateDescriptorSet(set, layout))
    {
      return false;
    }
    
    //write descriptor
    for (VkWriteDescriptorSet& w : writes) {
      w.dstSet = *set;
    }
    
    //vkUpdateDescriptorSets(Vulkan::LogicalDevice(), writes.size(), writes.data(), 0, nullptr);
    
    //bindings.clear();
    //writes.clear();
    return true;
  }
  
  bool DescriptorBuilder::Build(VkDescriptorSet* set)
  {
    VkDescriptorSetLayout layout;
    return Build(set, layout);
  }
  void DescriptorBuilder::Write(VkDescriptorSet set)
  {
    BindWrites(set);
    /*for (VkWriteDescriptorSet w : writes) {
      Renderer::AddWrite(w);
    }*/
    vkUpdateDescriptorSets(Vulkan::LogicalDevice(), writes.size(), writes.data(), 0, nullptr);
  }
  
  void DescriptorBuilder::BindWrites(VkDescriptorSet set)
  {
    for (VkWriteDescriptorSet& w : writes) {
      w.dstSet = set;
    }
  }
  
  std::vector<VkWriteDescriptorSet> DescriptorBuilder::GetWrites()
  {
    return writes;
  }
}