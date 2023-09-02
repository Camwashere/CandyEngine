#pragma once
#include "CandyPch.hpp"
#include "candy/graphics/Color.hpp"
#include "../ShaderData.hpp"
#include "vulkan/vulkan.h"
#include <filesystem>
#include "../../vulkan/descriptor/DescriptorBuilder.hpp"
#include "../ShaderLayout.hpp"
#include "../../vulkan/descriptor/DescriptorSetLayout.hpp"
#include "../ShaderSettings.hpp"

namespace spirv_cross
{
  
  class Compiler;
  class CompilerGLSL;
  class Resource;
  template<typename T>
  class VectorView;
  template<typename T, size_t N>
  class SmallVector;
 
}
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
    ShaderLayout shaderLayout;
    
    
  private:
    void CompileOrGetBinaries(const std::unordered_map<ShaderData::Stage, std::string>& sources, const std::filesystem::path& filepath);
    void Reflect(ShaderData::Stage stage, std::vector<uint32_t> spirvBinary);
    void ReflectStageInputs(const spirv_cross::CompilerGLSL& compiler, ShaderData::Stage stage, const spirv_cross::SmallVector<spirv_cross::Resource, 8>& stageInputs);
    void ReflectStageStorageBuffers(const spirv_cross::CompilerGLSL& compiler, ShaderData::Stage stage, const spirv_cross::SmallVector<spirv_cross::Resource, 8>& stageStorageBuffers);
    void ReflectStageUniformBuffers(const spirv_cross::CompilerGLSL& compiler, ShaderData::Stage stage, const spirv_cross::SmallVector<spirv_cross::Resource, 8>& stageUniformBuffers);
    void ReflectStageSampledImages(const spirv_cross::CompilerGLSL& compiler, ShaderData::Stage stage, const spirv_cross::SmallVector<spirv_cross::Resource, 8>& stageSampledImages);
    void ReflectStagePushConstants(const spirv_cross::CompilerGLSL& compiler, ShaderData::Stage stage);
    
    
    
  public:
    explicit ShaderPostProcessor(const ShaderSettings& settings);
    
  public:
    ShaderLayout& GetLayout();
    
  private:
    friend class Shader;
    
  
  };
}