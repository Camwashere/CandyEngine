#include <gum/font/FontInternal.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <CandyPch.hpp>
#include <CandyEngine.hpp>
namespace Candy::Gum
{
  struct FontInternalData
  {
    FT_Library library;
    uint32_t dpi;
  };
  
  static FontInternalData data;
  
  
  FontInternal::FontInternal(const std::filesystem::path& path)
  {
    
    FT_Error error = FT_New_Face(data.library, path.string().c_str(), 0, &face);
    if (error)
    {
      CANDY_CORE_ERROR("Error: {}, Could not load font file: {}", FT_Error_String(error), path.string());
      CANDY_CORE_ASSERT(false);
    }
    SetPixelSize(128.f);
    
    FontAttributes attr;
    attr.pointSize = GetPointSize();
    CreateGlyphCache(attr);
    atlas.Load(face, Charset::ASCII);
    
    
    
  }
  void FontInternal::Init(uint32_t dpi)
  {
    data.dpi = dpi;
    FT_Error error = FT_Init_FreeType(&data.library);
    if (error != 0)
    {
      CANDY_CORE_ERROR("Error: {}, Could not initialize FreeType", FT_Error_String(error));
      CANDY_CORE_ASSERT(false);
    }
  }
  void FontInternal::CreateGlyphCache(const FontAttributes& attributes)
  {
    auto it = glyphCaches.find(attributes);
    if (it == glyphCaches.end())
    {
      glyphCaches.emplace(attributes, GlyphCache(face, attributes));
    }
  }
  SharedPtr<FontInternal> FontInternal::Default()
  {
    static SharedPtr<FontInternal> defaultFont;
    
    if (defaultFont)
    {
      return defaultFont;
    }
    defaultFont = CreateSharedPtr<FontInternal>(CandyEngine::GetInternalAssetsDirectory() / "fonts" / "raleway" / "Raleway-Regular.ttf");
    return defaultFont;
  
  }
  void FontInternal::Shutdown()
  {
    FT_Done_FreeType(data.library);
  }
  SharedPtr<Graphics::Texture> FontInternal::GetAtlasTexture()const
  {
    return atlas.GetTexture();
  }
  void FontInternal::SetPointSize(float value)
  {
    auto ftPointSize = static_cast<FT_F26Dot6>(value * 64); // convert to FreeType's 26.6 fixed point format
    FT_Error error = FT_Set_Char_Size(face, ftPointSize, 0, data.dpi, data.dpi);
    if (error == 0)
    {
      pixelSize = value * static_cast<float>(data.dpi) / 72; // convert points to pixels
    }
    else
    {
      CANDY_CORE_ERROR("Error: {}, Could not set point size: '{}' for font: '{}'", FT_Error_String(error), value, GetName());
      CANDY_CORE_ASSERT(false);
    }
  }
  void FontInternal::SetPixelSize(float value)
  {
    pixelSize = value;
    FT_Set_Pixel_Sizes(face, 0, static_cast<int>(pixelSize));
  }
  const BitmapAtlas& FontInternal::GetAtlas()const
  {
    return atlas;
  }
  BitmapAtlas& FontInternal::GetAtlas()
  {
    return atlas;
  }
  
  const GlyphCache& FontInternal::GetGlyphCache(float pixSize)
  {
    FontAttributes attributes{};
    attributes.pointSize = pixSize * 72 / static_cast<float>(data.dpi);
    auto it = glyphCaches.find(attributes);
    if (it == glyphCaches.end())
    {
      CreateGlyphCache(attributes);
      it = glyphCaches.find(attributes);
    }
    return it->second;
  }
  const Glyph* FontInternal::GetGlyph(unicode_t codepoint)
  {
    FontAttributes attr{};
    attr.pointSize = GetPointSize();
    return GetGlyph(codepoint, attr);
  }
  const Glyph* FontInternal::GetGlyph(unicode_t codepoint, const FontAttributes& attributes)
  {
    auto it = glyphCaches.find(attributes);
    if (it == glyphCaches.end())
    {
      CreateGlyphCache(attributes);
      it = glyphCaches.find(attributes);
    }
    const Glyph* glyph = it->second.GetGlyph(codepoint);
    return glyph;
  }
  float FontInternal::GetPixelSize()const
  {
    return pixelSize;
  }
  
