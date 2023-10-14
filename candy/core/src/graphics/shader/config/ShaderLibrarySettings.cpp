#include "candy/graphics/shader/config/ShaderLibrarySettings.hpp"
#include "CandyPch.hpp"
#include "rapidyaml/src/ryml_std.hpp"
#include "rapidyaml/src/ryml.hpp"
#include <CandyEngine.hpp>

namespace Candy::Graphics
{
  /*ShaderLibrarySettings ShaderLibrarySettings::Default()
  {
    ShaderLibrarySettings settings{};
    settings.compilationSettings.optimize=true;
    settings.compilationSettings.recompileOnLoad=true;
    settings.compilationSettings.glslVersion=460;
    settings.compilationSettings.vulkanVersion=Version(1, 3);
    settings.compilationSettings.preserveBindings=false;
    
    return settings;
  }*/
  
 /* void ShaderLibrarySettings::Save(const std::filesystem::path& filepath, const ShaderLibrarySettings& settings)
  {
    c4::yml::Tree tree;
    c4::yml::NodeRef root = tree.rootref();
    root |= c4::yml::MAP;
    auto libNode = root["ShaderLibrarySettings"];
    libNode |= c4::yml::MAP;
    
    //libNode["InternalCacheDirectory"] << settings.internalCacheDirectory.string();
    //libNode["InternalSourceDirectory"] << settings.internalSourceDirectory.string();
    //libNode["ProjectCacheDirectory"] << settings.projectCacheDirectory.string();
    //libNode["ProjectSourceDirectory"] << settings.projectSourceDirectory.string();
    
    auto compilationNode = libNode["CompilationSettings"];
    auto comp = settings.compilationSettings;
    compilationNode |= c4::yml::MAP;
    compilationNode["AutoMapping"] << comp.autoMapping;
    compilationNode["PreserveBindings"] << comp.preserveBindings;
    compilationNode["SuppressWarnings"] << comp.suppressWarnings;
    compilationNode["WarningsAsErrors"] << comp.warningsAsErrors;
    compilationNode["InvertY"] << comp.invertY;
    compilationNode["GenerateDebugInfo"] << comp.generateDebugInfo;
    compilationNode["Optimize"] << comp.optimize;
    compilationNode["RecompileOnLoad"] << comp.recompileOnLoad;
    compilationNode["GLSLVersion"] << comp.glslVersion;
    compilationNode["VulkanVersion"] << comp.vulkanVersion;
    
    
    
    FILE* out = fopen(filepath.string().c_str(), "w");
    if (!out)
    {
      CANDY_CORE_ERROR("Failed to open file {0} for project serialization", filepath.string());
      CANDY_CORE_ASSERT(false);
    }
    c4::yml::emit_yaml(tree, out);
    fclose(out);
  }*/
  
  
  ShaderLibrarySettings ShaderLibrarySettings::Load()
  {
    CANDY_CORE_INFO("DESERIALIZING PROJECT");
    ShaderLibrarySettings settings{};
    std::filesystem::path filepath = CandyEngine::GetInternalConfigDirectory() / "shader" / "librarySettings.yml";
    // read the file into a string
    std::ifstream fin(filepath);
    std::stringstream buffer;
    buffer << fin.rdbuf();
    std::string yaml_str = buffer.str();
    if (yaml_str.empty())
    {
      CANDY_CORE_ERROR("EMPTY YAML STRING WITH PATH: {}", filepath.string());
      CANDY_CORE_ASSERT(false);
    }
    // parse the YAML string
    ryml::Tree tree = ryml::parse_in_arena(ryml::to_csubstr(yaml_str));
    ryml::NodeRef root = tree.rootref();
    
    auto libNode = root["ShaderLibrarySettings"];
    if (libNode.empty())
    {
      CANDY_CORE_ERROR("Failed to deserialize project file {0}. Empty Project Root Node", filepath.string());
      CANDY_CORE_ASSERT(false);
    }
    
    
    /*std::string internalCache, internalSource, projectCache, projectSource;
    libNode["InternalCacheDirectory"] >> internalCache;
    libNode["InternalSourceDirectory"] >> internalSource;
    libNode["ProjectCacheDirectory"] >> projectCache;
    libNode["ProjectSourceDirectory"] >> projectSource;*/
    
    //settings.internalCacheDirectory = internalCache;
    //settings.internalSourceDirectory = internalSource;
    //settings.projectCacheDirectory = projectCache;
    //settings.projectSourceDirectory = projectSource;
    
    auto compilationNode = libNode["CompilationSettings"];
    
    compilationNode["AutoMapping"] >> settings.compilationSettings.autoMapping;
    compilationNode["PreserveBindings"] >> settings.compilationSettings.preserveBindings;
    compilationNode["SuppressWarnings"] >> settings.compilationSettings.suppressWarnings;
    compilationNode["WarningsAsErrors"] >> settings.compilationSettings.warningsAsErrors;
    compilationNode["InvertY"] >> settings.compilationSettings.invertY;
    compilationNode["GenerateDebugInfo"] >> settings.compilationSettings.generateDebugInfo;
    compilationNode["Optimize"] >> settings.compilationSettings.optimize;
    compilationNode["RecompileOnLoad"] >> settings.compilationSettings.recompileOnLoad;
    compilationNode["GLSLVersion"] >> settings.compilationSettings.glslVersion;
    compilationNode["VulkanVersion"] >> settings.compilationSettings.vulkanVersion;
    
    return settings;
  }
  
}