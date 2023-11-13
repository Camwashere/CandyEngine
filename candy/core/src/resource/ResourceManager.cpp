#include <candy/resource/ResourceManager.hpp>
#include <CandyPch.hpp>
namespace Candy
{
  ResourceManager::ResourceManager(std::filesystem::path  dir, bool createMissing) : rootDirectory(std::move(dir)), database(rootDirectory)
  {
    bool validated = ValidateRootDirectory(createMissing);
    CANDY_CORE_ASSERT_MSG(validated, "Failed to validate resource manager directory structure for directory '{}'", rootDirectory.string());
    
  
  }
  void ResourceManager::BuildDatabase()
  {
    for (const auto& dirEntry : std::filesystem::recursive_directory_iterator(assetsDirectory))
    {
      if (dirEntry.is_regular_file())
      {
        const auto& path = dirEntry.path();
        ResourceType resourceType = DetermineResourceType(path);
        
        AddResource(resourceType, path);
      }
    }
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
  bool ResourceManager::ValidateRootDirectory(bool createIfMissing)
  {
    CANDY_CORE_ASSERT(std::filesystem::exists(rootDirectory) && std::filesystem::is_directory(rootDirectory));
    
    assetsDirectory = rootDirectory / "assets";
    if (! std::filesystem::exists(assetsDirectory))
    {
      if (createIfMissing)
      {
        std::filesystem::create_directory(assetsDirectory);
      }
      else
      {
        return false;
      
      }
    }
    cacheDirectory = rootDirectory / "cache";
    if (! std::filesystem::exists(cacheDirectory))
    {
      if (createIfMissing)
      {
        std::filesystem::create_directory(cacheDirectory);
      }
      else
      {
        return false;
      
      }
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
        return ResourceTypeFromExtension(path.extension().string());
      }
      
    }
    return ResourceType::Unknown;
  }
  ResourceType ResourceManager::ResourceTypeFromExtension(const std::string& extension)
  {
    if (extension == ".ttf" || extension == ".otf" || extension == ".woff")
    {
      return ResourceType::Font;
    }
    if (extension == ".jpg" || extension == ".jpeg" || extension == ".png" || extension == ".bmp" || extension == ".tga")
    {
      return ResourceType::Image;
    }
    if (extension == ".tex")
    {
      return ResourceType::Texture;
    }
    if (extension == ".glsl" || extension == ".hlsl" || extension == ".spv")
    {
      return ResourceType::Shader;
    }
    if (extension == ".mesh")
    {
      return ResourceType::Mesh;
    }
    if (extension == ".anim")
    {
      return ResourceType::Animation;
    }
    if (extension == ".model" || extension == ".fbx" || extension == ".obj")
    {
      return ResourceType::Model;
    }
    if (extension == ".cs")
    {
      return ResourceType::Script;
    }
    return ResourceType::Unknown;
  }
  const std::filesystem::path& ResourceManager::GetRootDirectory()const
  {
    return rootDirectory;
  }
  
  
}