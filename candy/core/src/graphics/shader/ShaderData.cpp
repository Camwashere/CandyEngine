#include "candy/graphics/shader/ShaderData.hpp"
#include "CandyPch.hpp"
#include "SPIRV-Cross/spirv_glsl.hpp"
namespace Candy::Graphics
{
  std::array<std::string, static_cast<size_t>(ShaderData::Type::End)> ShaderData::InitTypeToStringArray()
  {
    std::array<std::string, static_cast<size_t>(Type::End)> arr;
    arr[static_cast<size_t>(Type::None)] = "unknown";
    arr[static_cast<size_t>(Type::Bool)] = "bool";
    arr[static_cast<size_t>(Type::BVec2)] = "bvec2";
    arr[static_cast<size_t>(Type::BVec3)] = "bvec3";
    arr[static_cast<size_t>(Type::BVec4)] = "bvec4";
    arr[static_cast<size_t>(Type::Int)] = "int";
    arr[static_cast<size_t>(Type::IVec2)] = "ivec2";
    arr[static_cast<size_t>(Type::IVec3)] = "ivec3";
    arr[static_cast<size_t>(Type::IVec4)] = "ivec4";
    arr[static_cast<size_t>(Type::UInt)] = "uint";
    arr[static_cast<size_t>(Type::UInt2)] = "uvec2";
    arr[static_cast<size_t>(Type::UInt3)] = "uvec3";
    arr[static_cast<size_t>(Type::UInt4)] = "uvec4";
    arr[static_cast<size_t>(Type::Float)] = "float";
    arr[static_cast<size_t>(Type::Vec2)] = "vec2";
    arr[static_cast<size_t>(Type::Vec3)] = "vec3";
    arr[static_cast<size_t>(Type::Vec4)] = "vec4";
    arr[static_cast<size_t>(Type::Double)] = "double";
    arr[static_cast<size_t>(Type::Double2)] = "dvec2";
    arr[static_cast<size_t>(Type::Double3)] = "dvec3";
    arr[static_cast<size_t>(Type::Double4)] = "dvec4";
    arr[static_cast<size_t>(Type::Matrix2)] = "mat2";
    arr[static_cast<size_t>(Type::Matrix3)] = "mat3";
    arr[static_cast<size_t>(Type::Matrix4)] = "mat4";
    
    // Samplers
    arr[static_cast<size_t>(Type::Sampler2D)] = "sampler2D";
    arr[static_cast<size_t>(Type::SamplerCube)] = "samplerCube";
    arr[static_cast<size_t>(Type::Void)] = "void";
    return arr;
    
  }
  std::array<VkFormat, static_cast<size_t>(ShaderData::Type::End)> ShaderData::InitTypeToVulkanArray()
  {
    std::array<VkFormat, static_cast<size_t>(Type::End)> arr{};
    arr[static_cast<size_t>(Type::None)] = VK_FORMAT_UNDEFINED;
    arr[static_cast<size_t>(Type::Float)] = VK_FORMAT_R32_SFLOAT;
    arr[static_cast<size_t>(Type::Vec2)] = VK_FORMAT_R32G32_SFLOAT;
    arr[static_cast<size_t>(Type::Vec3)] = VK_FORMAT_R32G32B32_SFLOAT;
    arr[static_cast<size_t>(Type::Vec4)] = VK_FORMAT_R32G32B32A32_SFLOAT;
    arr[static_cast<size_t>(Type::Int)] = VK_FORMAT_R32_SINT;
    arr[static_cast<size_t>(Type::IVec2)] = VK_FORMAT_R32G32_SINT;
    arr[static_cast<size_t>(Type::IVec3)] = VK_FORMAT_R32G32B32_SINT;
    arr[static_cast<size_t>(Type::IVec4)] = VK_FORMAT_R32G32B32A32_SINT;
    arr[static_cast<size_t>(Type::UInt)] = VK_FORMAT_R32_UINT;
    arr[static_cast<size_t>(Type::UInt2)] = VK_FORMAT_R32G32_UINT;
    arr[static_cast<size_t>(Type::UInt3)] = VK_FORMAT_R32G32B32_UINT;
    arr[static_cast<size_t>(Type::UInt4)] = VK_FORMAT_R32G32B32A32_UINT;
    arr[static_cast<size_t>(Type::Bool)] = VK_FORMAT_R32_SINT;
    arr[static_cast<size_t>(Type::BVec2)] = VK_FORMAT_R32G32_SINT;
    arr[static_cast<size_t>(Type::BVec3)] = VK_FORMAT_R32G32B32_SINT;
    arr[static_cast<size_t>(Type::BVec4)] = VK_FORMAT_R32G32B32A32_SINT;
    
    return arr;
    
  
  }
  std::array<std::string, static_cast<size_t>(ShaderData::Stage::End)> ShaderData::InitStageToStringArray()
  {
    std::array<std::string, static_cast<size_t>(Stage::End)> arr;
    arr[static_cast<size_t>(Stage::None)] = "none";
    arr[static_cast<size_t>(Stage::Vertex)] = "vertex";
    arr[static_cast<size_t>(Stage::Fragment)] = "fragment";
    arr[static_cast<size_t>(Stage::Geometry)] = "geometry";
    arr[static_cast<size_t>(Stage::Compute)] = "compute";
    arr[static_cast<size_t>(Stage::TessellationControl)] = "tessellation_control";
    arr[static_cast<size_t>(Stage::TessellationEvaluation)] = "tessellation_evaluation";
    return arr;
  }
  
