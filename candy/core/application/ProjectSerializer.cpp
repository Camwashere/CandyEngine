#include "ProjectSerializer.hpp"
#include <ryml_std.hpp>
#include <ryml.hpp>


namespace Candy{
    ProjectSerializer::ProjectSerializer(SharedPtr<Project> projectValue) : project(projectValue)
    {
    
    }
    
    bool ProjectSerializer::Serialize(const std::filesystem::path& filepath)
    {
        c4::yml::Tree tree;
        c4::yml::NodeRef root = tree.rootref();
        const auto& config = project->GetConfig();
        
        root |= c4::yml::MAP;
        root["Project"] |= c4::yml::MAP;
        root["Project"]["Name"] << config.name;
        root["Project"]["StartScene"] << config.startScene.string();
        root["Project"]["AssetDirectory"] << config.assetDirectory.string();
        root["Project"]["ScriptModulePath"] << config.scriptModulePath.string();
        
        std::ofstream fout(filepath);
        fout << c4::yml::emit_yaml(tree);
        
        return true;
    }
    
    bool ProjectSerializer::Deserialize(const std::filesystem::path& filepath)
    {
        auto& config = project->GetConfig();
        
        // read the file into a string
        std::ifstream fin(filepath);
        std::string yaml_str((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());
        
        // parse the YAML string
        ryml::Tree tree = ryml::parse_in_arena(ryml::to_csubstr(yaml_str));
        ryml::NodeRef root = tree.rootref();
        
        auto projectNode = root["Project"];
        if (projectNode.empty())
        {
            return false;
        }
        auto nameNode = projectNode["Name"];
        auto startSceneNode = projectNode["StartScene"].val();
        auto assetDirectoryNode = projectNode["AssetDirectory"].val();
        auto scriptModulePathNode = projectNode["ScriptModulePath"].val();
        projectNode["Name"] >> config.name;
        std::string startScenePath;
        std::string assetDirectoryPath;
        std::string scriptModulePath;
        projectNode["StartScene"] >> startScenePath;
        projectNode["AssetDirectory"] >> assetDirectoryPath;
        projectNode["ScriptModulePath"] >> scriptModulePath;
        config.startScene = startScenePath;
        config.assetDirectory = assetDirectoryPath;
        config.scriptModulePath = scriptModulePath;
      

        return true;
        
    }
}