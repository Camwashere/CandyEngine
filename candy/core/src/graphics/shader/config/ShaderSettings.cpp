#include "candy/graphics/shader/config/ShaderSettings.hpp"
#include "CandyPch.hpp"
namespace Candy::Graphics
{
  
  
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
  

}