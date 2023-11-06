#include <gum/font/BitmapAtlas.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <CandyPch.hpp>
namespace Candy::Gum
{
  void BitmapAtlas::Clear()
  {
    data.clear();
  }
  void BitmapAtlas::CalculateSize(FT_FaceRec_* face, const Charset& charset)
  {
    size = Math::Vector2u(0, 0);
    for (const auto& codepoint : charset)
    {
      FT_Error error = FT_Load_Char(face, codepoint, FT_LOAD_RENDER);
      if (error)
      {
        CANDY_CORE_ERROR("Error: {}, Could not load glyph: {}", FT_Error_String(error), codepoint);
        CANDY_CORE_ASSERT(false);
      }
      size.x += face->glyph->bitmap.width;
      size.y = std::max(size.y, face->glyph->bitmap.rows);
    }
  }
  void BitmapAtlas::Load(FT_FaceRec_* face, const Charset& charset)
  {
    CalculateSize(face, charset);
    data.resize(size.x * size.y);
    size_t x = 0;
    for (unsigned char c = 0; c<128; c++) {
      if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
        continue;  // Skip glyphs that can't be loaded
      }
      Math::Bounds2D bounds;
      bounds.SetMin(static_cast<float>(x) / size.x, 0.0f);
      bounds.SetMax(static_cast<float>(x + face->glyph->bitmap.width) / size.x, 1.0f);
      glyphUVs[c] = bounds;
      
      for (int i = face->glyph->bitmap.rows - 1; i >= 0; --i) {
        for (int j = 0; j < face->glyph->bitmap.width; ++j) {
          data[x + j + (face->glyph->bitmap.rows - 1 - i) * size.width] = face->glyph->bitmap.buffer[j + face->glyph->bitmap.width * i];
        }
      }
      x += face->glyph->bitmap.width;
    }
  }
  Math::Bounds2D BitmapAtlas::GetUV(unicode_t codepoint)const
  {
    auto it = glyphUVs.find(codepoint);
    if (it != glyphUVs.end())
    {
      return it->second;
    }
    CANDY_CORE_ERROR("Could not find glyph uv for codepoint: {}", codepoint);
    return {};
  }
  [[nodiscard]] const Math::Vector2u& BitmapAtlas::GetSize()const
  {
    return size;
  }
  [[nodiscard]] const std::vector<uint8_t>& BitmapAtlas::GetData()const
  {
    return data;
  }
}