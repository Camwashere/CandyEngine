#pragma once
#include "AssetType.hpp"
#include <string>
#include <vector>
#include <unordered_map>
#include <filesystem>
namespace Candy
{
  class Asset
  {
  private:
    const uint32_t id;
    const AssetType type;
    std::filesystem::path path;
    uint32_t refCount;
    
  public:
    Asset(uint32_t id, AssetType type, std::filesystem::path  path);
    
    
  public:
    [[nodiscard]] uint32_t GetID()const;
    [[nodiscard]] AssetType GetType()const;
    [[nodiscard]] const std::filesystem::path& GetPath()const;
    [[nodiscard]] uint32_t GetRefCount()const;
    void AddRef();
    void FreeRef();
    
  
  private:
    static std::vector<std::string> assetTypeStrings;
    static std::unordered_map<std::string, AssetType> extensionAssociations;
  public:
    static const std::string& TypeToString(AssetType type);
    static AssetType TypeFromExtension(const std::string& extension);
  };
}