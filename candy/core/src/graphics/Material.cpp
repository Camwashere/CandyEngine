#include <candy/graphics/Material.hpp>
#include <candy/graphics/Vulkan.hpp>
namespace Candy::Graphics
{
  void Material::Bind()
  {
    CANDY_CORE_ASSERT(shader!=nullptr, "Shader is null! Material cannot bind!");
    shader->Bind();
    DescriptorBuilder builder = DescriptorBuilder::Begin();
    VkDescriptorBufferInfo bufferInfo{};
    bufferInfo.buffer = *Vulkan::GetCurrentContext().GetCurrentFrame().uniformBuffer;
    bufferInfo.offset = 0;
    bufferInfo.range = sizeof(Color);
    
    
    VkDescriptorImageInfo imageInfo{};
    imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    imageInfo.imageView = textureImageView;
    imageInfo.sampler = textureImageView.GetSampler();
    
    for (const auto& block : shader->GetLayout().uniformBlockProperties)
    {
      builder.AddBufferWrite(block.binding, &bufferInfo, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC);
      //builder.BindBuffer(block.binding, &bufferInfo, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, ShaderData::StageToVulkan(block.stage));
    }
    for (const auto& block : shader->GetLayout().uniformImageProperties)
    {
      //CANDY_CORE_INFO("IMAGE BINDING: {}", block.binding);
      //builder.BindImage(block.binding, &imageInfo, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, ShaderData::StageToVulkan(block.stage));
      builder.AddImageWrite(block.binding, &imageInfo, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER);
    }
    builder.Write(&Vulkan::GetCurrentContext().GetCurrentFrame().globalDescriptor);
  }

  Shader* Material::GetShader()
  {
    CANDY_CORE_ASSERT(shader!=nullptr, "Shader is null! Material cannot fetch shader!");
    return shader;
  }

}