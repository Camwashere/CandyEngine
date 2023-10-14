#include "CandyEngine.hpp"
#include <vector>
#include <string>
#include "CandyPch.hpp"
#include <candy/project/ProjectManager.hpp>
namespace Candy
{
  struct CandyEngineData
  {
    std::filesystem::path internalDirectory;
    std::filesystem::path projectsDirectory;
    
    std::filesystem::path internalAssetsDirectory;
    std::filesystem::path internalConfigDirectory;
    
    Version engineVersion=Version(0, 0, 1);
  };
  
  static CandyEngineData data;
  
  static bool ValidateDirectories(const std::filesystem::path& directoryPath, const std::vector<std::string>& names)
  {
    CANDY_PROFILE_FUNCTION();
    if (!std::filesystem::exists(directoryPath))
    {
      CANDY_CORE_ERROR("Directory {0} does not exist!", directoryPath.string());
      return false;
    }
    
    for (const std::string& name : names)
    {
      std::filesystem::path path=directoryPath/name;
      if (!std::filesystem::exists(path))
      {
        CANDY_CORE_ERROR("Directory {0} does not contain the directory: {1}!", path.string(), name);
        return false;
      }
    }
    
    return true;
  }
  bool CandyEngine::Init()
  {
    data.internalDirectory=CANDY_DIRECTORY_INTERNALS;
    data.projectsDirectory=CANDY_DIRECTORY_PROJECTS;
    
    if (!ValidateDirectories(data.internalDirectory, {"assets", "config"}))
    {
      return false;
    }
    
    data.internalAssetsDirectory=data.internalDirectory/"assets";
    data.internalConfigDirectory=data.internalDirectory/"config";
    
    if (! ValidateDirectories(data.projectsDirectory, {"TestProject"}))
    {
      return false;
    }
    
    if (! ValidateDirectories(data.internalAssetsDirectory, {"fonts", "icons", "shaders"}))
    {
      return false;
    }
    
    if (! ValidateDirectories(data.internalConfigDirectory, {"font", "shader", "ui", "vulkan"}))
    {
      return false;
    }
    
    return ProjectManager::Init();
  }
  
  
  const std::filesystem::path& CandyEngine::GetInternalDirectory()
  {
    return data.internalDirectory;
  }
  const std::filesystem::path& CandyEngine::GetInternalAssetsDirectory()
  {
    return data.internalAssetsDirectory;
  }
  const std::filesystem::path& CandyEngine::GetInternalConfigDirectory()
  {
    return data.internalConfigDirectory;
  }
  
  const std::filesystem::path& CandyEngine::GetProjectsDirectory()
  {
    return data.projectsDirectory;
  }
  
  const Version& CandyEngine::EngineVersion()
  {
    return data.engineVersion;
  }
}