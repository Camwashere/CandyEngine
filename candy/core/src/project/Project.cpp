#include "candy/project/Project.hpp"
#include <utility>
#include "CandyPch.hpp"
#include "candy/project/ProjectSerializer.hpp"

namespace Candy
{
  
  Project::Project(std::filesystem::path  filePath) : projectFilePath(std::move(filePath)), rootDirectory(projectFilePath.parent_path())
  {
    assetsDirectory = rootDirectory / "assets";
    cacheDirectory = rootDirectory / "cache";
    packagesDirectory = rootDirectory / "packages";
    libraryDirectory = rootDirectory / "library";
    logsDirectory = rootDirectory / "logs";
    configDirectory = rootDirectory / "config";
    metaDirectory = rootDirectory / "meta";
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
    return assetsDirectory;
  }
  std::filesystem::path Project::GetStartScenePath()const
  {
    return rootDirectory / metaData.startScenePath;
  }
  
}