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
    DescriptorBuilder& AddBinding(uint32_t binding, VkDescriptorType type, VkShaderStageFlags stageFlags, uint32_t arrayCount=1);
    DescriptorBuilder& AddImageWrite(uint32_t binding,  const VkDescriptorImageInfo* imageInfo, VkDescriptorType type);
    DescriptorBuilder& AddBufferWrite(uint32_t binding,  const VkDescriptorBufferInfo* bufferInfo, VkDescriptorType type);
    DescriptorBuilder& AddImageWrite(uint32_t binding,  const VkDescriptorImageInfo* imageInfo, VkDescriptorType type, uint32_t set);
    DescriptorBuilder& AddImageArrayWrite(uint32_t binding, const std::vector<VkDescriptorImageInfo>& imageInfos, VkDescriptorType type, uint32_t set, uint32_t destinationStart=0);
    
    DescriptorBuilder& AddBufferWrite(uint32_t binding,  const VkDescriptorBufferInfo* bufferInfo, VkDescriptorType type, uint32_t set);
    
    VkDescriptorSetLayout BuildLayout();
    bool AllocateDescriptorSet(VkDescriptorSet* set, VkDescriptorSetLayout layout);
    bool Build(VkDescriptorSet* set, VkDescriptorSetLayout& layout);
    bool Build(VkDescriptorSet* set);
    void Write();
    void Write(VkDescriptorSet set);
    void BindWrites(VkDescriptorSet set);
    std::vector<VkWriteDescriptorSet> GetWrites();
 
  };
}