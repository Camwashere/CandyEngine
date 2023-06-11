#pragma once

#include "EntityManager.hpp"
#include "ComponentManager.hpp"
#include "SystemManager.hpp"
#include <ranges>
namespace Candy::ECS::Internal {
    
    class Registry {
    private:
        EntityManager* entityManager;
        ComponentManager* componentManager;
        SystemManager* systemManager;
    
    public:
        Registry()
        {
            entityManager = new EntityManager();
            componentManager = new ComponentManager();
            systemManager = new SystemManager();
        }
        
        ~Registry()
        {
            delete entityManager;
            delete componentManager;
            delete systemManager;
        }
    
    public:
        std::uint32_t CreateEntity(){return entityManager->CreateEntity();}
        void DestroyEntity(std::uint32_t entity)
        {
            entityManager->DestroyEntity(entity);
            componentManager->EntityDestroyed(entity);
            entityManager->DestroyEntity(entity);
        }
        
        template<typename T>
        std::vector<std::uint32_t> GetEntitiesWith()
        {
            auto map = componentManager->GetIndexToEntityMap<T>();
            std::vector<std::uint32_t> entities;
            for (const auto&[key, value] : map)
            {
                entities.push_back(value);
            }
            return entities;
        }
        
        template<typename T>
        std::vector<std::pair<std::uint32_t, T*>> GetEntityComponentPairs()
        {
            return componentManager->GetEntityComponentPairs<T>();
        }
        
        template<typename T, typename...Args>
        T& AddComponent(std::uint32_t entity, Args&&... args)
        {
            
            T& component =  componentManager->AddComponent<T>(entity, std::forward<Args>(args)...);
            Signature signature = entityManager->GetSignature(entity);
            signature.set(componentManager->GetComponentType<T>(), true);
            entityManager->SetSignature(entity, signature);
            systemManager->EntitySignatureChanged(entity, signature);
            return component;
        }
        
        template<typename T>
        void RemoveComponent(std::uint32_t entity)
        {
            componentManager->RemoveComponent<T>(entity);
            
            auto signature = entityManager->GetSignature(entity);
            signature.set(componentManager->GetComponentType<T>(), false);
            entityManager->SetSignature(entity, signature);
            
            systemManager->EntitySignatureChanged(entity, signature);
        }
        
        template<typename T>
        T& GetComponent(std::uint32_t entity)
        {
            
            return componentManager->GetComponent<T>(entity);
        }
        
        template<typename T>
        auto View()
        {
        
        
        }
        
        
        
        template<typename T>
        bool HasComponent(std::uint32_t entity)
        {
            componentManager->HasComponent<T>(entity);
        }
        
        template<typename T>
        ComponentType GetComponentType()
        {
            return componentManager->GetComponentType<T>();
        }
        
        
        
        
        
        
    };
}

