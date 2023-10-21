#pragma once
#include <vector>
#include <filesystem>
#include <candy/utils/Version.hpp>
#include <candy/base/Base.hpp>
#include <vulkan/vulkan.h>

namespace Candy::Graphics
{
  
  class Shader;
  
  struct ShaderLibrarySettings;
  struct ShaderCompilationSettings;
  
    class ShaderLibrary
    {
    
    private:
      static bool LoadLibrarySettings(ShaderLibrarySettings& shaderLibSettings, const std::filesystem::path& filepath);
    
    public:
      /// Initialize the shader library. Must be called before any shader creation/loading
      /// @param internalCacheDirectory The directory where the compiled shaders used internally by CandyEngine will be stored
      /// @param internalShaderDirectory The directory where the source shaders used internally by CandyEngine will be stored
      /// @param projectCacheDirectory The directory where the compiled shaders used by the project will be stored
      /// @param projectSourceDirectory The directory where the source shaders used by the project will be stored
      /// @param createDirectoriesIfNeeded If true, the directories will be created if they don't exist
      /// @return True if the initialization was successful, false otherwise
      static bool Init();
      
      static void AddShader(const SharedPtr<Shader>& shader);
      static void Reload();
      static void Bake();
      
      static std::vector<VkDescriptorSetLayout> BakeDescriptorSetLayouts(uint8_t renderPassIndex);
      
      /// Compiled cached shaders used internally by CandyEngine
      static const std::filesystem::path& GetInternalCacheDirectory();
      /// Source shaders used internally by CandyEngine
      static const std::filesystem::path& GetInternalSourceDirectory();
      
      const std::filesystem::path& GetInternalProfileDirectory();
      
      static const ShaderCompilationSettings& GetCompilationSettings();
      
      static bool IsInitialized();
      
    
        
    private:
      friend class ShaderLayout;
    };
}