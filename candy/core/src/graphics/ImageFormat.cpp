#include <candy/graphics/ImageFormat.hpp>
#include <CandyPch.hpp>
namespace Candy::Graphics
{
  ImageFormat::ImageFormat(int channel, int bytesPerChan, ImageFormatPrimitiveType type) : channels(channel), bytesPerChannel(bytesPerChan), primitiveType(type)
  {
    vulkanFormat = ImageFormatToVulkanFormat(*this);
  }
 
  ImageFormat::ImageFormat(VkFormat vulkanFormat)
  {
    this->vulkanFormat = vulkanFormat;
    *this = VulkanFormatToImageFormat(vulkanFormat);
  }
  const ImageFormat ImageFormat::R8(1, 8, ImageFormatPrimitiveType::RGB);
  const ImageFormat ImageFormat::R16(1, 16, ImageFormatPrimitiveType::Float);
  const ImageFormat ImageFormat::R32(1, 32, ImageFormatPrimitiveType::Float);
  const ImageFormat ImageFormat::R8Int(1, 8, ImageFormatPrimitiveType::Int);
  const ImageFormat ImageFormat::R16Int(1, 16, ImageFormatPrimitiveType::Int);
  const ImageFormat ImageFormat::R32Int(1, 32, ImageFormatPrimitiveType::Int);
  const ImageFormat ImageFormat::RGB8(3, 8, ImageFormatPrimitiveType::RGB);
  const ImageFormat ImageFormat::RGBA8(4, 8, ImageFormatPrimitiveType::RGB);
  const ImageFormat ImageFormat::RGBA32F(4, 32, ImageFormatPrimitiveType::Float);
  
  bool ImageFormat::operator==(const ImageFormat& other)const
  {
    return channels == other.channels && bytesPerChannel == other.bytesPerChannel && primitiveType == other.primitiveType && vulkanFormat == other.vulkanFormat;
  }
  void ImageFormat::SetChannels(int value)
  {
    channels = value;
    vulkanFormat = ImageFormatToVulkanFormat(*this);
  }
  
  void ImageFormat::SetBytesPerChannel(int value)
  {
    bytesPerChannel = value;
    vulkanFormat = ImageFormatToVulkanFormat(*this);
  }
  
  void ImageFormat::SetPrimitiveType(ImageFormatPrimitiveType type)
  {
    primitiveType = type;
    vulkanFormat = ImageFormatToVulkanFormat(*this);
  }
  
  void ImageFormat::SetVulkanFormat(VkFormat format)
  {
    vulkanFormat = format;
  }
  
  bool ImageFormat::IsValidFormat() const
  {
    return channels>0 && bytesPerChannel>0 && primitiveType != ImageFormatPrimitiveType::None;
  }
  
  [[nodiscard]] int ImageFormat::GetChannels() const
  {
    return channels;
  }
  
