#pragma once
#include "CandyPch.hpp"
#include "candy/graphics/Color.hpp"
#include "../ShaderData.hpp"
#include "vulkan/vulkan.h"
#include <filesystem>
#include "../../vulkan/descriptor/DescriptorBuilder.hpp"
#include "../ShaderLayout.hpp"
#include "../../vulkan/descriptor/DescriptorSetLayout.hpp"
#include "candy/graphics/shader/config/ShaderSettings.hpp"

namespace spirv_cross
{
  
  class Compiler;
  class CompilerGLSL;
  class Resource;
  template<typename T>
  class VectorView;
  template<typename T, size_t N>
  class SmallVector;
  
  struct SpecializationConstant;
 
}
namespace shaderc
{
  class Compiler;
}
namespace Candy::Graphics
{
  struct ShaderCompilationSettings;
  class ShaderPostProcessor
  {
  private:
    std::unordered_map<ShaderData::Stage, std::vector<uint32_t>> spirvBinaries{};
    //ShaderLayout shaderLayout;
    
    
  private:
    
    void Reflect(ShaderLayout& shaderLayout, ShaderData::Stage stage, std::vector<uint32_t> spirvBinary);
    void ReflectSpecializationConstants(ShaderLayout& shaderLayout, const spirv_cross::CompilerGLSL& compiler, ShaderData::Stage stage, const spirv_cross::SmallVector<spirv_cross::SpecializationConstant, 8>& stageSpecializationConstants);
    void ReflectStageInputs(ShaderLayout& shaderLayout, const spirv_cross::CompilerGLSL& compiler, ShaderData::Stage stage, const spirv_cross::SmallVector<spirv_cross::Resource, 8>& stageInputs);
    void ReflectStageStorageBuffers(ShaderLayout& shaderLayout, const spirv_cross::CompilerGLSL& compiler, ShaderData::Stage stage, const spirv_cross::SmallVector<spirv_cross::Resource, 8>& stageStorageBuffers);
    void ReflectStageUniformBuffers(ShaderLayout& shaderLayout, const spirv_cross::CompilerGLSL& compiler, ShaderData::Stage stage, const spirv_cross::SmallVector<spirv_cross::Resource, 8>& stageUniformBuffers);
    void ReflectStageSampledImages(ShaderLayout& shaderLayout, const spirv_cross::CompilerGLSL& compiler, ShaderData::Stage stage, const spirv_cross::SmallVector<spirv_cross::Resource, 8>& stageSampledImages);
    void ReflectStagePushConstants(ShaderLayout& shaderLayout, const spirv_cross::CompilerGLSL& compiler, ShaderData::Stage stage);
    
    
    
  public:
    ShaderPostProcessor(const ShaderCompilationSettings& compilationSettings, const std::unordered_map<ShaderData::Stage, std::string>& sources, const std::filesystem::path& filepath);
    void BuildLayout(ShaderLayout& layout);
    //static std::unordered_map<ShaderData::Stage, std::vector<uint32_t>> CompileOrGetBinaries(const ShaderCompilationSettings& compilationSettings, const std::unordered_map<ShaderData::Stage, std::string>& sources, const std::filesystem::path& filepath);
    //void CompileOrGetBinaries(const ShaderCompilationSettings& compilationSettings, const std::unordered_map<ShaderData::Stage, std::string>& sources, const std::filesystem::path& filepath);
    //explicit ShaderPostProcessor(const ShaderSettings& settings);
    
    
  public:
    //ShaderLayout& GetLayout();
    
  private:
    friend class Shader;
    
  
  };
}