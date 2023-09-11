#pragma once
#include <filesystem>
namespace Candy::Graphics
{
  struct MSDFData;
  struct FontGeometryData;
  class MSDFSerializer
  {
  public:
    static bool Serialize(MSDFData* msdfData, const std::filesystem::path& filepath);
    static bool Deserialize(MSDFData* fontData, const std::filesystem::path& filepath);
    
  };
}