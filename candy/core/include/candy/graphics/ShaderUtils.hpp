#pragma once
#include <string>
#include <unordered_map>
#include <filesystem>
#include <vector>
#include <vulkan/vulkan.h>
namespace Candy::Graphics
{
    enum ShaderStage
    {
        NONE = 0,
        VERTEX = 1,
        FRAGMENT = 2,
        COMPUTE = 3,
        GEOMETRY = 4,
        TESSELATION_CONTROL=5,
        TESSELATION_EVALUATION=6,
    };
    class ShaderUtils
    {
    public:
        static ShaderStage ShaderStageFromString(const std::string& type);
        static const char* ShaderStageCachedVulkanFileExtension(ShaderStage stage);
        static const char* ShaderStageToString(ShaderStage stage);
        static std::vector<char> ReadSpvFileBinary(const std::string& filename);
        static VkShaderStageFlagBits ShaderStageToVulkan(ShaderStage stage);
        static std::string ReadFile(const std::filesystem::path& path);
        static std::unordered_map<ShaderStage, std::string> PreProcess(const std::string& source);
        static std::string ExtractNameFromFilePath(const std::filesystem::path& path);
        static bool HasBinaries(const std::unordered_map<ShaderStage, std::string> &sources, const std::filesystem::path& cacheDirectory, const std::filesystem::path& shaderFilePath);
        static void CompileOrGetBinaries(std::unordered_map<ShaderStage, std::vector<uint32_t>>& binaries, const std::unordered_map<ShaderStage, std::string> &sources, const std::filesystem::path& filepath, const std::filesystem::path& cacheDirectory);
        static void GetBinaries(std::unordered_map<ShaderStage, std::vector<uint32_t>>& binaries, const std::unordered_map<ShaderStage, std::string> &sources, const std::filesystem::path& filepath, const std::filesystem::path& cacheDirectory);
        static void Reflect(ShaderStage stage, const std::vector<uint32_t>& shaderData, const std::filesystem::path& filepath);
    };
}