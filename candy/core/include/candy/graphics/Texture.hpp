#pragma once
#include <vulkan/vulkan.h>
#include <vma/vk_mem_alloc.h>
#include <candy/math/Vector.hpp>
#include "Color.hpp"
#include <filesystem>
#include "vulkan/CommandBuffer.hpp"
#include "vulkan/Image.hpp"
namespace Candy::Graphics
{
  
  struct TextureFormat
  {
    ColorLayout layout=ColorLayout::NONE;
    ColorDataType dataType=ColorDataType::NONE;
  };
  struct TextureSpecification
  {
    Math::Vector2u size{};
    uint8_t channels=0;
    TextureFormat format;
    
    [[nodiscard]] uint64_t ImageSize()const;
    
  };
  
  class Texture
  {
  private:
    //VkImage image;
    Image image;
    TextureSpecification specification;
    std::filesystem::path path;
    //VkSampler sampler;
    VmaAllocation allocation;
    
  public:
    //void CreateSampler();
    
  public:
    Texture();
    explicit Texture(std::filesystem::path  path);
    explicit Texture(const TextureSpecification& textureSpecification);
    
    
    
  public:
    VkImage GetImage(){return image;}
    //VkSampler GetSampler(){return sampler;}
    bool Load(const std::filesystem::path& path);
    [[nodiscard]] VkFormat GetVulkanFormat()const;
    void Destroy();
  
  };
}