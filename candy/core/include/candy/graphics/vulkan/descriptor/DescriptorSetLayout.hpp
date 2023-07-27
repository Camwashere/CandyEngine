#pragma once
#include <vector>
#include <vulkan/vulkan.h>
#include "../../shader/ShaderData.hpp"

namespace Candy::Graphics
{
  class DescriptorSetLayout
  {
    VkDescriptorSetLayout layout;
    std::vector<VkDescriptorSetLayoutBinding> bindings;
    std::vector<VkWriteDescriptorSet> writes;
  public:
    void Bind(uint32_t binding, ShaderData::Stage stage, VkDescriptorType type);
    void BindBuffer(uint32_t binding, ShaderData::Stage stage);
    void BindImage(uint32_t binding, ShaderData::Stage stage);
    void Build();
    
    VkDescriptorSetLayout GetLayout(){return layout;}
  };
}