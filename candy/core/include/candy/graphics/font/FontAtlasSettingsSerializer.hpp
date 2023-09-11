#pragma once
#include "FontManager.hpp"
namespace Candy::Graphics
{
  class FontAtlasSettingsSerializer
  {
  private:
    FontAtlasGeneratorSettings* settings;
    
  public:
    explicit FontAtlasSettingsSerializer(FontAtlasGeneratorSettings* settings);
    bool Serialize(const std::filesystem::path& filepath);
    bool Deserialize(const std::filesystem::path& filepath);
  };
}