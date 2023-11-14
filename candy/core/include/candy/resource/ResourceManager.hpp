#pragma once
#include <filesystem>
#include "InternalResource.hpp"
#include <unordered_map>
#include <vector>
#include "ResourceDatabase.hpp"
#include <deque>
namespace Candy
{
  class ResourceManager
  {
  private:
    std::filesystem::path rootDirectory;
    std::filesystem::path assetsDirectory;
    std::filesystem::path cacheDirectory;
    std::filesystem::path configDirectory;
    std::filesystem::path logsDirectory;
    ResourceDatabase database;
    
    std::deque<uint32_t> freeIDs;
    uint32_t currentMaxID=0;
    std::unordered_map<uint32_t, InternalResource> resources;
    std::unordered_map<ResourceType, std::vector<uint32_t>> resourceTypeMap;
    
    
  public:
    explicit ResourceManager(std::filesystem::path  rootDirectory);
    
  public:
    void BuildDatabase();
    bool ValidateAll(bool createIfMissing = true);
    void AddResource(ResourceType resourceType, const std::filesystem::path& resourceFilePath);
    const std::filesystem::path& GetRootDirectory()const;
    const std::filesystem::path& GetAssetsDirectory()const;
    const std::filesystem::path& GetCacheDirectory()const;
    const std::filesystem::path& GetConfigDirectory()const;
    const std::filesystem::path& GetLogsDirectory()const;
    
    
    
    static ResourceType DetermineResourceType(const std::filesystem::path& path);
    
    
  };
}