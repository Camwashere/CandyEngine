#include <candy/resource/Resource.hpp>

namespace Candy
{
  
  static constexpr std::vector<std::string> InitResourceTypeStrings()
  {
    std::vector<std::string> vec;
    vec.resize(static_cast<uint32_t>(ResourceType::Unknown)+1);
    vec[static_cast<uint32_t>(ResourceType::Image)]="Image";
    vec[static_cast<uint32_t>(ResourceType::Texture)]="Texture";
    vec[static_cast<uint32_t>(ResourceType::Font)]="Font";
    vec[static_cast<uint32_t>(ResourceType::Mesh)]="Mesh";
    vec[static_cast<uint32_t>(ResourceType::Shader)]="Shader";
    vec[static_cast<uint32_t>(ResourceType::Animation)]="Animation";
    vec[static_cast<uint32_t>(ResourceType::Model)]="Model";
    vec[static_cast<uint32_t>(ResourceType::Script)]="Script";
    vec[static_cast<uint32_t>(ResourceType::Scene)]="Scene";
    
    
    
    vec[static_cast<uint32_t>(ResourceType::Unknown)]="Unknown";
    
    return vec;
    
  }
  
  static std::unordered_map<std::string, ResourceType> InitExtensionAssociations()
  {
    std::unordered_map<std::string, ResourceType> map;
    map["png"]=ResourceType::Image;
    map["jpg"]=ResourceType::Image;
    map["jpeg"]=ResourceType::Image;
    map["bmp"]=ResourceType::Image;
    map["tga"]=ResourceType::Image;
    
    
    map["tex"]=ResourceType::Texture;
    
    map["ttf"]=ResourceType::Font;
    map["otf"]=ResourceType::Font;
    map["woff"]=ResourceType::Font;
    
    map["glsl"]=ResourceType::Shader;
    map["hlsl"]=ResourceType::Shader;
    map["spv"]=ResourceType::Shader;
    
    map["mesh"]=ResourceType::Mesh;
    
    map["anim"]=ResourceType::Animation;
    
    map["model"]=ResourceType::Model;
    map["fbx"]=ResourceType::Model;
    map["obj"]=ResourceType::Model;
    
    map["cs"]=ResourceType::Script;
    return map;
  }
  
  std::vector<std::string> Resource::resourceTypeStrings = InitResourceTypeStrings();
  std::unordered_map<std::string, ResourceType> Resource::extensionAssociations = InitExtensionAssociations();
  
  const std::string& Resource::TypeToString(ResourceType type)
  {
    return resourceTypeStrings[static_cast<uint32_t>(type)];
  }
  
  ResourceType Resource::TypeFromExtension(const std::string& extension)
  {
    std::string ext = extension;
    if (ext[0] == '.')
    {
      ext.erase(0, 1);
    }
    auto it = extensionAssociations.find(ext);
    if (it != extensionAssociations.end())
    {
      return it->second;
    }
    return ResourceType::Unknown;
  
  }
}