#include <candy/graphics/shader/processing/ShaderPostProcessor.hpp>
#include "candy/graphics/Vulkan.hpp"
#include "candy/utils/FileUtils.hpp"
#include "shaderc/libshaderc/include/shaderc/shaderc.hpp"

#include "SPIRV-Cross/spirv_cross.hpp"
#include "SPIRV-Cross/spirv_glsl.hpp"
#include <candy/graphics/shader/ShaderLibrary.hpp>
namespace Candy::Graphics
{
  static std::filesystem::path GetCacheDirectory()
  {
    return "assets/cache/shader";
  }
  static shaderc_shader_kind StageToShaderC(ShaderData::Stage stage)
  {
    CANDY_PROFILE_FUNCTION();
    switch (stage)
    {
      
      case ShaderData::Stage::Vertex:   return shaderc_glsl_vertex_shader;
      case ShaderData::Stage::Fragment: return shaderc_glsl_fragment_shader;
      case ShaderData::Stage::Compute: return shaderc_glsl_compute_shader;
      case ShaderData::Stage::Geometry: return shaderc_glsl_geometry_shader;
      case ShaderData::Stage::TessellationControl: return shaderc_glsl_tess_control_shader;
      case ShaderData::Stage::TessellationEvaluation: return shaderc_glsl_tess_evaluation_shader;
      default:
      CANDY_CORE_ASSERT(false, "Unknown shader stage!");
        return (shaderc_shader_kind)0;
    }
  }
  
