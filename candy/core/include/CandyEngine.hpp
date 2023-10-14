#pragma once
#include <filesystem>
#include <candy/utils/Version.hpp>
namespace Candy
{
  class CandyEngine
  {
  public:
    static bool Init();
    static const std::filesystem::path& GetInternalDirectory();
    static const std::filesystem::path& GetInternalAssetsDirectory();
    static const std::filesystem::path& GetInternalConfigDirectory();
    static const std::filesystem::path& GetProjectsDirectory();
    static const Version& EngineVersion();
    static inline const std::string PROJECT_FILE_EXTENSION=".candy";
  };
}