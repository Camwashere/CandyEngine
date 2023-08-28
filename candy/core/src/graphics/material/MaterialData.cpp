#include <candy/graphics/material/MaterialData.hpp>
#include <utility>

namespace Candy::Graphics
{
  MaterialParameter::MaterialParameter(std::string nameV, ShaderData::Type typeV, uint32_t bindingV, uint32_t setV) : name(std::move(nameV)), type(typeV), binding(bindingV), set(setV)
  {
  
  }
  
  void MaterialParameter::SetValue(const ShaderData::Value& val)
  {
    value=val;
  }
  size_t MaterialParameter::GetSize()const
  {
    return ShaderData::TypeSize(type);
  }
  
  uint32_t MaterialParameter::GetBinding()const
  {
    return binding;
  }
  uint32_t MaterialParameter::GetSet()const
  {
    return set;
  }
  ShaderData::Type MaterialParameter::GetType()const
  {
    return type;
  }
  std::string MaterialParameter::GetName()const
  {
    return name;
  }
  
  
  
  MaterialTextureParameter::MaterialTextureParameter(std::string nameV, uint32_t bindingV, uint32_t setV) : name(std::move(nameV)), binding(bindingV), set(setV)
  {
  
  }
  
  void MaterialTextureParameter::SetTexture(const std::filesystem::path& path)
  {
    texture.Load(path);
    //textureImageView.Set(texture);
  }
  std::string MaterialTextureParameter::GetName()const
  {
    return name;
  }
  VkSampler MaterialTextureParameter::GetSampler()const
  {
    return texture.GetSampler();
    //return textureImageView.GetSampler();
  }
  /*VkImageView MaterialTextureParameter::GetImageView()const
  {
    return textureImageView;
  }*/
  uint32_t MaterialTextureParameter::GetBinding()const
  {
    return binding;
  }
  uint32_t MaterialTextureParameter::GetSet()const
  {
    return set;
  }
}