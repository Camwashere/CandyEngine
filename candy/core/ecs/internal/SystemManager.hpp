#pragma once

#include "System.hpp"

namespace Candy::ECS::Internal
{
    class SystemManager
    {
    private:
        std::unordered_map <std::size_t, System*> systems;
        std::unordered_map <std::size_t, Signature> signatures;
    
    public:
        template<typename T>
        System& AddSystem()
        {
            std::size_t hash = typeid(T).hash_code();
            auto system = new T();
            systems.insert({hash, system});
            return system;
        }
        
        template<typename T>
        void SetSignature(Signature signature)
        {
            std::size_t hash = typeid(T).hash_code();
            signatures.insert({hash, signature});
        }
        
        void EntityDestroyed(std::uint32_t entity)
        {
            for (auto const &pair: systems)
            {
                auto const &system = pair.second;
                system->entities.erase(entity);
            }
        }
        
        void EntitySignatureChanged(std::uint32_t entity, Signature entitySignature)
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
