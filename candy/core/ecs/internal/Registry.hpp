#pragma once

#include "EntityManager.hpp"
#include "ComponentManager.hpp"
#include "SystemManager.hpp"
#include <ranges>
namespace Candy::ECS::Internal {
    
    class Registry {
    private:
        std::unique_ptr<EntityManager> entityManager;
        std::unique_ptr<ComponentManager> componentManager;
        std::unique_ptr<SystemManager> systemManager;
    
    public:
        Registry()
        {
            entityManager = std::make_unique<EntityManager>();
            componentManager = std::make_unique<ComponentManager>();
            systemManager = std::make_unique<SystemManager>();
        }
    
    public:
        uint32 CreateEntity(){return entityManager->CreateEntity();}
        void DestroyEntity(uint32 entity)
        {
            entityManager->DestroyEntity(entity);
            componentManager->EntityDestroyed(entity);
            entityManager->DestroyEntity(entity);
        }
        
        template<typename T>
        std::vector<uint32> GetEntitiesWith()
        {
            auto map = componentManager->GetIndexToEntityMap<T>();
            std::vector<uint32> entities;
            for (const auto&[key, value] : map)
            {
                entities.push_back(value);
            }
            return entities;
        }
        template<typename T>
        auto GetEntityPairs()
        {
        
        }
        
        template<typename T, typename...Args>
        std::shared_ptr<T> AddComponent(uint32 entity, Args&&... args)
        {
            
            auto component =  componentManager->AddComponent<T>(entity, std::forward<Args>(args)...);
            auto signature = entityManager->GetSignature(entity);
            signature.set(componentManager->GetComponentType<T>(), true);
            entityManager->SetSignature(entity, signature);
            systemManager->EntitySignatureChanged(entity, signature);
            return component;
        }
        
        template<typename T>
        void RemoveComponent(uint32 entity)
        {
            componentManager->RemoveComponent<T>(entity);
            
            auto signature = entityManager->GetSignature(entity);
            signature.set(componentManager->GetComponentType<T>(), false);
            entityManager->SetSignature(entity, signature);
            
            systemManager->EntitySignatureChanged(entity, signature);
        }
        
        template<typename T>
        SharedPtr<T> GetComponent(uint32 entity)
        {
            return componentManager->GetComponent<T>(entity);
        }
        
        template<typename T>
        ComponentType GetComponentType()
        {
            return componentManager->GetComponentType<T>();
        }
        
        
        
        
        
        
    };
}

