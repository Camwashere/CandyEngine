#pragma once
#include <candy/base/Base.hpp>
#include <unordered_map>
#include <vector>
#include <filesystem>
namespace Candy::Graphics
{
  class Font;
  
  class FontFamily
  {
  private:
    std::string name;
    std::unordered_map<std::string, SharedPtr<Font>> styleToFontMap;
    
  private:
    bool AddFont(const SharedPtr<Font>& font);
    
  public:
    explicit FontFamily(std::string  name);
    
  public:
    bool HasFont(const std::string& style) const;
    SharedPtr<Font> GetFont(const std::string& style);
    
  private:
    friend class FontManager;
    
    
    
  };
  
  struct FontAtlasGeneratorSettings
  {
    float pixelRange=2.0f;
    float minimumScale=40.0f;
    float scale=40.0f;
    float miterLimit=1.0f;
    int padding=0;
    int dimensionWidth=-1;
    int dimensionHeight=-1;
    bool expensiveColoring=false;
    
    enum class DimensionConstraint
    {
      NONE=0,
      SQUARE,
      EVEN_SQUARE,
      MULTIPLE_OF_4_SQUARE,
      POWER_OF_2_SQUARE,
      POWER_OF_2_RECTANGLE,
    };
    DimensionConstraint dimensionConstraint = DimensionConstraint::NONE;
    
    enum class AtlasType
    {
      NONE=0,
      MSDF,
      SDF,
      PSDF,
      MTSDF,
    };
    struct GeneratorAttributeSettings
    {
      bool overlapSupport=true;
      bool scanlinePass=true;
      AtlasType atlasType = AtlasType::MTSDF;
      int threadCount=8;
    };
    
    GeneratorAttributeSettings attributeSettings{};
    float defaultAngleThreshold=3.0f;
  };
  
  
  struct FontManagerSettings
  {
    std::vector<std::filesystem::path> fontDirectories;
    bool recursiveFontDirectorySearch = true;
    std::vector<std::string> validFontFileExtensions = {".ttf"};
    size_t maxRecursiveFontDirectorySearchDepth = 10;
    std::filesystem::path atlasGeneratorSettingsPath;
    
    
  };
  class FontManager
  {
  
  private:
    static void LoadDirectory(const std::filesystem::path& directory, size_t currentDepth=0);
    static bool LoadFile(const std::filesystem::path& file);
    //static bool AddFont(const SharedPtr<Font>& font);
    static bool AddFont(const SharedPtr<Font>& font, const SharedPtr<FontFamily>& family);
    static bool AddFamily(const SharedPtr<FontFamily>& family);
  
  public:
    static void Init(const FontManagerSettings& settings);
    
    static bool SaveAtlasGeneratorSettings(const std::filesystem::path& filepath);
    static bool LoadAtlasGeneratorSettings(const std::filesystem::path& filepath);
    
    static bool IsValidFontFile(const std::filesystem::path& path);
    
    static bool LoadFont(const std::string& fontName);
    static bool LoadFont(const std::string& familyName, const std::string& styleName);
    static SharedPtr<Font> GetFont(const std::string& fontName);
    static SharedPtr<Font> GetFont(const std::string& fontFamilyName, const std::string& fontStyleName);
    static SharedPtr<FontFamily> GetFamily(const std::string& fontFamilyName);
    static const FontAtlasGeneratorSettings& GetAtlasGeneratorSettings();
    static size_t GetFamilyCount();
    static size_t GetFontCount();
    static const std::vector<std::string>& GetFontNames();
    static bool UseCachedAtlasImages();
    static std::filesystem::path GetCachedAtlasPath();
    
    static SharedPtr<Font> DefaultFont();
  
  };
}