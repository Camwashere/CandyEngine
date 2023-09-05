#include "candy/graphics/font/Font.hpp"
#include <freetype/freetype.h>
#include "candy/math/MathOps.hpp"
#include <candy/graphics/font/FontAtlas.hpp>
#define FONT_CHECK(x, ...) if (x) { CANDY_CORE_ERROR(__VA_ARGS__); CANDY_CORE_ERROR("Error code: {0}, {1}", x, FT_Error_String(x)); CANDY_CORE_ASSERT(false); }

namespace Candy::Graphics
{
  struct GlobalFontData
  {
    FT_Library library;
  };
  
  
  static GlobalFontData globalData{};
  
  Font::Font(const std::filesystem::path& filepath)
  {
    FONT_CHECK(FT_New_Face(globalData.library, filepath.string().c_str(), 0, &face), "Failed to load font: {0}", filepath.string());
    
    
    FT_Set_Pixel_Sizes(face, 0, 64);  // Set the size of the glyphs/characters.
    
    atlas.Generate(face);
    
    FONT_CHECK(FT_Done_Face(face), "Failed to unload font: {0}", filepath.string());
    
    
    
  }
  
  SharedPtr<Texture> Font::GetAtlasTexture()const
  {
    return atlas.texture;
  }
  const FontAtlas& Font::GetAtlas()const
  {
    return atlas;
  }
  
  void Font::Init()
  {
    FONT_CHECK(FT_Init_FreeType(&globalData.library), "Failed to initialize FreeType Library.");
    
  }
  
  void Font::Shutdown()
  {
    FT_Error result = FT_Done_FreeType(globalData.library);
  }
  SharedPtr<Font> Font::Default()
  {
    static SharedPtr<Font> defaultFont;
    if (!defaultFont)
      defaultFont = CreateSharedPtr<Font>("assets/fonts/opensans/OpenSans-Regular.ttf");
    
    return defaultFont;
  }
  
}