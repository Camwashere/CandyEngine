#include <candy/graphics/shader/ShaderLibrarySettings.hpp>
#include "CandyPch.hpp"
#include <ryml_std.hpp>
#include <ryml.hpp>
//#include <c4/format.hpp>


/*namespace Candy
{
  size_t to_chars(c4::substr buf, const Candy::Version& v)
  {
    // this call to c4::format() is the type-safe equivalent
    // of snprintf(buf.str, buf.len, "(%f,%f,%f)", v.x, v.y, v.z)
    return c4::format(buf, "[{},{},{}]", v.GetMajor(), v.GetMinor(), v.GetPatch());
  }
  
  bool from_chars(c4::csubstr buf, Candy::Version* v)
  {
    // equivalent to sscanf(buf.str, "(%f,%f,%f)", &v->x, &v->y, &v->z)
    // --- actually snscanf(buf.str, buf.len, ...) but there's
    // no such function in the standard.
    uint32_t major, minor, patch;
    size_t ret = c4::unformat(buf, "[{},{}]", major, minor, patch);
    v->Set(major, minor, patch);
    return ret != c4::csubstr::npos;
  }
}*/

namespace Candy::Graphics
{
  ShaderLibrarySettings ShaderLibrarySettings::Default()
  {
    ShaderLibrarySettings settings{};
    settings.internalCacheDirectory = "assets/cache/shader";
    settings.internalSourceDirectory = "assets/shaders";
    settings.projectCacheDirectory = "projects/TestProject/cache/shaders";
    settings.projectSourceDirectory = "projects/TestProject/assets/shaders";
    settings.compilationSettings.optimize=true;
    settings.compilationSettings.recompileOnLoad=true;
    settings.compilationSettings.glslVersion=460;
    settings.compilationSettings.vulkanVersion=Version(1, 3);
    settings.compilationSettings.preserveBindings=false;
    
    return settings;
  }
  
  void ShaderLibrarySettings::Save(const std::filesystem::path& filepath, const ShaderLibrarySettings& settings)
  {
    c4::yml::Tree tree;
    c4::yml::NodeRef root = tree.rootref();
    root |= c4::yml::MAP;
    auto libNode = root["ShaderLibrarySettings"];
    libNode |= c4::yml::MAP;
    
    libNode["InternalCacheDirectory"] << settings.internalCacheDirectory.string();
    libNode["InternalSourceDirectory"] << settings.internalSourceDirectory.string();
    libNode["ProjectCacheDirectory"] << settings.projectCacheDirectory.string();
    libNode["ProjectSourceDirectory"] << settings.projectSourceDirectory.string();
    
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
  }
  
  
  ShaderLibrarySettings ShaderLibrarySettings::Load(const std::filesystem::path& filepath)
  {
    CANDY_CORE_INFO("DESERIALIZING PROJECT");
    ShaderLibrarySettings settings{};
    
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
    
    
    std::string internalCache, internalSource, projectCache, projectSource;
    libNode["InternalCacheDirectory"] >> internalCache;
    libNode["InternalSourceDirectory"] >> internalSource;
    libNode["ProjectCacheDirectory"] >> projectCache;
    libNode["ProjectSourceDirectory"] >> projectSource;
    
    settings.internalCacheDirectory = internalCache;
    settings.internalSourceDirectory = internalSource;
    settings.projectCacheDirectory = projectCache;
    settings.projectSourceDirectory = projectSource;
    
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