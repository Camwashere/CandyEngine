#pragma once
#include <Candy/CandyEngineBase.hpp>
namespace Candy{
    struct ProjectConfig
    {
        std::string name="Untitled";
        std::filesystem::path startScene;
        std::filesystem::path assetDirectory;
        std::filesystem::path scriptModulePath;
    };
    class Project
    {
    private:
        ProjectConfig config;
        std::filesystem::path projectDirectory="sugar/SandboxProject";
        inline static SharedPtr<Project> activeProject;
    
    public:
        ProjectConfig& GetConfig(){return config;}
    
    public:
        static const std::filesystem::path& GetProjectDirectory()
        {
            CANDY_CORE_ASSERT(activeProject);
            return activeProject->projectDirectory;
        }
        
        static std::filesystem::path GetAssetDirectory()
        {
            CANDY_CORE_ASSERT(activeProject);
            return GetProjectDirectory() / activeProject->config.assetDirectory;
        }
        
        static std::filesystem::path GetAssetFilePath(const std::filesystem::path& path)
        {
            CANDY_CORE_ASSERT(activeProject);
            return GetAssetDirectory()/path;
        }
        
        static SharedPtr<Project> GetActive(){return activeProject;}
        
        static SharedPtr<Project> New();
        static SharedPtr<Project> Load(const std::filesystem::path& path);
        static bool SaveActive(const std::filesystem::path& path);
        
        
        
    };
    
}