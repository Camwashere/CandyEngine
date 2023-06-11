#pragma once


#include "InternalBase.hpp"
namespace Candy::ECS::Internal {
    
    class EntityManager {
    private:
        std::queue<std::uint32_t> unusedEntities{};
        std::vector<Signature> signatures{};
        std::uint32_t livingEntityCount=0;
        std::uint32_t currentMax=1000;
    public:
        EntityManager() {
            for (int i=0; i<currentMax; i++)
            {
                unusedEntities.push(i);
            }
        }
    public:
        std::uint32_t CreateEntity() {
            std::uint32_t id = unusedEntities.front();
            unusedEntities.pop();
            ++livingEntityCount;
            signatures.push_back(Signature(currentMax));
            return id;
        }
        void DestroyEntity(std::uint32_t entity) {
            // Invalidate the destroyed entity's signature
            signatures[entity].reset();
            // Put the destroyed ID at the back of the queue
            unusedEntities.push(entity);
            --livingEntityCount;
        }
        void SetSignature(std::uint32_t entity, Signature signature) {
            // Put this entity's signature into the array
            signatures[entity] = signature;
        }
        Signature GetSignature(std::uint32_t entity) {
            // Get this entity's signature from the array
            return signatures[entity];
        }
    };
}



