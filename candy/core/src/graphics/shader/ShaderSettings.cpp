#include <candy/graphics/shader/ShaderSettings.hpp>
#include <CandyPch.hpp>
namespace Candy::Graphics
{
  /*SpecializationConstantInput::SpecializationConstantInput(const std::string& name, int value)
  {
    this->name = name;
    this->type = ShaderData::Type::Int;
    this->value = value;
  }
  SpecializationConstantInput::SpecializationConstantInput(const std::string& name, float value)
  {
    this->name = name;
    this->type = ShaderData::Type::Float;
    this->value = value;
  }
  SpecializationConstantInput::SpecializationConstantInput(const std::string& name, bool value)
  {
    this->name = name;
    this->type = ShaderData::Type::Bool;
    this->value = value;
  }*/
  
  const std::string& SpecializationConstantInput::GetName()const
  {
    return name;
  }
  ShaderData::Type SpecializationConstantInput::GetType()const
  {
    return type;
  }
  const Collections::GenericBuffer& SpecializationConstantInput::GetValue()const
  {
    return value;
  }
  size_t SpecializationConstantInput::GetSize()const
  {
    return value.Size();
  }
  
  
  
  
  VkPrimitiveTopology  ShaderSettings::TopologyToVulkan(TopologyType value)
  {
    switch (value)
    {
      case TopologyType::TRIANGLE:
        return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
      case TopologyType::LINE:
        return VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
      case TopologyType::LINE_STRIP:
        return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;
      case TopologyType::POINT:
        return VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
      default:
        CANDY_CORE_ASSERT(false, "INVALID TOPOLOGY TYPE");
        return (VkPrimitiveTopology)0;
    }
  }
  
  VkPipelineBindPoint ShaderSettings::PipelineTypeToVulkan(PipelineType value)
  {
    switch(value)
    {
      case PipelineType::Graphics:
        return VK_PIPELINE_BIND_POINT_GRAPHICS;
      case PipelineType::Compute:
        return VK_PIPELINE_BIND_POINT_COMPUTE;
      default:
        CANDY_CORE_ASSERT(false, "Invalid pipeline type!");
        return (VkPipelineBindPoint)0;
      
    }
  }
  
  VkPolygonMode ShaderSettings::RenderModeToVulkan(RenderMode value)
  {
    switch (value)
    {
      case RenderMode::Shaded:
        return VK_POLYGON_MODE_FILL;
      case RenderMode::Wireframe:
        return VK_POLYGON_MODE_LINE;
      case RenderMode::Point:
        return VK_POLYGON_MODE_POINT;
      default:
        CANDY_CORE_ASSERT(false, "INVALID POLYGON TYPE");
        return (VkPolygonMode)0;
    }
  }
  
  VkCullModeFlags ShaderSettings::CullModeToVulkan(CullMode value)
  {
    switch (value)
    {
      case CullMode::BACK:
        return VK_CULL_MODE_BACK_BIT;
      case CullMode::FRONT:
        return VK_CULL_MODE_FRONT_BIT;
      case CullMode::BOTH:
        return VK_CULL_MODE_FRONT_AND_BACK;
      default:
        CANDY_CORE_ASSERT(false, "INVALID CULL MODE");
        return (VkCullModeFlags)0;
    }
    
  }
}