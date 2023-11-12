#pragma once
#include <filesystem>
#include "AssetFileManager.hpp"
namespace Candy
{
  class FileManager
  {
  private:
    AssetFileManager assetFileManager;
  
  public:
    static std::filesystem::path InternalDirectory();
    static std::filesystem::path InternalAssetsDirectory();
    static std::filesystem::path InternalConfigDirectory();
    static std::filesystem::path ProjectsDirectory();
    
    
  };
}