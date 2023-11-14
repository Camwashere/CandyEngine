#pragma once
#include <filesystem>
#include "candy/utils/Version.hpp"
#include "candy/base/Base.hpp"
#include <vector>
#include <candy/resource/AssetManager.hpp>
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
    AssetManager resourceManager;
    
    
    ProjectMetaData metaData;
    
  public:
    explicit Project(std::filesystem::path  projectFilePath);
    
  public:
    [[nodiscard]] std::string GetName()const;
    [[nodiscard]] const std::filesystem::path& GetProjectFilePath()const;
    [[nodiscard]] const ProjectMetaData& GetMetaData()const;
    [[nodiscard]] const std::filesystem::path& GetAssetsDirectory()const;
    [[nodiscard]] std::filesystem::path GetStartScenePath()const;
    AssetManager& GetResourceManager();
    const AssetManager& GetResourceManager()const;
    
    
    friend class ProjectManager;
  };
  
}