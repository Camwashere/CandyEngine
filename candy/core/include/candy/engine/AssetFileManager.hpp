#pragma once
#include <filesystem>
namespace Candy
{
  class AssetFileManager
  {
  private:
    std::filesystem::path projectPath;
    
  public:
    AssetFileManager(std::filesystem::path  projectPath);
  };
}