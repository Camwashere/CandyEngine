#include <candy/engine/AssetFileManager.hpp>
#include <utility>

namespace Candy
{
  AssetFileManager::AssetFileManager(std::filesystem::path  projectPathVal) : projectPath(std::move(projectPathVal))
  {
  
  }
}