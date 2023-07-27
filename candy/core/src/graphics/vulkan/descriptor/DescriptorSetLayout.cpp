#include <candy/graphics/vulkan/descriptor/DescriptorSetLayout.hpp>
#include <candy/graphics/Vulkan.hpp>
namespace Candy::Graphics
{
  void DescriptorSetLayout::BindBuffer(uint32_t binding, ShaderData::Stage stage)
  {
    Bind(binding, stage, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC);
  }
  void DescriptorSetLayout::BindImage(uint32_t binding, ShaderData::Stage stage)
  {
    Bind(binding, stage, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER);
  }
  
  void DescriptorSetLayout::Bind(uint32_t binding, ShaderData::Stage stage, VkDescriptorType type)
  {
    VkDescriptorSetLayoutBinding layoutBinding{};
    layoutBinding.descriptorCount = 1;
    layoutBinding.descriptorType = type;
    layoutBinding.pImmutableSamplers = nullptr;
    layoutBinding.stageFlags = ShaderData::StageToVulkan(stage);
    layoutBinding.binding = binding;
    
    bindings.push_back(layoutBinding);
    
    /*VkWriteDescriptorSet newWrite{};
    newWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    newWrite.pNext = nullptr;
    
    newWrite.descriptorCount = 1;
    newWrite.descriptorType = type;
    newWrite.pBufferInfo = nullptr;
    newWrite.pImageInfo = nullptr;
    newWrite.dstBinding = binding;
    
    writes.push_back(newWrite);*/
  }
  
  void DescriptorSetLayout::Build()
  {
    VkDescriptorSetLayoutCreateInfo layoutInfo{};
    layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    layoutInfo.pNext = nullptr;
    
    layoutInfo.pBindings = bindings.data();
    layoutInfo.bindingCount = bindings.size();
    
    
    layout = Vulkan::GetDescriptorLayoutCache().CreateDescriptorSetLayout(&layoutInfo);
   
  }

}