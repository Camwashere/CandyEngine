#pragma once
#include <vector>
#include <filesystem>
#include <candy/utils/Version.hpp>
#include <candy/base/Base.hpp>
#include "ShaderLibrarySettings.hpp"
#include <vulkan/vulkan.h>
namespace Candy::Graphics
{
  
  class Shader;
  
    class ShaderLibrary
    {
    
    public:
      enum DirectoryType
      {
        InternalCache = BIT(0),
        InternalSource = BIT(1),
        ProjectCache = BIT(2),
        ProjectSource = BIT(3),
        
        InternalDirs = InternalCache | InternalSource,
        ProjectDirs = ProjectCache | ProjectSource,
        CacheDirs = InternalCache | ProjectCache,
        SourceDirs = InternalSource | ProjectSource,
        AllDirs = InternalDirs | ProjectDirs,
      };
    
    public:
      /// Initialize the shader library. Must be called before any shader creation/loading
      /// @param internalCacheDirectory The directory where the compiled shaders used internally by CandyEngine will be stored
      /// @param internalShaderDirectory The directory where the source shaders used internally by CandyEngine will be stored
      /// @param projectCacheDirectory The directory where the compiled shaders used by the project will be stored
      /// @param projectSourceDirectory The directory where the source shaders used by the project will be stored
      /// @param createDirectoriesIfNeeded If true, the directories will be created if they don't exist
      /// @return True if the initialization was successful, false otherwise
      static bool Init(const ShaderLibrarySettings& settings, bool createDirectoriesIfNeeded=false);
      
      static void AddShader(const SharedPtr<Shader>& shader);
      static void Reload();
      
      static std::vector<VkDescriptorSetLayout> BakeDescriptorSetLayouts(uint8_t renderPassIndex);
      
      /// Compiled cached shaders used internally by CandyEngine
      static const std::filesystem::path& GetInternalCacheDirectory();
      /// Source shaders used internally by CandyEngine
      static const std::filesystem::path& GetInternalSourceDirectory();
      
      /// Compiled cached shaders used by the project
      static const std::filesystem::path& GetProjectCacheDirectory();
      
      /// Source shaders used by the project
      static const std::filesystem::path& GetProjectSourceDirectory();
      
      static const ShaderCompilationSettings& GetCompilationSettings();
      
      static bool IsInitialized();
      
      static std::string DirectoryTypeToString(DirectoryType type);
    
        
    private:
      friend class ShaderLayout;
    };
}