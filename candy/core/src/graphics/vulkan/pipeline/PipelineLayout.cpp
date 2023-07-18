#include <candy/graphics/vulkan/pipeline/PipelineLayout.hpp>
#include <candy/graphics/Vulkan.hpp>
namespace Candy::Graphics
{
  PipelineLayout::PipelineLayout()
  {
  
  }
  void PipelineLayout::AddDescriptorSetLayout(VkDescriptorSetLayout descriptorSetLayout)
  {
    descriptorSetLayouts.push_back(descriptorSetLayout);
  }
  /*void PipelineLayout::Bake()
  {
    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    
    
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    
    //pipelineLayoutInfo.setLayoutCount = 1;
    //pipelineLayoutInfo.pSetLayouts = &descriptorSetLayout;
    pipelineLayoutInfo.setLayoutCount = descriptorSetLayouts.size(); // Optional
    pipelineLayoutInfo.pSetLayouts = descriptorSetLayouts.data(); // Optional
    pipelineLayoutInfo.pushConstantRangeCount = pushConstantRanges.size(); // Optional
    pipelineLayoutInfo.pPushConstantRanges = pushConstantRanges.data(); // Optional
    
    CANDY_CORE_ASSERT(vkCreatePipelineLayout(Vulkan::LogicalDevice(), &pipelineLayoutInfo, nullptr, &layout) == VK_SUCCESS, "Failed to create pipeline layout!");
  }*/
  
  void PipelineLayout::Bake(const SharedPtr<Shader>& shader)
  {
    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    
    
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    
    //pipelineLayoutInfo.setLayoutCount = 1;
    //pipelineLayoutInfo.pSetLayouts = &descriptorSetLayout;
    pipelineLayoutInfo.setLayoutCount = descriptorSetLayouts.size(); // Optional
    pipelineLayoutInfo.pSetLayouts = descriptorSetLayouts.data(); // Optional
    CANDY_CORE_INFO("Push Constant Range Count: {0}", shader->PushConstantRangeCount());
    pipelineLayoutInfo.pushConstantRangeCount = shader->PushConstantRangeCount(); // Optional
    pipelineLayoutInfo.pPushConstantRanges = shader->PushConstantRangeData(); // Optional
    
    CANDY_CORE_ASSERT(vkCreatePipelineLayout(Vulkan::LogicalDevice(), &pipelineLayoutInfo, nullptr, &layout) == VK_SUCCESS, "Failed to create pipeline layout!");
  }
}