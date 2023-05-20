#include "ProjectSerializer.hpp"
#include <fstream>


namespace Candy{
    ProjectSerializer::ProjectSerializer(SharedPtr<Project> projectValue) : project(projectValue)
    {
    
    }
    
    bool ProjectSerializer::Serialize(const std::filesystem::path& filepath)
    {
        const auto& config = project->GetConfig();
        
        //YAML::Emitter out;
        /*{
            out << YAML::BeginMap;
            out << YAML::Key << "project" << YAML::Value;
            {
                out << YAML::BeginMap; // Project
                out << YAML::Key << "name" << YAML::Value << config.name.ToStdString();
                out << YAML::Key << "startScene" << YAML::Value << config.startScene.string();
                out << YAML::Key << "assetDirectory" << YAML::Value << config.assetDirectory.string();
                out << YAML::Key << "scriptModulePath" << YAML::Value << config.scriptModulePath.string();
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
            CANDY_CORE_ERROR("Failed to load project file '{0}'\n", e.what());
            return false;
        }
        auto projectNode = data["project"];
        if (!projectNode)
            return false;

        config.name = projectNode["name"].as<std::string>();
        config.startScene = projectNode["startScene"].as<std::string>();
        config.assetDirectory = projectNode["assetDirectory"].as<std::string>();
        config.scriptModulePath = projectNode["scriptModulePath"].as<std::string>();*/
        return true;
        
    }
}