  const std::unordered_map<std::string, ShaderData::Type> ShaderData::stringToTypeMap = {
    {"float", Type::Float},
    {"vec2", Type::Vec2},
    {"vec3", Type::Vec3},
    {"vec4", Type::Vec4},
    {"mat3", Type::Mat3},
    {"mat4", Type::Mat4},
    {"int", Type::Int},
    {"ivec2", Type::IVec2},
    {"ivec3", Type::IVec3},
    {"ivec4", Type::IVec4},
    {"bool", Type::Bool},
    {"bvec2", Type::BVec2},
    {"bvec3", Type::BVec3},
    {"bvec4", Type::BVec4},
    {"sampler2D", Type::Sampler2D},
    {"samplerCube", Type::SamplerCube},
    {"void", Type::Void}
  };
  const std::unordered_map<std::string, ShaderData::Stage> ShaderData::stringToStageMap = {
    {"vertex", Stage::Vertex},
    {"fragment", Stage::Fragment},
    {"geometry", Stage::Geometry},
    {"compute", Stage::Compute},
    {"tessellation_control", Stage::TessellationControl},
    {"tessellation_evaluation", Stage::TessellationEvaluation}
  };
  const std::array<std::string, static_cast<size_t>(ShaderData::Type::End)> ShaderData::typeToStringArray = InitTypeToStringArray();
  const std::array<std::string, static_cast<size_t>(ShaderData::Stage::End)> ShaderData::stageToStringArray = ShaderData::InitStageToStringArray();
  const std::array<VkFormat, static_cast<size_t>(ShaderData::Type::End)> ShaderData::typeToVulkanArray=ShaderData::InitTypeToVulkanArray();
  
  
  const std::string& ShaderData::TypeToString(Type type)
  {
    return typeToStringArray[static_cast<size_t>(type)];
  }
  
  VkFormat ShaderData::TypeToVulkan(Type type)
  {
    return typeToVulkanArray[static_cast<size_t>(type)];
  }
  ShaderData::Type ShaderData::StringToType(const std::string& type)
  {
    auto it = stringToTypeMap.find(type);
    if (it != stringToTypeMap.end())
      return it->second;
    return Type::None;
  }
  
  
  ShaderData::Type ShaderData::SpirvToType(const spirv_cross::SPIRType& spirvType)
  {
    switch(spirvType.basetype)
    {
      
      case spirv_cross::SPIRType::Unknown:
        break;
      case spirv_cross::SPIRType::Void:
        break;
      case spirv_cross::SPIRType::Boolean:
        break;
      case spirv_cross::SPIRType::SByte:
        break;
      case spirv_cross::SPIRType::UByte:
        break;
      case spirv_cross::SPIRType::Short:
        break;
      case spirv_cross::SPIRType::UShort:
        break;
      case spirv_cross::SPIRType::Int:
        break;
      case spirv_cross::SPIRType::UInt:
        break;
      case spirv_cross::SPIRType::Int64:
        break;
      case spirv_cross::SPIRType::UInt64:
        break;
      case spirv_cross::SPIRType::AtomicCounter:
        break;
      case spirv_cross::SPIRType::Half:
        break;
      case spirv_cross::SPIRType::Float:
        if (spirvType.columns == 1)
        {
          switch(spirvType.vecsize)
          {
            case 1: return Type::Float;
            case 2: return Type::Vec2;
            case 3: return Type::Vec3;
            case 4: return Type::Vec4;
            default:
              return Type::Unknown;
              break;
          }
        }
        else
        {
          if (spirvType.columns == spirvType.vecsize)
          {
            switch(spirvType.columns)
            {
              case 2: return Type::Matrix2;
              case 3: return Type::Matrix3;
              case 4: return Type::Matrix4;
              default:
                return Type::Unknown;
                break;
            }
          }
          return Type::Unknown;
        }
        
        break;
      case spirv_cross::SPIRType::Double:
        break;
      case spirv_cross::SPIRType::Struct:
        break;
      case spirv_cross::SPIRType::Image:
        break;
      case spirv_cross::SPIRType::SampledImage:
        return Type::Sampler2D;
      case spirv_cross::SPIRType::Sampler:
        break;
      case spirv_cross::SPIRType::AccelerationStructure:
        break;
      case spirv_cross::SPIRType::RayQuery:
        break;
      case spirv_cross::SPIRType::ControlPointArray:
        break;
      case spirv_cross::SPIRType::Interpolant:
        break;
      case spirv_cross::SPIRType::Char:
        break;
    }
    
    CANDY_CORE_INFO("Vec Size: {}, Columns: {}", spirvType.vecsize, spirvType.columns);
    return Type::Unknown;
    
  }
  
  
  const std::string& ShaderData::StageToString(Stage stage)
  {
    return stageToStringArray[static_cast<size_t>(stage)];
  }
  ShaderData::Stage ShaderData::StringToStage(const std::string& stage)
  {
    auto it = stringToStageMap.find(stage);
    if (it != stringToStageMap.end())
      return it->second;
    return Stage::None;
  }
  VkShaderStageFlagBits ShaderData::StageToVulkan(Stage stage)
  {
    switch (stage)
    {
      case Stage::Vertex: return VK_SHADER_STAGE_VERTEX_BIT;
      case Stage::Fragment: return VK_SHADER_STAGE_FRAGMENT_BIT;
      case Stage::Compute: return VK_SHADER_STAGE_COMPUTE_BIT;
      case Stage::Geometry: return VK_SHADER_STAGE_GEOMETRY_BIT;
      case Stage::TessellationControl: return VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
      case Stage::TessellationEvaluation: return VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
      default:
      CANDY_CORE_ASSERT(false, "Unknown shader stage!");
        return (VkShaderStageFlagBits)0;
    }
  
  }
  
