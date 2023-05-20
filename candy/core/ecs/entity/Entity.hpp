#pragma once
#include "../scene/Scene.hpp"
#include "../component/BaseComponents.hpp"

namespace Candy::ECS {
    class Entity {
    private:
        uint32 id;
        Scene *scene = nullptr;
    
    public:
        Entity()=default;
        Entity(uint32 entityID, Scene* scene) : id(entityID), scene(scene){}
        Entity(const Entity &other) = default;
    
    public:
        operator uint32()const{return id;}
    
    public:
        template<typename T, typename... Args>
        std::shared_ptr<T> AddComponent(Args&&... args)
        {
            return scene->registry.AddComponent<T>(id, std::forward<Args>(args)...);
        }
        template<typename T>
        T& GetComponent()
        {
            return *scene->registry.GetComponent<T>(id);
        }
        template<typename T>
        bool HasComponent()
        {
            return false;
        }
    
    public:
        UUID GetUUID(){return GetComponent<IDComponent>().id;}
        std::string GetName(){return GetComponent<NameComponent>().name;}
        void SetName(const std::string& name){GetComponent<NameComponent>().name=name;}
        
        
        
    };
}

