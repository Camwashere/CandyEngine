#pragma once
#include <filesystem>
#include "candy/base/Base.hpp"
#include "candy/graphics/texture/Texture.hpp"
#include "FontManager.hpp"


namespace Candy::Graphics
{
 
  struct MSDFData;
  struct FontGeometryData;
  struct FontAtlasGeneratorSettings;
  struct FontManagerSettings;
  class Font
  {
    
  public:
    
  
  private:
    std::string style;
    std::string family;
    std::string name;
    MSDFData* data;
    
    SharedPtr<Texture> atlasTexture=nullptr;
    std::filesystem::path filepath;
    
    
  private:
    void Initialize();
    void GenerateAtlas();
    void LoadAtlas();
  public:
    Font();
    explicit Font(std::filesystem::path  font);
    //Font(std::filesystem::path font, const AtlasGeneratorSettings& settings);
    ~Font();
    
  public:
    [[nodiscard]] SharedPtr<Texture> GetAtlasTexture()const;
    [[nodiscard]] const MSDFData* GetMSDFData()const;
    
    [[nodiscard]] const std::string& GetStyle()const;
    [[nodiscard]] const std::string& GetFamily()const;
    [[nodiscard]] const std::string& GetName()const;
    [[nodiscard]] bool IsLoaded()const;
    
    bool Load();
    
    
    
    
  
    
  public:
    static void Init(const std::filesystem::path& atlasGenSettingsPath, const std::filesystem::path& fontFilesPath);
    static void Init(const FontManagerSettings& settings);
    static void Shutdown();
    static bool SaveAtlasGeneratorSettings(const std::filesystem::path& filepath);
    static bool LoadAtlasGeneratorSettings(const std::filesystem::path& filepath);
    static const FontAtlasGeneratorSettings& GetAtlasGeneratorSettings();
    
    
    
    static SharedPtr<Font> Default();
    
  private:
    friend class FontAtlasSettingsSerializer;
  };
}