#pragma once
#include "ShaderData.hpp"
#include "../UniformBuffer.hpp"
namespace Candy::Graphics
{
  // Responsible for automatically creating descriptor sets
  struct ShaderProperty
  {
    std::string name;
    uint32_t id;
    ShaderData::Type type;
    std::uint32_t binding;
    std::uint32_t set;
    std::uint32_t offset;
    std::uint32_t size;
    
    [[nodiscard]] std::string ToString()const;
    
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
  public:
    uint32_t layoutVertexStride;
    UniquePtr<UniformBuffer> uniformBuffer;
    std::unordered_map<std::string, uint32_t> propertyMap;
    std::vector<ShaderPushConstantBlockProperty> pushConstantBlockProperties;
    std::vector<ShaderUniformBlockProperty> uniformBlockProperties;
    std::vector<ShaderUniformImageProperty> uniformImageProperties;
    std::vector<ShaderLayoutProperty> inputLayoutProperties;
    std::vector<ShaderLayoutProperty> outputLayoutProperties;
    
  public:
    void CalculateOffsetsAndStride();
    size_t MaxSetCount()const;
    //std::vector<VkDescriptorSetLayout> GetDescriptorSetLayouts();
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
    [[nodiscard]] uint32_t GetLayoutVertexStride()const;
  
    
  };
}