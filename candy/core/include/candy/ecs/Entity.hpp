#pragma once
#include "BaseComponents.hpp"
#include "Scene.hpp"
#include <entt/entt.hpp>
namespace Candy::ECS
{
  class Entity {
  private:
    entt::entity handle{entt::null};
    Scene* scene=nullptr;
  
  public:
    Entity()=default;
    Entity(entt::entity entityID, Scene* parentScene) : handle(entityID), scene(parentScene){}
    Entity(const Entity &other)=default;
  
  public:
    operator bool()const{return handle!=entt::null;}
    operator std::uint32_t()const{return (std::uint32_t)handle;}
    operator entt::entity()const{return handle;}
    
    bool operator==(const Entity& other)const
    {
      return handle==other.handle && scene==other.scene;
    }
    bool operator!=(const Entity& other)const
    {
      return !(*this==other);
    }
  
  public:
    template<typename T, typename... Args>
    T& AddComponent(Args&&... args)
    {
      CANDY_CORE_ASSERT(!HasComponent<T>(), "Entity already has component");
      T& component = scene->registry.emplace<T>(handle, std::forward<Args>(args)...);
      scene->OnComponentAdded(*this, component);
      return component;
    }
    template<typename T>
    T& GetComponent()
    {
      CANDY_CORE_ASSERT(HasComponent<T>(), "Entity does not have component");
      return scene->registry.get<T>(handle);
      //return scene->registry.GetComponent<T>(handle);
    }
    template<typename T>
    bool HasComponent()
    {
      return scene->registry.all_of<T>(handle);
    }
    template<typename T, typename... Args>
    T& AddOrReplaceComponent(Args&&... args)
    {
      T& component = scene->registry.emplace_or_replace<T>(handle, std::forward<Args>(args)...);
      scene->OnComponentAdded<T>(*this, component);
      return component;
    }
    template<typename T>
    void RemoveComponent()
    {
      CANDY_CORE_ASSERT(HasComponent<T>(), "Entity does not have component");
      scene->registry.remove<T>(handle);
    }
  
  public:
    UUID GetUUID(){return GetComponent<IDComponent>().id;}
    std::string GetTag(){return GetComponent<TagComponent>().tag;}
    TransformComponent& GetTransform(){return GetComponent<TransformComponent>();}
    void SetName(const std::string& tag){GetComponent<TagComponent>().tag=tag;}
    
    
    
  };
}