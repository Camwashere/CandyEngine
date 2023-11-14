#pragma once
#include <filesystem>
#include <unordered_map>
#include <vector>
#include "AssetDatabase.hpp"
#include <deque>
namespace Candy
{
  class AssetManager
  {
  private:
    std::filesystem::path rootDirectory;
    std::filesystem::path assetsDirectory;
    std::filesystem::path cacheDirectory;
    std::filesystem::path configDirectory;
    std::filesystem::path logsDirectory;
    AssetDatabase database;
    
    std::deque<uint32_t> freeIDs;
    uint32_t currentMaxID=0;
    std::unordered_map<uint32_t, Asset> assets;
    std::unordered_map<AssetType, std::vector<uint32_t>> assetTypeMap;
    
    
  public:
    explicit AssetManager(std::filesystem::path  rootDirectory);
    
  public:
    void BuildDatabase();
    bool ValidateAll(bool createIfMissing = true);
    void AddAsset(AssetType assetType, const std::filesystem::path& resourceFilePath);
    const std::filesystem::path& GetRootDirectory()const;
    const std::filesystem::path& GetAssetsDirectory()const;
    const std::filesystem::path& GetCacheDirectory()const;
    const std::filesystem::path& GetConfigDirectory()const;
    const std::filesystem::path& GetLogsDirectory()const;
    
    
    
    static AssetType DetermineAssetType(const std::filesystem::path& path);
    
    
  };
}