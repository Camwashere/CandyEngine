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
  
  
  std::string InternalResource::ResourceTypeToString(ResourceType type)
  {
    switch (type)
    {
      case ResourceType::Image:
        return "Image";
      case ResourceType::Texture:
        return "Texture";
      case ResourceType::Font:
        return "Font";
      case ResourceType::Shader:
        return "Shader";
      case ResourceType::Mesh:
        return "Mesh";
      case ResourceType::Script:
        return "Script";
      case ResourceType::Scene:
        return "Scene";
      default:
        return "Unknown";
    }
  }
  
 
}