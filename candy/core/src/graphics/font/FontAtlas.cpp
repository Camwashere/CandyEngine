#include <candy/graphics/font/FontAtlas.hpp>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>
namespace Candy::Graphics
{
  
  TextureSpecification CalculateTextureSpecification(FT_Face face)
  {
    TextureSpecification spec{};
    
    // Variables to store atlas dimensions
    uint32_t atlas_width = 0;
    uint32_t atlas_height = 0;
    for(FT_ULong i = 0; i < 128; i++) {   // For simplicity, we just extract the first 128 ASCII glyphs.
      if(FT_Load_Char(face, i, FT_LOAD_RENDER)) {
        CANDY_CORE_WARN("Could not load font character: {}", i);
        continue;
      }
      atlas_width += face->glyph->bitmap.width;
      atlas_height = Math::Max(atlas_height, face->glyph->bitmap.rows);
      
    }
    spec.size.Set(atlas_width, atlas_height);
    spec.format = ImageFormat::R8;
    return spec;
  }
  FontAtlas::FontAtlas(FT_Face face)
  {
    
    Generate(face);
    
  }
  
  void FontAtlas::Generate(FT_Face face)
  {
    TextureSpecification spec = CalculateTextureSpecification(face);
    texture = Texture::Create(spec);
    
    // Create atlas
    data = new unsigned char[spec.size.width*spec.size.height]();  // Initialized to zero
    
    // Copy glyphs to atlas and save their positions
    uint32_t x_offset = 0;
    for (FT_ULong i = 0; i<128; i++)
    {
      if (FT_Load_Char(face, i, FT_LOAD_RENDER))
      {
        CANDY_CORE_WARN("Could not load font character: {}", i);
        continue;
      }
      
      FT_Bitmap *bitmap = &face->glyph->bitmap;
      uint32_t glyph_width = bitmap->width;
      uint32_t glyph_height = bitmap->rows;
      
      for (int y = 0; y<glyph_height; y++)
      {
        for (int x = 0; x<glyph_width; x++)
        {
          data[(y*spec.size.width)+x+x_offset] = bitmap->buffer[(y*glyph_width)+x];
        }
      }
      
      // Save glyph info for later use
      // GlyphInfo could be a struct that holds position, width and height of a glyph in the atlas
      /*GlyphInfo glyph{};
      glyph.position = Math::Vector2u(x_offset, 0);
      glyph.size = Math::Vector2u(glyph_width, glyph_height);
      glyph.unicode = i;
      glyphMap[i] = glyphs.size();*/
      Glyph glyph(i);
      glyph.SetAtlasPosition((int)x_offset, 0);
      glyph.SetAtlasSize((int)glyph_width, (int)glyph_height);
      glyphsByCodepoint[glyph.GetCodepoint()] = glyphs.size();
      x_offset += glyph_width;
      glyphs.push_back(glyph);
    }
    
    
    
    
   
    CANDY_CORE_ASSERT(Save("output/atlas.png"), "Failed to save atlas.");
    
    //texture->SetData((void*)data, spec.size.width*spec.size.height);
  }
  
  bool FontAtlas::Save(const std::filesystem::path& path)
  {
    // Assuming you want to save a png and already have RGB data in an unsigned char array.
    TextureSpecification spec = texture->GetSpecification();
    int width = (int)spec.size.width; // Image width
    int height = (int)spec.size.height; // Image height
    int channels = 1; // Number of channels (3 for RGB)
    
    
    int result = stbi_write_png(path.string().c_str(), width, height, channels, data, width * channels);
    return result != 0;
  }
  
  
  
  const Glyph* FontAtlas::GetGlyph(unicode_t codepoint)const
  {
    std::map<unicode_t, size_t>::const_iterator it = glyphsByCodepoint.find(codepoint);
    if (it != glyphsByCodepoint.end())
      return &(glyphs)[it->second];
    return nullptr;
  }
}
