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
  
  //TODO: Make explicit descriptor set for material parameters. Shader.SetInt() etc functions set global values. Material.SetInt() etc functions set material values.
  // We should also only store parameters in this class that are material parameters. Rather than storing things like camera data
  void Material::Bind()
  {
    CANDY_CORE_ASSERT(shader!=nullptr, "Shader is null! Material cannot bind!");
    //shader->Bind();
    
    
    
    writes.clear();
    
    DescriptorBuilder builder = DescriptorBuilder::Begin();
    size_t count=0;
    for (const auto& param : parameters)
    {
      VkDescriptorBufferInfo bufferInfo{};
      bufferInfo.buffer = *Vulkan::GetCurrentContext().GetCurrentFrame().uniformBuffer;
      bufferInfo.offset=0;
      bufferInfo.range = bufferSize;
      
      builder.AddBufferWrite(param.GetBinding(), &bufferInfo, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, param.GetSet());
    }
    
    for (const auto& param : textureParameters)
    {
      VkDescriptorImageInfo imageInfo{};
      imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
      imageInfo.imageView = param.GetImageView();
      imageInfo.sampler = param.GetSampler();
      
      builder.AddImageWrite(param.GetBinding(), &imageInfo, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, param.GetSet());
    }
    

    writes = builder.GetWrites();

    vkUpdateDescriptorSets(Vulkan::LogicalDevice(), writes.size(), writes.data(), 0, nullptr);

  }
  void Material::Bind(uint32_t set)
  {
    CANDY_CORE_ASSERT(shader!=nullptr, "Shader is null! Material cannot bind!");
    //shader->Bind();
    
    
    
    writes.clear();
    
    DescriptorBuilder builder = DescriptorBuilder::Begin();
    size_t count=0;
    for (const auto& param : parameters)
    {
      if (param.GetSet() != set)
      {
        continue;
      }
      VkDescriptorBufferInfo bufferInfo{};
      bufferInfo.buffer = *Vulkan::GetCurrentContext().GetCurrentFrame().uniformBuffer;
      bufferInfo.offset=0;
      bufferInfo.range = bufferSize;
      
      builder.AddBufferWrite(param.GetBinding(), &bufferInfo, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, param.GetSet());
      
    }
    
    for (const auto& param : textureParameters)
    {
      if (param.GetSet()!=set)
      {
        continue;
      }
      VkDescriptorImageInfo imageInfo{};
      imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
      imageInfo.imageView = param.GetImageView();
      imageInfo.sampler = param.GetSampler();
      
      builder.AddImageWrite(param.GetBinding(), &imageInfo, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, param.GetSet());
    }
    
    
    writes = builder.GetWrites();
    if (!writes.empty())
    {
      vkUpdateDescriptorSets(Vulkan::LogicalDevice(), writes.size(), writes.data(), 0, nullptr);
    }
  }
  
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
    const auto& it = nameToTextureParameterMap.find(name);
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
    for (const auto& set : shader->GetLayout().sets)
    {
      //CANDY_CORE_INFO("SET NUMBER: {}", set.GetSet());
      /*if (set.GetSet()!=MATERIAL_SET)
      {
        continue;
      }*/
      for (const auto& block : set.blocks)
      {
        for (const auto &p: block.properties)
        {
          MaterialParameter parameter(p.name, p.type, block.binding, block.set);
          nameToParameterMap[parameter.GetName()] = parameters.size();
          parameters.push_back(parameter);
        }
        
      }
      
      for (const auto& block : set.textures)
      {
        MaterialTextureParameter parameter(block.name, block.binding, block.set);
        nameToTextureParameterMap[parameter.GetName()] = textureParameters.size();
        textureParameters.push_back(parameter);
        //builder.AddImageWrite(block.binding, &imageInfo, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER);
      }
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