  [[nodiscard]] int ImageFormat::GetBytesPerChannel() const
  {
    return bytesPerChannel;
  }
  [[nodiscard]] int ImageFormat::GetBytesPerPixel()const
  {
    return channels*bytesPerChannel;
  }
  [[nodiscard]] ImageFormatPrimitiveType ImageFormat::GetPrimitiveType()const
  {
    return primitiveType;
  }
  [[nodiscard]] VkFormat ImageFormat::GetVulkanFormat()const
  {
    return vulkanFormat;
  }
  static VkFormat FindFormatR(int bytesPerChannel, ImageFormatPrimitiveType primitiveType)
  {
    switch(bytesPerChannel)
    {
      
      case 8:
        switch(primitiveType)
        {
          case ImageFormatPrimitiveType::Int:
            return VK_FORMAT_R8_SINT;
          case ImageFormatPrimitiveType::UInt:
            return VK_FORMAT_R8_UINT;
          case ImageFormatPrimitiveType::RGB:
            return VK_FORMAT_R8_SRGB;
          case ImageFormatPrimitiveType::Normalized:
            return VK_FORMAT_R8_SNORM;
          case ImageFormatPrimitiveType::UNormalized:
            return VK_FORMAT_R8_UNORM;
          case ImageFormatPrimitiveType::Scaled:
            return VK_FORMAT_R8_SSCALED;
          case ImageFormatPrimitiveType::UScaled:
            return VK_FORMAT_R8_USCALED;
          default:
            CANDY_CORE_ERROR("Invalid image format");
            CANDY_CORE_ASSERT(false);
            return VK_FORMAT_UNDEFINED;
        }
      case 16:
        switch(primitiveType)
        {
          case ImageFormatPrimitiveType::Int:
            return VK_FORMAT_R16_SINT;
          case ImageFormatPrimitiveType::UInt:
            return VK_FORMAT_R16_UINT;
          case ImageFormatPrimitiveType::Float:
            return VK_FORMAT_R16_SFLOAT;
          case ImageFormatPrimitiveType::Normalized:
            return VK_FORMAT_R16_SNORM;
          case ImageFormatPrimitiveType::UNormalized:
            return VK_FORMAT_R16_UNORM;
          case ImageFormatPrimitiveType::Scaled:
            return VK_FORMAT_R16_SSCALED;
          case ImageFormatPrimitiveType::UScaled:
            return VK_FORMAT_R16_USCALED;
          default:
            CANDY_CORE_ERROR("Invalid image format");
            CANDY_CORE_ASSERT(false);
            return VK_FORMAT_UNDEFINED;
        }
      case 32:
        switch(primitiveType)
        {
          case ImageFormatPrimitiveType::Int:
            return VK_FORMAT_R32_SINT;
          case ImageFormatPrimitiveType::UInt:
            return VK_FORMAT_R32_UINT;
          case ImageFormatPrimitiveType::Float:
            return VK_FORMAT_R32_SFLOAT;
          default:
            CANDY_CORE_ERROR("Invalid image format");
            CANDY_CORE_ASSERT(false);
            return VK_FORMAT_UNDEFINED;
        }
      case 64:
        switch(primitiveType)
        {
          case ImageFormatPrimitiveType::Int:
            return VK_FORMAT_R64_SINT;
          case ImageFormatPrimitiveType::UInt:
            return VK_FORMAT_R64_UINT;
          case ImageFormatPrimitiveType::Float:
            return VK_FORMAT_R64_SFLOAT;
          default:
            CANDY_CORE_ERROR("Invalid image format");
            CANDY_CORE_ASSERT(false);
            return VK_FORMAT_UNDEFINED;
        }
      
      default:
        CANDY_CORE_ERROR("Invalid image format");
        CANDY_CORE_ASSERT(false);
        return VK_FORMAT_UNDEFINED;
      
    }
  }
  
