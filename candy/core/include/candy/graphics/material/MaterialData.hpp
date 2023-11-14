#pragma once
#include "candy/graphics/texture/Texture.hpp"
#include "candy/graphics/vulkan/VulkanImageView.hpp"
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
  
  enum class MaterialTextureType : uint8_t
  {
    NONE = 0,
    DIFFUSE = 1,
    SPECULAR = 2,
    AMBIENT = 3,
    EMISSIVE = 4,
    HEIGHT = 5,
    NORMALS = 6,
    SHININESS = 7,
    OPACITY = 8,
    DISPLACEMENT = 9,
    LIGHTMAP = 10,
    REFLECTION = 11,
    
    BASE_COLOR = 12,
    NORMAL_CAMERA = 13,
    EMISSION_COLOR = 14,
    METALNESS = 15,
    DIFFUSE_ROUGHNESS = 16,
    AMBIENT_OCCLUSION = 17,
    
    SHEEN = 19,
    
    CLEARCOAT = 20,
    
    
    TRANSMISSION = 21,
    UNKNOWN = 18,
  };
  
  class MaterialTextureParameter
  {
  private:
    std::string name;
    uint32_t binding;
    uint32_t set;
    SharedPtr<Texture> texture;
    //VulkanImageView textureImageView;
  
  public:
    MaterialTextureParameter(std::string name, uint32_t binding, uint32_t set);
    
    void SetTexture(const std::filesystem::path& path);
    [[nodiscard]] std::string GetName()const;
    [[nodiscard]] VkSampler GetSampler()const;
    //[[nodiscard]] VkImageView GetImageView()const;
    [[nodiscard]] const SharedPtr<Texture>& GetTexture()const{return texture;}
    [[nodiscard]] uint32_t GetBinding()const;
    [[nodiscard]] uint32_t GetSet()const;

  };
  
  struct MaterialSet
  {
    uint32_t set;
    std::vector<MaterialParameter> parameters;
    std::vector<MaterialTextureParameter> textures;
  };
}