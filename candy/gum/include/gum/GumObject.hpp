#pragma once
#include "GumGraph.hpp"
#include <candy/base/Instrumentor.hpp>
#include <candy/base/Assert.hpp>
namespace Candy::Gum
{
  struct GumParent;
  struct GumChildren;
  class GumTransform;
  struct GumID;
  struct GumTag;
  
  
  class GumObject
  {
  private:
    entt::entity handle{entt::null};
    GumGraph* graph=nullptr;
    
    
  public:
    GumObject();
    GumObject(entt::entity objectHandle, GumGraph* gumGraph);
    GumObject(const GumObject &other);
    
  public:
    operator bool()const;
    operator std::uint32_t()const;
    operator entt::entity()const;
    
    bool operator==(const GumObject& other)const;
    bool operator!=(const GumObject& other)const;
    
  public:
    template<typename T, typename... Args>
    T& AddComponent(Args&&... args)
    {
      CANDY_PROFILE_FUNCTION();
      CANDY_CORE_ASSERT(!HasComponent<T>(), "Entity already has component");
      T& component = graph->registry.emplace<T>(handle, std::forward<Args>(args)...);
      graph->OnComponentAdded<T>(*this, component);
      return component;
    }
    template<typename T>
    T& GetComponent()
    {
      CANDY_PROFILE_FUNCTION();
      CANDY_CORE_ASSERT(HasComponent<T>(), "Entity does not have component");
      return graph->registry.get<T>(handle);
    }
    
    template<typename T>
    const T& GetComponent()const
    {
      CANDY_PROFILE_FUNCTION();
      CANDY_CORE_ASSERT(HasComponent<T>(), "Entity does not have component");
      return graph->registry.get<T>(handle);
    }
    template<typename T>
    [[nodiscard]] bool HasComponent()const
    {
      CANDY_PROFILE_FUNCTION();
      if (graph==nullptr)
        return false;
      return graph->registry.all_of<T>(handle);
    }
    template<typename T, typename... Args>
    T& AddOrReplaceComponent(Args&&... args)
    {
      CANDY_PROFILE_FUNCTION();
      T& component = graph->registry.emplace_or_replace<T>(handle, std::forward<Args>(args)...);
      graph->OnComponentAdded<T>(*this, component);
      return component;
    }
    template<typename T>
    void RemoveComponent()
    {
      CANDY_PROFILE_FUNCTION();
      CANDY_CORE_ASSERT(HasComponent<T>(), "Entity does not have component");
      graph->OnComponentRemoved<T>(*this, GetComponent<T>());
      graph->registry.remove<T>(handle);
    }
    
  public:
    UUID GetUUID();
    GumParent& GetParent();
    [[nodiscard]] const GumParent& GetParent()const;
    GumObject GetParentObject();
    [[nodiscard]] GumObject GetParentObject()const;
    [[nodiscard]] bool HasParent()const;
    [[nodiscard]] bool HasChildren()const;
    [[nodiscard]] bool IsParent()const;
    [[nodiscard]] bool IsChild()const;
    [[nodiscard]] bool IsRoot()const;
    [[nodiscard]] bool HasGraph()const;
    bool RemoveChild(const GumObject& child);
    bool AddChild(const GumObject& child);
    GumChildren& GetChildren();
    [[nodiscard]] const GumChildren& GetChildren()const;
    std::string GetTag();
    GumTransform& GetTransform();
    void SetParent(GumObject parent);
    void SetName(const std::string& tag);
    GumGraph* GetGraph();
    
  };
}