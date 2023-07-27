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
      Reflect(stage, data, layoutBindings);
    }
    
    descriptorLayout.Build();
    /*VkDescriptorSetLayoutCreateInfo layoutInfo{};
    layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    layoutInfo.bindingCount = layoutBindings.size();
    layoutInfo.pBindings = layoutBindings.data();
    
    CANDY_CORE_ASSERT(vkCreateDescriptorSetLayout(Vulkan::LogicalDevice(), &layoutInfo, nullptr, &descriptorSetLayout) == VK_SUCCESS, "Failed to create descriptor set layout!");*/
  
  }
  
  
  void ShaderPostProcessor::Reflect(ShaderData::Stage stage, std::vector<uint32_t> spirvBinary, std::vector<VkDescriptorSetLayoutBinding>& layoutBindings)
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
      shaderLayout.AddInputLayoutProperty(compiler.get_name(resource.id), shaderType, binding, set, offset, stride, location);
    }
    for (auto& resource : resources.stage_outputs)
    {
      uint32_t location = compiler.get_decoration(resource.id, spv::DecorationLocation);
      uint32_t binding = compiler.get_decoration(resource.id, spv::DecorationBinding);
      uint32_t offset = compiler.get_decoration(resource.id, spv::DecorationOffset);
      uint32_t stride = compiler.get_decoration(resource.id, spv::DecorationXfbStride);
      uint32_t set = compiler.get_decoration(resource.id, spv::DecorationDescriptorSet);
      
      ShaderData::Type shaderType = ShaderData::SpirvToType(compiler.get_type(resource.type_id));
      shaderLayout.AddInputLayoutProperty(compiler.get_name(resource.id), shaderType, binding, set, offset, stride, location);
    }
    
    for (auto& resource : resources.uniform_buffers)
    {
      //CANDY_CORE_INFO("UNIFORM NAME: {}", resource.name);
      //CANDY_CORE_INFO("UNIFORM SIZE: {}", compiler.get_declared_struct_size(compiler.get_type(resource.base_type_id)));
      auto memberNames = compiler.get_type(resource.base_type_id).member_name_cache;
      for (auto& memberName : memberNames)
      {
        //CANDY_CORE_INFO("UNIFORM MEMBER NAME: {}", memberName);
      }
      uint32_t set = compiler.get_decoration(resource.id, spv::DecorationDescriptorSet);
      uint32_t binding = compiler.get_decoration(resource.id, spv::DecorationBinding);
      descriptorLayout.BindBuffer(binding, stage);
      /*VkDescriptorSetLayoutBinding layoutBinding{};
      
      layoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
      layoutBinding.descriptorCount = 1;
      layoutBinding.binding = binding;
      layoutBinding.stageFlags = ShaderData::StageToVulkan(stage);
      layoutBinding.pImmutableSamplers = nullptr;
      layoutBindings.push_back(layoutBinding);*/
      //descriptorBuilder.BindBuffer(binding, )
      
    }
    
    for (auto& resource : resources.sampled_images)
    {
      uint32_t binding = compiler.get_decoration(resource.id, spv::DecorationBinding);
      descriptorLayout.BindImage(binding, stage);
      
      /*VkDescriptorSetLayoutBinding samplerLayoutBinding{};
      samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
      
      samplerLayoutBinding.descriptorCount = 1;
      samplerLayoutBinding.binding = binding;
      samplerLayoutBinding.stageFlags = ShaderData::StageToVulkan(stage);
      samplerLayoutBinding.pImmutableSamplers = nullptr;
      layoutBindings.push_back(samplerLayoutBinding);*/
    }
    VkPushConstantRange pushRange{};
    pushRange.stageFlags = ShaderData::StageToVulkan(stage);
    pushRange.offset = 0;
    
    
    uint32_t id = compiler.get_shader_resources().push_constant_buffers[0].id;
    uint32_t base_type_id = compiler.get_shader_resources().push_constant_buffers[0].base_type_id;
    uint32_t pcrSize=0;
    std::vector<spirv_cross::BufferRange> ranges = (std::vector<spirv_cross::BufferRange>)compiler.get_active_buffer_ranges(id);
    for (auto& range : ranges)
    {
      
      //CANDY_CORE_INFO("MEMBER NAME {}", compiler.get_member_name(base_type_id, range.index));
      //CANDY_CORE_INFO("Member: {0}, Offset: {1}, Size: {2}", range.index, range.offset, range.range);
      pcrSize += range.range;
    }
    pushRange.size = pcrSize;
    if (pushRange.size > 0)
    {
      pushConstantRanges.push_back(pushRange);
    }
  }

}