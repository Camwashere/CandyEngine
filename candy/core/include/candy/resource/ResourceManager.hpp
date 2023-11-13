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
    ResourceDatabase database;
    
    std::deque<uint32_t> freeIDs;
    uint32_t currentMaxID=0;
    std::unordered_map<uint32_t, InternalResource> resources;
    std::unordered_map<ResourceType, std::vector<uint32_t>> resourceTypeMap;
    
  private:
    void BuildDatabase();
    bool ValidateRootDirectory(bool createIfMissing = true);
    
  public:
    explicit ResourceManager(std::filesystem::path  rootDirectory, bool createMissing);
    
  public:
    void AddResource(ResourceType resourceType, const std::filesystem::path& resourceFilePath);
    const std::filesystem::path& GetRootDirectory()const;
    static ResourceType ResourceTypeFromExtension(const std::string& extension);
    static ResourceType DetermineResourceType(const std::filesystem::path& path);
    
    
  };
}