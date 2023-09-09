#pragma once
#include <vector>
#include <filesystem>
#include "Shader.hpp"

namespace Candy::Graphics
{
    class ShaderLibrary
    {
    private:
        std::filesystem::path cacheDirectory;
        std::filesystem::path internalShaderDirectory;
        std::vector<SharedPtr<Shader>> shaders;
        std::vector<ShaderSet> shaderSets;
        
    private:
      std::vector<VkDescriptorSetLayout> BakeDescriptorSetLayouts(uint8_t renderPassIndex);
        
    public:
      ShaderLibrary();
        ShaderLibrary(std::filesystem::path  cacheDirectory, std::filesystem::path  internalShaderDirectory, bool createDirectoriesIfNeeded=false);
        
        static ShaderLibrary instance;
        
    public:
      void AddShader(const SharedPtr<Shader>& shader);
      void Reload();
      
        [[nodiscard]] const std::filesystem::path& GetCacheDirectory()const;
        [[nodiscard]] const std::filesystem::path& GetInternalShaderDirectory()const;
        
        [[nodiscard]] bool IsValid()const;
        [[nodiscard]] bool HasCacheDirectory()const;
        [[nodiscard]] bool HasInternalShaderDirectory()const;
        
    private:
      friend class ShaderLayout;
    };
}