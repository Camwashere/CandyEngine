#pragma once
#include "candy/graphics/vulkan/Image.hpp"
#include "candy/graphics/vulkan/ImageView.hpp"
#include <filesystem>
#include "ImageFormat.hpp"
namespace Candy::Graphics
{
  class InternalTexture
  {
  private:
    
    Image image;
    std::filesystem::path path;
    Math::Vector2u size{1, 1};
    ImageFormat format = ImageFormat::RGBA8;
    int64_t refCount = 0;
    
  private:
    
    bool Load();
    
  public:
    explicit InternalTexture(std::filesystem::path  filepath);
    InternalTexture(const ImageFormat& format, const Math::Vector2u& size);
   
    
    
  public:
    void SetData(void* data, uint32_t size);
    void AddRef();
    
    /// Decrements the ref counter by 1
    /// @return the new ref counter value
    int64_t RemoveRef();
    void ResetRef();
    [[nodiscard]] int64_t GetRefCount()const;
    [[nodiscard]] const std::filesystem::path& GetPath()const;
    Image& GetImage();
    [[nodiscard]] const Image& GetImage()const;
    
    [[nodiscard]] uint32_t GetWidth()const;
    [[nodiscard]] uint32_t GetHeight()const;
    [[nodiscard]] Math::Vector2u GetSize()const;
    
    [[nodiscard]] bool HasPath()const;
    [[nodiscard]] const ImageFormat& GetFormat()const;
    
    [[nodiscard]] size_t GetTotalChannelCount()const;
    [[nodiscard]] size_t GetPixelCount()const;
    [[nodiscard]] size_t GetSizeInBytes()const;
  };
}