#include <candy/graphics/vulkan/pipeline/PipelineLayout.hpp>
#include <candy/graphics/Vulkan.hpp>
namespace Candy::Graphics
{
  PipelineLayout::PipelineLayout()
  {
  
  }
  
  
  void PipelineLayout::Bake(const SharedPtr<Shader>& shader)
  {
    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    
    
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    
    std::vector<VkDescriptorSetLayout> descriptorSetLayouts{shader->GetDescriptorSetLayout()};
    pipelineLayoutInfo.setLayoutCount = descriptorSetLayouts.size();
    pipelineLayoutInfo.pSetLayouts = descriptorSetLayouts.data();
    //pipelineLayoutInfo.setLayoutCount = descriptorSetLayouts.size(); // Optional
    //pipelineLayoutInfo.pSetLayouts = descriptorSetLayouts.data(); // Optional
    CANDY_CORE_INFO("Push Constant Range Count: {0}", shader->PushConstantRangeCount());
    pipelineLayoutInfo.pushConstantRangeCount = shader->PushConstantRangeCount(); // Optional
    pipelineLayoutInfo.pPushConstantRanges = shader->PushConstantRangeData(); // Optional
    
    CANDY_CORE_ASSERT(vkCreatePipelineLayout(Vulkan::LogicalDevice(), &pipelineLayoutInfo, nullptr, &layout) == VK_SUCCESS, "Failed to create pipeline layout!");
  }
}