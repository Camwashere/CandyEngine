#pragma once
#include <filesystem>
#include <vulkan/vulkan.h>
#include <utility>
#include <vector>
#include "candy/graphics/shader/ShaderProperty.hpp"
#include "candy/collections/GenericBuffer.hpp"
#include "candy/graphics/RenderCommand.hpp"
#include <candy/graphics/shader/config/ShaderProfile.hpp>
namespace Candy::Graphics
{
  /*class SpecializationConstantInput
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
  
  enum class CullMode
  {
    NONE=0,
    FRONT,
    BACK,
    BOTH,
  };
  struct DepthBiasSettings
  {
    bool enable=false;
    float constantFactor=0.0f;
    float slopeFactor=0.0f;
  };
  struct PipelineConfigSettings
  {
    RenderMode renderMode=RenderMode::Shaded;
    TopologyType topologyType=TopologyType::TRIANGLE;
    CullMode cullMode = CullMode::BACK;
    DepthBiasSettings depthBiasSettings{};
    std::vector<SpecializationConstantInput> constantInputs{};
    
  };
  struct ShaderConfigSettings
  {
    PipelineType pipelineType=PipelineType::Graphics;
    
    bool depthTesting=true;
    bool alphaColorBlending=false;
    std::vector<VkDynamicState> dynamicStates{};
  };*/
  
  struct ShaderSettings
  {
    std::filesystem::path sourceFilePath;
    ShaderProfileSettings profileSettings;
    std::vector<ShaderConfigurationSettings> configs;
    
    
    
  };
  /*struct ShaderSettings
  {
    
    std::filesystem::path filepath;
    ShaderConfigSettings profileSettings;
    std::vector<PipelineConfigSettings> configs;
    uint8_t renderPassIndex=0;
    
    
    
    
    
    static VkPipelineBindPoint PipelineTypeToVulkan(PipelineType value);
    static VkPrimitiveTopology  TopologyToVulkan(TopologyType value);
    static VkPolygonMode RenderModeToVulkan(RenderMode value);
    static VkCullModeFlags CullModeToVulkan(CullMode value);
    
  };*/
}