#include <candy/graphics/shader/processing/ShaderPostProcessor.hpp>
#include "candy/graphics/Vulkan.hpp"
#include "candy/utils/FileUtils.hpp"
#include "shaderc/libshaderc/include/shaderc/shaderc.hpp"
#include "SPIRV-Cross/spirv_glsl.hpp"
namespace Candy::Graphics
{
  static std::filesystem::path GetCacheDirectory()
  {
    return "assets/cache/shader";
    //CANDY_CORE_ASSERT(shaderLibrary->IsValid(), "Shader library is not valid!");
    //return shaderLibrary->GetCacheDirectory();
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
  
  
  void ShaderPostProcessor::CompileOrGetBinaries(const std::unordered_map<ShaderData::Stage, std::string>& sources, const std::filesystem::path& filepath)
  {
    shaderc::Compiler compiler;
    shaderc::CompileOptions options;
    options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_3);
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
        CANDY_CORE_INFO("ALREADY HAS SHADER CACHED");
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
    
    std::vector<VkDescriptorSetLayoutBinding> layoutBindings{};
    //descriptorBuilder = DescriptorBuilder::Begin();
    
    for (auto&& [stage, data] : shaderData)
    {
      Reflect(stage, data);
    }
    
    //descriptorLayout.Build();
    shaderLayout.CalculateOffsetsAndStride();
    shaderLayout.CalculateProperties();
    
    /*VkDescriptorSetLayoutCreateInfo layoutInfo{};
    layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    layoutInfo.bindingCount = layoutBindings.size();
    layoutInfo.pBindings = layoutBindings.data();
    
    CANDY_CORE_ASSERT(vkCreateDescriptorSetLayout(Vulkan::LogicalDevice(), &layoutInfo, nullptr, &descriptorSetLayout) == VK_SUCCESS, "Failed to create descriptor set layout!");*/
  
  }
  
  
  void ShaderPostProcessor::Reflect(ShaderData::Stage stage, std::vector<uint32_t> spirvBinary)
  {
    spirv_cross::CompilerGLSL compiler(std::move(spirvBinary));
    auto resources = compiler.get_shader_resources();
    
    for (auto& resource : resources.stage_inputs)
    {
      uint32_t location = compiler.get_decoration(resource.id, spv::DecorationLocation);
      uint32_t binding = compiler.get_decoration(resource.id, spv::DecorationBinding);
      uint32_t offset = compiler.get_decoration(resource.id, spv::DecorationOffset);
      uint32_t stride = compiler.get_decoration(resource.id, spv::DecorationXfbStride);
      uint32_t set = compiler.get_decoration(resource.id, spv::DecorationDescriptorSet);
      
      ShaderData::Type shaderType = ShaderData::SpirvToType(compiler.get_type(resource.type_id));
      shaderLayout.AddInputLayoutProperty(compiler.get_name(resource.id), stage, shaderType, binding, set, offset, stride, location);
    }
    for (auto& resource : resources.stage_outputs)
    {
      uint32_t location = compiler.get_decoration(resource.id, spv::DecorationLocation);
      uint32_t binding = compiler.get_decoration(resource.id, spv::DecorationBinding);
      uint32_t offset = compiler.get_decoration(resource.id, spv::DecorationOffset);
      uint32_t stride = compiler.get_decoration(resource.id, spv::DecorationXfbStride);
      uint32_t set = compiler.get_decoration(resource.id, spv::DecorationDescriptorSet);
      
      ShaderData::Type shaderType = ShaderData::SpirvToType(compiler.get_type(resource.type_id));
      shaderLayout.AddOutputLayoutProperty(compiler.get_name(resource.id), stage, shaderType, binding, set, offset, stride, location);
    }
    
    for (auto& resource : resources.uniform_buffers)
    {
      //CANDY_CORE_INFO("UNIFORM NAME: {}", resource.name);
      //CANDY_CORE_INFO("UNIFORM SIZE: {}", compiler.get_declared_struct_size(compiler.get_type(resource.base_type_id)));
      ShaderUniformBlockProperty block;
      block.name = compiler.get_name(resource.id);
      block.id = resource.id;
      block.stage = stage;
      block.binding = compiler.get_decoration(resource.id, spv::DecorationBinding);
      block.set = compiler.get_decoration(resource.id, spv::DecorationDescriptorSet);
      size_t blockSize = compiler.get_declared_struct_size(compiler.get_type(resource.base_type_id));
      //CANDY_CORE_INFO("BLOCK NAME: {}, BLOCK ID: {}, BLOCK SIZE: {}", block.name, block.id, blockSize);
      auto members = compiler.get_type(resource.base_type_id).member_types;
      size_t memberSize = members.size();
      //CANDY_CORE_INFO("MEMBER COUNT: {}", memberSize);
      for (int i=0; i<memberSize; i++)
      {
        ShaderUniformProperty prop;
        prop.name = compiler.get_member_name(resource.base_type_id, i);
        prop.id = members[i];
        prop.parentBlockID = resource.base_type_id;
        prop.type = ShaderData::SpirvToType(compiler.get_type(prop.id));
        CANDY_CORE_INFO("MEMBER NAME: {}, MEMBER ID: {}, PARENT ID: {}, TYPE: {}", prop.name, prop.id, prop.parentBlockID, ShaderData::TypeToString(prop.type));
        block.properties.push_back(prop);
      }
      
      shaderLayout.AddUniformBlockProperty(block);

      
    }
    
    for (auto& resource : resources.sampled_images)
    {
      ShaderUniformImageProperty prop;
      prop.id = resource.id;
      prop.name = compiler.get_name(resource.id);
      prop.stage = stage;
      prop.type = ShaderData::SpirvToType(compiler.get_type(resource.type_id));
      prop.binding = compiler.get_decoration(resource.id, spv::DecorationBinding);
      prop.set = compiler.get_decoration(resource.id, spv::DecorationDescriptorSet);
      CANDY_CORE_INFO("IMAGE PROP NAME: {}, ID: {}, TYPE: {},  BINDING: {}, SET: {}", prop.name, prop.id, ShaderData::TypeToString(prop.type), prop.binding, prop.set);
      shaderLayout.AddUniformImageProperty(prop);
      //descriptorLayout.BindImage(prop.binding, stage);
      
      /*VkDescriptorSetLayoutBinding samplerLayoutBinding{};
      samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
      
      samplerLayoutBinding.descriptorCount = 1;
      samplerLayoutBinding.binding = binding;
      samplerLayoutBinding.stageFlags = ShaderData::StageToVulkan(stage);
      samplerLayoutBinding.pImmutableSamplers = nullptr;
      layoutBindings.push_back(samplerLayoutBinding);*/
    }
    
    ShaderPushConstantBlockProperty pushBlock{};
    pushBlock.stage = stage;
    pushBlock.offset = 0;
    VkPushConstantRange pushRange{};
    pushRange.stageFlags = ShaderData::StageToVulkan(stage);
    pushRange.offset = 0;
    
    spirv_cross::Resource pushResource = compiler.get_shader_resources().push_constant_buffers[0];
    
    CANDY_CORE_INFO("PUSH RESOURCE ID: {}, Type ID: {}, Base Type ID: {}", pushResource.id, pushResource.type_id, pushResource.base_type_id);
    CANDY_CORE_INFO("PRE PUSH TYPE");
    
   
    CANDY_CORE_INFO("POST PUSH TYPE");
   
    
    
    uint32_t id = pushResource.id;
    
    
    pushBlock.id = id;
    uint32_t base_type_id = pushResource.base_type_id;
    uint32_t pcrSize=0;
    std::vector<spirv_cross::BufferRange> ranges = (std::vector<spirv_cross::BufferRange>)compiler.get_active_buffer_ranges(id);
    if (ranges.empty())
    {
      return;
    }
    auto pushMembers = compiler.get_type(base_type_id).member_types;
    for (auto& range : ranges)
    {
      ShaderPushConstantProperty prop;
      prop.name = compiler.get_member_name(base_type_id, range.index);
      prop.index = range.index;
      prop.offset = range.offset;
      prop.size = range.range;
      prop.type = ShaderData::SpirvToType(compiler.get_type(pushMembers[range.index]));
      
      //CANDY_CORE_INFO("PUSH CONSTANT VAR TYPE: {}", ShaderData::TypeToString(prop.type));
      prop.parentBlockID = pushBlock.id;
      
      
      pushBlock.properties.push_back(prop);
      //CANDY_CORE_INFO("MEMBER NAME {}", compiler.get_member_name(base_type_id, range.index));
      //CANDY_CORE_INFO("Member: {0}, Offset: {1}, Size: {2}", range.index, range.offset, range.range);
      pcrSize += range.range;
    }
    pushRange.size = pcrSize;
    if (pushRange.size > 0)
    {
      shaderLayout.AddPushConstantBlockProperty(pushBlock);
      //pushConstantRanges.push_back(pushRange);
    }
  }
  
  ShaderLayout& ShaderPostProcessor::GetLayout()
  {
    return shaderLayout;
  }

}