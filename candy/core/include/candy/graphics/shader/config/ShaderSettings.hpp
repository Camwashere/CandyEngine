#pragma once
#include <filesystem>
#include <vulkan/vulkan.h>
#include <utility>
#include <vector>
#include "candy/graphics/shader/ShaderProperty.hpp"
#include "candy/collections/GenericBuffer.hpp"
#include "candy/graphics/RenderCommand.hpp"
#include <candy/graphics/shader/config/ShaderProfile.hpp>
#include "candy/utils/Version.hpp"
namespace Candy::Graphics
{
  struct ShaderCompilationSettings
  {
    bool autoMapping=false;
    bool preserveBindings=false;
    bool suppressWarnings=false;
    bool warningsAsErrors=false;
    bool invertY=true;
    bool generateDebugInfo=true;
    bool optimize=true;
    bool recompileOnLoad=true;
    int glslVersion=460;
    Version vulkanVersion = Version(1, 3);
  };
  
  struct ShaderLibrarySettings
  {
    
    ShaderCompilationSettings compilationSettings;
  
  
  private:
    friend class ShaderLibrary;
    
  };
  struct ShaderSettings
  {
    std::filesystem::path sourceFilePath;
    ShaderProfileSettings profileSettings;
    std::vector<ShaderConfigurationSettings> configs;
    
    
    
  };
  
}