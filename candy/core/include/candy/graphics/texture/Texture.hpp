#pragma once
#include <vulkan/vulkan.h>
#include "vma/vk_mem_alloc.h"
#include "candy/math/Vector.hpp"
#include "candy/graphics/Color.hpp"
#include <filesystem>
#include "candy/graphics/vulkan/CommandBuffer.hpp"
#include "candy/graphics/vulkan/Image.hpp"
#include "candy/graphics/vulkan/ImageView.hpp"
#include "ImageFormat.hpp"
#include "InternalTexture.hpp"
#include <candy/base/Base.hpp>
namespace Candy::Graphics
{
  
  
  struct TextureSpecification
  {
    Math::Vector2u size{0, 0};
    ImageFormat format = ImageFormat::RGBA8;
    bool generateMipmaps = true;
    
    [[nodiscard]] uint64_t SizeInBytes()const;
    [[nodiscard]] bool Valid()const;
    
  };
  
  class Texture
  {
  private:
    const uint32_t id;
    TextureSpecification specification;
    ImageView imageView;
    VkDescriptorImageInfo descriptorImageInfo;
    InternalTexture* internal=nullptr;
    
  private:
    Texture();
    
    
  public:
    explicit Texture(const std::filesystem::path&  path);
    explicit Texture(const TextureSpecification& textureSpecification);
    ~Texture();
    
  public:
    bool operator==(const Texture& other)const;
    
    
    
  public:
    void SetData(void* data, uint32_t size);
    //void Bind(uint32_t slot = 0)const;
    //void Bind(uint32_t slot, uint32_t arrayIndex);
    [[nodiscard]] uint32_t GetWidth()const;
    [[nodiscard]] uint32_t GetHeight()const;
    [[nodiscard]] Math::Vector2u GetSize()const;
    [[nodiscard]] const TextureSpecification& GetSpecification()const;
    [[nodiscard]] const std::filesystem::path& GetPath()const;
    Image& GetImage();
    [[nodiscard]] const Image& GetImage()const;
    ImageView& GetImageView();
    [[nodiscard]] const ImageView& GetImageView()const;
    [[nodiscard]] VkSampler GetSampler()const;
    [[nodiscard]] const VkDescriptorImageInfo& GetDescriptorImageInfo();
    
    [[nodiscard]] VkFormat GetVulkanFormat()const;
    
    
  public:
   
    static SharedPtr<Texture> White();
    static SharedPtr<Texture> Create(const std::filesystem::path& path);
    static SharedPtr<Texture> Create(const TextureSpecification& spec);
    
  
  
  };
}