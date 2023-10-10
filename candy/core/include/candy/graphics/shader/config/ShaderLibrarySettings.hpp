#pragma once
#include "candy/utils/Version.hpp"
#include <filesystem>
namespace Candy::Graphics
{
  struct ShaderCompilationSettings
  {
    bool autoMapping=true;
    bool preserveBindings=false;
    bool suppressWarnings=false;
    bool warningsAsErrors=false;
    bool invertY=false;
    bool generateDebugInfo=true;
    bool optimize=true;
    bool recompileOnLoad=true;
    int glslVersion=460;
    Version vulkanVersion = Version(1, 3);
  };
  
  struct ShaderLibrarySettings
  {
    ShaderCompilationSettings compilationSettings;
    
    std::filesystem::path internalCacheDirectory;
    std::filesystem::path internalSourceDirectory;
    std::filesystem::path projectCacheDirectory;
    std::filesystem::path projectSourceDirectory;
    
    
    static ShaderLibrarySettings Default();
    static ShaderLibrarySettings Load(const std::filesystem::path& filepath);
    static void Save(const std::filesystem::path& filepath, const ShaderLibrarySettings& settings);
    
  };
}