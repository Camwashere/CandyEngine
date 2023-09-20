#pragma once
#include <filesystem>
#include <vulkan/vulkan.h>
#include <utility>
#include <vector>
#include "ShaderProperty.hpp"
#include <candy/collections/GenericBuffer.hpp>
namespace Candy::Graphics
{
  class SpecializationConstantInput
  {
  private:
    std::string name;
    ShaderData::Type type;
    Collections::GenericBuffer value;
    
    
    
  public:
    template<typename T>
    SpecializationConstantInput(std::string  constantName, T constantValue) : name(std::move(constantName)), type(ShaderData::TypeFrom<T>())
    {
      size_t size = ShaderData::TypeSize(type);
      CANDY_CORE_ASSERT(size > 0, "INVALID SPECIALIZATION CONSTANT TYPE");
      value.Add(constantValue);
    }
    
    
    
    
    [[nodiscard]] const std::string& GetName()const;
    [[nodiscard]] ShaderData::Type GetType()const;
    [[nodiscard]] const Collections::GenericBuffer& GetValue()const;
    [[nodiscard]] size_t GetSize()const;
    
    
    
  };
  struct ShaderSettings
  {
    enum class PipelineType
    {
      None=0,
      Graphics,
      Compute,
      RayTracing,
    };
    enum class TopologyType
    {
      TRIANGLE,
      LINE,
      LINE_STRIP,
      POINT
    };
    enum class PolygonType
    {
      FILL,
      LINE,
      POINT,
    };
    enum class CullMode
    {
      NONE=0,
      FRONT,
      BACK,
      BOTH,
    };
    std::filesystem::path filepath;
    uint8_t renderPassIndex;
    PipelineType pipelineType=PipelineType::Graphics;
    TopologyType topologyType=TopologyType::TRIANGLE;
    PolygonType polygonType = PolygonType::FILL;
    CullMode cullMode = CullMode::BACK;
    float lineWidth=1.0f;
    
    bool depthTesting=true;
    bool alphaColorBlending=false;
    std::vector<VkDynamicState> dynamicStates{};
    std::vector<SpecializationConstantInput> constantInputs{};
    
    static VkPipelineBindPoint PipelineTypeToVulkan(PipelineType value);
    static VkPrimitiveTopology  TopologyToVulkan(TopologyType value);
    static VkPolygonMode PolygonToVulkan(PolygonType value);
    static VkCullModeFlags CullModeToVulkan(CullMode value);
    
  };
}