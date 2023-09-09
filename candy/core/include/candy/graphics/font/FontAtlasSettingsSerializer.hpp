#pragma once
#include "Font.hpp"
namespace Candy::Graphics
{
  class FontAtlasSettingsSerializer
  {
  private:
    Font::AtlasGeneratorSettings* settings;
    
  public:
    explicit FontAtlasSettingsSerializer(Font::AtlasGeneratorSettings* settings);
    bool Serialize(const std::filesystem::path& filepath);
    bool Deserialize(const std::filesystem::path& filepath);
  };
}