  static VkFormat FindFormatRG(int bytesPerChannel, ImageFormatPrimitiveType primitiveType)
  {
    switch(bytesPerChannel)
    {
      
      case 8:
        switch(primitiveType)
        {
          case ImageFormatPrimitiveType::Int:
            return VK_FORMAT_R8G8_SINT;
          case ImageFormatPrimitiveType::UInt:
            return VK_FORMAT_R8G8_UINT;
          case ImageFormatPrimitiveType::RGB:
            return VK_FORMAT_R8G8_SRGB;
          case ImageFormatPrimitiveType::Scaled:
            return VK_FORMAT_R8G8_SSCALED;
          case ImageFormatPrimitiveType::UScaled:
            return VK_FORMAT_R8G8_USCALED;
          case ImageFormatPrimitiveType::Normalized:
            return VK_FORMAT_R8G8_SNORM;
          case ImageFormatPrimitiveType::UNormalized:
            return VK_FORMAT_R8G8_UNORM;
          default:
            CANDY_CORE_ERROR("Invalid image format");
            CANDY_CORE_ASSERT(false);
            return VK_FORMAT_UNDEFINED;
        }
      case 16:
        switch(primitiveType)
        {
          case ImageFormatPrimitiveType::Int:
            return VK_FORMAT_R16G16_SINT;
          case ImageFormatPrimitiveType::UInt:
            return VK_FORMAT_R16G16_UINT;
          case ImageFormatPrimitiveType::Float:
            return VK_FORMAT_R16G16_SFLOAT;
          case ImageFormatPrimitiveType::Scaled:
            return VK_FORMAT_R16G16_SSCALED;
          case ImageFormatPrimitiveType::UScaled:
            return VK_FORMAT_R16G16_USCALED;
          case ImageFormatPrimitiveType::Normalized:
            return VK_FORMAT_R16G16_SNORM;
          case ImageFormatPrimitiveType::UNormalized:
            return VK_FORMAT_R16G16_UNORM;
          default:
            CANDY_CORE_ERROR("Invalid image format");
            CANDY_CORE_ASSERT(false);
            return VK_FORMAT_UNDEFINED;
        }
      case 32:
        switch(primitiveType)
        {
          case ImageFormatPrimitiveType::Int:
            return VK_FORMAT_R32G32_SINT;
          case ImageFormatPrimitiveType::UInt:
            return VK_FORMAT_R32G32_UINT;
          case ImageFormatPrimitiveType::Float:
            return VK_FORMAT_R32G32_SFLOAT;
          default:
            CANDY_CORE_ERROR("Invalid image format");
            CANDY_CORE_ASSERT(false);
            return VK_FORMAT_UNDEFINED;
        }
      case 64:
        switch(primitiveType)
        {
          case ImageFormatPrimitiveType::Int:
            return VK_FORMAT_R64G64_SINT;
          case ImageFormatPrimitiveType::UInt:
            return VK_FORMAT_R64G64_UINT;
          case ImageFormatPrimitiveType::Float:
            return VK_FORMAT_R64G64_SFLOAT;
          default:
            CANDY_CORE_ERROR("Invalid image format");
            CANDY_CORE_ASSERT(false);
            return VK_FORMAT_UNDEFINED;
        }
      default:
        CANDY_CORE_ERROR("Invalid image format");
        CANDY_CORE_ASSERT(false);
        return VK_FORMAT_UNDEFINED;
      
    }
  }
  static VkFormat FindFormatRGB(int bytesPerChannel, ImageFormatPrimitiveType primitiveType)
  {
    switch(bytesPerChannel)
    {
      
      case 8:
        switch(primitiveType)
        {
          case ImageFormatPrimitiveType::Int:
            return VK_FORMAT_R8G8B8_SINT;
          case ImageFormatPrimitiveType::UInt:
            return VK_FORMAT_R8G8B8_UINT;
          case ImageFormatPrimitiveType::RGB:
            return VK_FORMAT_R8G8B8_SRGB;
          case ImageFormatPrimitiveType::Scaled:
            return VK_FORMAT_R8G8B8_SSCALED;
          case ImageFormatPrimitiveType::UScaled:
            return VK_FORMAT_R8G8B8_USCALED;
          case ImageFormatPrimitiveType::Normalized:
            return VK_FORMAT_R8G8B8_SNORM;
          case ImageFormatPrimitiveType::UNormalized:
            return VK_FORMAT_R8G8B8_UNORM;
          default:
            CANDY_CORE_ERROR("Invalid image format");
            CANDY_CORE_ASSERT(false);
            return VK_FORMAT_UNDEFINED;
        }
      case 16:
        switch(primitiveType)
        {
          case ImageFormatPrimitiveType::Int:
            return VK_FORMAT_R16G16B16_SINT;
          case ImageFormatPrimitiveType::UInt:
            return VK_FORMAT_R16G16B16_UINT;
          case ImageFormatPrimitiveType::Float:
            return VK_FORMAT_R16G16B16_SFLOAT;
          case ImageFormatPrimitiveType::Scaled:
            return VK_FORMAT_R16G16B16_SSCALED;
          case ImageFormatPrimitiveType::UScaled:
            return VK_FORMAT_R16G16B16_USCALED;
          case ImageFormatPrimitiveType::Normalized:
            return VK_FORMAT_R16G16B16_SNORM;
          case ImageFormatPrimitiveType::UNormalized:
            return VK_FORMAT_R16G16B16_UNORM;
          default:
            CANDY_CORE_ERROR("Invalid image format");
            CANDY_CORE_ASSERT(false);
            return VK_FORMAT_UNDEFINED;
        }
      case 32:
        switch(primitiveType)
        {
          case ImageFormatPrimitiveType::Int:
            return VK_FORMAT_R32G32B32_SINT;
          case ImageFormatPrimitiveType::UInt:
            return VK_FORMAT_R32G32B32_UINT;
          case ImageFormatPrimitiveType::Float:
            return VK_FORMAT_R32G32B32_SFLOAT;
          default:
            CANDY_CORE_ERROR("Invalid image format");
            CANDY_CORE_ASSERT(false);
            return VK_FORMAT_UNDEFINED;
        }
      case 64:
        switch(primitiveType)
        {
          case ImageFormatPrimitiveType::Int:
            return VK_FORMAT_R64G64B64_SINT;
          case ImageFormatPrimitiveType::UInt:
            return VK_FORMAT_R64G64B64_UINT;
          case ImageFormatPrimitiveType::Float:
            return VK_FORMAT_R64G64B64_SFLOAT;
          default:
            CANDY_CORE_ERROR("Invalid image format");
            CANDY_CORE_ASSERT(false);
            return VK_FORMAT_UNDEFINED;
        }
      default:
        CANDY_CORE_ERROR("Invalid image format");
        CANDY_CORE_ASSERT(false);
        return VK_FORMAT_UNDEFINED;
      
    }
  }
  static VkFormat FindFormatRGBA(int bytesPerChannel, ImageFormatPrimitiveType primitiveType)
  {
    switch(bytesPerChannel)
    {
      
      case 8:
        switch(primitiveType)
        {
          case ImageFormatPrimitiveType::Int:
            return VK_FORMAT_R8G8B8A8_SINT;
          case ImageFormatPrimitiveType::UInt:
            return VK_FORMAT_R8G8B8A8_UINT;
          case ImageFormatPrimitiveType::RGB:
            return VK_FORMAT_R8G8B8A8_SRGB;
          case ImageFormatPrimitiveType::Scaled:
            return VK_FORMAT_R8G8B8A8_SSCALED;
          case ImageFormatPrimitiveType::UScaled:
            return VK_FORMAT_R8G8B8A8_USCALED;
          case ImageFormatPrimitiveType::Normalized:
            return VK_FORMAT_R8G8B8A8_SNORM;
          case ImageFormatPrimitiveType::UNormalized:
            return VK_FORMAT_R8G8B8A8_UNORM;
          default:
            CANDY_CORE_ERROR("Invalid image format");
            CANDY_CORE_ASSERT(false);
            return VK_FORMAT_UNDEFINED;
        }
      case 16:
        switch(primitiveType)
        {
          case ImageFormatPrimitiveType::Int:
            return VK_FORMAT_R16G16B16A16_SINT;
          case ImageFormatPrimitiveType::UInt:
            return VK_FORMAT_R16G16B16A16_UINT;
          case ImageFormatPrimitiveType::Float:
            return VK_FORMAT_R16G16B16A16_SFLOAT;
          case ImageFormatPrimitiveType::Scaled:
            return VK_FORMAT_R16G16B16A16_SSCALED;
          case ImageFormatPrimitiveType::UScaled:
            return VK_FORMAT_R16G16B16A16_USCALED;
          case ImageFormatPrimitiveType::Normalized:
            return VK_FORMAT_R16G16B16A16_SNORM;
          case ImageFormatPrimitiveType::UNormalized:
            return VK_FORMAT_R16G16B16A16_UNORM;
          default:
            CANDY_CORE_ERROR("Invalid image format");
            CANDY_CORE_ASSERT(false);
            return VK_FORMAT_UNDEFINED;
        }
      case 32:
        switch(primitiveType)
        {
          case ImageFormatPrimitiveType::Int:
            return VK_FORMAT_R32G32B32A32_SINT;
          case ImageFormatPrimitiveType::UInt:
            return VK_FORMAT_R32G32B32A32_UINT;
          case ImageFormatPrimitiveType::Float:
            return VK_FORMAT_R32G32B32A32_SFLOAT;
          default:
            CANDY_CORE_ERROR("Invalid image format");
            CANDY_CORE_ASSERT(false);
            return VK_FORMAT_UNDEFINED;
        }
      case 64:
        switch(primitiveType)
        {
          case ImageFormatPrimitiveType::Int:
            return VK_FORMAT_R64G64B64A64_SINT;
          case ImageFormatPrimitiveType::UInt:
            return VK_FORMAT_R64G64B64A64_UINT;
          case ImageFormatPrimitiveType::Float:
            return VK_FORMAT_R64G64B64A64_SFLOAT;
          default:
            CANDY_CORE_ERROR("Invalid image format");
            CANDY_CORE_ASSERT(false);
            return VK_FORMAT_UNDEFINED;
        }
      default:
        CANDY_CORE_ERROR("Invalid image format");
        CANDY_CORE_ASSERT(false);
        return VK_FORMAT_UNDEFINED;
      
    }
  }
  VkFormat ImageFormat::ImageFormatToVulkanFormat(const ImageFormat& format)
  {
    switch(format.channels)
    {
      case 1:
        return FindFormatR(format.bytesPerChannel, format.primitiveType);
      case 2:
        return FindFormatRG(format.bytesPerChannel, format.primitiveType);
      case 3:
        return FindFormatRGB(format.bytesPerChannel, format.primitiveType);
      case 4:
        return FindFormatRGBA(format.bytesPerChannel, format.primitiveType);
      default:
        CANDY_CORE_ERROR("Invalid image format with channels: {0}", format.channels);
        return VK_FORMAT_UNDEFINED;
    }
  }
  
  
  
