#pragma once
//#include "BaseComponents.hpp"
#include "Scene.hpp"
#include <entt/entt.hpp>
namespace Candy::ECS
{
  struct TagComponent;
  struct IDComponent;
  class TransformComponent;
  struct ParentComponent;
  struct ChildrenComponent;
  
  class Entity {
  private:
    entt::entity handle{entt::null};
    Scene* scene=nullptr;
    
  public:
    Entity();
    Entity(entt::entity entityID, Scene* parentScene);
    Entity(const Entity &other);
    
  
  public:
    operator bool()const;
    operator std::uint32_t()const;
    operator entt::entity()const;
    
    bool operator==(const Entity& other)const;
    bool operator!=(const Entity& other)const;
    
  
  public:
    template<typename T, typename... Args>
    T& AddComponent(Args&&... args)
    {
      CANDY_PROFILE_FUNCTION();
      CANDY_CORE_ASSERT(!HasComponent<T>(), "Entity already has component");
      T& component = scene->registry.emplace<T>(handle, std::forward<Args>(args)...);
      scene->OnComponentAdded(*this, component);
      return component;
    }
    template<typename T>
    T& GetComponent()
    {
      CANDY_PROFILE_FUNCTION();
      CANDY_CORE_ASSERT(HasComponent<T>(), "Entity does not have component");
      return scene->registry.get<T>(handle);
    }
    
    template<typename T>
    const T& GetComponent()const
    {
      CANDY_PROFILE_FUNCTION();
      CANDY_CORE_ASSERT(HasComponent<T>(), "Entity does not have component");
      return scene->registry.get<T>(handle);
    }
    template<typename T>
    [[nodiscard]] bool HasComponent()const
    {
      CANDY_PROFILE_FUNCTION();
      if (scene==nullptr)
        return false;
      return scene->registry.all_of<T>(handle);
    }
    template<typename T, typename... Args>
    T& AddOrReplaceComponent(Args&&... args)
    {
      CANDY_PROFILE_FUNCTION();
      T& component = scene->registry.emplace_or_replace<T>(handle, std::forward<Args>(args)...);
      scene->OnComponentAdded<T>(*this, component);
      return component;
    }
    template<typename T>
    void RemoveComponent()
    {
      CANDY_PROFILE_FUNCTION();
      CANDY_CORE_ASSERT(HasComponent<T>(), "Entity does not have component");
      scene->registry.remove<T>(handle);
    }
  
  public:
    
    UUID GetUUID();
    std::string GetTag();
    ParentComponent& GetParent();
    const ParentComponent& GetParent()const;
    Entity GetParentEntity();
    Entity GetParentEntity()const;
    [[nodiscard]] bool HasParent()const;
    [[nodiscard]] bool HasChildren()const;
    [[nodiscard]] bool IsParent()const;
    [[nodiscard]] bool IsChild()const;
    [[nodiscard]] bool IsRoot()const;
    [[nodiscard]] bool HasScene()const;
    bool RemoveChild(const Entity& child);
    bool AddChild(const Entity& child);
    ChildrenComponent& GetChildren();
    const ChildrenComponent& GetChildren()const;
    [[nodiscard]] bool Is2D()const;
    TransformComponent& GetTransform();
    void SetParent(Entity parent);
    void SetName(const std::string& tag);
    Scene* GetScene();
    
    
    
    
  };
}