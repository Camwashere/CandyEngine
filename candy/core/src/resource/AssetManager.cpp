#include <candy/resource/AssetManager.hpp>
#include <CandyPch.hpp>
#include "candy/resource/Asset.hpp"
namespace Candy
{
  AssetManager::AssetManager(std::filesystem::path  dir) : rootDirectory(std::move(dir)), database(rootDirectory)
  {
    assetsDirectory = rootDirectory / "assets";
    cacheDirectory = rootDirectory / "cache";
    configDirectory = rootDirectory / "config";
    logsDirectory = rootDirectory / "logs";
    
    
    
    
  
  }
  void AssetManager::BuildDatabase()
  {
    for (const auto& dirEntry : std::filesystem::recursive_directory_iterator(assetsDirectory))
    {
      if (dirEntry.is_regular_file())
      {
        const auto& path = dirEntry.path();
        AssetType resourceType = DetermineAssetType(path);
        
        if (resourceType != AssetType::Unknown)
        {
          AddAsset(resourceType, path);
        }
      }
    }
    database.Build(assetTypeMap, assets);
  }
  
  void AssetManager::AddAsset(AssetType assetType, const std::filesystem::path& assetFilePath)
  {
    if (freeIDs.empty())
    {
      uint32_t currentID = currentMaxID;
      
      auto it = assets.find(currentID);
      if (it != assets.end())
      {
        CANDY_CORE_ERROR("Add asset ID assignment error with id: '{}', filepath: '{}'", currentID, assetFilePath.string());
        return;
      }
      
      currentMaxID++;
      Asset asset(currentID, assetType, assetFilePath);
      assets.insert({currentID, asset});
      assetTypeMap[assetType].push_back(currentID);
    }
    else
    {
      uint32_t currentID = freeIDs.front();
      freeIDs.pop_front();
      
      auto it = assets.find(currentID);
      if (it != assets.end())
      {
        CANDY_CORE_ERROR("Add asset ID assignment error with id: '{}', filepath: '{}'", currentID, assetFilePath.string());
        return;
      }
      
      Asset asset(currentID, assetType, assetFilePath);
      assets.insert({currentID, asset});
      assetTypeMap[assetType].push_back(currentID);
      
    
    }
  }
  
  static bool ValidateDirectory(const std::filesystem::path& dir, bool createIfMissing)
  {
    if (! std::filesystem::exists(dir))
    {
      if (createIfMissing)
      {
        std::filesystem::create_directory(dir);
      }
      else
      {
        return false;
        
      }
    }
    return true;
  }
  bool AssetManager::ValidateAll(bool createIfMissing)
  {
    CANDY_CORE_ASSERT(std::filesystem::exists(rootDirectory) && std::filesystem::is_directory(rootDirectory));
    
    if (! ValidateDirectory(assetsDirectory, createIfMissing))
    {
      return false;
    }
    if (! ValidateDirectory(cacheDirectory, createIfMissing))
    {
      return false;
    }
    if (! ValidateDirectory(configDirectory, createIfMissing))
    {
      return false;
    }
    if (! ValidateDirectory(logsDirectory, createIfMissing))
    {
      return false;
    }
    if (! database.ValidFile())
    {
      if (createIfMissing)
      {
        database.CreateFile();
      }
    }
    return true;
  }
  
  AssetType AssetManager::DetermineAssetType(const std::filesystem::path& path)
  {
    if (std::filesystem::is_regular_file(path))
    {
      if (path.has_extension())
      {
        return Asset::TypeFromExtension(path.extension().string());
      }
      
    }
    return AssetType::Unknown;
  }
  
  const std::filesystem::path& AssetManager::GetRootDirectory()const
  {
    return rootDirectory;
  }
  
  const std::filesystem::path& AssetManager::GetAssetsDirectory()const
  {
    return assetsDirectory;
  }
  const std::filesystem::path& AssetManager::GetCacheDirectory()const
  {
    return cacheDirectory;
  }
  
  const std::filesystem::path& AssetManager::GetConfigDirectory()const
  {
    return configDirectory;
  }
  const std::filesystem::path& AssetManager::GetLogsDirectory()const
  {
    return logsDirectory;
  }
  
  
}