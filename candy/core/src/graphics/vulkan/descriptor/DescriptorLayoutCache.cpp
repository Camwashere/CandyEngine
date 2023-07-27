#include "candy/graphics/vulkan/descriptor/DescriptorLayoutCache.hpp"
#include "candy/graphics/Vulkan.hpp"
namespace Candy::Graphics
{
  void DescriptorLayoutCache::Destroy()
  {
    //delete every descriptor layout held
    for (const auto& pair : layoutCache)
    {
      vkDestroyDescriptorSetLayout(Vulkan::LogicalDevice(), pair.second, nullptr);
    }
  }
  
  VkDescriptorSetLayout DescriptorLayoutCache::CreateDescriptorSetLayout(VkDescriptorSetLayoutCreateInfo* info)
  {
    DescriptorLayoutInfo layoutInfo;
    layoutInfo.bindings.reserve(info->bindingCount);
    bool isSorted = true;
    int lastBinding = -1;
    
    //copy from the direct info struct into our own one
    for (int i = 0; i < info->bindingCount; i++)
    {
      layoutInfo.bindings.push_back(info->pBindings[i]);
      
      //check that the bindings are in strict increasing order
      if (info->pBindings[i].binding > lastBinding)
      {
        lastBinding = info->pBindings[i].binding;
      }
      else
      {
        isSorted = false;
      }
    }
    //sort the bindings if they aren't in order
    if (!isSorted)
    {
      std::sort(layoutInfo.bindings.begin(), layoutInfo.bindings.end(), [](VkDescriptorSetLayoutBinding& a, VkDescriptorSetLayoutBinding& b )
      {
      return a.binding < b.binding;
      });
    }
    
    //try to grab from cache
    auto it = layoutCache.find(layoutInfo);
    if (it != layoutCache.end())
    {
      return (*it).second;
    }
    else
    {
      //create a new one (not found)
      VkDescriptorSetLayout layout;
      vkCreateDescriptorSetLayout(Vulkan::LogicalDevice(), info, nullptr, &layout);
      
      //add to cache
      layoutCache[layoutInfo] = layout;
      return layout;
    }
  }
  
  bool DescriptorLayoutCache::DescriptorLayoutInfo::operator==(const DescriptorLayoutInfo& other) const{
    if (other.bindings.size() != bindings.size()){
      return false;
    }
    else {
      //compare each of the bindings is the same. Bindings are sorted so they will match
      for (int i = 0; i < bindings.size(); i++) {
        if (other.bindings[i].binding != bindings[i].binding){
          return false;
        }
        if (other.bindings[i].descriptorType != bindings[i].descriptorType){
          return false;
        }
        if (other.bindings[i].descriptorCount != bindings[i].descriptorCount){
          return false;
        }
        if (other.bindings[i].stageFlags != bindings[i].stageFlags){
          return false;
        }
      }
      return true;
    }
  }
  
  size_t DescriptorLayoutCache::DescriptorLayoutInfo::hash() const{
    using std::size_t;
    using std::hash;
    
    size_t result = hash<size_t>()(bindings.size());
    
    for (const VkDescriptorSetLayoutBinding& b : bindings)
    {
      //pack the binding data into a single int64. Not fully correct but it's ok
      size_t binding_hash = b.binding | b.descriptorType << 8 | b.descriptorCount << 16 | b.stageFlags << 24;
      
      //shuffle the packed binding data and xor it with the main hash
      result ^= hash<size_t>()(binding_hash);
    }
    
    return result;
  }
}