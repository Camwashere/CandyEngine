#include <candy/graphics/shader/ShaderLayout.hpp>

namespace Candy::Graphics
{
  void ShaderLayout::AddInputLayoutProperty(const std::string& name, ShaderData::Type type, std::uint32_t binding, std::uint32_t set, std::uint32_t offset, std::uint32_t stride, std::uint32_t location)
  {
    AddLayoutProperty(name, true, type, binding, set, offset, stride, location);
  }
  void ShaderLayout::AddOutputLayoutProperty(const std::string& name, ShaderData::Type type, std::uint32_t binding, std::uint32_t set, std::uint32_t offset, std::uint32_t stride, std::uint32_t location)
  {
    AddLayoutProperty(name, false, type, binding, set, offset, stride, location);
  }
  void ShaderLayout::AddLayoutProperty(const std::string& name, bool isInput, ShaderData::Type type, std::uint32_t binding, std::uint32_t set, std::uint32_t offset, std::uint32_t stride, std::uint32_t location)
  {
    layoutProperties.push_back({name, type, binding, set, offset, stride, location, isInput});
  
  }

}