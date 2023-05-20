#pragma once

#include "InternalBase.hpp"
namespace Candy::ECS::Internal {
    
    class EntityManager {
    private:
        std::queue<uint32> unusedEntities{};
        std::vector<Signature> signatures{};
        uint32 livingEntityCount=0;
        uint32 currentMax=1000;
    public:
        EntityManager() {
            for (int i=0; i<currentMax; i++)
            {
                unusedEntities.push(i);
            }
        }
    public:
        uint32 CreateEntity() {
            uint32 id = unusedEntities.front();
            unusedEntities.pop();
            ++livingEntityCount;
            signatures.push_back(Signature(currentMax));
            return id;
        }
        void DestroyEntity(uint32 entity) {
            // Invalidate the destroyed entity's signature
            signatures[entity].reset();
            // Put the destroyed ID at the back of the queue
            unusedEntities.push(entity);
            --livingEntityCount;
        }
        void SetSignature(uint32 entity, Signature signature) {
            // Put this entity's signature into the array
            signatures[entity] = signature;
        }
        Signature GetSignature(uint32 entity) {
            // Get this entity's signature from the array
            return signatures[entity];
        }
    };
}

