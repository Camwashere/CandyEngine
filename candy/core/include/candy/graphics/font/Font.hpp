#pragma once
#include <filesystem>
#include "candy/base/Base.hpp"
#include "candy/graphics/Texture.hpp"
#include "FontAtlas.hpp"

namespace Candy::Graphics
{
 
  
  class Font
  {
  private:
    FT_Face face=nullptr;
    FontAtlas atlas;
    
  public:
    explicit Font(const std::filesystem::path& font);
    
  public:
    SharedPtr<Texture> GetAtlasTexture()const;
    const FontAtlas& GetAtlas()const;
    
  public:
    static void Init();
    static void Shutdown();
    
    static SharedPtr<Font> Default();
  };
}