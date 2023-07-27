#include <candy/graphics/Material.hpp>
#include <candy/graphics/Vulkan.hpp>
namespace Candy::Graphics
{
  
  void Material::BakePipelineLayout()
  {
    CANDY_CORE_ASSERT(shader!=nullptr, "Shader is null! Material cannot bake pipeline layout!");
    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    
    
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    
    //std::vector<VkDescriptorSetLayout> descriptorSetLayouts{shader->GetDescriptorSetLayout()};
    auto descriptorSetLayouts = BakeDescriptorSetLayouts();
    CANDY_CORE_INFO("DESCRIPTOR SET VECTOR SIZE: {}", descriptorSetLayouts.size());
    for (auto d : descriptorSetLayouts)
    {
      if (d==VK_NULL_HANDLE)
      {
        CANDY_CORE_ERROR("NULL DESCRIPTOR SET LAYOUT HANDLE");
      }
    }
    pipelineLayoutInfo.setLayoutCount = descriptorSetLayouts.size();
    pipelineLayoutInfo.pSetLayouts = descriptorSetLayouts.data();
    //pipelineLayoutInfo.setLayoutCount = descriptorSetLayouts.size(); // Optional
    //pipelineLayoutInfo.pSetLayouts = descriptorSetLayouts.data(); // Optional
    auto pushConstantRanges = shader->GetPushConstantRanges();
    CANDY_CORE_INFO("Push Constant Range Count: {0}", pushConstantRanges.size());
    pipelineLayoutInfo.pushConstantRangeCount = pushConstantRanges.size(); // Optional
    pipelineLayoutInfo.pPushConstantRanges = pushConstantRanges.data(); // Optional
    
    CANDY_CORE_ASSERT(vkCreatePipelineLayout(Vulkan::LogicalDevice(), &pipelineLayoutInfo, nullptr, &pipelineLayout) == VK_SUCCESS, "Failed to create pipeline layout!");
  }
  std::vector<VkDescriptorSetLayout> Material::BakeDescriptorSetLayouts()
  {
    CANDY_CORE_ASSERT(shader!=nullptr, "Shader is null! Material cannot bake descriptor set layouts!");
    
    std::vector<VkDescriptorSetLayout> layouts;
    layouts.resize(FRAME_OVERLAP);
   
    //std::vector<VkDescriptorSetLayoutBinding> bindings;
    
    
    for (int i=0; i<FRAME_OVERLAP; i++)
    {
      DescriptorBuilder builder = DescriptorBuilder::Begin();
      VkDescriptorBufferInfo bufferInfo{};
      bufferInfo.buffer = *Vulkan::GetCurrentContext().GetFrame(i).uniformBuffer;
      bufferInfo.offset = 0;
      bufferInfo.range = sizeof(Color);
      
      
      VkDescriptorImageInfo imageInfo{};
      imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
      imageInfo.imageView = textureImageView;
      imageInfo.sampler = textureImageView.GetSampler();
      
      for (const auto& block : shader->GetLayout().uniformBlockProperties)
      {
        builder.BindBuffer(block.binding, &bufferInfo, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, ShaderData::StageToVulkan(block.stage));
      }
      for (const auto& block : shader->GetLayout().uniformImageProperties)
      {
        CANDY_CORE_INFO("IMAGE BINDING: {}", block.binding);
        builder.BindImage(block.binding, &imageInfo, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, ShaderData::StageToVulkan(block.stage));
      }
      
      builder.Build(&Vulkan::GetCurrentContext().GetFrame(i).globalDescriptor, layouts[i]);
    }
    return layouts;
    
  }
  Shader* Material::GetShader()
  {
    CANDY_CORE_ASSERT(shader!=nullptr, "Shader is null! Material cannot fetch shader!");
    return shader;
  }
  void Material::Destroy()
  {
    textureImageView.Destroy();
    texture.Destroy();
    
  }
}