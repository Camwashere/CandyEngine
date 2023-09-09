#pragma once
#include <filesystem>
#include <vulkan/vulkan.h>
#include <vector>
#include "ShaderProperty.hpp"
namespace Candy::Graphics
{
  class SpecializationConstantInput
  {
  private:
    std::string name;
    ShaderData::Type type;
    std::variant<int, float, bool> value;
    
    
  public:
    SpecializationConstantInput(const std::string& name, int value);
    SpecializationConstantInput(const std::string& name, float value);
    SpecializationConstantInput(const std::string& name, bool value);
    
    [[nodiscard]] const std::string& GetName()const;
    [[nodiscard]] ShaderData::Type GetType()const;
    [[nodiscard]] const std::variant<int, float, bool>& GetValue()const;
    
    
    
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