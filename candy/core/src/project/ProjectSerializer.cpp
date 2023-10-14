#include "candy/project/ProjectSerializer.hpp"
#include "CandyPch.hpp"
#include <utility>
#include "rapidyaml/src/ryml_std.hpp"
#include "rapidyaml/src/ryml.hpp"

namespace Candy
{
  ProjectSerializer::ProjectSerializer(SharedPtr<Project> projectValue) : project(std::move(projectValue))
  {
  
  }
  bool ProjectSerializer::Serialize(const std::filesystem::path& filepath)
  {
    /*CANDY_PROFILE_FUNCTION();
    c4::yml::Tree tree;
    c4::yml::NodeRef root = tree.rootref();
    root |= c4::yml::MAP;
    const auto& config = project->GetConfiguration();
    root["Project"] |= c4::yml::MAP;
    root["Project"]["Name"] << config.name;
    root["Project"]["StartScene"] << config.startScene.string();
    root["Project"]["AssetDirectory"] << config.assetDirectory.string();
    root["Project"]["EngineVersion"] << config.engineVersion;
    root["Project"]["ProjectVersion"] << config.projectVersion;
    
    
    
    FILE* out = fopen(filepath.string().c_str(), "w");
    if (!out)
    {
      CANDY_CORE_ERROR("Failed to open file {0} for project serialization", filepath.string());
      return false;
    }
    c4::yml::emit_yaml(tree, out);
    fclose(out);
    return true;*/
  }
  
  bool ProjectSerializer::Deserialize(const std::filesystem::path& filepath)
  {
    /*CANDY_PROFILE_FUNCTION();
    CANDY_CORE_INFO("DESERIALIZING PROJECT");
    auto& config = project->GetConfiguration();
    
    // read the file into a string
    std::ifstream fin(filepath);
    std::stringstream buffer;
    buffer << fin.rdbuf();
    std::string yaml_str = buffer.str();
    if (yaml_str.empty())
    {
      CANDY_CORE_ERROR("EMPTY YAML STRING WITH PATH: {}", filepath.string());
      return false;
    }
    // parse the YAML string
    ryml::Tree tree = ryml::parse_in_arena(ryml::to_csubstr(yaml_str));
    ryml::NodeRef root = tree.rootref();
    
    auto projectNode = root["Project"];
    if (projectNode.empty())
    {
      CANDY_CORE_ERROR("Failed to deserialize project file {0}. Empty Project Root Node", filepath.string());
      return false;
    }
    std::string startScene;
    std::string assetDir;
    projectNode["Name"] >> config.name;
    projectNode["StartScene"] >> startScene;
    projectNode["AssetDirectory"] >> assetDir;
    projectNode["EngineVersion"] >> config.engineVersion;
    projectNode["ProjectVersion"] >> config.projectVersion;
    
    config.startScene = startScene;
    config.assetDirectory = assetDir;*/
    
    return true;
    
  }
}