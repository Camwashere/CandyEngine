#pragma once
#include <candy/math/Vector.hpp>
#include <candy/math/Rectangle.hpp>
#include <freetype/freetype.h>
#include <candy/graphics/Texture.hpp>
#include "Glyph.hpp"
#include <map>

namespace Candy::Graphics
{
  
  
  class FontAtlas
  {
  private:
    unsigned char* data=nullptr;
    SharedPtr<Texture> texture=nullptr;
    std::vector<Glyph> glyphs{};
    std::map<unicode_t, size_t> glyphsByCodepoint;
    
    
  public:
    FontAtlas()=default;
    explicit FontAtlas(FT_Face face);
    
    void Generate(FT_Face face);
    bool Save(const std::filesystem::path& path);
    [[nodiscard]] const Glyph* GetGlyph(unicode_t codepoint)const;
    
  private:
    friend class Font;
  };
}