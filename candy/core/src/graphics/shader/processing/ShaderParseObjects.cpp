#include <candy/graphics/shader/processing/ShaderParseObjects.hpp>

namespace Candy::Graphics
{
  Utils::IDManager<uint32_t> ShaderParseObject::idManager;
  ShaderParseObject::ShaderParseObject() : id(idManager.Assign())
  {
  
  }
  
  ShaderParseObject::ShaderParseObject(const ShaderParseObject& other) : id(other.id)
  {
  
  }
  
  bool ShaderParseObject::IsValid()const{return id>0;}
  uint32_t ShaderParseObject::GetID()const{return id;}
  
  
  bool ShaderObjectLayout::HasAttribute()const
  {
    return !attribute.empty();
  }
  bool ShaderObjectLayout::HasLocation()const
  {
    return location!=-1;
  }
  bool ShaderObjectLayout::HasBinding()const
  {
    return binding!=-1;
  }
  bool ShaderObjectLayout::HasSet()const
  {
    return set!=-1;
  }
  ShaderObjectLayout::ShaderObjectLayout(const std::vector<LayoutQualifier>& layoutQualifiers)
  {
    for (const auto& qualifier : layoutQualifiers)
    {
      if (qualifier.name == "location")
      {
        location = std::stoi(qualifier.value);
      }
      else if (qualifier.name == "binding")
      {
        binding = std::stoi(qualifier.value);
      }
      else if (qualifier.name == "set")
      {
        set = std::stoi(qualifier.value);
      }
      else if (qualifier.name == "attribute")
      {
        attribute = qualifier.value;
      }
    }
    
  }
  std::string ShaderObjectLayout::ToString()const
  {
    std::string result = "";
    if (HasAttribute())
    {
      result += "Attribute: " + attribute + ' ';
    }
    if (HasBinding())
    {
      result += "Binding: " + std::to_string(binding) + ' ';
    }
    if (HasSet())
    {
      result += "Set: " + std::to_string(set) + ' ';
    }
    if (HasLocation())
    {
      result += "Location: " + std::to_string(location) + ' ';
    }
    return result;
    
    
  }
}