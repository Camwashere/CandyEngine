#pragma once
#include <filesystem>
#include <candy/utils/Version.hpp>
#include <candy/base/Base.hpp>
namespace Candy
{
  struct ProjectConfig
  {
    std::string name;
    std::filesystem::path startScene;
    std::filesystem::path assetDirectory;
    Version engineVersion;
    Version projectVersion;
  };
  
  
  class Project
  {
  private:
    ProjectConfig config;
    std::filesystem::path projectDirectory;
    
  public:
    ProjectConfig& GetConfiguration();
    
    
    
    
  private:
    static SharedPtr<Project> activeProject;
    
  public:
    static inline const char* PROJECT_FILE_EXTENSION=".candy";
    static std::filesystem::path GetAssetDirectory();
    static const std::filesystem::path& GetActiveProjectDirectory();
   static std::filesystem::path GetAllProjectsDirectory();
    static SharedPtr<Project> New();
    static SharedPtr<Project> Load(const std::filesystem::path& path);
    static bool SaveActive();
    static bool SaveActive(const std::filesystem::path& path);
    static SharedPtr<Project> GetActive();
    
  };
}