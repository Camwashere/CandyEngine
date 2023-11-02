#include "candy/graphics/font/Font.hpp"
#include "candy/math/MathOps.hpp"

#include <CandyPch.hpp>
#include "FontAtlas/msdf-atlas-gen.hpp"
#include "FontAtlas/Atlas/FontGeometry.hpp"
#include "FontAtlas/Atlas/GlyphGeometry.hpp"


#include <candy/graphics/font/MSDFData.hpp>
#include <utility>
#include <candy/graphics/font/FontAtlasSettingsSerializer.hpp>
#include <candy/graphics/font/MSDFSerializer.hpp>
//#include <candy/graphics/font/FontManager.hpp>


namespace Candy::Graphics
{
  
  
  
  template<typename T, typename S, int N, msdf_atlas::GeneratorFunction<S, N> GenFunc>
  static SharedPtr<Texture> CreateAndCacheAtlas(const std::string& fontName, float fontSize, const std::vector<msdf_atlas::GlyphGeometry>& glyphs,
                                  const msdf_atlas::FontGeometry& fontGeometry, uint32_t width, uint32_t height, FontAtlasGeneratorSettings::GeneratorAttributeSettings attributeSettings)
  {
    msdf_atlas::GeneratorAttributes attributes;
    attributes.config.overlapSupport = attributeSettings.overlapSupport;
    attributes.scanlinePass = attributeSettings.scanlinePass;
    
    
    msdf_atlas::ImmediateAtlasGenerator<S, N, GenFunc, msdf_atlas::BitmapAtlasStorage<T, N>> generator(width, height);
    generator.setAttributes(attributes);
    generator.setThreadCount(attributeSettings.threadCount);
    generator.generate(glyphs.data(), (int)glyphs.size());
    
    msdfgen::BitmapConstRef<T, N> bitmap = (msdfgen::BitmapConstRef<T, N>)generator.atlasStorage();
    
    //std::string extension = "bmp";
    std::string extension = ".png";
    //std::string saveFileName = "output/" + fontName + extension;
    //std::filesystem::path saveFilePath = FontManager::GetCachedAtlasPath() / fontName / extension;
    std::string saveFileName = "assets/cache/font/" + fontName + extension;
    bool saved = msdf_atlas::saveImage(bitmap, msdf_atlas::ImageFormat::PNG, saveFileName.c_str(), msdf_atlas::YDirection::BOTTOM_UP);
    //bool saved = msdf_atlas::saveImage(bitmap, msdf_atlas::ImageFormat::PNG, saveFileName.c_str(), msdf_atlas::YDirection::BOTTOM_UP);
    
    
    
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
    CANDY_PROFILE_FUNCTION();
  }
  Font::Font(std::filesystem::path  path) : data(new MSDFData()), filepath(std::move(path))
  {
    CANDY_PROFILE_FUNCTION();
    Initialize();
  }
  
  Font::~Font()
  {
    CANDY_PROFILE_FUNCTION();
    delete data;
  }
  void Font::Initialize()
  {
    CANDY_PROFILE_FUNCTION();
    msdf_atlas::FontHandle* handle = msdf_atlas::FontAtlasLoader::LoadFont(filepath.string().c_str());
    
    if (! handle)
    {
      CANDY_CORE_ERROR("Failed to load font: {}", filepath.string());
      return;
    }
    
    family = msdf_atlas::FontAtlasLoader::GetFontFamily(handle);
    style = msdf_atlas::FontAtlasLoader::GetFontStyle(handle);
    name = family + ' ' + style;
    std::replace(name.begin(), name.end(), ' ', '-');
    
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
    data->fontGeometry = msdf_atlas::FontGeometry(&data->glyphStorage);
    int glyphsLoaded = data->fontGeometry.loadCharset(handle, fontScale, charset);
    CANDY_CORE_INFO("Loaded {} glyphs from font (out of {})", glyphsLoaded, charset.size());
    CANDY_CORE_INFO("Family: {0}, Style: {1}, Name: {2}", family, style, name);
    
    
    
    
    msdf_atlas::FontAtlasLoader::DestroyFont(handle);
  }
  SharedPtr<Texture> Font::GetAtlasTexture()const
  {
    CANDY_CORE_ASSERT(atlasTexture != nullptr);
    return atlasTexture;
  }
  const MSDFData* Font::GetMSDFData()const
  {
    return data;
  }
  
