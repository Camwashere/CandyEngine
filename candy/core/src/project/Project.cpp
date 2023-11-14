#include "candy/project/Project.hpp"
#include <utility>
#include "CandyPch.hpp"


namespace Candy
{
  
  Project::Project(std::filesystem::path  filePath) : projectFilePath(std::move(filePath)), rootDirectory(projectFilePath.parent_path()), resourceManager(rootDirectory)
  {
    resourceManager.ValidateAll(true);
    resourceManager.BuildDatabase();
  }
  
  std::string Project::GetName()const
  {
    return projectFilePath.stem().string();
  }
  const std::filesystem::path& Project::GetProjectFilePath()const
  {
    return projectFilePath;
  }
  const ProjectMetaData& Project::GetMetaData()const
  {
    return metaData;
  }
  const std::filesystem::path& Project::GetAssetsDirectory()const
  {
    return resourceManager.GetAssetsDirectory();
  }
  AssetManager& Project::GetResourceManager()
  {
    return resourceManager;
  }
  
  const AssetManager& Project::GetResourceManager()const
  {
    return resourceManager;
  }
  std::filesystem::path Project::GetStartScenePath()const
  {
    return rootDirectory / metaData.startScenePath;
  }
  
}