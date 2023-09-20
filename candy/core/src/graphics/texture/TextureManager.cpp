#include "candy/graphics/texture/TextureManager.hpp"
#include <filesystem>
#include <unordered_map>


#include "CandyPch.hpp"
#include "candy/utils/IDManager.hpp"
namespace Candy::Graphics
{
  using namespace Utils;
  struct TextureManagerData
  {
    std::unordered_map<std::string, uint32_t> fileToIDMap;
    std::unordered_map<uint32_t, InternalTexture> textures;
    IDManager<uint32_t> idManager;
    uint32_t whiteTextureID=0;
    bool initialized=false;
  };
  static TextureManagerData data;
  
  InternalTexture* TextureManager::GetInternalTexture(uint32_t id)
  {
    CANDY_PROFILE_FUNCTION();
    auto it = data.textures.find(id);
    if (it != data.textures.end())
    {
      return &it->second;
    }
    else
    {
      CANDY_CORE_WARN("Cannot get internal texture, id: {0} is not valid!", id);
      return nullptr;
    }
  }
  
  static uint32_t RegisterTexture(const std::filesystem::path& path)
  {
    CANDY_PROFILE_FUNCTION();
    uint32_t id = data.idManager.Assign();
    data.fileToIDMap[path.string()] = id;
    CANDY_CORE_ASSERT(data.textures.find(id) == data.textures.end(), "Cannot register texture, id already exists!");
    data.textures.emplace(std::piecewise_construct,
                          std::forward_as_tuple(id),
                          std::forward_as_tuple(path));
    
    return id;
  }
  
  
  void TextureManager::Init()
  {
    CANDY_PROFILE_FUNCTION();
    data.initialized=true;
    Math::Vector2u size{1, 1};
    ImageFormat format = ImageFormat::RGBA8;
    uint32_t whiteTextureID = AssignTextureID(format, size);
    uint32_t whiteTextureData = 0xffffffff;
    InternalTexture* internal = GetInternalTexture(whiteTextureID);
    CANDY_CORE_ASSERT(internal != nullptr);
    internal->SetData(&whiteTextureData, sizeof(uint32_t));
  }
  
  void TextureManager::Shutdown()
  {
  
  }
  
  uint32_t TextureManager::AssignEmptyTextureID()
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_ASSERT(data.initialized);
    auto it = data.textures.find(data.whiteTextureID);
    CANDY_CORE_ASSERT(it != data.textures.end(), "Cannot assign empty texture id, white texture id does not exist!");
    it->second.AddRef();
    return data.whiteTextureID;
  }
  
  
  
  void TextureManager::FreeTextureID(uint32_t id)
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_ASSERT(data.initialized);
    
    
    auto it = data.textures.find(id);
    
    if (it == data.textures.end())
    {
      //CANDY_CORE_WARN("Cannot free texture id: {0}, id is not valid!", id);
      return;
    }
    
    
    int64_t count = it->second.RemoveRef();
    if (count > 0)
    {
      //CANDY_CORE_INFO("Texture id: {0} has {1} references left!", id, count);
      return;
    }
    else
    {
      
      //CANDY_CORE_INFO("Texture id: {0} has no more references left! ({1}) Deleting texture", id, count);
    }
    
    if (it->second.HasPath())
    {
      auto fileIt = data.fileToIDMap.find(it->second.GetPath().string());
      //CANDY_CORE_ASSERT(fileIt != data.fileToIDMap.end());
      data.fileToIDMap.erase(fileIt);
    }
    //CANDY_CORE_INFO("Erasing internal texture id: {0}", id);
    data.textures.erase(it);
    data.idManager.Free(id);
    //CANDY_CORE_INFO("Removed internal texture id: {0}", id);
    
  }
  uint32_t TextureManager::AssignTextureID(const std::filesystem::path& path)
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_ASSERT(std::filesystem::exists(path));
    
    auto itPath = data.fileToIDMap.find(path.string());
    if(itPath != data.fileToIDMap.end())
    {
      auto it = data.textures.find(itPath->second);
      CANDY_CORE_ASSERT(it != data.textures.end(), fmt::format("Texture id is not valid for path: {}. Cannot assign texture id!", path.string()));
      it->second.AddRef();
      return it->first;
    }
    else
    {
      uint32_t id = RegisterTexture(path);
      return id;
    }
  }
  
  uint32_t TextureManager::AssignTextureID(const ImageFormat& format, const Math::Vector2u& size)
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_ASSERT(format.Valid(), "Cannot assign texture id, Invalid image format!");
    uint32_t id = data.idManager.Assign();
    CANDY_CORE_ASSERT(data.textures.find(id) == data.textures.end(), "Cannot assign texture id. Custom format and size texture id already exists!");
    auto placed = data.textures.emplace(std::piecewise_construct,
                                        std::forward_as_tuple(id),
                                        std::forward_as_tuple(format, size));
    CANDY_CORE_ASSERT(placed.second, "Failed to emplace texture in map!");
    placed.first->second.AddRef();
    
    return id;
  }
}