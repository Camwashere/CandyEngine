#pragma once
#include <filesystem>
#include <candy/utils/Version.hpp>
namespace Candy
{
  struct ProjectConfig
  {
    std::string name;
    std::filesystem::path projectFilePath;
    std::filesystem::path rootWorkingDirectory;
    Version engineVersion;
  };
  class Project
  {
  private:
    ProjectConfig config;
    
  public:
    explicit Project(ProjectConfig projectConfig);
    
  public:
    ProjectConfig& GetConfiguration(){return config;}
    [[nodiscard]] std::string GetName()const{return config.name;}
    [[nodiscard]] std::filesystem::path GetProjectFilePath()const{return config.projectFilePath;}
    [[nodiscard]] std::filesystem::path GetRootWorkingDirectory()const{return config.rootWorkingDirectory;}
    [[nodiscard]] Version GetEngineVersion()const{return config.engineVersion;}
    
    
  };
}