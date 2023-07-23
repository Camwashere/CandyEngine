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
}