#pragma once
#include "../component/BaseComponents.hpp"
#include "../scene/Scene.hpp"
#include <entt/entt.hpp>
namespace Candy::ECS {
    
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
            T& component = scene->registry.emplace<T>(handle, std::forward<Args>(args)...);
            //scene->OnComponentAdded(*this, component);
            return component;
            //return scene->registry.AddComponent<T>(handle, std::forward<Args>(args)...);
        }
        template<typename T>
        T& GetComponent()
        {
            return scene->registry.get<T>(handle);
            //return scene->registry.GetComponent<T>(handle);
        }
        template<typename T>
        bool HasComponent()
        {
            return scene->registry.all_of<T>(handle);
            
            //return scene->registry.HasComponent<T>(handle);
            
        }
        template<typename T, typename... Args>
        T& AddOrReplaceComponent(Args&&... args)
        {
            T& component = scene->registry.emplace_or_replace<T>(handle, std::forward<Args>(args)...);
            //scene->OnComponentAdded<T>(*this, component);
            return component;
        }
        template<typename T>
        void RemoveComponent()
        {
            scene->registry.remove<T>(handle);
            //CANDY_CORE_ASSERT(HasComponent<T>(), "Entity does not have component");
            //scene->registry.RemoveComponent<T>(handle);
        }
    
    public:
        UUID GetUUID(){return GetComponent<IDComponent>().id;}
        std::string GetName(){return GetComponent<NameComponent>().name;}
        void SetName(const std::string& name){GetComponent<NameComponent>().name=name;}
        
        
        
    };
}

