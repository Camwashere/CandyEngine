#pragma once
#include <filesystem>
#include "candy/base/Base.hpp"
#include "candy/graphics/Texture.hpp"



namespace Candy::Graphics
{
 
  struct MSDFData;
  
  class Font
  {
    
  public:
    
    struct AtlasGeneratorSettings
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
  private:
    MSDFData* data;
    SharedPtr<Texture> atlasTexture;
    std::filesystem::path filepath;
    static AtlasGeneratorSettings settings;
    
  private:
    void Initialize();
    
  public:
    Font();
    explicit Font(std::filesystem::path  font);
    Font(std::filesystem::path font, const AtlasGeneratorSettings& settings);
    ~Font();
    
  public:
    SharedPtr<Texture> GetAtlasTexture()const;
    const MSDFData* GetMSDFData()const;
    
    void GenerateAtlas();
    
    
  
    
  public:
    static void Init();
    static void Shutdown();
    static bool SaveAtlasGeneratorSettings(const std::filesystem::path& filepath);
    static bool LoadAtlasGeneratorSettings(const std::filesystem::path& filepath);
    static const AtlasGeneratorSettings& GetAtlasGeneratorSettings();
    
    
    
    static SharedPtr<Font> Default();
    
  private:
    friend class FontAtlasSettingsSerializer;
  };
}