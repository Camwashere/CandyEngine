#pragma once
#include <filesystem>
#include "candy/utils/Version.hpp"
#include "candy/base/Base.hpp"
#include <vector>
namespace Candy
{

  struct ProjectMetaData
  {
    std::filesystem::path startScenePath;
    Version engineVersion;
    Version applicationVersion;
  };
  
  
  
  class Project
  {
  private:
    std::filesystem::path projectFilePath;
    std::filesystem::path rootDirectory;
    
    
    std::filesystem::path assetsDirectory;
    std::filesystem::path cacheDirectory;
    std::filesystem::path packagesDirectory;
    std::filesystem::path libraryDirectory;
    std::filesystem::path logsDirectory;
    std::filesystem::path configDirectory;
    std::filesystem::path metaDirectory;
    
    ProjectMetaData metaData;
    
  public:
    explicit Project(std::filesystem::path  projectFilePath);
    
  public:
    [[nodiscard]] std::string GetName()const;
    [[nodiscard]] const std::filesystem::path& GetProjectFilePath()const;
    [[nodiscard]] const ProjectMetaData& GetMetaData()const;
    [[nodiscard]] const std::filesystem::path& GetAssetsDirectory()const;
    [[nodiscard]] const std::filesystem::path& GetStartScenePath()const;
    
    friend class ProjectManager;
  };
  
}