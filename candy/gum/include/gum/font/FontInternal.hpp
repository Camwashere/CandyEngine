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
    static void LoadFont(const std::filesystem::path& path);
  
  private:
    
    FT_FaceRec_* face;
    float pixelSize;
    std::map<FontAttributes, GlyphCache> glyphCaches;
    
  public:
    BitmapAtlas atlas;
    SharedPtr<Graphics::Texture> atlasTexture;
    
  public:
    FontInternal(const std::filesystem::path& path);
    SharedPtr<Graphics::Texture> GetAtlasTexture()const;
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