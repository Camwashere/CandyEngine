#pragma once
#include <vulkan/vulkan.h>
namespace Candy::Graphics
{
  enum class ImageFormatPrimitiveType : uint8_t
  {
    None=0,
    Int,
    UInt,
    Float,
    RGB,
    Normalized,
    UNormalized,
    Scaled,
    UScaled,
    
  };
  class ImageFormat
  {
  private:
    int channels=0;
    int bytesPerChannel=0;
    ImageFormatPrimitiveType primitiveType=ImageFormatPrimitiveType(0);
    VkFormat vulkanFormat=VK_FORMAT_UNDEFINED;
    //ImageFormatType formatType=ImageFormatType::None;
    
    
  
  
  public:
    static const ImageFormat R8;
    static const ImageFormat R16;
    static const ImageFormat R32;
    static const ImageFormat R8Int;
    static const ImageFormat R16Int;
    static const ImageFormat R32Int;
    static const ImageFormat RGB8;
    static const ImageFormat RGBA8;
    static const ImageFormat RGBA32F;
  
  
  public:
    ImageFormat()=default;
    ImageFormat(int channels, int bytesPerChannel, ImageFormatPrimitiveType type);
    explicit ImageFormat(VkFormat vulkanFormat);
    
  public:
    bool operator==(const ImageFormat& other)const;
  
  public:
    void SetChannels(int value);
    void SetBytesPerChannel(int value);
    void SetPrimitiveType(ImageFormatPrimitiveType type);
    void SetVulkanFormat(VkFormat format);
    [[nodiscard]] bool Valid()const;
    [[nodiscard]] int GetChannels()const;
    [[nodiscard]] int GetBytesPerChannel()const;
    [[nodiscard]] int GetBytesPerPixel()const;
    [[nodiscard]] ImageFormatPrimitiveType GetPrimitiveType()const;
    [[nodiscard]] VkFormat GetVulkanFormat()const;
  
  public:
    static VkFormat ImageFormatToVulkanFormat(const ImageFormat& format);
    static ImageFormat VulkanFormatToImageFormat(VkFormat format);
    
    
  };
}