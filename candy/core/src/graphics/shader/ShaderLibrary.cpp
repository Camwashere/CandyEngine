#include "candy/graphics/shader/ShaderLibrary.hpp"
#include "CandyPch.hpp"
#include <utility>
#include <filesystem>

namespace Candy::Graphics
{
    ShaderLibrary::ShaderLibrary(std::filesystem::path  cacheDir, std::filesystem::path  internalShaderDir, bool createDirectoriesIfNeeded) : cacheDirectory(std::move(cacheDir)), internalShaderDirectory(std::move(internalShaderDir))
    {
        if (createDirectoriesIfNeeded)
        {
            if (! HasCacheDirectory())
            {
                std::filesystem::create_directories(cacheDirectory);
            }
            if (! HasInternalShaderDirectory())
            {
                std::filesystem::create_directories(internalShaderDirectory);
            }
        }
        CANDY_CORE_ASSERT(std::filesystem::exists(cacheDirectory), "Cache directory does not exist!");
        CANDY_CORE_ASSERT(std::filesystem::exists(internalShaderDirectory), "Internal shader directory does not exist!");
        
    }
    
    const std::filesystem::path& ShaderLibrary::GetCacheDirectory()const{return cacheDirectory;}
    const std::filesystem::path& ShaderLibrary::GetInternalShaderDirectory()const{return internalShaderDirectory;}
    
    bool ShaderLibrary::IsValid()const
    {
        return HasCacheDirectory() && HasInternalShaderDirectory();
    }
    bool ShaderLibrary::HasCacheDirectory()const
    {
        return std::filesystem::exists(cacheDirectory);
    }
    bool ShaderLibrary::HasInternalShaderDirectory()const
    {
        return std::filesystem::exists(internalShaderDirectory);
    }
}