  float FontInternal::GetPointSize()const
  {
    return pixelSize * 72 / static_cast<float>(data.dpi);
  }
  
  float FontInternal::GetAscenderPixelSize() const
  {
    return face->size->metrics.ascender / 64.0f;
  }
  
  float FontInternal::GetDescenderPixelSize() const
  {
    return face->size->metrics.descender / 64.0f;
  }
  
  float FontInternal::GetLineHeightPixelSize() const
  {
    return face->size->metrics.height / 64.0f;
  }
  
  float FontInternal::GetAscenderPointSize() const
  {
    return (face->size->metrics.ascender / 64.0f) * 72 / data.dpi;
  }
  
  float FontInternal::GetDescenderPointSize() const
  {
    return (face->size->metrics.descender / 64.0f) * 72 / data.dpi;
  }
  
  float FontInternal::GetLineHeightPointSize() const
  {
    return (face->size->metrics.height / 64.0f) * 72 / data.dpi;
  }
  
  uint16_t FontInternal::GetUnitsPerEM()const
  {
    return face->units_per_EM;
  }
  Math::Bounds2D FontInternal::GetMaxGlyphPixelBounds()const
  {
    FT_F26Dot6 pixel_bbox_xMin = FT_MulFix(face->bbox.xMin, face->size->metrics.x_scale);
    FT_F26Dot6 pixel_bbox_yMin = FT_MulFix(face->bbox.yMin, face->size->metrics.y_scale);
    FT_F26Dot6 pixel_bbox_xMax = FT_MulFix(face->bbox.xMax, face->size->metrics.x_scale);
    FT_F26Dot6 pixel_bbox_yMax = FT_MulFix(face->bbox.yMax, face->size->metrics.y_scale);
    
    float xMin = static_cast<float>(pixel_bbox_xMin) / 64.0f;
    float yMin = static_cast<float>(pixel_bbox_yMin) / 64.0f;
    float xMax = static_cast<float>(pixel_bbox_xMax) / 64.0f;
    float yMax = static_cast<float>(pixel_bbox_yMax) / 64.0f;
    
    Math::Bounds2D bounds;
    bounds.SetMin(xMin, yMin);
    bounds.SetMax(xMax, yMax);
    return bounds;
  }
  Math::Bounds2D FontInternal::GetMaxGlyphPointBounds()const
  {
    Math::Bounds2D pixelBounds = GetMaxGlyphPixelBounds();
    float pointsPerInch = 72.0f;
    auto dpi = static_cast<float>(data.dpi);
    
    Math::Vector2 minPt = pixelBounds.GetMin();
    Math::Vector2 maxPt = pixelBounds.GetMax();
    
    float point_xMin = (minPt.x / dpi) * pointsPerInch;
    float point_yMin = (minPt.y / dpi) * pointsPerInch;
    float point_xMax = (maxPt.x / dpi) * pointsPerInch;
    float point_yMax = (maxPt.y / dpi) * pointsPerInch;
    
    Math::Bounds2D bounds;
    bounds.SetMin(point_xMin, point_yMin);
    bounds.SetMax(point_xMax, point_yMax);
    return bounds;
  }
  std::string FontInternal::GetFamilyName()const
  {
    CANDY_CORE_ASSERT(face);
    if (face->family_name)
    {
      return face->family_name;
    }
    return "<unknown>";
  }
  std::string FontInternal::GetStyleName()const
  {
    CANDY_CORE_ASSERT(face);
    if (face->style_name)
    {
      return face->style_name;
    }
    return "<unknown>";
  }
  
  std::string FontInternal::GetName()const
  {
    return GetFamilyName() + " : " + GetStyleName();
  }
}