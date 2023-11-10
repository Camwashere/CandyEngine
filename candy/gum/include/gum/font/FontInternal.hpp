#pragma once
#include <filesystem>
#include <candy/math/geometry/Bounds2D.hpp>
#include <unordered_map>
#include <map>
#include <gum/font/Glyph.hpp>
#include <gum/font/BitmapAtlas.hpp>
#include <candy/graphics/texture/Texture.hpp>
struct FT_FaceRec_;
namespace Candy::Gum
{
  
  class FontInternal
  {
  public:
    static void Init(uint32_t dpi = 96);
    static void Shutdown();
    static SharedPtr<FontInternal> Default();
    
    
  
  private:
    FT_FaceRec_* face=nullptr;
    float pixelSize=0.0f;
    std::map<FontAttributes, GlyphCache> glyphCaches{};
    BitmapAtlas atlas;
    
    
    
  public:
    explicit FontInternal(const std::filesystem::path& path);
    
  private:
    void CreateGlyphCache(const FontAttributes& attributes);
  public:
    SharedPtr<Graphics::Texture> GetAtlasTexture()const;
    const BitmapAtlas& GetAtlas()const;
    BitmapAtlas& GetAtlas();
    const GlyphCache& GetGlyphCache(float pixelSize);
    const Glyph* GetGlyph(unicode_t codepoint);
    const Glyph* GetGlyph(unicode_t codepoint, const FontAttributes& attributes);
    void SetPointSize(float value);
    void SetPixelSize(float value);
    [[nodiscard]] float GetPixelSize()const;
    [[nodiscard]] float GetPointSize()const;
    [[nodiscard]] float GetAscenderPixelSize()const;
    [[nodiscard]] float GetAscenderPointSize()const;
    [[nodiscard]] float GetDescenderPixelSize()const;
    [[nodiscard]] float GetDescenderPointSize()const;
    [[nodiscard]] float GetLineHeightPixelSize()const;
    [[nodiscard]] float GetLineHeightPointSize()const;
    [[nodiscard]] uint16_t GetUnitsPerEM()const;
    [[nodiscard]] Math::Bounds2D GetMaxGlyphPixelBounds()const;
    [[nodiscard]] Math::Bounds2D GetMaxGlyphPointBounds()const;
    
    
    
    [[nodiscard]] std::string GetFamilyName()const;
    [[nodiscard]] std::string GetStyleName()const;
    [[nodiscard]] std::string GetName()const;
  };
}