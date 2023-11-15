#pragma once
#include <filesystem>
#include <unordered_map>
#include <vector>
#include "AssetDatabase.hpp"
#include <deque>
#include <efsw/efsw.hpp>
#include <thread>


namespace Candy
{
  class AssetManager  : public efsw::FileWatchListener
  {
  private:
    std::filesystem::path rootDirectory;
    std::filesystem::path assetsDirectory;
    std::filesystem::path cacheDirectory;
    std::filesystem::path configDirectory;
    std::filesystem::path logsDirectory;
    AssetDatabase database;
    
    
    efsw::FileWatcher fileWatcher;
    std::thread fileWatcherThread;
    
    std::deque<uint32_t> freeIDs;
    uint32_t currentMaxID=0;
    std::unordered_map<uint32_t, Asset> assets;
    std::unordered_map<AssetType, std::vector<uint32_t>> assetTypeMap;
    
    std::vector<long> watchIDs;
    
    
  public:
    explicit AssetManager(std::filesystem::path rootDirectory);
    
  private:
    void handleFileAction(efsw::WatchID watchid, const std::string& dir, const std::string& filename, efsw::Action action, std::string oldFilename) override;
    
  public:
    void StartFileWatcher();
    void StopFileWatcher();
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