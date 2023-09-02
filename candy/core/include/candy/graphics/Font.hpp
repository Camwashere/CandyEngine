#pragma once
#include <filesystem>
#include <candy/base/Base.hpp>
#include <candy/graphics/Texture.hpp>
namespace Candy::Graphics
{
  struct MSDFData;
  class Font
  {
  private:
    MSDFData* data;
    SharedPtr<Texture> atlasTexture;
    
  public:
    explicit Font(const std::filesystem::path& path);
    ~Font();
    
    const MSDFData* GetMSDFData()const;
    [[nodiscard]] SharedPtr<Texture> GetAtlasTexture()const;
    
    static SharedPtr<Font> Default();
  };
}