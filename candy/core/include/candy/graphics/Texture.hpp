#pragma once
#include <vulkan/vulkan.h>
#include <vma/vk_mem_alloc.h>
#include <candy/math/Vector.hpp>
#include "Color.hpp"
#include <filesystem>
#include "vulkan/CommandBuffer.hpp"
#include "vulkan/Image.hpp"
#include "vulkan/ImageView.hpp"
#include "ImageFormat.hpp"
namespace Candy::Graphics
{
  
  
  struct TextureSpecification
  {
    Math::Vector2u size{1, 1};
    ImageFormat format = ImageFormat::RGBA8;
    bool generateMipmaps = true;
    
    [[nodiscard]] uint64_t SizeInBytes()const;
    
  };
  
  class Texture
  {
  private:
    //VkImage image;
    ImageView imageView;
    Image image;
    TextureSpecification specification;
    std::filesystem::path path;
    bool isLoaded = false;
    //VmaAllocation allocation;
    
  
    
  public:
    Texture();
    explicit Texture(std::filesystem::path  path);
    explicit Texture(const TextureSpecification& textureSpecification);
    
    
    
  public:
    void SetData(void* data, uint32_t size);
    void Bind(uint32_t slot = 0)const;
    void Bind(uint32_t slot, uint32_t arrayIndex);
    [[nodiscard]] uint32_t GetWidth()const;
    [[nodiscard]] uint32_t GetHeight()const;
    [[nodiscard]] Math::Vector2u GetSize()const;
    [[nodiscard]] const TextureSpecification& GetSpecification()const;
    [[nodiscard]] const std::filesystem::path& GetPath()const;
    [[nodiscard]] bool IsLoaded()const;
    Image& GetImage(){return image;}
    [[nodiscard]] const Image& GetImage()const{return image;}
    ImageView& GetImageView(){return imageView;}
    [[nodiscard]] const ImageView& GetImageView()const{return imageView;}
    [[nodiscard]] VkSampler GetSampler()const{return imageView.GetSampler();}
    VkDescriptorImageInfo GetDescriptorImageInfo()const;
    
    bool Load(const std::filesystem::path& path);
    [[nodiscard]] VkFormat GetVulkanFormat()const;
    
    
  public:
   
    static SharedPtr<Texture> Create(const std::filesystem::path& path);
    static SharedPtr<Texture> Create(const TextureSpecification& spec);
  
  };
}