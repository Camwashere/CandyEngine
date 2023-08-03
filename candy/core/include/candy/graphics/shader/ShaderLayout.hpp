#pragma once
#include "ShaderData.hpp"
#include "../UniformBuffer.hpp"
#include <candy/math/Matrix.hpp>
#include "../vulkan/pipeline/Pipeline.hpp"
#include <candy/graphics/BufferLayout.hpp>
namespace Candy::Graphics
{
  // Responsible for automatically creating descriptor sets
  struct ShaderProperty
  {
    std::string name;
    uint32_t id;
    uint32_t parentBlockID;
    uint32_t offset;
    uint32_t size;
    ShaderData::Type type;
    
    
    [[nodiscard]] std::string ToString()const;
    
  };
  struct ShaderParentProperty
  {
    std::string name;
    uint32_t id;
    uint32_t binding;
  };
  
  struct ShaderPushProperty
  {
    std::string name;
    uint32_t id;
    uint32_t offset;
    uint32_t size;
    ShaderData::Stage stage;
    ShaderData::Type type;
  };
  
  struct ShaderUniformProperty
  {
    std::string name;
    uint32_t id;
    uint32_t parentBlockID;
    ShaderData::Type type;
  };
  struct ShaderUniformImageProperty
  {
    std::string name;
    uint32_t id;
    ShaderData::Stage stage;
    ShaderData::Type type;
    uint32_t binding;
    uint32_t set;
  };
  struct ShaderUniformBlockProperty
  {
    std::string name;
    uint32_t id;
    ShaderData::Stage stage;
    uint32_t binding;
    uint32_t set;
    
    std::vector<ShaderUniformProperty> properties;
  };
  struct ShaderPushConstantProperty
  {
    std::string name;
    uint32_t parentBlockID;
    uint32_t index;
    uint32_t offset;
    size_t size;
    ShaderData::Type type;
  };
  struct ShaderPushConstantBlockProperty
  {
    uint32_t id;
    ShaderData::Stage stage;
    uint32_t offset;
    std::vector<ShaderPushConstantProperty> properties;
  };
  // Responsible for pipelines vertex input info and vertex binding info replacements
  // Grab the layout properties from the 'vertex' stage and calculate the stride/offsets with them there based on the location variables
  struct ShaderLayoutProperty
  {
  
    std::string name;
    ShaderData::Stage stage;
    ShaderData::Type type;
    std::uint32_t binding;
    std::uint32_t set;
    std::uint32_t offset;
    std::uint32_t stride;
    std::uint32_t location;
    bool input;
    
    [[nodiscard]] std::string ToString()const;

  };
  class ShaderLayout
  {
  private:
    Pipeline pipeline;
  
  public:
    //uint32_t layoutVertexStride=0;
    BufferLayout bufferLayout;
    UniquePtr<UniformBuffer> uniformBuffer;
    std::unordered_map<std::string, uint32_t> propertyMap;
    std::unordered_map<std::string, uint32_t> pushPropertyMap;
    std::vector<ShaderProperty> properties;
    std::vector<ShaderParentProperty> parentProperties;
    std::vector<ShaderParentProperty> imageProperties;
    std::vector<ShaderPushProperty> pushProperties;
    
    std::vector<ShaderPushConstantBlockProperty> pushConstantBlockProperties;
    std::vector<ShaderUniformBlockProperty> uniformBlockProperties;
    std::vector<ShaderUniformImageProperty> uniformImageProperties;
    std::vector<ShaderLayoutProperty> inputLayoutProperties;
    std::vector<ShaderLayoutProperty> outputLayoutProperties;
    
  private:
    VkPipelineLayout BakePipelineLayout();
    std::vector<VkDescriptorSetLayout> BakeDescriptorSetLayouts();
    void BakePipeline(VkRenderPass renderPass, const std::vector<VkPipelineShaderStageCreateInfo>& createInfos);
    
  public:
    ShaderLayout();
    uint32_t PushConstant(const std::string& name, const void* data);
    void PushConstant(uint32_t id, const void* data);
    uint32_t SetUniform(const std::string& name, const void* data);
    void SetUniform(uint32_t id, const void* data);
    void CalculateOffsetsAndStride();
    void CalculateProperties();
    BufferLayout GetBufferLayout()const;
    size_t MaxSetCount()const;
    std::vector<VkPushConstantRange> GetPushConstantRanges();
    std::vector<VkVertexInputBindingDescription> GetVertexBindingDescriptions()const;
    std::vector<VkVertexInputAttributeDescription> GetVertexAttributeDescriptions()const;
    
  public:
    void AddPushConstantBlockProperty(const ShaderPushConstantBlockProperty& prop);
    void AddUniformBlockProperty(const ShaderUniformBlockProperty& prop);
    void AddUniformImageProperty(const ShaderUniformImageProperty& prop);
    void AddInputLayoutProperty(const std::string& name, ShaderData::Stage stage, ShaderData::Type type, std::uint32_t binding, std::uint32_t set, std::uint32_t offset, std::uint32_t stride, std::uint32_t location);
    void AddOutputLayoutProperty(const std::string& name, ShaderData::Stage stage, ShaderData::Type type, std::uint32_t binding, std::uint32_t set, std::uint32_t offset, std::uint32_t stride, std::uint32_t location);
    void AddLayoutProperty(const std::string& name, bool isInput, ShaderData::Stage stage, ShaderData::Type type, std::uint32_t binding, std::uint32_t set, std::uint32_t offset, std::uint32_t stride, std::uint32_t location);
    
  public:
    //[[nodiscard]] uint32_t GetLayoutVertexStride()const;
    [[nodiscard]] VkPipeline GetPipeline()const;
    [[nodiscard]] VkPipelineLayout GetPipelineLayout()const;
    
  private:
    friend class Shader;
  
    
  };
}