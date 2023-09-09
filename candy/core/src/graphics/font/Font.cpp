#include "candy/graphics/font/Font.hpp"
#include "candy/math/MathOps.hpp"

#include <CandyPch.hpp>
#include "FontAtlas/msdf-atlas-gen.hpp"
#include "FontAtlas/Atlas/FontGeometry.hpp"
#include "FontAtlas/Atlas/GlyphGeometry.hpp"


#include <candy/graphics/font/MSDFData.hpp>
#include <utility>
#include <candy/graphics/font/FontAtlasSettingsSerializer.hpp>


namespace Candy::Graphics
{
  
  Font::AtlasGeneratorSettings Font::settings{};
  
  template<typename T, typename S, int N, msdf_atlas::GeneratorFunction<S, N> GenFunc>
  static SharedPtr<Texture> CreateAndCacheAtlas(const std::string& fontName, float fontSize, const std::vector<msdf_atlas::GlyphGeometry>& glyphs,
                                  const msdf_atlas::FontGeometry& fontGeometry, uint32_t width, uint32_t height, Font::AtlasGeneratorSettings::GeneratorAttributeSettings attributeSettings)
  {
    msdf_atlas::GeneratorAttributes attributes;
    attributes.config.overlapSupport = attributeSettings.overlapSupport;
    attributes.scanlinePass = attributeSettings.scanlinePass;
    
    
    msdf_atlas::ImmediateAtlasGenerator<S, N, GenFunc, msdf_atlas::BitmapAtlasStorage<T, N>> generator(width, height);
    generator.setAttributes(attributes);
    generator.setThreadCount(attributeSettings.threadCount);
    generator.generate(glyphs.data(), (int)glyphs.size());
    
    msdfgen::BitmapConstRef<T, N> bitmap = (msdfgen::BitmapConstRef<T, N>)generator.atlasStorage();
    
    bool saved = msdf_atlas::saveImage(bitmap, msdf_atlas::ImageFormat::PNG, "output/test.png", msdf_atlas::YDirection::BOTTOM_UP);
    
    if (saved)
    {
      CANDY_CORE_INFO("Saved Image!");
    }
    else
    {
      CANDY_CORE_ERROR("Failed to save image!");
    }
    TextureSpecification spec;
    spec.size.Set(bitmap.width, bitmap.height);
    spec.format = ImageFormat::RGBA8;
    spec.generateMipmaps = false;
    
    SharedPtr<Texture> texture = Texture::Create(spec);
    texture->SetData((void*)bitmap.pixels, bitmap.width * bitmap.height * N);
    return texture;
  }
  Font::Font() : data(new MSDFData())
  {
  
  }
  Font::Font(std::filesystem::path  path) : data(new MSDFData()), filepath(std::move(path))
  {
    Initialize();
  }
  Font::Font(std::filesystem::path  path, const AtlasGeneratorSettings& atlasGeneratorSettings) : data(new MSDFData()), filepath(std::move(path))
  {
    Initialize();
  }
  Font::~Font()
  {
    delete data;
  }
  void Font::Initialize()
  {
    msdf_atlas::FontHandle* handle = msdf_atlas::FontAtlasLoader::LoadFont(filepath.string().c_str());
    
    if (! handle)
    {
      CANDY_CORE_ERROR("Failed to load font: {}", filepath.string());
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
    
    float fontScale = 1.0f;
    data->fontGeometry = msdf_atlas::FontGeometry(&data->glyphs);
    int glyphsLoaded = data->fontGeometry.loadCharset(handle, fontScale, charset);
    CANDY_CORE_INFO("Loaded {} glyphs from font (out of {})", glyphsLoaded, charset.size());
    
    GenerateAtlas();
    
    
    
    
    
    /*atlasTexture = CreateAndCacheAtlas<uint8_t, float, 4, msdf_atlas::mtsdfGenerator>("Test", (float)emSize, data->glyphs, data->fontGeometry, width, height);
    atlasTexture = CreateAndCacheAtlas<uint8_t, float, 3, msdf_atlas::msdfGenerator>("Test", (float)emSize, data->glyphs, data->fontGeometry, width, height);
    
    msdf_atlas::sdfGenerator;
    msdf_atlas::psdfGenerator;*/
    
    msdf_atlas::FontAtlasLoader::DestroyFont(handle);
  }
  SharedPtr<Texture> Font::GetAtlasTexture()const
  {
    return atlasTexture;
  }
  const MSDFData* Font::GetMSDFData()const
  {
    return data;
  }
  
  void Font::GenerateAtlas()
  {
    
    
    msdf_atlas::TightAtlasPacker atlasPacker;
    //atlasPacker.setDimensionConstraint(msdf_atlas::TightAtlasPacker::DimensionsConstraint::);
    atlasPacker.setPixelRange(settings.pixelRange);
    atlasPacker.setMinimumScale(settings.minimumScale);
    atlasPacker.setMiterLimit(settings.miterLimit);
    atlasPacker.setPadding(settings.padding);
    atlasPacker.setScale(settings.scale);
    if (settings.dimensionConstraint != AtlasGeneratorSettings::DimensionConstraint::NONE && settings.dimensionWidth<=0 && settings.dimensionHeight<=0)
    {
      
      atlasPacker.setDimensions(settings.dimensionWidth, settings.dimensionHeight);
      switch (settings.dimensionConstraint)
      {
        case AtlasGeneratorSettings::DimensionConstraint::SQUARE:
          atlasPacker.setDimensionsConstraint(msdf_atlas::TightAtlasPacker::DimensionsConstraint::SQUARE);
          break;
        case AtlasGeneratorSettings::DimensionConstraint::EVEN_SQUARE:
          atlasPacker.setDimensionsConstraint(msdf_atlas::TightAtlasPacker::DimensionsConstraint::EVEN_SQUARE);
          break;
        case AtlasGeneratorSettings::DimensionConstraint::MULTIPLE_OF_4_SQUARE:
          atlasPacker.setDimensionsConstraint(msdf_atlas::TightAtlasPacker::DimensionsConstraint::MULTIPLE_OF_FOUR_SQUARE);
          break;
        case AtlasGeneratorSettings::DimensionConstraint::POWER_OF_2_SQUARE:
          atlasPacker.setDimensionsConstraint(msdf_atlas::TightAtlasPacker::DimensionsConstraint::POWER_OF_TWO_SQUARE);
          break;
        case AtlasGeneratorSettings::DimensionConstraint::POWER_OF_2_RECTANGLE:
          atlasPacker.setDimensionsConstraint(msdf_atlas::TightAtlasPacker::DimensionsConstraint::POWER_OF_TWO_RECTANGLE);
          break;
        default:
          break;
      }
    }
    //atlasPacker.setScale(emSize);
    int remaining = atlasPacker.pack(data->glyphs.data(), (int)data->glyphs.size());
    CANDY_CORE_ASSERT(remaining == 0);
    
    int width, height;
    atlasPacker.getDimensions(width, height);
    float emSize = atlasPacker.getScale();
    
    #define DEFAULT_ANGLE_THRESHOLD 3.0f
#define LCG_MULTIPLIER 6364136223846793005ull
#define LCG_INCREMENT 1442695040888963407ull

    
    uint64_t coloringSeed = 0;
    
    if (settings.expensiveColoring)
    {
      msdf_atlas::Workload([&glyphs = data->glyphs, &coloringSeed, this](int i, int threadNo) -> bool {
      unsigned long long glyphSeed = (LCG_MULTIPLIER * (coloringSeed ^ i) + LCG_INCREMENT) * !!coloringSeed;
      glyphs[i].edgeColoring(msdfgen::edgeColoringInkTrap, settings.defaultAngleThreshold, glyphSeed);
      return true;
      }, data->glyphs.size()).finish(settings.attributeSettings.threadCount);
    }
    else
    {
      unsigned long long glyphSeed = coloringSeed;
      for (msdf_atlas::GlyphGeometry& glyph : data->glyphs)
      {
        glyphSeed *= LCG_MULTIPLIER;
        glyph.edgeColoring(msdfgen::edgeColoringInkTrap, settings.defaultAngleThreshold, glyphSeed);
      }
    }
    
    switch (settings.attributeSettings.atlasType)
    {
      case AtlasGeneratorSettings::AtlasType::MSDF:
        atlasTexture = CreateAndCacheAtlas<uint8_t, float, 3, msdf_atlas::msdfGenerator>("Test", (float)emSize, data->glyphs, data->fontGeometry, width, height, settings.attributeSettings);
        break;
      case AtlasGeneratorSettings::AtlasType::SDF:
        atlasTexture = CreateAndCacheAtlas<uint8_t, float, 1, msdf_atlas::sdfGenerator>("Test", (float)emSize, data->glyphs, data->fontGeometry, width, height, settings.attributeSettings);
        break;
      case AtlasGeneratorSettings::AtlasType::PSDF:
        atlasTexture = CreateAndCacheAtlas<uint8_t, float, 1, msdf_atlas::psdfGenerator>("Test", (float)emSize, data->glyphs, data->fontGeometry, width, height, settings.attributeSettings);
        break;
      case AtlasGeneratorSettings::AtlasType::MTSDF:
        atlasTexture = CreateAndCacheAtlas<uint8_t, float, 4, msdf_atlas::mtsdfGenerator>("Test", (float)emSize, data->glyphs, data->fontGeometry, width, height, settings.attributeSettings);
        break;
      default:
        CANDY_CORE_ERROR("Invalid font atlas type! Cannot generate!");
        CANDY_CORE_ASSERT(false);
        return;
    }
    //atlasTexture = CreateAndCacheAtlas<uint8_t, float, 4, msdf_atlas::mtsdfGenerator>("Test", (float)emSize, data->glyphs, data->fontGeometry, width, height, settings.attributeSettings);
    
  }
  void Font::Init()
  {
    
    msdf_atlas::FontAtlasLoader::Init();
    FontAtlasSettingsSerializer serializer(&settings);
    if (serializer.Deserialize("config/font/defaultFont.yml"))
    {
      CANDY_CORE_INFO("Deserialized font atlas generator settings!");
    }
    else
    {
      CANDY_CORE_ERROR("Failed to deserialize font atlas generator settings!");
    }
    
    
    
  }
  
  void Font::Shutdown()
  {
    CANDY_CORE_INFO("SHUTDOWN FONT");
    msdf_atlas::FontAtlasLoader::Shutdown();
  }
  
  
  
  bool Font::SaveAtlasGeneratorSettings(const std::filesystem::path& filepath)
  {
    FontAtlasSettingsSerializer serializer(&settings);
    return serializer.Serialize(filepath);
  }
  bool Font::LoadAtlasGeneratorSettings(const std::filesystem::path& filepath)
  {
    
    FontAtlasSettingsSerializer serializer(&settings);
    return serializer.Deserialize(filepath);
    
  }
  const Font::AtlasGeneratorSettings& Font::GetAtlasGeneratorSettings()
  {
    return settings;
  }
  
  
  SharedPtr<Font> Font::Default()
  {
    static SharedPtr<Font> defaultFont;
    if (!defaultFont)
    {
      
      defaultFont = CreateSharedPtr<Font>("assets/fonts/opensans/OpenSans-Regular.ttf");
      
    }
    
    
    return defaultFont;
  }
  
}