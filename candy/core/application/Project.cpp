#include "Project.hpp"
#include "ProjectSerializer.hpp"
namespace Candy{
    SharedPtr<Project> Project::New()
    {
        activeProject = CreateSharedPtr<Project>();
        return activeProject;
    }
    
    SharedPtr<Project> Project::Load(const std::filesystem::path& path)
    {
        SharedPtr<Project> project;
        
        ProjectSerializer serializer(project);
        if (serializer.Serialize(path))
        {
            activeProject->projectDirectory = path.parent_path();
            activeProject = project;
            return activeProject;
        }
        
        return nullptr;
        
    }
    
    bool Project::SaveActive(const std::filesystem::path& path)
    {
        ProjectSerializer serializer(activeProject);
        
        if (serializer.Serialize(path))
        {
            activeProject->projectDirectory = path.parent_path();
            return true;
        }
        return false;
    }
}