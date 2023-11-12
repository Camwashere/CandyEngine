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
    size_t offsetX = 0;
    for (const auto& c : charset)
    {
      if (FT_Load_Char(face, c, FT_LOAD_RENDER))
      {
        continue;  // Skip glyphs that can't be loaded
      }
      
      //float glyphHeight = static_cast<float>(face->glyph->metrics.height) / (64.0f) / size.y;
      //float glyphTop = static_cast<float>(face->glyph->metrics.horiBearingY) / (64.0f) / size.y;
      float glyphHeight = static_cast<float>(face->glyph->metrics.height) / 64.0f;
      float glyphTop = (static_cast<float>(face->glyph->metrics.horiBearingY) / 64.0f);
      Math::Bounds2D bounds;
      
      float glyphOffsetY = (glyphHeight-glyphTop);
      bounds.SetMin(static_cast<float>(offsetX) / static_cast<float>(size.x), (static_cast<float>(size.y) - (glyphOffsetY + static_cast<float>(face->glyph->bitmap.rows)))/static_cast<float>(size.y));
      bounds.SetMax(static_cast<float>(offsetX + face->glyph->bitmap.width) / static_cast<float>(size.x), 1.0f);
      
      glyphUVs[c] = bounds;
      
      for(int y = 0; y < face->glyph->bitmap.rows; y++) {
        for(int x = 0; x < face->glyph->bitmap.width; x++) {
          int destIdx = offsetX + x + (this->size.y - y - 1) * this->size.x;
          int srcIdx = x + y * face->glyph->bitmap.pitch;
          this->data[destIdx] = face->glyph->bitmap.buffer[srcIdx];
        }
      }
      offsetX += face->glyph->bitmap.width;
    }
    
    
    Graphics::TextureSpecification spec;
    
    spec.format = Graphics::ImageFormat::R8;
    spec.size = size;
    spec.generateMipmaps = false;
    texture = Graphics::Texture::Create(spec);
    texture->SetData((void*) data.data(), data.size());
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
  SharedPtr<Graphics::Texture> BitmapAtlas::GetTexture()const
  {
    return texture;
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