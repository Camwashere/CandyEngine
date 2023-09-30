#pragma once
#include <string>
#include <unordered_map>
#include "CandyPch.hpp"
#include "candy/graphics/Color.hpp"
#include "ShaderData.hpp"
#include "vulkan/vulkan.h"
//#include "ShaderSettings.hpp"
//#include "processing/ShaderPreProcessor.hpp"
//#include "processing/ShaderPostProcessor.hpp"
#include "../vulkan/pipeline/Pipeline.hpp"
namespace Candy::Graphics
{
  
  class ShaderLayout;
  class ShaderPreProcessor;
  class ShaderPostProcessor;
  
    class Shader
    {
    private:
      std::string shaderName;
      uint32_t id;
        
      UniquePtr<ShaderPreProcessor> preProcessor;
      UniquePtr<ShaderPostProcessor> postProcessor;
    
    private:
      VkShaderModule CreateShaderModule(ShaderData::Stage stage);
      std::vector<VkPipelineShaderStageCreateInfo> CreateShaderStageCreateInfos();
      std::vector<VkPushConstantRange> GetPushConstantRanges();
    
    public:
      explicit Shader(const ShaderSettings&  settings);
      
    public:
      void Bake();
      void Bind();
      void Commit();
      
    public:
      // Push constant functions
      [[nodiscard]] uint32_t GetPushID(const std::string& name)const;
      
      
      uint32_t PushInt(const std::string& name, int value);
      uint32_t PushFloat(const std::string& name, float value);
      uint32_t PushVector2(const std::string& name, const Math::Vector2& vector);
      uint32_t PushVector3(const std::string& name, const Math::Vector3& vector);
      uint32_t PushVector4(const std::string& name, const Math::Vector4& vector);
      uint32_t PushMatrix(const std::string& name, const Math::Matrix4& matrix);
      
      void PushInt(uint32_t id, int value);
      void PushFloat(uint32_t id, float value);
      void PushVector2(uint32_t id, const Math::Vector2& vector);
      void PushVector3(uint32_t id, const Math::Vector3& vector);
      void PushVector4(uint32_t id, const Math::Vector4& vector);
      void PushMatrix(uint32_t id, const Math::Matrix4& matrix);
      
      // Set uniform functions
      uint32_t SetFloat(const std::string& name, float value);
      uint32_t SetVector2(const std::string& name, const Math::Vector2& vector);
      uint32_t SetVector3(const std::string& name, const Math::Vector3& vector);
      uint32_t SetVector4(const std::string& name, const Math::Vector4& vector);
      uint32_t SetColor(const std::string& name, const Color& color);
      uint32_t SetMatrix(const std::string& name, const Math::Matrix4& matrix);
      
      void SetFloat(uint32_t id, float value);
      void SetVector2(uint32_t id, const Math::Vector2& vector);
      void SetVector3(uint32_t id, const Math::Vector3& vector);
      void SetVector4(uint32_t id, const Math::Vector4& vector);
      void SetColor(uint32_t id, const Color& color);
      void SetMatrix(uint32_t id, const Math::Matrix4& matrix);
      
      
    public:
      [[nodiscard]] const std::string& GetName()const;
      [[nodiscard]] const std::filesystem::path& GetFilepath()const;
      [[nodiscard]] const ShaderSettings& GetSettings()const;
      [[nodiscard]] VkPipeline GetPipeline()const;
      [[nodiscard]] VkPipelineLayout GetPipelineLayout()const;
        
      
      ShaderPostProcessor& GetPostProcessor();
      ShaderLayout& GetLayout();
      [[nodiscard]] const ShaderLayout& GetLayout()const;
      [[nodiscard]] BufferLayout GetBufferLayout()const;
      [[nodiscard]] size_t GetMaterialBufferSize()const;
      [[nodiscard]] size_t GetGlobalBufferSize()const;
        
    public:
      static std::vector<char> ReadSpvFileBinary(const std::string& filename);
      static SharedPtr<Shader> Create(const ShaderSettings& settings);
      
        
    private:
        friend class GraphicsContext;
        friend class GraphicsPipeline;
        friend class Pipeline;
        
       
    
    
   
        
        
        
    };
}