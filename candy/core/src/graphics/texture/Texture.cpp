#include "candy/graphics/texture/Texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/include/stb/stb_image.h"
#include <vulkan/vulkan.h>
#include "CandyPch.hpp"
#include <candy/graphics/texture/TextureManager.hpp>
namespace Candy::Graphics
{
  Texture::Texture() : id(TextureManager::AssignEmptyTextureID())
  {
    CANDY_PROFILE_FUNCTION();
    internal = TextureManager::GetInternalTexture(id);
    imageView.Set(internal->GetImage());
  
  }
  Texture::Texture(const std::filesystem::path&  filePath) : id(TextureManager::AssignTextureID(filePath))
  {
    CANDY_PROFILE_FUNCTION();
    internal = TextureManager::GetInternalTexture(id);
    specification.size.Set(static_cast<uint32_t>(internal->GetWidth()), static_cast<uint32_t>(internal->GetHeight()));
    specification.format.SetChannels(internal->GetFormat().GetChannels());
    imageView.Set(internal->GetImage());
    
  
  }
  Texture::Texture(const TextureSpecification& textureSpecification) : id(TextureManager::AssignTextureID(textureSpecification.format, textureSpecification.size)), specification(textureSpecification)
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_ASSERT(specification.Valid(), "Invalid texture specification!");
    internal = TextureManager::GetInternalTexture(id);
    
    
    
    
    
  }
  
  Texture::~Texture()
  {
    CANDY_PROFILE_FUNCTION();
    TextureManager::FreeTextureID(id);
  }
  
  bool Texture::operator==(const Texture& other)const
  {
    return id == other.id;
    //return path == other.path && specification.size == other.specification.size && specification.format == other.specification.format && specification.generateMipmaps == other.specification.generateMipmaps;
  }
  
  void Texture::SetData(void* data, uint32_t size)
  {
    CANDY_PROFILE_FUNCTION();
    //internal = TextureManager::GetInternalTexture(id);
    internal->SetData(data, size);
    imageView.Set(internal->GetImage());
    
    
  }
 
  uint32_t Texture::GetWidth()const
  {
    //return internal->GetWidth();
    return specification.size.width;
  }
  uint32_t Texture::GetHeight()const
  {
    //return internal->GetHeight();
    return specification.size.height;
  }
  Math::Vector2u Texture::GetSize()const
  {
    return specification.size;
  }
  const TextureSpecification& Texture::GetSpecification()const
  {
    return specification;
  }
  const std::filesystem::path& Texture::GetPath()const
  {
    return internal->GetPath();
    
  }
  
  
  uint64_t TextureSpecification::SizeInBytes()const
  {
    return size.x*size.y*format.GetBytesPerPixel();
  }
  
  bool TextureSpecification::Valid()const
  {
    
    return size.width > 0 && size.height > 0 && format.Valid();
  }
  Image& Texture::GetImage()
  {
    return internal->GetImage();
  }
  const Image& Texture::GetImage()const
  {
    return internal->GetImage();
  }
  ImageView& Texture::GetImageView()
  {
    return imageView;
  }
  const ImageView& Texture::GetImageView()const
  {
    return imageView;
  }
  VkSampler Texture::GetSampler()const
  {
    return imageView.GetSampler();
  }
  
  
  
  const VkDescriptorImageInfo& Texture::GetDescriptorImageInfo()
  {
    CANDY_PROFILE_FUNCTION();
    descriptorImageInfo.imageView = imageView;
    descriptorImageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    descriptorImageInfo.sampler = GetSampler();
    return descriptorImageInfo;
    
  }
  VkFormat Texture::GetVulkanFormat()const
  {
    CANDY_PROFILE_FUNCTION();
    return specification.format.GetVulkanFormat();
    
  }
  SharedPtr<Texture> Texture::White()
  {
    static SharedPtr<Texture> whiteTexture = nullptr;
    if (whiteTexture == nullptr)
    {
      whiteTexture = SharedPtr<Texture>(new Texture());
    }
    return whiteTexture;
  }
  SharedPtr<Texture> Texture::Create(const std::filesystem::path& path)
  {
    return CreateSharedPtr<Texture>(path);
  }
  SharedPtr<Texture> Texture::Create(const TextureSpecification& spec)
  {
    return CreateSharedPtr<Texture>(spec);
  }
  

  
}