  const std::string& Font::GetStyle()const
  {
    return style;
  }
  const std::string& Font::GetFamily()const
  {
    return family;
  }
  
  const std::string& Font::GetName()const
  {
    return name;
  }
  bool Font::IsLoaded()const
  {
    return atlasTexture != nullptr;
  }
  
  bool Font::Load()
  {
    CANDY_PROFILE_FUNCTION();
    if (IsLoaded())
    {
      CANDY_CORE_WARN("Font {0} is already loaded!", name);
      return true;
    }
    if (FontManager::UseCachedAtlasImages())
    {
      LoadAtlas();
    }
    else
    {
      GenerateAtlas();
    }
    
    return IsLoaded();
  }
  void Font::LoadAtlas()
  {
    CANDY_PROFILE_FUNCTION();
    std::string path = "assets/cache/font/" + name + ".msdf";
    if (MSDFSerializer::Deserialize(data, path))
    {
      CANDY_CORE_INFO("Deserialized MSDF data!");
    }
    else
    {
      CANDY_CORE_ERROR("Failed to deserialize MSDF data!");
    }
    atlasTexture = Texture::Create("assets/cache/font/" + name + ".png");
  }
  // TODO: Convert MSDFData to FontGeometryData
  void Font::GenerateAtlas()
  {
    CANDY_PROFILE_FUNCTION();
    FontAtlasGeneratorSettings settings = FontManager::GetAtlasGeneratorSettings();
    
    msdf_atlas::TightAtlasPacker atlasPacker;
    //atlasPacker.setDimensionConstraint(msdf_atlas::TightAtlasPacker::DimensionsConstraint::);
    atlasPacker.setPixelRange(settings.pixelRange);
    atlasPacker.setMinimumScale(settings.minimumScale);
    atlasPacker.setMiterLimit(settings.miterLimit);
    atlasPacker.setPadding(settings.padding);
    atlasPacker.setScale(settings.scale);
    if (settings.dimensionConstraint != FontAtlasGeneratorSettings::DimensionConstraint::NONE && settings.dimensionWidth<=0 && settings.dimensionHeight<=0)
    {
      
      atlasPacker.setDimensions(settings.dimensionWidth, settings.dimensionHeight);
      switch (settings.dimensionConstraint)
      {
        case FontAtlasGeneratorSettings::DimensionConstraint::SQUARE:
          atlasPacker.setDimensionsConstraint(msdf_atlas::TightAtlasPacker::DimensionsConstraint::SQUARE);
          break;
        case FontAtlasGeneratorSettings::DimensionConstraint::EVEN_SQUARE:
          atlasPacker.setDimensionsConstraint(msdf_atlas::TightAtlasPacker::DimensionsConstraint::EVEN_SQUARE);
          break;
        case FontAtlasGeneratorSettings::DimensionConstraint::MULTIPLE_OF_4_SQUARE:
          atlasPacker.setDimensionsConstraint(msdf_atlas::TightAtlasPacker::DimensionsConstraint::MULTIPLE_OF_FOUR_SQUARE);
          break;
        case FontAtlasGeneratorSettings::DimensionConstraint::POWER_OF_2_SQUARE:
          atlasPacker.setDimensionsConstraint(msdf_atlas::TightAtlasPacker::DimensionsConstraint::POWER_OF_TWO_SQUARE);
          break;
        case FontAtlasGeneratorSettings::DimensionConstraint::POWER_OF_2_RECTANGLE:
          atlasPacker.setDimensionsConstraint(msdf_atlas::TightAtlasPacker::DimensionsConstraint::POWER_OF_TWO_RECTANGLE);
          break;
        default:
          break;
      }
    }
    //atlasPacker.setScale(emSize);
    int remaining = atlasPacker.pack(data->glyphStorage.data(), (int)data->glyphStorage.size());
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
      msdf_atlas::Workload([&glyphs = data->glyphStorage, &coloringSeed](int i, int threadNo) -> bool {
      unsigned long long glyphSeed = (LCG_MULTIPLIER * (coloringSeed ^ i) + LCG_INCREMENT) * !!coloringSeed;
      glyphs[i].edgeColoring(msdfgen::edgeColoringInkTrap, FontManager::GetAtlasGeneratorSettings().defaultAngleThreshold, glyphSeed);
      return true;
      }, data->glyphStorage.size()).finish(settings.attributeSettings.threadCount);
    }
    else
    {
      unsigned long long glyphSeed = coloringSeed;
      for (msdf_atlas::GlyphGeometry& glyph : data->glyphStorage)
      {
        glyphSeed *= LCG_MULTIPLIER;
        glyph.edgeColoring(msdfgen::edgeColoringInkTrap, settings.defaultAngleThreshold, glyphSeed);
      }
    }
    
