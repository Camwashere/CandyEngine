#pragma once
#include <filesystem>
#include "Asset.hpp"
#include <unordered_map>
namespace c4::yml
{
  class Tree;
}
namespace Candy
{
  class AssetDatabase
  {
  private:
    std::filesystem::path databaseFilePath;
    
    
  public:
    explicit AssetDatabase(const std::filesystem::path& rootDirectory);
    
  public:
    void Build(const std::unordered_map<AssetType, std::vector<uint32_t>>& assetMap, const std::unordered_map<uint32_t, Asset>& assets);
    [[nodiscard]] bool ValidFile()const;
    bool CreateFile(bool replaceExisting = false);
    
    
    
    friend class AssetManager;
    
    
    
  };
}