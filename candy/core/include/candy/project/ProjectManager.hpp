#pragma once
#include "Project.hpp"
namespace Candy
{
  class ProjectManager
  {
  private:
    static bool Serialize(const ProjectMetaData& metaData, const std::filesystem::path& filepath);
    static bool Deserialize(ProjectMetaData* metaData, const std::filesystem::path& filepath);
    //static bool CreateProjectDirectories(const Project& project);
    
    static bool LoadProjectDirectory(const std::filesystem::path& projectDirectoryPath);
    static bool LoadProjectFile(const std::filesystem::path& projectFilePath);
  public:
    static bool Init();
    static bool NewProject(const std::string& projectName);
    static bool NewProject(const std::string& projectName, const std::filesystem::path& containingFolder);
    static bool SaveProject();
    static bool SaveProjectAs(const std::filesystem::path& filepath);
    
    /**
     * @brief Loads a new project as the active project if successful.
     * @param projectPath The path to the project directory that contains the .candy file. If a path to a .candy file is given, the parent directory is used.
     * @return True if the project directory structure is valid and the project was successfully loaded as the active project
     * @return False if the project directory structure is invalid or the project could not be loaded
     */
    static bool LoadProject(const std::filesystem::path& projectPath);
    
    static bool LoadOrCreateProject(const std::string& projectName);
    
    
    
    static const SharedPtr<Project>& GetActiveProject();
    
    static std::string ProjectName();
    static const std::filesystem::path& ProjectFilePath();
    static const ProjectMetaData& GetMetaData();
    static const std::filesystem::path& GetAssetsDirectory();
    static const std::filesystem::path& GetConfigDirectory();
    static const std::filesystem::path& GetStartScenePath();
  };
}