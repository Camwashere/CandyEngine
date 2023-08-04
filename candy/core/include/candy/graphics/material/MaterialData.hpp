#pragma once
#include "candy/graphics/Texture.hpp"
#include "candy/graphics/vulkan/ImageView.hpp"
namespace Candy::Graphics
{
  class MaterialParameter
  {
  private:
    std::string name;
    ShaderData::Type type;
    ShaderData::Value value;
    uint32_t binding;
    uint32_t set;
  
  public:
    MaterialParameter(std::string name, ShaderData::Type type, uint32_t binding, uint32_t set);
    
    void SetValue(const ShaderData::Value& value);
    
    
  public:
    [[nodiscard]] size_t GetSize()const;
    [[nodiscard]] uint32_t GetBinding()const;
    [[nodiscard]] uint32_t GetSet()const;
    [[nodiscard]] ShaderData::Type GetType()const;
    [[nodiscard]] std::string GetName()const;
  
  
  
  };
  
  
  
  class MaterialTextureParameter
  {
  private:
    std::string name;
    uint32_t binding;
    uint32_t set;
    Texture texture;
    ImageView textureImageView;
  
  public:
    MaterialTextureParameter(std::string name, uint32_t binding, uint32_t set);
    
    void SetTexture(const std::filesystem::path& path);
    [[nodiscard]] std::string GetName()const;
    [[nodiscard]] VkSampler GetSampler()const;
    [[nodiscard]] VkImageView GetImageView()const;
    [[nodiscard]] uint32_t GetBinding()const;
    [[nodiscard]] uint32_t GetSet()const;
    
  
    
  
  
  };
}