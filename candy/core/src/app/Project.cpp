#include <candy/app/Project.hpp>
#include <utility>
#include <CandyPch.hpp>
#include <candy/app/ProjectSerializer.hpp>

namespace Candy
{
  
  SharedPtr<Project> Project::activeProject = nullptr;
  ProjectConfig& Project::GetConfiguration()
  {
    return config;
  }
  
  std::filesystem::path Project::GetAssetDirectory()
  {
    CANDY_CORE_ASSERT(activeProject);
    return activeProject->config.assetDirectory;
  }
  const std::filesystem::path& Project::GetActiveProjectDirectory()
  {
    CANDY_CORE_ASSERT(activeProject);
    return activeProject->projectDirectory;
  }
  std::filesystem::path Project::GetAllProjectsDirectory()
  {
    return "projects";
  }
  SharedPtr<Project> Project::New()
  {
    CANDY_PROFILE_FUNCTION();
    activeProject = CreateSharedPtr<Project>();
    return activeProject;
  }
  SharedPtr<Project> Project::Load(const std::filesystem::path& path)
  {
    CANDY_PROFILE_FUNCTION();
    SharedPtr<Project> project = CreateSharedPtr<Project>();
    
    ProjectSerializer serializer(project);
    if (serializer.Deserialize(path))
    {
      project->projectDirectory = path.parent_path();
      activeProject = project;
      return activeProject;
    }
    
    return nullptr;
  }
  bool Project::SaveActive()
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_ASSERT(activeProject);
    std::filesystem::path activePath = GetActiveProjectDirectory()/(activeProject->config.name + PROJECT_FILE_EXTENSION);
    return SaveActive(activePath);
  }
  bool Project::SaveActive(const std::filesystem::path& path)
  {
    CANDY_PROFILE_FUNCTION();
    ProjectSerializer serializer(activeProject);
    if (serializer.Serialize(path))
    {
      activeProject->projectDirectory = path.parent_path();
      return true;
    }
    return false;
    
  }
  SharedPtr<Project> Project::GetActive()
  {
    return activeProject;
  }
}