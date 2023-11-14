#pragma once
#include <filesystem>
#include "InternalResource.hpp"
#include <unordered_map>
namespace c4::yml
{
  class Tree;
}
namespace Candy
{
  class ResourceDatabase
  {
  private:
    std::filesystem::path databaseFilePath;
    
    
  public:
    explicit ResourceDatabase(const std::filesystem::path& rootDirectory);
    
  public:
    void Build(const std::unordered_map<ResourceType, std::vector<uint32_t>>& resourceMap, const std::unordered_map<uint32_t, InternalResource>& resources);
    [[nodiscard]] bool ValidFile()const;
    bool CreateFile(bool replaceExisting = false);
    bool ValidateResource(const InternalResource& resource);
    bool RemoveResource(uint32_t id);
    bool AddResource(const InternalResource& resource);
    bool AddOrReplaceResource(const InternalResource& resource);
    bool UpdateResource(const InternalResource& resource);
    
    
    friend class ResourceManager;
    
    
    
  };
}