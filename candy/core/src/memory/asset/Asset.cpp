#include "candy/memory/asset/Asset.hpp"

namespace Candy
{
  
  Asset::Asset(uint32_t id, AssetType type, std::filesystem::path  path) : id(id), type(type), path(path), refCount(0)
  {
  
  }
  
  uint32_t Asset::GetID()const{return id;}
  AssetType Asset::GetType()const{return type;}
  const std::filesystem::path& Asset::GetPath()const{return path;}
  
  uint32_t Asset::GetRefCount()const
  {
    return refCount;
  }
  void Asset::AddRef()
  {
    refCount++;
  }
  void Asset::FreeRef()
  {
    refCount--;
  }
  
  static constexpr std::vector<std::string> InitResourceTypeStrings()
  {
    std::vector<std::string> vec;
    vec.resize(static_cast<uint32_t>(AssetType::Unknown)+1);
    vec[static_cast<uint32_t>(AssetType::Image)]="Image";
    vec[static_cast<uint32_t>(AssetType::Texture)]="Texture";
    vec[static_cast<uint32_t>(AssetType::Font)]="Font";
    vec[static_cast<uint32_t>(AssetType::Mesh)]="Mesh";
    vec[static_cast<uint32_t>(AssetType::Shader)]="Shader";
    vec[static_cast<uint32_t>(AssetType::Animation)]="Animation";
    vec[static_cast<uint32_t>(AssetType::Model)]="Model";
    vec[static_cast<uint32_t>(AssetType::Script)]="Script";
    vec[static_cast<uint32_t>(AssetType::Scene)]="Scene";
    
    
    
    vec[static_cast<uint32_t>(AssetType::Unknown)]="Unknown";
    
    return vec;
    
  }
  
  static std::unordered_map<std::string, AssetType> InitExtensionAssociations()
  {
    std::unordered_map<std::string, AssetType> map;
    map["png"]=AssetType::Image;
    map["jpg"]=AssetType::Image;
    map["jpeg"]=AssetType::Image;
    map["bmp"]=AssetType::Image;
    map["tga"]=AssetType::Image;
    
    
    map["tex"]=AssetType::Texture;
    
    map["ttf"]=AssetType::Font;
    map["otf"]=AssetType::Font;
    map["woff"]=AssetType::Font;
    
    map["glsl"]=AssetType::Shader;
    map["hlsl"]=AssetType::Shader;
    map["spv"]=AssetType::Shader;
    
    map["mesh"]=AssetType::Mesh;
    
    map["anim"]=AssetType::Animation;
    
    map["model"]=AssetType::Model;
    map["fbx"]=AssetType::Model;
    map["obj"]=AssetType::Model;
    
    map["cs"]=AssetType::Script;
    return map;
  }
  
  std::vector<std::string> Asset::assetTypeStrings = InitResourceTypeStrings();
  std::unordered_map<std::string, AssetType> Asset::extensionAssociations = InitExtensionAssociations();
  
  const std::string& Asset::TypeToString(AssetType type)
  {
    return assetTypeStrings[static_cast<uint32_t>(type)];
  }
  
  AssetType Asset::TypeFromExtension(const std::string& extension)
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
    return AssetType::Unknown;
  
  }
}