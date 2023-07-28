#pragma once
#include <string>
#include <unordered_map>
#include "CandyPch.hpp"
#include "candy/graphics/Color.hpp"
#include "ShaderData.hpp"
#include "vulkan/vulkan.h"
#include "processing/ShaderPreProcessor.hpp"
#include "processing/ShaderPostProcessor.hpp"
namespace Candy::Graphics
{
  
    class Shader
    {
    private:
      std::string shaderName;
      std::filesystem::path filepath;
        
      UniquePtr<ShaderPreProcessor> preProcessor;
      ShaderPostProcessor postProcessor;
      std::vector<VkShaderModule> shaderModules;
    
    private:
      VkShaderModule CreateShaderModule(ShaderData::Stage stage);
      std::vector<VkPipelineShaderStageCreateInfo> CreateShaderStageCreateInfos();
        
    
    public:
      explicit Shader(std::filesystem::path  shaderFilePath);
    
    public:
      // Push constant functions
      uint32_t PushFloat(const std::string& name, float value);
      uint32_t PushVector2(const std::string& name, const Math::Vector2& vector);
      uint32_t PushVector3(const std::string& name, const Math::Vector3& vector);
      uint32_t PushVector4(const std::string& name, const Math::Vector4& vector);
      uint32_t PushMatrix(const std::string& name, const Math::Matrix4& matrix);
      
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
      
      
      
      
      const std::string& GetName()const{return shaderName;}
      const std::filesystem::path& GetFilepath()const{return filepath;}
      void DestroyShaderModules();
      
        
      std::vector<VkPushConstantRange> GetPushConstantRanges();
      ShaderPostProcessor& GetPostProcessor(){return postProcessor;}
      ShaderLayout& GetLayout(){return postProcessor.shaderLayout;}
        
    public:
      static std::vector<char> ReadSpvFileBinary(const std::string& filename);
      static SharedPtr<Shader> Create(const std::filesystem::path& shaderFilePath);
        
    private:
        friend class GraphicsContext;
        friend class GraphicsPipeline;
        friend class Pipeline;
        
       
    
    
   
        
        
        
    };
}