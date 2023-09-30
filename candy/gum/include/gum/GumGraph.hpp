#pragma once
#include <entt/entt.hpp>
#include <candy/base/UUID.hpp>
#include <candy/event/Events.hpp>
#include <unordered_map>
namespace Candy::Gum
{
  class GumObject;
  
  class GumGraph
  {
  private:
    entt::registry registry;
    std::unordered_map<UUID, GumObject> objectMap;
    std::vector<GumObject> deletionQueue;
    std::string name;
    
  private:
    void MarkForDelete(GumObject object);
    
  public:
    explicit GumGraph(const std::string& graphName);
    
  public:
    template<typename T>
    void OnComponentAdded(GumObject& object, T& component);
    
    template<typename T>
    void OnComponentRemoved(GumObject& object, T& component);
    
  public:
    GumObject CreateObject(const std::string &tag = std::string());
    GumObject CreateObjectWithUUID(UUID uuid, const std::string&tag=std::string());
    void DestroyObject(GumObject entity);
    void DestroyObjectTree(GumObject parent);
    GumObject DuplicateObject(GumObject entity);
    GumObject FindObjectByTag(std::string_view tag);
    GumObject GetObjectByUUID(UUID uuid);
    [[nodiscard]] std::string GetName()const;
    
  public:
    void OnUpdate();
    void OnEvent(Events::Event& event);
    
    
    
  private:
    friend class GumObject;
  };
  
  template<typename T>
  inline void GumGraph::OnComponentAdded(GumObject& object, T& component){}
  template<typename T>
  inline void GumGraph::OnComponentRemoved(GumObject& object, T& component){}
}