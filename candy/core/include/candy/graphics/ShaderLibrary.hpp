#pragma once
#include <filesystem>


namespace Candy::Graphics
{
    class ShaderLibrary
    {
    private:
        std::filesystem::path cacheDirectory;
        std::filesystem::path internalShaderDirectory;
        
    public:
        ShaderLibrary(std::filesystem::path  cacheDirectory, std::filesystem::path  internalShaderDirectory, bool createDirectoriesIfNeeded=false);
        
    public:
        [[nodiscard]] const std::filesystem::path& GetCacheDirectory()const;
        [[nodiscard]] const std::filesystem::path& GetInternalShaderDirectory()const;
        
        [[nodiscard]] bool IsValid()const;
        [[nodiscard]] bool HasCacheDirectory()const;
        [[nodiscard]] bool HasInternalShaderDirectory()const;
    };
}