  ShaderData::Stage ShaderData::VulkanToStage(VkShaderStageFlagBits stage)
  {
    switch(stage)
    {
      case VK_SHADER_STAGE_VERTEX_BIT: return Stage::Vertex;
      case VK_SHADER_STAGE_FRAGMENT_BIT: return Stage::Fragment;
      case VK_SHADER_STAGE_COMPUTE_BIT: return Stage::Compute;
      case VK_SHADER_STAGE_GEOMETRY_BIT: return Stage::Geometry;
      case VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT: return Stage::TessellationControl;
      case VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT: return Stage::TessellationEvaluation;
      default:
      CANDY_CORE_ASSERT(false, "Unknown shader stage!");
        return Stage::None;
    }
  
  }
  
  std::string ShaderData::StageToCachedFileExtension(Stage stage)
  {
    switch (stage)
    {
      case Stage::Vertex:    return ".cached_vulkan.vert";
      case Stage::Fragment:  return ".cached_vulkan.frag";
      case Stage::Geometry:  return ".cached_vulkan.geometry";
      case Stage::Compute:   return ".cached_vulkan.compute";
      default:
      CANDY_CORE_ASSERT(false, "Unknown shader stage!");
        return {};
    }
  
  }
  size_t ShaderData::ComponentSize(Type type)
  {
    switch(type)
    {
      case Type::Float:
      case Type::Float2:
      case Type::Float3:
      case Type::Float4:
      case Type::Matrix2:
      case Type::Matrix3:
      case Type::Matrix4:
        return sizeof(float);
      case Type::Int:
      case Type::Int2:
      case Type::Int3:
      case Type::Int4:
      case Type::UInt:
      case Type::UInt2:
      case Type::UInt3:
      case Type::UInt4:
        return sizeof(int);
      case Type::Double:
      case Type::Double2:
      case Type::Double3:
      case Type::Double4:
        return sizeof(double);
      case Type::Bool:
      case Type::BVec2:
      case Type::BVec3:
      case Type::BVec4:
        return sizeof(bool);
      default:
        return 0;
    }
  
  }
  size_t ShaderData::ComponentCount(Type type)
  {
    switch(type)
    {
      case Type::Float:
      case Type::Int:
      case Type::Bool:
      case Type::UInt:
      case Type::Double:
        return 1;
      case Type::Float2:
      case Type::Int2:
      case Type::Double2:
      case Type::UInt2:
      case Type::BVec2:
        return 2;
      case Type::Float3:
      case Type::Int3:
      case Type::BVec3:
      case Type::UInt3:
      case Type::Double3:
        return 3;
      case Type::Float4:
      case Type::Int4:
      case Type::UInt4:
      case Type::Double4:
      case Type::BVec4:
      case Type::Matrix2:
        return 4;
      case Type::Matrix3:
        return 9;
      case Type::Matrix4:
        return 16;
      default:
        return 0;
    }
  
  }
  size_t ShaderData::TypeSize(Type type)
  {
    return ComponentSize(type) * ComponentCount(type);
  
  }
}