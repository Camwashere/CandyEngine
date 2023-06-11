#pragma once
#include "Entity.hpp"

namespace Candy::ECS
{
    class ScriptableEntity
    {
    private:
        Entity entity;
        friend class Scene;
        
    protected:
        virtual void OnCreate(){}
        virtual void OnDestroy(){}
        virtual void OnUpdate(){}
        
    public:
        virtual ~ScriptableEntity(){}
        
        template<typename T>
        T& GetComponent()
        {
            return entity.GetComponent<T>();
        }
    };
}