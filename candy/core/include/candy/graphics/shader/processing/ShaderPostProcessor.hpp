#pragma once
#include "CandyPch.hpp"
#include "candy/graphics/Color.hpp"
#include "../ShaderData.hpp"
#include "vulkan/vulkan.h"
#include <filesystem>
namespace Candy::Graphics
{
  class ShaderPostProcessor
  {
  private:
    std::unordered_map<ShaderData::Stage, std::vector<uint32_t>> spirvBinaries{};
    bool autoMapping=true;
    bool generateDebugInfo=true;
    bool optimize=true;
    bool recompileOnLoad=true;
    VkDescriptorSetLayout descriptorSetLayout=VK_NULL_HANDLE;
    std::vector<VkPushConstantRange> pushConstantRanges;
  private:
    void CompileOrGetBinaries(const std::unordered_map<ShaderData::Stage, std::string>& sources, const std::filesystem::path& filepath);
    void Reflect(ShaderData::Stage stage, std::vector<uint32_t> spirvBinary, std::vector<VkDescriptorSetLayoutBinding>& layoutBindings);
    
  public:
    ShaderPostProcessor()=default;
    
  private:
    friend class Shader;
    
  
  };
}