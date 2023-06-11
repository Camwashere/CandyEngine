#pragma once

#include "InternalBase.hpp"
namespace Candy::ECS::Internal {
    class IComponentArray
    {
    protected:
        std::unordered_map<std::uint32_t, std::uint32_t> entityToIndexMap{};
        std::unordered_map<std::uint32_t, std::uint32_t> indexToEntityMap{};
        
        std::uint32_t size=0;
    public:
        virtual ~IComponentArray()=default;
        virtual void EntityDestroyed(std::uint32_t entity) {};
    
    private:
        friend class ComponentManager;
    };
    
    template<typename T>
    class ComponentArray : public IComponentArray{
    protected:
        std::vector<T*> componentArray{};
    
    
    public:
        ComponentArray()=default;
    
    public:
        void InsertData(std::uint32_t entity, T* component)
        {
            std::uint32_t index = size;
            entityToIndexMap[entity]=index;
            indexToEntityMap[index]=entity;
            componentArray.push_back(component);
            ++size;
        }
        void RemoveData(std::uint32_t entity)
        {
            
            // Copy element at end into deleted element's place to maintain density
            std::uint32_t indexOfRemovedEntity = entityToIndexMap[entity];
            delete componentArray[indexOfRemovedEntity];
            std::uint32_t indexOfLastElement = size-1;
            componentArray[indexOfRemovedEntity] = componentArray[indexOfLastElement];
            
            // Update map to point to moved spot
            std::uint32_t entityOfLastElement = indexToEntityMap[indexOfLastElement];
            entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
            indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;
            entityToIndexMap[entity]=0;
            indexToEntityMap[indexOfLastElement]=0;
            --size;
        }
        T& GetData(std::uint32_t entity)
        {
            return *componentArray[entityToIndexMap[entity]];
        }
        
        bool HasComponent(std::uint32_t entity)
        {
            if (entityToIndexMap.contains(entity))
            {
                return entityToIndexMap[entity] < size;
                
            }
            return false;
            
        }
        
        
        void EntityDestroyed(std::uint32_t entity) override
        {
            if (entityToIndexMap[entity])
            {
                // Remove the entity's component if it existed
                RemoveData(entity);
            }
        }
        const std::unordered_map<std::uint32_t, std::uint32_t>& GetIndexToEntityMap()const{return indexToEntityMap;}
    };
    class ComponentManager
    {
    private:
        std::unordered_map<const char*, IComponentArray*> componentArrays{};
        std::unordered_map<const char*, ComponentType> componentTypes{};
        
        ComponentType nextComponentType;
    
    private:
        
        template<typename T>
        ComponentArray<T>& GetComponentArray()
        {
            //std::size_t hash = typeid(T).hash_code();
            const char* hash = typeid(T).name();
            return static_cast<ComponentArray<T>&>(*componentArrays[hash]);
            
        }
        
        
        
        template<typename T>
        void RegisterComponent(const char* hash)
        {
            //const char* hash =typeid(T).name();
            
            // Add this component type to the component type map
            componentTypes.insert({hash, nextComponentType});
            
            // Create a ComponentArray pointer and add it to the component arrays map
            componentArrays.insert({hash, new ComponentArray<T>()});
            
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
        const std::unordered_map<std::uint32_t, std::uint32_t>& GetIndexToEntityMap()
        {
            return GetComponentArray<T>().GetIndexToEntityMap();
        }
        template<typename T>
        std::vector<std::pair<std::uint32_t, T&>> GetEntityComponentPairs()
        {
            ComponentArray<T>* arr = GetComponentArray<T>();
            const std::unordered_map<std::uint32_t, std::uint32_t>& entityMap = arr->GetIndexToEntityMap();
            std::vector<std::pair<std::uint32_t, T*>> pairs;
            for (const auto& pair : entityMap)
            {
                pairs.push_back(std::pair<std::uint32_t, T*>(pair.second, arr->GetData(pair.second)));
            }
            return pairs;
            
        }
        template<typename T>
        bool HasComponent(std::uint32_t entity)
        {
            const char* hash = typeid(T).name();
            if (componentArrays.contains(hash))
            {
                return static_cast<ComponentArray<T>*>(componentArrays[hash])->HasComponent(entity);
            }
            return false;
        }
        template<typename T, typename...Args>
        T& AddComponent(std::uint32_t entity, Args...args)
        {
            RegistryCheck<T>();
            T* component = new T({args...});
            GetComponentArray<T>().InsertData(entity, component);
            return *component;
        }
        template<typename T>
        void RemoveComponent(std::uint32_t entity)
        {
            
            // Remove a component from the array for an entity
            GetComponentArray<T>().RemoveData(entity);
        }
        template<typename T>
        T& GetComponent(std::uint32_t entity)
        {
            return GetComponentArray<T>().GetData(entity);
        }
        
        template<typename T>
        ComponentArray<T>& GetComponents()
        {
            return GetComponentArray<T>();
        }
        void EntityDestroyed(std::uint32_t entity)
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


