#include "candy/graphics/material/Material.hpp"
#include "candy/graphics/Vulkan.hpp"
namespace Candy::Graphics
{
  void Material::SetShader(Shader* shaderValue)
  {
    shader = shaderValue;
    CalculateParameterLayout();
    CalculateBufferSize();
  }
  void Material::Bind()
  {
    CANDY_CORE_ASSERT(shader!=nullptr, "Shader is null! Material cannot bind!");
    shader->Bind();
    VkDescriptorBufferInfo bufferInfo{};
    bufferInfo.buffer = *Vulkan::GetCurrentContext().GetCurrentFrame().uniformBuffer;
    bufferInfo.offset=0;
    bufferInfo.range = bufferSize;
    
    
    
    
    DescriptorBuilder builder = DescriptorBuilder::Begin();
    
    for (const auto& param : parameters)
    {
      builder.AddBufferWrite(param.GetBinding(), &bufferInfo, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC);
    }
    
    for (const auto& param : textureParameters)
    {
      VkDescriptorImageInfo imageInfo{};
      imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
      imageInfo.imageView = param.GetImageView();
      imageInfo.sampler = param.GetSampler();
      builder.AddImageWrite(param.GetBinding(), &imageInfo, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER);
    }
    
    
    
    
    builder.Write(&Vulkan::GetCurrentContext().GetCurrentFrame().globalDescriptor);
  }
  /*void Material::Bind()
  {
    CANDY_CORE_ASSERT(shader!=nullptr, "Shader is null! Material cannot bind!");
    shader->Bind();
    VkDescriptorBufferInfo bufferInfo{};
    bufferInfo.buffer = *Vulkan::GetCurrentContext().GetCurrentFrame().uniformBuffer;
    size_t bufferSize = Vulkan::PhysicalDevice().PadUniformBufferSize(sizeof(Math::Matrix4)*3 + sizeof(Math::Vector4));
    bufferInfo.offset=0;
    bufferInfo.range = bufferSize;
    
    
    
    VkDescriptorImageInfo imageInfo{};
    imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    imageInfo.imageView = textureImageView;
    //imageInfo.imageView = textureParameter.GetImageView();
    
    imageInfo.sampler = textureImageView.GetSampler();
    //imageInfo.sampler = textureParameter.GetSampler();
    DescriptorBuilder builder = DescriptorBuilder::Begin();
    for (const auto& block : shader->GetLayout().uniformBlockProperties)
    {
      builder.AddBufferWrite(block.binding, &bufferInfo, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC);
    }
    
    for (const auto& block : shader->GetLayout().uniformImageProperties)
    {
      builder.AddImageWrite(block.binding, &imageInfo, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER);
    }
    builder.Write(&Vulkan::GetCurrentContext().GetCurrentFrame().globalDescriptor);
  }*/
  
  void Material::SetParameter(const std::string& name, const ShaderData::Value& value)
  {
    auto it = nameToParameterMap.find(name);
    if (it != nameToParameterMap.end())
    {
      parameters[nameToParameterMap[name]].SetValue(value);
    }
    else
    {
      CANDY_CORE_WARN("Parameter {0} not found in shader {1}", name, shader->GetName());
    }
  }
  void Material::SetTexture(const std::string& name, const std::filesystem::path& path)
  {
    auto it = nameToTextureParameterMap.find(name);
    if (it != nameToTextureParameterMap.end())
    {
      textureParameters[nameToTextureParameterMap[name]].SetTexture(path);
    }
    else
    {
      CANDY_CORE_WARN("Texture parameter {0} not found in shader {1}", name, shader->GetName());
    }
    
  }
  void Material::CalculateParameterLayout()
  {
    nameToParameterMap.clear();
    nameToTextureParameterMap.clear();
    parameters.clear();
    textureParameters.clear();
    for (const auto& block : shader->GetLayout().uniformBlockProperties)
    {
      for (const auto &p: block.properties)
      {
        MaterialParameter parameter(p.name, p.type, block.binding, block.set);
        nameToParameterMap[parameter.GetName()] = parameters.size();
        parameters.push_back(parameter);
      }
      
    }
    
    for (const auto& block : shader->GetLayout().uniformImageProperties)
    {
      MaterialTextureParameter parameter(block.name, block.binding, block.set);
      nameToTextureParameterMap[parameter.GetName()] = textureParameters.size();
      textureParameters.push_back(parameter);
      //builder.AddImageWrite(block.binding, &imageInfo, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER);
    }
  }
  void Material::CalculateBufferSize()
  {
    //size_t bufferSize = Vulkan::PhysicalDevice().PadUniformBufferSize(sizeof(Math::Matrix4)*3 + sizeof(Math::Vector4));
    size_t size=0;
    for (const auto& p : parameters)
    {
      size += p.GetSize();
    }
    bufferSize = Vulkan::PhysicalDevice().PadUniformBufferSize(size);
  }
  Shader* Material::GetShader()
  {
    CANDY_CORE_ASSERT(shader!=nullptr, "Shader is null! Material cannot fetch shader!");
    return shader;
  }

}