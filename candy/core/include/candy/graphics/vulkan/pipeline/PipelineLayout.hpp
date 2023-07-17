#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include "../../ShaderUtils.hpp"
namespace Candy::Graphics
{
  class PipelineLayout
  {
  private:
    VkPipelineLayout layout = VK_NULL_HANDLE;
    std::vector<VkPushConstantRange> pushConstantRanges;
    std::vector<VkDescriptorSetLayout> descriptorSetLayouts;
  
  public:
    PipelineLayout();
  
  public:
    void AddDescriptorSetLayout(VkDescriptorSetLayout descriptorSetLayout);
    
    template<typename T>
    void AddPushConstantRange(ShaderStage stage, uint32_t offset)
    {
      VkPushConstantRange value{};
      value.size = sizeof(T);
      value.offset = offset;
      value.stageFlags = ShaderUtils::ShaderStageToVulkan(stage);
      pushConstantRanges.push_back(value);
    }
    
    void Bake();
  };
}