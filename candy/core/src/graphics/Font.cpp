#include <candy/graphics/Font.hpp>

/*#undef INFINITE
#include <msdf-atlas-gen/msdf-atlas-gen.h>
#include <msdf-atlas-gen/FontGeometry.h>
#include <msdf-atlas-gen/GlyphGeometry.h>*/

#include <candy/graphics/MSDFData.hpp>
namespace Candy::Graphics
{
  /*template<typename T, typename S, int N, msdf_atlas::GeneratorFunction<S, N> GenFunc>
  static SharedPtr<Texture> CreateAndCacheAtlas(const std::string& fontName, float fontSize, const std::vector<msdf_atlas::GlyphGeometry>& glyphs,
                                            const msdf_atlas::FontGeometry& fontGeometry, uint32_t width, uint32_t height)
  {
    msdf_atlas::GeneratorAttributes attributes;
    attributes.config.overlapSupport = true;
    attributes.scanlinePass = true;
    
    msdf_atlas::ImmediateAtlasGenerator<S, N, GenFunc, msdf_atlas::BitmapAtlasStorage<T, N>> generator(width, height);
    generator.setAttributes(attributes);
    generator.setThreadCount(8);
    generator.generate(glyphs.data(), (int)glyphs.size());
    
    msdfgen::BitmapConstRef<T, N> bitmap = (msdfgen::BitmapConstRef<T, N>)generator.atlasStorage();
    
    TextureSpecification spec;
    spec.size = {static_cast<unsigned int>(bitmap.width), static_cast<unsigned int>(bitmap.height)};
    spec.format = ImageFormat::RGB8;
    spec.generateMipmaps = false;
    
    SharedPtr<Texture> texture = Texture::Create(spec);
    texture->SetData((void*)bitmap.pixels, bitmap.width * bitmap.height * 3);
    return texture;
  }*/
  
  Font::Font(const std::filesystem::path& filepath)
  : data(new MSDFData())
  {
    /*msdfgen::FreetypeHandle* ft = msdfgen::initializeFreetype();
    CANDY_CORE_ASSERT(ft);
    
    std::string fileString = filepath.string();
    
    // TODO(Yan): msdfgen::loadFontData loads from memory buffer which we'll need 
    msdfgen::FontHandle* font = msdfgen::loadFont(ft, fileString.c_str());
    if (!font)
    {
      CANDY_CORE_ERROR("Failed to load font: {}", fileString);
      return;
    }
    
    struct CharsetRange
    {
      uint32_t Begin, End;
    };
    
    // From imgui_draw.cpp
    static const CharsetRange charsetRanges[] =
    {
    { 0x0020, 0x00FF }
    };
    
    msdf_atlas::Charset charset;
    for (CharsetRange range : charsetRanges)
    {
      for (uint32_t c = range.Begin; c <= range.End; c++)
        charset.add(c);
    }
    
    double fontScale = 1.0;
    data->fontGeometry = msdf_atlas::FontGeometry(&data->glyphs);
    int glyphsLoaded = data->fontGeometry.loadCharset(font, fontScale, charset);
    CANDY_CORE_INFO("Loaded {} glyphs from font (out of {})", glyphsLoaded, charset.size());
    
    
    double emSize = 40.0;
    
    msdf_atlas::TightAtlasPacker atlasPacker;
    // atlasPacker.setDimensionsConstraint()
    atlasPacker.setPixelRange(2.0);
    atlasPacker.setMiterLimit(1.0);
    atlasPacker.setPadding(0);
    atlasPacker.setScale(emSize);
    int remaining = atlasPacker.pack(data->glyphs.data(), (int)data->glyphs.size());
    CANDY_CORE_ASSERT(remaining == 0);
    
    int width, height;
    atlasPacker.getDimensions(width, height);
    emSize = atlasPacker.getScale();

#define DEFAULT_ANGLE_THRESHOLD 3.0
#define LCG_MULTIPLIER 6364136223846793005ull
#define LCG_INCREMENT 1442695040888963407ull
#define THREAD_COUNT 8
    // if MSDF || MTSDF
    
    uint64_t coloringSeed = 0;
    bool expensiveColoring = false;
    if (expensiveColoring)
    {
      msdf_atlas::Workload([&glyphs = data->glyphs, &coloringSeed](int i, int threadNo) -> bool {
      unsigned long long glyphSeed = (LCG_MULTIPLIER * (coloringSeed ^ i) + LCG_INCREMENT) * !!coloringSeed;
      glyphs[i].edgeColoring(msdfgen::edgeColoringInkTrap, DEFAULT_ANGLE_THRESHOLD, glyphSeed);
      return true;
      }, data->glyphs.size()).finish(THREAD_COUNT);
    }
    else {
      unsigned long long glyphSeed = coloringSeed;
      for (msdf_atlas::GlyphGeometry& glyph : data->glyphs)
      {
        glyphSeed *= LCG_MULTIPLIER;
        glyph.edgeColoring(msdfgen::edgeColoringInkTrap, DEFAULT_ANGLE_THRESHOLD, glyphSeed);
      }
    }
    
    
    atlasTexture = CreateAndCacheAtlas<uint8_t, float, 3, msdf_atlas::msdfGenerator>("Test", (float)emSize, data->glyphs, data->fontGeometry, width, height);


#if 0
    msdfgen::Shape shape;
		if (msdfgen::loadGlyph(shape, font, 'C'))
		{
			shape.normalize();
			//                      max. angle
			msdfgen::edgeColoringSimple(shape, 3.0);
			//           image width, height
			msdfgen::Bitmap<float, 3> msdf(32, 32);
			//                     range, scale, translation
			msdfgen::generateMSDF(msdf, shape, 4.0, 1.0, msdfgen::Vector2(4.0, 4.0));
			msdfgen::savePng(msdf, "output.png");
		}
#endif
    
    msdfgen::destroyFont(font);
    msdfgen::deinitializeFreetype(ft);*/
  }
  Font::~Font()
  {
    delete data;
  }
  const MSDFData* Font::GetMSDFData()const
  {
    return data;
  }
  SharedPtr<Texture> Font::GetAtlasTexture()const
  {
    return atlasTexture;
  }
  
  SharedPtr<Font> Font::Default()
  {
    static SharedPtr<Font> defaultFont;
    if (!defaultFont)
      defaultFont = CreateSharedPtr<Font>("assets/fonts/opensans/OpenSans-Regular.ttf");
    
    return defaultFont;
  }
}