  /*ShaderPostProcessor::ShaderPostProcessor(const ShaderSettings& settings) //: shaderLayout(settings)
  {
  
  }*/
  void ShaderPostProcessor::BuildLayout(ShaderLayout& layout)
  {
    auto& shaderData = spirvBinaries;
    for (auto&& [stage, data] : shaderData)
    {
      Reflect(layout, stage, data);
    }
  }
  ShaderPostProcessor::ShaderPostProcessor(const ShaderCompilationSettings& settings, const std::unordered_map<ShaderData::Stage, std::string>& sources, const std::filesystem::path& filepath)
  {
    CANDY_PROFILE_FUNCTION();
    shaderc::Compiler compiler;
    shaderc::CompileOptions options;
    
    
    options.SetOptimizationLevel(settings.optimize? shaderc_optimization_level_performance : shaderc_optimization_level_zero);
    if (settings.generateDebugInfo)
    {
      options.SetGenerateDebugInfo();
    }
    options.SetPreserveBindings(settings.preserveBindings);
    
    //options.SetForcedVersionProfile(settings.glslVersion, shaderc_profile_core);
    
    options.SetTargetSpirv(shaderc_spirv_version_1_3);
    if (settings.vulkanVersion.GetMajor() == 1)
    {
      switch(settings.vulkanVersion.GetMinor())
      {
        case 0:
          options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_0);
          break;
        case 1:
          options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_1);
          break;
        case 2:
          options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_2);
          break;
        case 3:
          options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_3);
          break;
        default:
          CANDY_CORE_WARN("Invalid vulkan version in shader compilation settings ({}). Defaulting to 1.0", settings.vulkanVersion);
          options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_0);
          break;
      }
    }
    else
    {
      CANDY_CORE_WARN("Invalid vulkan version in shader compilation settings ({}). Defaulting to 1.0", settings.vulkanVersion);
      options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_0);
    }
    
    
    options.SetAutoBindUniforms(settings.autoMapping);
    options.SetAutoMapLocations(settings.autoMapping);
    options.SetInvertY(settings.invertY);
    //CANDY_CORE_ASSERT(settings.invertY == true, "Settings invert y is still false");
    if (settings.suppressWarnings)
    {
      options.SetSuppressWarnings();
    }
    if (settings.warningsAsErrors)
    {
      options.SetWarningsAsErrors();
    }
    
    
    std::filesystem::path cacheDirectory = GetCacheDirectory();
    
    auto& shaderData = spirvBinaries;
    shaderData.clear();
    
    for (auto&& [stage, source] : sources)
    {
      std::filesystem::path shaderFilePath = filepath;
      std::filesystem::path cachedPath = cacheDirectory / (shaderFilePath.filename().string() + ShaderData::StageToCachedFileExtension(stage));
      
      std::ifstream in(cachedPath, std::ios::in | std::ios::binary);
      if (in.is_open() && !settings.recompileOnLoad)
      {
        //CANDY_CORE_INFO("ALREADY HAS SHADER CACHED");
        
        in.seekg(0, std::ios::end);
        auto size = in.tellg();
        in.seekg(0, std::ios::beg);
        
        auto& data = shaderData[stage];
        data.resize(size / sizeof(uint32_t));
        in.read((char*)data.data(), size);
      }
      else
      {
        CANDY_CORE_INFO("NO SHADER CACHED, COMPILING BINARIES");
        
        /*shaderc::PreprocessedSourceCompilationResult preResult = compiler.PreprocessGlsl(source, StageToShaderC(stage), filepath.string().c_str(), options);
        CANDY_CORE_ASSERT_MSG(preResult.GetCompilationStatus() == shaderc_compilation_status_success, "Preprocess failed for file: {0}, with error message: {1}", filepath.string(), preResult.GetErrorMessage());
        std::string prePassedSource(preResult.begin());*/
        shaderc::SpvCompilationResult result = compiler.CompileGlslToSpv(source, StageToShaderC(stage), filepath.string().c_str(), options);
        CANDY_CORE_ASSERT_MSG(result.GetCompilationStatus() == shaderc_compilation_status_success, "Compilation failed for file: {0}, with error message: {1}", filepath.string(), result.GetErrorMessage());
        
        
        shaderData[stage] = std::vector<uint32_t>(result.cbegin(), result.cend());
        
        std::ofstream out(cachedPath, std::ios::out | std::ios::binary);
        if (out.is_open())
        {
          auto& data = shaderData[stage];
          out.write((char*)data.data(), data.size() * sizeof(uint32_t));
          out.flush();
          out.close();
        }
      }
    }
    
    
    
    
  }
  
  
  void ShaderPostProcessor::Reflect(ShaderLayout& shaderLayout, ShaderData::Stage stage, std::vector<uint32_t> spirvBinary)
  {
    CANDY_PROFILE_FUNCTION();
    spirv_cross::CompilerGLSL compiler(std::move(spirvBinary));
    //spirv_cross::CompilerGLSL::Options options = compiler.get_common_options();
    //std::string decompiledGLSL = compiler.compile();
    //CANDY_CORE_INFO("Decompiled GLSL: \n\n\n{0}\n\n\n", decompiledGLSL);
    auto resources = compiler.get_shader_resources();
    auto specConstants = compiler.get_specialization_constants();
    
    if (!specConstants.empty())
    {
      CANDY_CORE_INFO("Has spec constants");
      ReflectSpecializationConstants(shaderLayout, compiler, stage, specConstants);
    }
    
    
    ReflectStageInputs(shaderLayout, compiler, stage, resources.stage_inputs);
    ReflectStageStorageBuffers(shaderLayout, compiler, stage, resources.storage_buffers);
    ReflectStageUniformBuffers(shaderLayout, compiler, stage, resources.uniform_buffers);
    ReflectStageSampledImages(shaderLayout, compiler, stage, resources.sampled_images);
    ReflectStagePushConstants(shaderLayout, compiler, stage);
    //spirv_cross::SmallVector<spirv_cross::Asset> stageInputs;
  }
  void ShaderPostProcessor::ReflectSpecializationConstants(ShaderLayout& shaderLayout, const spirv_cross::CompilerGLSL& compiler, ShaderData::Stage stage, const spirv_cross::SmallVector<spirv_cross::SpecializationConstant, 8>& specConstants)
  {
    CANDY_PROFILE_FUNCTION();
    for (const auto& specConst : specConstants)
    {
      
      uint32_t constID = specConst.constant_id;
      std::string name = compiler.get_name(specConst.id);
      spirv_cross::SPIRConstant c = compiler.get_constant(specConst.id);
      
      
      ShaderData::Type type = ShaderData::SpirvToType(compiler.get_type(c.constant_type));
      ShaderSpecializationConstant v{};
      v.id = specConst.constant_id;
      v.name = name;
      v.type = type;
      v.stage = stage;
      shaderLayout.AddSpecConstant(v);
      
      CANDY_CORE_INFO("ID: {0}, Constant ID: {1}, Name: {2}, Type: {3}", v.id, specConst.constant_id, name, ShaderData::TypeToString(v.type));
      /*uint32_t specID = compiler.get_decoration(specConst.id, spv::DecorationSpecId);
      ShaderData::Type specType = ShaderData::SpirvToType(compiler.get_type(specConst.constant_id));
      std::string name = compiler.get_name(specConst.id);
      CANDY_CORE_INFO("Specialization constant: {0} with ID: {1} and type: {2}", name, specID, ShaderData::TypeToString(specType));*/
    }
  }
  void ShaderPostProcessor::ReflectStageInputs(ShaderLayout& shaderLayout, const spirv_cross::CompilerGLSL& compiler, ShaderData::Stage stage, const spirv_cross::SmallVector<spirv_cross::Resource>& stageInputs)
  {
    CANDY_PROFILE_FUNCTION();
    if (stage != ShaderData::Stage::Vertex)
      return;
    for (auto& resource : stageInputs)
    {
      uint32_t location = compiler.get_decoration(resource.id, spv::DecorationLocation);
      ShaderData::Type shaderType = ShaderData::SpirvToType(compiler.get_type(resource.type_id));
      shaderLayout.AddVertexInput(compiler.get_name(resource.id), shaderType, location);
    }
  }
  
  
  void ShaderPostProcessor::ReflectStageStorageBuffers(ShaderLayout& shaderLayout, const spirv_cross::CompilerGLSL& compiler, ShaderData::Stage stage, const spirv_cross::SmallVector<spirv_cross::Resource>& stageStorageBuffers)
  {
    CANDY_PROFILE_FUNCTION();
    for (auto& resource : stageStorageBuffers)
    {

      ShaderBlock block;

      block.stage = stage;
      block.binding = compiler.get_decoration(resource.id, spv::DecorationBinding);
      block.set = compiler.get_decoration(resource.id, spv::DecorationDescriptorSet);

      block.name = compiler.get_name(resource.id);

      auto members = compiler.get_type(resource.base_type_id).member_types;
      if (!members.empty())
      {
        for (auto& member : members)
        {
          ShaderData::Type shaderType = ShaderData::SpirvToType(compiler.get_type(member));
        }
      }
      shaderLayout.AddBlock(block);

    }
  }
  void ShaderPostProcessor::ReflectStageUniformBuffers(ShaderLayout& shaderLayout, const spirv_cross::CompilerGLSL& compiler, ShaderData::Stage stage, const spirv_cross::SmallVector<spirv_cross::Resource>& stageUniformBuffers)
  {
    CANDY_PROFILE_FUNCTION();
    for (auto& resource : stageUniformBuffers)
    {
      ShaderBlock block{};

      block.name = compiler.get_name(resource.id);

      block.stage = stage;
      block.binding = compiler.get_decoration(resource.id, spv::DecorationBinding);
      block.set = compiler.get_decoration(resource.id, spv::DecorationDescriptorSet);
      

      auto members = compiler.get_type(resource.base_type_id).member_types;
      size_t memberSize = members.size();
      for (int i=0; i<memberSize; i++)
      {
        ShaderProperty prop;
        prop.name = compiler.get_member_name(resource.base_type_id, i);

        prop.type = ShaderData::SpirvToType(compiler.get_type(members[i]));
        block.AddProperty(prop);
      }
      shaderLayout.AddBlock(block);
    }
  }
  void ShaderPostProcessor::ReflectStageSampledImages(ShaderLayout& shaderLayout, const spirv_cross::CompilerGLSL& compiler, ShaderData::Stage stage, const spirv_cross::SmallVector<spirv_cross::Resource>& stageSampledImages)
  {
    CANDY_PROFILE_FUNCTION();
    for (auto& resource : stageSampledImages)
    {
      ShaderTexture texture{};
      texture.name = compiler.get_name(resource.id);
      texture.stage = stage;
      texture.type = ShaderData::SpirvToType(compiler.get_type(resource.type_id));
      if (texture.type == ShaderData::Type::Sampler2DArray)
      {
        
        texture.arraySize = compiler.get_type(resource.type_id).array[0];
        CANDY_CORE_INFO("Sampler2DArray with size: {}", texture.arraySize);
      }
      else
      {
        texture.arraySize=1;
      }
      texture.binding = compiler.get_decoration(resource.id, spv::DecorationBinding);
      texture.set = compiler.get_decoration(resource.id, spv::DecorationDescriptorSet);
      shaderLayout.AddTexture(texture);
    }
  }
  void ShaderPostProcessor::ReflectStagePushConstants(ShaderLayout& shaderLayout, const spirv_cross::CompilerGLSL& compiler, ShaderData::Stage stage)
  {
    CANDY_PROFILE_FUNCTION();
    ShaderPushBlock block;
    //block.stage = stage;
    
    VkPushConstantRange pushRange{};
    pushRange.stageFlags = ShaderData::StageToVulkan(stage);
    pushRange.offset = 0;
    const auto& pushBuffers = compiler.get_shader_resources().push_constant_buffers;
    if (pushBuffers.empty())
    {
      return;
    }
    spirv_cross::Resource pushResource = pushBuffers.front();
    uint32_t id = pushResource.id;
    
    uint32_t base_type_id = pushResource.base_type_id;
    
    uint32_t pcrSize=0;
    std::vector<spirv_cross::BufferRange> ranges = (std::vector<spirv_cross::BufferRange>)compiler.get_active_buffer_ranges(id);
    if (ranges.empty())
    {
      return;
    }
    block.name = compiler.get_name(pushResource.id);
    
    auto pushMembers = compiler.get_type(base_type_id).member_types;
    for (auto& range : ranges)
    {
      ShaderPushProperty prop;
      prop.name = compiler.get_member_name(base_type_id, range.index);

      prop.offset = range.offset;
      prop.size = range.range;
      prop.type = ShaderData::SpirvToType(compiler.get_type(pushMembers[range.index]));
      

      block.AddPushProperty(prop);

      pcrSize += range.range;
    }
    block.size = pcrSize;
    
    if (block.size > 0)
    {
      shaderLayout.AddPushBlock(block);
    }
  
  }
  
  /*ShaderLayout& ShaderPostProcessor::GetLayout()
  {
    return shaderLayout;
  }*/

}