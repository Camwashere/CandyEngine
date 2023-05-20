#pragma once

#include "System.hpp"

namespace Candy::ECS::Internal
{
    class SystemManager
    {
    private:
        std::unordered_map <std::size_t, std::shared_ptr<System>> systems;
        std::unordered_map <std::size_t, Signature> signatures;
    
    public:
        template<typename T>
        std::shared_ptr <T> AddSystem()
        {
            std::size_t hash = typeid(T).hash_code();
            auto system = std::make_shared<T>();
            systems.insert({hash, system});
            return system;
        }
        
        template<typename T>
        void SetSignature(Signature signature)
        {
            std::size_t hash = typeid(T).hash_code();
            signatures.insert({hash, signature});
        }
        
        void EntityDestroyed(uint32 entity)
        {
            for (auto const &pair: systems)
            {
                auto const &system = pair.second;
                system->entities.erase(entity);
            }
        }
        
        void EntitySignatureChanged(uint32 entity, Signature entitySignature)
        {
            for (auto const &pair: systems)
            {
                auto const &type = pair.first;
                auto const &system = pair.second;
                auto const &systemSignature = signatures[type];
                
                // Entity signature matches system signature - insert into set
                if ((entitySignature & systemSignature) == systemSignature)
                {
                    system->entities.insert(entity);
                }
                    // Entity signature does not match system signature - erase from set
                else
                {
                    system->entities.erase(entity);
                }
            }
        }
    };
}
