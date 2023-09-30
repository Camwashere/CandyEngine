#include <gum/GumGraph.hpp>
#include "CandyPch.hpp"
#include <gum/GumObject.hpp>
#include <gum/GumComponents.hpp>
namespace Candy::Gum
{
  
  template<typename... Component>
  static void CopyComponent(entt::registry& dst, entt::registry& src, const std::unordered_map<UUID, entt::entity>& enttMap)
  {
    CANDY_PROFILE_FUNCTION();
    ([&]()
    {
    auto view = src.view<Component>();
    for (auto srcEntity : view)
    {
      entt::entity dstEntity = enttMap.at(src.get<GumID>(srcEntity).id);
      
      auto& srcComponent = src.get<Component>(srcEntity);
      dst.emplace_or_replace<Component>(dstEntity, srcComponent);
    }
    }(), ...);
  }
  
  template<typename... Component>
  static void CopyComponent(GumComponentGroup<Component...>, entt::registry& dst, entt::registry& src, const std::unordered_map<UUID, entt::entity>& enttMap)
  {
    CopyComponent<Component...>(dst, src, enttMap);
  }
  
  template<typename... Component>
  static void CopyComponentIfExists(GumObject dst, GumObject src)
  {
    CANDY_PROFILE_FUNCTION();
    ([&]()
    {
    if (src.HasComponent<Component>())
      dst.AddOrReplaceComponent<Component>(src.GetComponent<Component>());
    }(), ...);
  }
  
  template<typename... Component>
  static void CopyComponentIfExists(GumComponentGroup<Component...>, GumObject dst, GumObject src)
  {
    CopyComponentIfExists<Component...>(dst, src);
  }
  
  
  GumGraph::GumGraph(const std::string& graphName) : name(graphName)
  {
  
  }
  
  GumObject GumGraph::CreateObject(const std::string &tag)
  {
    CANDY_PROFILE_FUNCTION();
    return CreateObjectWithUUID(UUID(), tag);
  }
  GumObject GumGraph::CreateObjectWithUUID(UUID uuid, const std::string&tag)
  {
    CANDY_PROFILE_FUNCTION();
    GumObject object = { registry.create(), this };
    object.AddComponent<GumID>(uuid);
    auto& tc = object.AddComponent<GumTag>();
    tc.tag = tag.empty() ? "Object" : tag;
    object.AddComponent<GumTransform>(object);
    
    objectMap[uuid] = object;
    
    return object;
  }
  void GumGraph::DestroyObject(GumObject object)
  {
    CANDY_PROFILE_FUNCTION();
    
    objectMap.erase(object.GetUUID());
    registry.destroy(object);
  }
  void GumGraph::DestroyObjectTree(GumObject parent)
  {
    MarkForDelete(parent);
    for (auto& e : deletionQueue)
    {
      DestroyObject(e);
    }
    
    //AppendUpdateFlag(SceneUpdateFlag::Meshes3D);
    deletionQueue.clear();
  }
  
  void GumGraph::MarkForDelete(GumObject object)
  {
    CANDY_PROFILE_FUNCTION();
    deletionQueue.push_back(object);
    
    if (object.HasChildren())
    {
      auto& children = object.GetChildren().children;
      for (auto& child : children)
      {
        MarkForDelete(child);
      }
    }
  }
  GumObject GumGraph::DuplicateObject(GumObject original)
  {
    if (original.HasParent() or original.HasChildren())
    {
      CANDY_CORE_INFO("OR WORKING IN C++");
    }
    CANDY_PROFILE_FUNCTION();
    // Copy name because we're going to modify component data structure
    std::string tag = original.GetTag();
    GumObject clone = CreateObject(tag);
    CopyComponentIfExists(AllGumComponents{}, clone, original);
    return clone;
  }
  
  
  void GumGraph::OnUpdate()
  {
  
  }
  
  void GumGraph::OnEvent(Events::Event& event)
  {
  
  }
  
  
  GumObject GumGraph::FindObjectByTag(std::string_view tag)
  {
    CANDY_PROFILE_FUNCTION();
    auto view = registry.view<GumTag>();
    for (auto object : view)
    {
      const GumTag& tc = view.get<GumTag>(object);
      if (tc.tag == tag)
        return GumObject{ object, this };
    }
    return {};
  }
  GumObject GumGraph::GetObjectByUUID(UUID uuid)
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_ASSERT(objectMap.find(uuid) != objectMap.end(), "Object not found in registry");
    return { objectMap.at(uuid), this };
  }
  
  std::string GumGraph::GetName()const
  {
    return name;
  }
}