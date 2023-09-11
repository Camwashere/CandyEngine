#include <candy/graphics/shader/processing/ShaderPostProcessor.hpp>
#include "candy/graphics/Vulkan.hpp"
#include "candy/utils/FileUtils.hpp"
#include "shaderc/libshaderc/include/shaderc/shaderc.hpp"

#include "SPIRV-Cross/spirv_cross.hpp"
#include "SPIRV-Cross/spirv_glsl.hpp"
namespace Candy::Graphics
{
  static std::filesystem::path GetCacheDirectory()
  {
    return "assets/cache/shader";
  }
  static shaderc_shader_kind StageToShaderC(ShaderData::Stage stage)
  {
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
  
  ShaderPostProcessor::ShaderPostProcessor(const ShaderSettings& settings) : shaderLayout(settings)
  {
  
  }
  void ShaderPostProcessor::CompileOrGetBinaries(const std::unordered_map<ShaderData::Stage, std::string>& sources, const std::filesystem::path& filepath)
  {
    shaderc::Compiler compiler;
    shaderc::CompileOptions options;
    spirv_cross::SmallVector<float> t;
    options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_2);
    if (generateDebugInfo)
    {
      options.SetGenerateDebugInfo();
    }
    options.SetAutoBindUniforms(autoMapping);
    options.SetAutoMapLocations(autoMapping);
    options.SetAutoSampledTextures(autoMapping);
    
    
    
    if (optimize)
      options.SetOptimizationLevel(shaderc_optimization_level_performance);
    
    
    
    
    std::filesystem::path cacheDirectory = GetCacheDirectory();
    
    auto& shaderData = spirvBinaries;
    shaderData.clear();
    
    for (auto&& [stage, source] : sources)
    {
      std::filesystem::path shaderFilePath = filepath;
      std::filesystem::path cachedPath = cacheDirectory / (shaderFilePath.filename().string() + ShaderData::StageToCachedFileExtension(stage));
      
      std::ifstream in(cachedPath, std::ios::in | std::ios::binary);
      if (in.is_open() && !recompileOnLoad)
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
        //CANDY_CORE_INFO("NO SHADER CACHED, COMPILING BINARIES");
        
        shaderc::SpvCompilationResult mod = compiler.CompileGlslToSpv(source, StageToShaderC(stage), filepath.string().c_str(), options);
        if (mod.GetCompilationStatus() != shaderc_compilation_status_success)
        {
          CANDY_CORE_ERROR(mod.GetErrorMessage());
          CANDY_CORE_ASSERT(false);
        }
        
        shaderData[stage] = std::vector<uint32_t>(mod.cbegin(), mod.cend());
        
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
    
    for (auto&& [stage, data] : shaderData)
    {
      Reflect(stage, data);
    }
    
  }
  
  
  void ShaderPostProcessor::Reflect(ShaderData::Stage stage, std::vector<uint32_t> spirvBinary)
  {
    spirv_cross::CompilerGLSL compiler(std::move(spirvBinary));
    
    auto resources = compiler.get_shader_resources();
    auto specConstants = compiler.get_specialization_constants();
    
    if (!specConstants.empty())
    {
      CANDY_CORE_INFO("Has spec constants");
      ReflectSpecializationConstants(compiler, stage, specConstants);
    }
    
    
    ReflectStageInputs(compiler, stage, resources.stage_inputs);
    ReflectStageStorageBuffers(compiler, stage, resources.storage_buffers);
    ReflectStageUniformBuffers(compiler, stage, resources.uniform_buffers);
    ReflectStageSampledImages(compiler, stage, resources.sampled_images);
    ReflectStagePushConstants(compiler, stage);
    spirv_cross::SmallVector<spirv_cross::Resource> stageInputs;
  }
  void ShaderPostProcessor::ReflectSpecializationConstants(const spirv_cross::CompilerGLSL& compiler, ShaderData::Stage stage, const spirv_cross::SmallVector<spirv_cross::SpecializationConstant, 8>& specConstants)
  {
    for (const auto& specConst : specConstants)
    {
      
      uint32_t constID = specConst.constant_id;
      std::string name = compiler.get_name(specConst.id);
      spirv_cross::SPIRConstant c = compiler.get_constant(specConst.id);
      
      
      ShaderData::Type type = ShaderData::SpirvToType(compiler.get_type(c.constant_type));
      ShaderSpecializationConstant v{};
      v.id = constID;
      v.name = name;
      v.type = type;
      v.stage = stage;
      shaderLayout.AddSpecConstant(v);
      
      CANDY_CORE_INFO("ID: {0}, Constant ID: {1}, Name: {2}, Type: {3}", specConst.id, specConst.constant_id, name, ShaderData::TypeToString(v.type));
      /*uint32_t specID = compiler.get_decoration(specConst.id, spv::DecorationSpecId);
      ShaderData::Type specType = ShaderData::SpirvToType(compiler.get_type(specConst.constant_id));
      std::string name = compiler.get_name(specConst.id);
      CANDY_CORE_INFO("Specialization constant: {0} with ID: {1} and type: {2}", name, specID, ShaderData::TypeToString(specType));*/
    }
  }
  void ShaderPostProcessor::ReflectStageInputs(const spirv_cross::CompilerGLSL& compiler, ShaderData::Stage stage, const spirv_cross::SmallVector<spirv_cross::Resource>& stageInputs)
  {
    if (stage != ShaderData::Stage::Vertex)
      return;
    for (auto& resource : stageInputs)
    {
      uint32_t location = compiler.get_decoration(resource.id, spv::DecorationLocation);
      ShaderData::Type shaderType = ShaderData::SpirvToType(compiler.get_type(resource.type_id));
      shaderLayout.AddVertexInput(compiler.get_name(resource.id), shaderType, location);
    }
  }
  
  
  void ShaderPostProcessor::ReflectStageStorageBuffers(const spirv_cross::CompilerGLSL& compiler, ShaderData::Stage stage, const spirv_cross::SmallVector<spirv_cross::Resource>& stageStorageBuffers)
  {
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
  void ShaderPostProcessor::ReflectStageUniformBuffers(const spirv_cross::CompilerGLSL& compiler, ShaderData::Stage stage, const spirv_cross::SmallVector<spirv_cross::Resource>& stageUniformBuffers)
  {
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
  void ShaderPostProcessor::ReflectStageSampledImages(const spirv_cross::CompilerGLSL& compiler, ShaderData::Stage stage, const spirv_cross::SmallVector<spirv_cross::Resource>& stageSampledImages)
  {
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
  void ShaderPostProcessor::ReflectStagePushConstants(const spirv_cross::CompilerGLSL& compiler, ShaderData::Stage stage)
  {
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
  
  ShaderLayout& ShaderPostProcessor::GetLayout()
  {
    return shaderLayout;
  }

}