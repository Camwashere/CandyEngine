#pragma once
#include "ShaderData.hpp"
#include "../UniformBuffer.hpp"
namespace Candy::Graphics
{
  // Responsible for automatically creating descriptor sets
  struct ShaderProperty
  {
    std::string name;
    ShaderData::Type type;
    std::uint32_t binding;
    std::uint32_t set;
    std::uint32_t offset;
    std::uint32_t size;
    
  };
  // Responsible for pipelines vertex input info and vertex binding info replacements
  struct ShaderLayoutProperty
  {
  
    std::string name;
    ShaderData::Type type;
    std::uint32_t binding;
    std::uint32_t set;
    std::uint32_t offset;
    std::uint32_t stride;
    std::uint32_t location;
    bool input;

  };
  class ShaderLayout
  {
  private:
    UniquePtr<UniformBuffer> uniformBuffer;
    std::unordered_map<std::string, uint32_t> propertyMap;
    std::vector<ShaderProperty> properties;
    std::vector<ShaderLayoutProperty> layoutProperties;
    
  public:
    void AddInputLayoutProperty(const std::string& name, ShaderData::Type type, std::uint32_t binding, std::uint32_t set, std::uint32_t offset, std::uint32_t stride, std::uint32_t location);
    void AddOutputLayoutProperty(const std::string& name, ShaderData::Type type, std::uint32_t binding, std::uint32_t set, std::uint32_t offset, std::uint32_t stride, std::uint32_t location);
    void AddLayoutProperty(const std::string& name, bool isInput, ShaderData::Type type, std::uint32_t binding, std::uint32_t set, std::uint32_t offset, std::uint32_t stride, std::uint32_t location);
  
    
  };
}