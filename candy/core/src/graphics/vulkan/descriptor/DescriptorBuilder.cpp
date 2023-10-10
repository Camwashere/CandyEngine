#include "candy/graphics/vulkan/descriptor/DescriptorBuilder.hpp"
#include "candy/graphics/Vulkan.hpp"
#include <candy/graphics/Renderer.hpp>
#include <candy/graphics/vulkan/descriptor/DescriptorBuilder.hpp>
#include <candy/graphics/GraphicsContext.hpp>
#include <candy/graphics/FrameResources.hpp>
namespace Candy::Graphics
{
  DescriptorBuilder DescriptorBuilder::Begin(){
    CANDY_PROFILE_FUNCTION();
    DescriptorBuilder builder;
    
    builder.cache = &Vulkan::GetDescriptorLayoutCache();
    builder.alloc = &Vulkan::GetDescriptorAllocator();
    return builder;
  }
  
  DescriptorBuilder& DescriptorBuilder::BindBuffer(uint32_t binding, VkDescriptorBufferInfo* bufferInfo, VkDescriptorType type, VkShaderStageFlags stageFlags)
  {
    CANDY_PROFILE_FUNCTION();
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
    CANDY_PROFILE_FUNCTION();
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
  
  DescriptorBuilder& DescriptorBuilder::AddBinding(uint32_t binding, VkDescriptorType type, VkShaderStageFlags stageFlags, uint32_t arrayCount)
  {
    CANDY_PROFILE_FUNCTION();
    VkDescriptorSetLayoutBinding newBinding{};
    if (arrayCount > 1)
    {
      CANDY_CORE_INFO("Binding {} with array count {}", binding, arrayCount);
    }
    CANDY_CORE_ASSERT(arrayCount > 0, "Array count must be greater than 0!");
    newBinding.descriptorCount = arrayCount;
    newBinding.descriptorType = type;
    newBinding.pImmutableSamplers = nullptr;
    newBinding.stageFlags = stageFlags;
    newBinding.binding = binding;
    
    
    bindings.push_back(newBinding);
    return *this;
  }
  
  DescriptorBuilder& DescriptorBuilder::AddImageWrite(uint32_t binding,  const VkDescriptorImageInfo* imageInfo, VkDescriptorType type)
  {
    CANDY_PROFILE_FUNCTION();
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
    CANDY_PROFILE_FUNCTION();
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
    CANDY_PROFILE_FUNCTION();
    VkWriteDescriptorSet newWrite{};
    newWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    newWrite.pNext = nullptr;
    
    newWrite.descriptorCount = 1;
    newWrite.descriptorType = type;
    newWrite.pImageInfo = imageInfo;
    newWrite.dstBinding = binding;
    newWrite.dstSet = Renderer::GetCurrentFrame().GetDescriptorSet(set);
    newWrite.dstArrayElement = 0;
    
    
    writes.push_back(newWrite);
    return *this;
  }
  DescriptorBuilder& DescriptorBuilder::AddImageArrayWrite(uint32_t binding, const std::vector<VkDescriptorImageInfo>& imageInfos, VkDescriptorType type, uint32_t set, uint32_t destinationStart)
  {
    CANDY_PROFILE_FUNCTION();
    VkWriteDescriptorSet newWrite{};
    newWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    newWrite.pNext = nullptr;
    
    newWrite.descriptorCount = imageInfos.size();
    newWrite.descriptorType = type;
    newWrite.pImageInfo = imageInfos.data();
    newWrite.dstBinding = binding;
    newWrite.dstSet = Renderer::GetCurrentFrame().GetDescriptorSet(set);
    newWrite.dstArrayElement = 0;
    
    
    writes.push_back(newWrite);
    return *this;
  }
  DescriptorBuilder& DescriptorBuilder::AddBufferWrite(uint32_t binding,  const VkDescriptorBufferInfo* bufferInfo, VkDescriptorType type, uint32_t set)
  {
    CANDY_PROFILE_FUNCTION();
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
    CANDY_PROFILE_FUNCTION();
    VkDescriptorSetLayoutCreateInfo layoutInfo{};
    layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    layoutInfo.pNext = nullptr;
    
    layoutInfo.pBindings = bindings.data();
    layoutInfo.bindingCount = bindings.size();
    
    return cache->CreateDescriptorSetLayout(&layoutInfo);
    
  }
  
  bool DescriptorBuilder::AllocateDescriptorSet(VkDescriptorSet* set, VkDescriptorSetLayout layout)
  {
    CANDY_PROFILE_FUNCTION();
    bool success = alloc->Allocate(set, layout);
    if (!success)
    {
      CANDY_CORE_ERROR("Failed to allocate descriptor set!");
      return false;
    };
    return true;
  }
  bool DescriptorBuilder::Build(VkDescriptorSet* set, VkDescriptorSetLayout& layout){
    CANDY_PROFILE_FUNCTION();
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
    CANDY_PROFILE_FUNCTION();
    VkDescriptorSetLayout layout;
    return Build(set, layout);
  }
  void DescriptorBuilder::Write(VkDescriptorSet set)
  {
    CANDY_PROFILE_FUNCTION();
    BindWrites(set);
    /*for (VkWriteDescriptorSet w : writes) {
      Renderer::AddWrite(w);
    }*/
    vkUpdateDescriptorSets(Vulkan::LogicalDevice(), writes.size(), writes.data(), 0, nullptr);
  }
  void DescriptorBuilder::Write()
  {
    CANDY_PROFILE_FUNCTION();
    vkUpdateDescriptorSets(Vulkan::LogicalDevice(), writes.size(), writes.data(), 0, nullptr);
  }
  void DescriptorBuilder::BindWrites(VkDescriptorSet set)
  {
    CANDY_PROFILE_FUNCTION();
    for (VkWriteDescriptorSet& w : writes) {
      w.dstSet = set;
    }
  }
  
  std::vector<VkWriteDescriptorSet> DescriptorBuilder::GetWrites()
  {
    return writes;
  }
}