  ImageFormat ImageFormat::VulkanFormatToImageFormat(VkFormat format)
  {
    switch(format)
    {
      // 1 channel
      case VK_FORMAT_R8_SRGB:
        return ImageFormat(1, 8, ImageFormatPrimitiveType::RGB);
      case VK_FORMAT_R8_SINT:
        return ImageFormat(1, 8, ImageFormatPrimitiveType::Int);
        case VK_FORMAT_R8_UINT:
        return ImageFormat(1, 8, ImageFormatPrimitiveType::UInt);
      case VK_FORMAT_R8_SNORM:
        return ImageFormat(1, 8, ImageFormatPrimitiveType::Normalized);
      case VK_FORMAT_R8_UNORM:
        return ImageFormat(1, 8, ImageFormatPrimitiveType::UNormalized);
      case VK_FORMAT_R8_SSCALED:
        return ImageFormat(1, 8, ImageFormatPrimitiveType::Scaled);
      case VK_FORMAT_R8_USCALED:
        return ImageFormat(1, 8, ImageFormatPrimitiveType::UScaled);
        
      
      case VK_FORMAT_R16_SFLOAT:
        return ImageFormat(1, 16, ImageFormatPrimitiveType::Float);
      case VK_FORMAT_R16_SINT:
        return ImageFormat(1, 16, ImageFormatPrimitiveType::Int);
        case VK_FORMAT_R16_UINT:
        return ImageFormat(1, 16, ImageFormatPrimitiveType::UInt);
      case VK_FORMAT_R16_SNORM:
        return ImageFormat(1, 16, ImageFormatPrimitiveType::Normalized);
      case VK_FORMAT_R16_UNORM:
        return ImageFormat(1, 16, ImageFormatPrimitiveType::UNormalized);
      case VK_FORMAT_R16_SSCALED:
        return ImageFormat(1, 16, ImageFormatPrimitiveType::Scaled);
      case VK_FORMAT_R16_USCALED:
        return ImageFormat(1, 16, ImageFormatPrimitiveType::UScaled);
        
        
      case VK_FORMAT_R32_SFLOAT:
        return ImageFormat(1, 32, ImageFormatPrimitiveType::Float);
      case VK_FORMAT_R32_SINT:
        return ImageFormat(1, 32, ImageFormatPrimitiveType::Int);
      case VK_FORMAT_R32_UINT:
        return ImageFormat(1, 32, ImageFormatPrimitiveType::UInt);
      
      
      case VK_FORMAT_R64_SFLOAT:
        return ImageFormat(1, 64, ImageFormatPrimitiveType::Float);
      case VK_FORMAT_R64_SINT:
        return ImageFormat(1, 64, ImageFormatPrimitiveType::Int);
      case VK_FORMAT_R64_UINT:
        return ImageFormat(1, 64, ImageFormatPrimitiveType::UInt);
      
        
      // 2 channels
      case VK_FORMAT_R8G8_SRGB:
        return ImageFormat(2, 8, ImageFormatPrimitiveType::RGB);
      case VK_FORMAT_R8G8_SINT:
        return ImageFormat(2, 8, ImageFormatPrimitiveType::Int);
      case VK_FORMAT_R8G8_UINT:
        return ImageFormat(2, 8, ImageFormatPrimitiveType::UInt);
      case VK_FORMAT_R8G8_SNORM:
        return ImageFormat(2, 8, ImageFormatPrimitiveType::Normalized);
      case VK_FORMAT_R8G8_UNORM:
        return ImageFormat(2, 8, ImageFormatPrimitiveType::UNormalized);
      case VK_FORMAT_R8G8_SSCALED:
        return ImageFormat(2, 8, ImageFormatPrimitiveType::Scaled);
      case VK_FORMAT_R8G8_USCALED:
        return ImageFormat(2, 8, ImageFormatPrimitiveType::UScaled);
      
      
      case VK_FORMAT_R16G16_SFLOAT:
        return ImageFormat(2, 16, ImageFormatPrimitiveType::Float);
      case VK_FORMAT_R16G16_SINT:
        return ImageFormat(2, 16, ImageFormatPrimitiveType::Int);
      case VK_FORMAT_R16G16_UINT:
        return ImageFormat(2, 16, ImageFormatPrimitiveType::UInt);
      case VK_FORMAT_R16G16_SNORM:
        return ImageFormat(2, 16, ImageFormatPrimitiveType::Normalized);
      case VK_FORMAT_R16G16_UNORM:
        return ImageFormat(2, 16, ImageFormatPrimitiveType::UNormalized);
      case VK_FORMAT_R16G16_SSCALED:
        return ImageFormat(2, 16, ImageFormatPrimitiveType::Scaled);
      case VK_FORMAT_R16G16_USCALED:
        return ImageFormat(2, 16, ImageFormatPrimitiveType::UScaled);
      
     
      case VK_FORMAT_R32G32_SFLOAT:
        return ImageFormat(2, 32, ImageFormatPrimitiveType::Float);
      case VK_FORMAT_R32G32_SINT:
        return ImageFormat(2, 32, ImageFormatPrimitiveType::Int);
      case VK_FORMAT_R32G32_UINT:
        return ImageFormat(2, 32, ImageFormatPrimitiveType::UInt);
      
        
      case VK_FORMAT_R64G64_SFLOAT:
        return ImageFormat(2, 64, ImageFormatPrimitiveType::Float);
      case VK_FORMAT_R64G64_SINT:
        return ImageFormat(2, 64, ImageFormatPrimitiveType::Int);
      case VK_FORMAT_R64G64_UINT:
        return ImageFormat(2, 64, ImageFormatPrimitiveType::UInt);
      
        
      // 3 channels
      case VK_FORMAT_R8G8B8_SRGB:
        return ImageFormat(3, 8, ImageFormatPrimitiveType::RGB);
      
      case VK_FORMAT_R8G8B8_SINT:
        return ImageFormat(3, 8, ImageFormatPrimitiveType::Int);
      case VK_FORMAT_R8G8B8_UINT:
        return ImageFormat(3, 8, ImageFormatPrimitiveType::UInt);
      case VK_FORMAT_R8G8B8_SNORM:
        return ImageFormat(3, 8, ImageFormatPrimitiveType::Normalized);
      case VK_FORMAT_R8G8B8_UNORM:
        return ImageFormat(3, 8, ImageFormatPrimitiveType::UNormalized);
      case VK_FORMAT_R8G8B8_SSCALED:
        return ImageFormat(3, 8, ImageFormatPrimitiveType::Scaled);
      case VK_FORMAT_R8G8B8_USCALED:
        return ImageFormat(3, 8, ImageFormatPrimitiveType::UScaled);
      
      
      case VK_FORMAT_R16G16B16_SFLOAT:
        return ImageFormat(3, 16, ImageFormatPrimitiveType::Float);
      case VK_FORMAT_R16G16B16_SINT:
        return ImageFormat(3, 16, ImageFormatPrimitiveType::Int);
      case VK_FORMAT_R16G16B16_UINT:
        return ImageFormat(3, 16, ImageFormatPrimitiveType::UInt);
      case VK_FORMAT_R16G16B16_SNORM:
        return ImageFormat(3, 16, ImageFormatPrimitiveType::Normalized);
      case VK_FORMAT_R16G16B16_UNORM:
        return ImageFormat(3, 16, ImageFormatPrimitiveType::UNormalized);
      case VK_FORMAT_R16G16B16_SSCALED:
        return ImageFormat(3, 16, ImageFormatPrimitiveType::Scaled);
      case VK_FORMAT_R16G16B16_USCALED:
        return ImageFormat(3, 16, ImageFormatPrimitiveType::UScaled);
      
      
      case VK_FORMAT_R32G32B32_SFLOAT:
        return ImageFormat(3, 32, ImageFormatPrimitiveType::Float);
      case VK_FORMAT_R32G32B32_SINT:
        return ImageFormat(3, 32, ImageFormatPrimitiveType::Int);
      case VK_FORMAT_R32G32B32_UINT:
        return ImageFormat(3, 32, ImageFormatPrimitiveType::UInt);
     
      
    
      case VK_FORMAT_R64G64B64_SFLOAT:
        return ImageFormat(3, 64, ImageFormatPrimitiveType::Float);
      case VK_FORMAT_R64G64B64_SINT:
        return ImageFormat(3, 64, ImageFormatPrimitiveType::Int);
      case VK_FORMAT_R64G64B64_UINT:
        return ImageFormat(3, 64, ImageFormatPrimitiveType::UInt);
      
        
      // 4 channels
      case VK_FORMAT_R8G8B8A8_SRGB:
        return ImageFormat(4, 8, ImageFormatPrimitiveType::RGB);
     
      case VK_FORMAT_R8G8B8A8_SINT:
        return ImageFormat(4, 8, ImageFormatPrimitiveType::Int);
      case VK_FORMAT_R8G8B8A8_UINT:
        return ImageFormat(4, 8, ImageFormatPrimitiveType::UInt);
      case VK_FORMAT_R8G8B8A8_SNORM:
        return ImageFormat(4, 8, ImageFormatPrimitiveType::Normalized);
      case VK_FORMAT_R8G8B8A8_UNORM:
        return ImageFormat(4, 8, ImageFormatPrimitiveType::UNormalized);
      case VK_FORMAT_R8G8B8A8_SSCALED:
        return ImageFormat(4, 8, ImageFormatPrimitiveType::Scaled);
      case VK_FORMAT_R8G8B8A8_USCALED:
        return ImageFormat(4, 8, ImageFormatPrimitiveType::UScaled);
      
     
      case VK_FORMAT_R16G16B16A16_SFLOAT:
        return ImageFormat(4, 16, ImageFormatPrimitiveType::Float);
      case VK_FORMAT_R16G16B16A16_SINT:
        return ImageFormat(4, 16, ImageFormatPrimitiveType::Int);
      case VK_FORMAT_R16G16B16A16_UINT:
        return ImageFormat(4, 16, ImageFormatPrimitiveType::UInt);
      case VK_FORMAT_R16G16B16A16_SNORM:
        return ImageFormat(4, 16, ImageFormatPrimitiveType::Normalized);
      case VK_FORMAT_R16G16B16A16_UNORM:
        return ImageFormat(4, 16, ImageFormatPrimitiveType::UNormalized);
      case VK_FORMAT_R16G16B16A16_SSCALED:
        return ImageFormat(4, 16, ImageFormatPrimitiveType::Scaled);
      case VK_FORMAT_R16G16B16A16_USCALED:
        return ImageFormat(4, 16, ImageFormatPrimitiveType::UScaled);
      
  
      case VK_FORMAT_R32G32B32A32_SFLOAT:
        return ImageFormat(4, 32, ImageFormatPrimitiveType::Float);
      case VK_FORMAT_R32G32B32A32_SINT:
        return ImageFormat(4, 32, ImageFormatPrimitiveType::Int);
      case VK_FORMAT_R32G32B32A32_UINT:
        return ImageFormat(4, 32, ImageFormatPrimitiveType::UInt);
   
 
      case VK_FORMAT_R64G64B64A64_SFLOAT:
        return ImageFormat(4, 64, ImageFormatPrimitiveType::Float);
      case VK_FORMAT_R64G64B64A64_SINT:
        return ImageFormat(4, 64, ImageFormatPrimitiveType::Int);
      case VK_FORMAT_R64G64B64A64_UINT:
        return ImageFormat(4, 64, ImageFormatPrimitiveType::UInt);
        
      default:
        CANDY_CORE_ERROR("Invalid image format");
        CANDY_CORE_ASSERT(false);
        return ImageFormat();
        
    }
  }
}