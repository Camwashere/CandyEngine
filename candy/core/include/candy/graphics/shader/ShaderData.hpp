#pragma once
#include <string>
#include <vector>
#include <array>
#include <unordered_map>
#include <vulkan/vulkan.h>
#include <typeinfo>
#include <candy/math/Vector.hpp>
namespace spirv_cross
{
  struct SPIRType;
}
namespace Candy::Graphics
{
  
  class ShaderData
  {
  
  public:
    enum class Type
    {
      // N/A
      None=0, Unknown=0,
      
      Void,
      
      //Byte
      Byte, Byte2, Byte3, Byte4,
      
      //UByte
      UByte, UByte2, UByte3, UByte4,
      
      // Bool
      Bool,Bool2,BVec2=Bool2,Bool3,BVec3=Bool3,Bool4,BVec4=Bool4,
      
      // Int
      Int,Int2,IVec2=Int2,Int3,IVec3=Int3,Int4,IVec4=Int4,
      
      // UInt
      UInt,UInt2,UInt3,UInt4,
      
      // Float
      Float,Float2,Vector2=Float2,Vec2=Vector2,Float3,Vector3=Float3,Vec3=Vector3,Float4,Vector4=Float4,Vec4=Vector4,
      
      // Double
      Double,Double2,Vector2Double=Double2,Double3,Vector3Double=Double3,Double4,Vector4Double=Double4,
      
      // Matrix
      Matrix2,Matrix2x2=Matrix2,Mat2=Matrix2,
      
      Matrix3,Matrix3x3=Matrix3,Mat3=Matrix3,
      
      Matrix4,Matrix4x4=Matrix4,Mat4=Matrix4,
      
      // Sampler
      Sampler1D,Sampler1DArray,Sampler1DShadow,Sampler1DArrayShadow,
      
      Sampler2D,Sampler2DArray,Sampler2DShadow,Sampler2DArrayShadow,Sampler2DRect,Sampler2DRectShadow,
      
      SamplerCube,SamplerCubeArray,SamplerCubeShadow,SamplerCubeArrayShadow,
      
      SamplerBuffer,ISamplerBuffer,USamplerBuffer,
      
      ISampler1D,ISampler1DArray,
      
      ISampler2D,ISampler2DArray,ISampler2DRect,
      
      ISamplerCube,ISamplerCubeArray,
      
      USampler1D,USampler1DArray,
      USampler2D,USampler2DArray,USampler2DRect,
      USamplerCube,USamplerCubeArray,
      End,
      
    };
    
    enum class Stage
    {
      None = 0,
      Vertex = 1,
      Fragment = 2,
      Compute = 3,
      Geometry = 4,
      TessellationControl=5,
      TessellationEvaluation=6,
      End,
    };
  
  private:
    static const std::array<std::string, static_cast<size_t>(Type::End)> typeToStringArray;
    static const std::array<VkFormat, static_cast<size_t>(Type::End)> typeToVulkanArray;
    
    static const std::array<std::string, static_cast<size_t>(Stage::End)> stageToStringArray;
    
    static const std::unordered_map<std::string, Type> stringToTypeMap;
    static const std::unordered_map<std::string, Stage> stringToStageMap;
    
    static std::array<std::string, static_cast<size_t>(Type::End)> InitTypeToStringArray();
    static std::array<std::string, static_cast<size_t>(Stage::End)> InitStageToStringArray();
    static std::array<VkFormat, static_cast<size_t>(Type::End)> InitTypeToVulkanArray();
    
    
    
    
    
  
  
  
  
  
  public:
    static const std::string& TypeToString(Type type);
    static Type StringToType(const std::string& type);
    static Type SpirvToType(const spirv_cross::SPIRType& spirvType);
    static Type ToBaseType(Type type);
    static const std::string& StageToString(Stage stage);
    static Stage StringToStage(const std::string& stage);
    static VkFormat TypeToVulkan(Type type);
    static VkShaderStageFlagBits StageToVulkan(Stage stage);
    static Stage VulkanToStage(VkShaderStageFlagBits stage);
    static std::string StageToCachedFileExtension(Stage stage);
    static size_t ComponentCount(Type type);
    static size_t ComponentSize(Type type);
    static size_t TypeSize(Type type);
    
    template<typename T>
    static constexpr Type TypeFrom()
    {
      return Type::None;
    }
    
    
  };
  
  
  template<> constexpr ShaderData::Type ShaderData::TypeFrom<void>() { return ShaderData::Type::Void; }
  template<> constexpr ShaderData::Type ShaderData::TypeFrom<char>() { return ShaderData::Type::Byte; }
  template<> constexpr ShaderData::Type ShaderData::TypeFrom<unsigned char>() { return ShaderData::Type::UByte; }
  template<> constexpr ShaderData::Type ShaderData::TypeFrom<bool>() { return ShaderData::Type::Bool; }
  template<> constexpr ShaderData::Type ShaderData::TypeFrom<int>() { return ShaderData::Type::Int; }
  template<> constexpr ShaderData::Type ShaderData::TypeFrom<unsigned int>() { return ShaderData::Type::UInt; }
  template<> constexpr ShaderData::Type ShaderData::TypeFrom<float>() { return ShaderData::Type::Float; }
  template<> constexpr ShaderData::Type ShaderData::TypeFrom<double>() { return ShaderData::Type::Double; }
  template<> constexpr ShaderData::Type ShaderData::TypeFrom<Math::Vector2>() { return ShaderData::Type::Vector2; }
  template<> constexpr ShaderData::Type ShaderData::TypeFrom<Math::Vector3>() { return ShaderData::Type::Vector3; }
  template<> constexpr ShaderData::Type ShaderData::TypeFrom<Math::Vector4>() { return ShaderData::Type::Vector4; }
  template<> constexpr ShaderData::Type ShaderData::TypeFrom<Math::Vector2d>() { return ShaderData::Type::Vector2Double; }
  template<> constexpr ShaderData::Type ShaderData::TypeFrom<Math::Vector3d>() { return ShaderData::Type::Vector3Double; }
  
  
}