    switch (settings.attributeSettings.atlasType)
    {
      case FontAtlasGeneratorSettings::AtlasType::MSDF:
        atlasTexture = CreateAndCacheAtlas<uint8_t, float, 3, msdf_atlas::msdfGenerator>(name, (float)emSize, data->glyphStorage, data->fontGeometry, width, height, settings.attributeSettings);
        break;
      case FontAtlasGeneratorSettings::AtlasType::SDF:
        atlasTexture = CreateAndCacheAtlas<uint8_t, float, 1, msdf_atlas::sdfGenerator>(name, (float)emSize, data->glyphStorage, data->fontGeometry, width, height, settings.attributeSettings);
        break;
      case FontAtlasGeneratorSettings::AtlasType::PSDF:
        atlasTexture = CreateAndCacheAtlas<uint8_t, float, 1, msdf_atlas::psdfGenerator>(name, (float)emSize, data->glyphStorage, data->fontGeometry, width, height, settings.attributeSettings);
        break;
      case FontAtlasGeneratorSettings::AtlasType::MTSDF:
        atlasTexture = CreateAndCacheAtlas<uint8_t, float, 4, msdf_atlas::mtsdfGenerator>(name, (float)emSize, data->glyphStorage, data->fontGeometry, width, height, settings.attributeSettings);
        break;
      default:
        CANDY_CORE_ERROR("Invalid font atlas type! Cannot generate!");
        CANDY_CORE_ASSERT(false);
        return;
    }
    CANDY_CORE_INFO("Serializing MSDF data!");
    std::string path = "assets/cache/font/" + name + ".msdf";
    if (MSDFSerializer::Serialize(data, path))
    {
      CANDY_CORE_INFO("Serialized MSDF data!");
    }
    else
    {
      CANDY_CORE_INFO("Failed to serialize MSDF data!");
    }
    
    
  }
  
  void Font::Init(const std::filesystem::path& atlasGenSettingsPath, const std::filesystem::path& fontFilesPath)
  {
    FontManagerSettings settings{};
    settings.atlasGeneratorSettingsPath = atlasGenSettingsPath;
    settings.fontDirectories.push_back(fontFilesPath);
    Init(settings);
  }
  void Font::Init(const FontManagerSettings& settings)
  {
    CANDY_PROFILE_FUNCTION();
    FontManager::Init(settings);
    
    
    
    
    
  }
  
  void Font::Shutdown()
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_INFO("SHUTDOWN FONT");
    msdf_atlas::FontAtlasLoader::Shutdown();
  }
  
  
  
  bool Font::SaveAtlasGeneratorSettings(const std::filesystem::path& filepath)
  {
    CANDY_PROFILE_FUNCTION();
    return FontManager::SaveAtlasGeneratorSettings(filepath);
  }
  bool Font::LoadAtlasGeneratorSettings(const std::filesystem::path& filepath)
  {
    CANDY_PROFILE_FUNCTION();
    return FontManager::LoadAtlasGeneratorSettings(filepath);
    
  }
  const FontAtlasGeneratorSettings& Font::GetAtlasGeneratorSettings()
  {
    return FontManager::GetAtlasGeneratorSettings();
  }
  
  
  SharedPtr<Font> Font::Default()
  {
    return FontManager::DefaultFont();
  }
  
}