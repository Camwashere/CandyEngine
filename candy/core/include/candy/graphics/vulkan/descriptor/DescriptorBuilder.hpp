#pragma once
#include "DescriptorAllocator.hpp"
#include "DescriptorLayoutCache.hpp"
namespace Candy::Graphics
{
  class DescriptorBuilder
  {
  private:
    std::vector<VkWriteDescriptorSet> writes;
    std::vector<VkDescriptorSetLayoutBinding> bindings;
    
    DescriptorLayoutCache* cache;
    DescriptorAllocator* alloc;
  public:
    static DescriptorBuilder Begin();
    
    DescriptorBuilder& BindBuffer(uint32_t binding, VkDescriptorBufferInfo* bufferInfo, VkDescriptorType type, VkShaderStageFlags stageFlags);
    DescriptorBuilder& BindImage(uint32_t binding, VkDescriptorImageInfo* imageInfo, VkDescriptorType type, VkShaderStageFlags stageFlags);
    
    
    bool Build(VkDescriptorSet* set, VkDescriptorSetLayout layout);
    bool Build(VkDescriptorSet* set);
 
  };
}