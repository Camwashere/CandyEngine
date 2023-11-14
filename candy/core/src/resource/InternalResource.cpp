#include <candy/resource/InternalResource.hpp>
#include <utility>

namespace Candy
{
  InternalResource::InternalResource(uint32_t id, ResourceType type, std::filesystem::path  path) : id(id), type(type), path(std::move(path))
  {
  
  }
  
  uint32_t InternalResource::GetID()const{return id;}
  ResourceType InternalResource::GetType()const{return type;}
  const std::filesystem::path& InternalResource::GetPath()const{return path;}
  
  
  
 
}