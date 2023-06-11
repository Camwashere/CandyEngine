#include "ProjectSerializer.hpp"



namespace Candy{
    ProjectSerializer::ProjectSerializer(SharedPtr<Project> projectValue) : project(projectValue)
    {
    
    }
    
    bool ProjectSerializer::Serialize(const std::filesystem::path& filepath)
    {
        /*const auto& config = project->GetConfig();
        
        YAML::Emitter out;
        {
            out << YAML::BeginMap;
            out << YAML::Key << "Project" << YAML::Value;
            {
                out << YAML::BeginMap; // Project
                out << YAML::Key << "Name" << YAML::Value << config.name.ToStdString();
                out << YAML::Key << "StartScene" << YAML::Value << config.startScene.string();
                out << YAML::Key << "AssetDirectory" << YAML::Value << config.assetDirectory.string();
                out << YAML::Key << "ScriptModulePath" << YAML::Value << config.scriptModulePath.string();
                out << YAML::EndMap; // Project
            }
            out << YAML::EndMap;
        }
        std::ofstream fout(filepath);
        fout << out.c_str();*/
        return true;
    }
    
    bool ProjectSerializer::Deserialize(const std::filesystem::path& filepath)
    {
        /*auto& config = project->GetConfig();
        
        YAML::Node data;
        try
        {
            data = YAML::LoadFile(filepath.string());
        }
        catch (YAML::ParserException& e)
        {
            CANDY_CORE_ERROR("Failed to load project file '{0}'\n   {1}", filepath.string(), e.what());
            return false;
        }
        auto projectNode = data["Project"];
        if (!projectNode)
            return false;

        config.name = projectNode["Name"].as<std::string>();
        config.startScene = projectNode["StartScene"].as<std::string>();
        config.assetDirectory = projectNode["AssetDirectory"].as<std::string>();
        config.scriptModulePath = projectNode["ScriptModulePath"].as<std::string>();*/
        return true;
        
    }
}