#pragma once
#include <CandyPch.hpp>
#include <vulkan/vulkan.h>
namespace Candy::Graphics
{
  class DescriptorLayoutCache
  {
  
  public:
    struct DescriptorLayoutInfo {
      //good idea to turn this into a inlined array
      std::vector<VkDescriptorSetLayoutBinding> bindings;
      
      bool operator==(const DescriptorLayoutInfo& other) const;
      
      [[nodiscard]] size_t hash() const;
    };
  private:
    struct DescriptorLayoutHash
    {
      size_t operator()(const DescriptorLayoutInfo &k) const{return k.hash();};
    };
    
  private:
    std::unordered_map<DescriptorLayoutInfo, VkDescriptorSetLayout, DescriptorLayoutHash> layoutCache;
    
  public:
    VkDescriptorSetLayout CreateDescriptorSetLayout(VkDescriptorSetLayoutCreateInfo* info);
    void Destroy();
    
    
    
    
  
  };
}