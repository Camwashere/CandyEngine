#pragma once
#include <filesystem>
#include <candy/math/Vector.hpp>
#include "ImageFormat.hpp"
#include "candy/graphics/texture/InternalTexture.hpp"
namespace Candy::Graphics
{
  class TextureManager
  {
  
  public:
    static void Init();
    static void Shutdown();
    static uint32_t AssignEmptyTextureID();
    static uint32_t AssignTextureID(const std::filesystem::path& path);
    static uint32_t AssignTextureID(const ImageFormat& format, const Math::Vector2u& size);
   
    static void FreeTextureID(uint32_t id);
    
    static InternalTexture* GetInternalTexture(uint32_t id);
    
  
  };
}