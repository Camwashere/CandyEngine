#include <candy/resource/ResourceManager.hpp>
#include <CandyPch.hpp>
#include <candy/resource/Resource.hpp>
namespace Candy
{
  ResourceManager::ResourceManager(std::filesystem::path  dir) : rootDirectory(std::move(dir)), database(rootDirectory)
  {
    assetsDirectory = rootDirectory / "assets";
    cacheDirectory = rootDirectory / "cache";
    configDirectory = rootDirectory / "config";
    logsDirectory = rootDirectory / "logs";
    
    
    
    
  
  }
  void ResourceManager::BuildDatabase()
  {
    for (const auto& dirEntry : std::filesystem::recursive_directory_iterator(assetsDirectory))
    {
      if (dirEntry.is_regular_file())
      {
        const auto& path = dirEntry.path();
        ResourceType resourceType = DetermineResourceType(path);
        
        if (resourceType != ResourceType::Unknown)
        {
          AddResource(resourceType, path);
        }
      }
    }
    database.Build(resourceTypeMap, resources);
  }
  
  void ResourceManager::AddResource(ResourceType resourceType, const std::filesystem::path& resourceFilePath)
  {
    if (freeIDs.empty())
    {
      uint32_t currentID = currentMaxID;
      
      auto it = resources.find(currentID);
      if (it != resources.end())
      {
        CANDY_CORE_ERROR("Add resource ID assignment error with id: '{}', filepath: '{}'", currentID, resourceFilePath.string());
        return;
      }
      
      currentMaxID++;
      InternalResource resource(currentID, resourceType, resourceFilePath);
      resources.insert({currentID, resource});
      resourceTypeMap[resourceType].push_back(currentID);
    }
    else
    {
      uint32_t currentID = freeIDs.front();
      freeIDs.pop_front();
      
      auto it = resources.find(currentID);
      if (it != resources.end())
      {
        CANDY_CORE_ERROR("Add resource ID assignment error with id: '{}', filepath: '{}'", currentID, resourceFilePath.string());
        return;
      }
      
      InternalResource resource(currentID, resourceType, resourceFilePath);
      resources.insert({currentID, resource});
      resourceTypeMap[resourceType].push_back(currentID);
      
    
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
  bool ResourceManager::ValidateAll(bool createIfMissing)
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
  
  ResourceType ResourceManager::DetermineResourceType(const std::filesystem::path& path)
  {
    if (std::filesystem::is_regular_file(path))
    {
      if (path.has_extension())
      {
        return Resource::TypeFromExtension(path.extension().string());
      }
      
    }
    return ResourceType::Unknown;
  }
  
  const std::filesystem::path& ResourceManager::GetRootDirectory()const
  {
    return rootDirectory;
  }
  
  const std::filesystem::path& ResourceManager::GetAssetsDirectory()const
  {
    return assetsDirectory;
  }
  const std::filesystem::path& ResourceManager::GetCacheDirectory()const
  {
    return cacheDirectory;
  }
  
  const std::filesystem::path& ResourceManager::GetConfigDirectory()const
  {
    return configDirectory;
  }
  const std::filesystem::path& ResourceManager::GetLogsDirectory()const
  {
    return logsDirectory;
  }
  
  
}