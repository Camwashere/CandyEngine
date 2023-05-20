#pragma once

#include "InternalBase.hpp"
namespace Candy::ECS::Internal {
    class IComponentArray
    {
    public:
        virtual ~IComponentArray()=default;
        virtual void EntityDestroyed(uint32 entity) {};
    };
    
    template<typename T>
    class ComponentArray : public IComponentArray{
    protected:
        std::vector<SharedPtr<T>> componentArray{};
        std::unordered_map<uint32, uint32> entityToIndexMap{};
        std::unordered_map<uint32, uint32> indexToEntityMap{};
        
        uint32 size=0;
    
    
    public:
        ComponentArray()=default;
    
    public:
        void InsertData(uint32 entity, const std::shared_ptr<T>& component)
        {
            uint32 index = size;
            entityToIndexMap[entity]=index;
            indexToEntityMap[index]=entity;
            componentArray.push_back(component);
            ++size;
        }
        void RemoveData(uint32 entity)
        {
            // Copy element at end into deleted element's place to maintain density
            uint32 indexOfRemovedEntity = entityToIndexMap[entity];
            uint32 indexOfLastElement = size-1;
            componentArray[indexOfRemovedEntity] = componentArray[indexOfLastElement];
            
            // Update map to point to moved spot
            uint32 entityOfLastElement = indexToEntityMap[indexOfLastElement];
            entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
            indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;
            entityToIndexMap[entity]=0;
            indexToEntityMap[indexOfLastElement]=0;
            --size;
        }
        SharedPtr<T> GetData(uint32 entity)
        {
            return componentArray[entityToIndexMap[entity]];
        }
        void EntityDestroyed(uint32 entity) override
        {
            if (entityToIndexMap[entity])
            {
                // Remove the entity's component if it existed
                RemoveData(entity);
            }
        }
        const std::unordered_map<uint32, uint32>& GetIndexToEntityMap()const{return indexToEntityMap;}
    };
    class ComponentManager
    {
    private:
        std::unordered_map<const char*, std::shared_ptr<IComponentArray>> componentArrays{};
        std::unordered_map<const char*, ComponentType> componentTypes{};
        ComponentType nextComponentType;
    
    private:
        
        template<typename T>
        std::shared_ptr<ComponentArray<T>> GetComponentArray()
        {
            //std::size_t hash = typeid(T).hash_code();
            const char* hash = typeid(T).name();
            
            return std::static_pointer_cast<ComponentArray<T>>(componentArrays[hash]);
        }
        
        template<typename T>
        void RegisterComponent(const char* hash)
        {
            //const char* hash =typeid(T).name();
            
            // Add this component type to the component type map
            componentTypes.insert({hash, nextComponentType});
            
            // Create a ComponentArray pointer and add it to the component arrays map
            componentArrays.insert({hash, std::make_shared_for_overwrite<ComponentArray<T>>()});
            
            // Increment the value so that the next component registered will be different
            ++nextComponentType;
        }
        template<typename T>
        void RegistryCheck()
        {
            const char* hash =typeid(T).name();
            if (!componentTypes.contains(hash))
            {
                RegisterComponent<T>(hash);
            }
        }
    public:
        template<typename T>
        const std::unordered_map<uint32, uint32>& GetIndexToEntityMap()
        {
            return GetComponentArray<T>()->GetIndexToEntityMap();
        }
        template<typename T, typename...Args>
        auto AddComponent(uint32 entity, Args...args)
        {
            RegistryCheck<T>();
            std::shared_ptr<T> component(new T({args...}));
            GetComponentArray<T>()->InsertData(entity, component);
            return component;
        }
        template<typename T>
        void RemoveComponent(uint32 entity)
        {
            RegistryCheck<T>();
            // Remove a component from the array for an entity
            GetComponentArray<T>()->RemoveData(entity);
        }
        template<typename T>
        auto GetComponent(uint32 entity)
        {
            return GetComponentArray<T>()->GetData(entity);
        }
        void EntityDestroyed(uint32 entity)
        {
            // Notify each component array that an entity has been destroyed
            // If it has a component for that entity, it will remove it
            for (auto const&pair : componentArrays)
            {
                auto const& component = pair.second;
                component->EntityDestroyed(entity);
            }
        }
        
        template<typename T>
        ComponentType GetComponentType()
        {
            const char* hash = typeid(T).name();
            return componentTypes[hash];
        }
    };
    
}


