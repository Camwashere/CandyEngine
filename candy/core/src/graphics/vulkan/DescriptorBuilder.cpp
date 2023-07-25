#include <candy/graphics/vulkan/DescriptorBuilder.hpp>
#include <candy/graphics/Vulkan.hpp>
namespace Candy::Graphics
{
  DescriptorBuilder DescriptorBuilder::Begin(DescriptorLayoutCache* layoutCache, DescriptorAllocator* allocator){
    
    DescriptorBuilder builder;
    
    builder.cache = layoutCache;
    builder.alloc = allocator;
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
  bool DescriptorBuilder::Build(VkDescriptorSet* set, VkDescriptorSetLayout layout){
    //build layout first
    VkDescriptorSetLayoutCreateInfo layoutInfo{};
    layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    layoutInfo.pNext = nullptr;
    
    layoutInfo.pBindings = bindings.data();
    layoutInfo.bindingCount = bindings.size();
    
    layout = cache->CreateDescriptorSetLayout(&layoutInfo);
    
    //allocate descriptor
    
    bool success = alloc->Allocate(set, layout);
    if (!success)
    {
      CANDY_CORE_ERROR("Failed to allocate descriptor set!");
      return false;
    };
    
    //write descriptor
    for (VkWriteDescriptorSet& w : writes) {
      w.dstSet = *set;
    }
    
    vkUpdateDescriptorSets(Vulkan::LogicalDevice(), writes.size(), writes.data(), 0, nullptr);
    
    return true;
  }
  
  bool DescriptorBuilder::Build(VkDescriptorSet* set)
  {
    VkDescriptorSetLayout layout;
    return Build(set, layout);
  }
}