#include "../entity/Entity.hpp"
#include "Scene.hpp"
#include <iostream>
#include "../component/BaseComponents.hpp"
#include <Candy/CandyEngineBase.hpp>
#include <Candy/Scripting.hpp>
namespace Candy::ECS {
    using namespace ::Candy::Scripting;
    using namespace Internal;
    
    Scene::Scene() {
    
    
    }
    
    Scene::~Scene() {
    
    }
    
    template<typename T>
    void Scene::OnComponentAdded(Entity entity, T &component) {
        entityMap.begin();
        for (auto i : entityMap)
        {
        
        }
    }
    Entity Scene::CreateEntity(const std::string &name) {
        Entity entity(registry.CreateEntity(), this);
        UUID entityUUID = registry.AddComponent<IDComponent>(entity, UUID())->id;
        registry.AddComponent<NameComponent>(entity, name);
        entityMap.insert({entityUUID, entity});
        
        return entity;
        
    }
    
    void Scene::OnRuntimeStart()
    {
        isRunning=true;
        {
            ScriptEngine::OnRuntimeStart(this);
            
            /*auto view = registry.view<ScriptComponent>();
            for (auto e : view)
            {
                Entity entity = {e, this};
                ScriptEngine::OnCreateEntity(entity);
            }*/
        }
    
    }
    
    void Scene::OnUpdateRuntime()
    {
    
    }
    
    void Scene::OnRuntimeStop()
    {
        isRunning=false;
        ScriptEngine::OnRuntimeStop();
    
    }
    
    
    void Scene::OnUpdate()
    {
        if (!isPaused || stepFrames-- > 0)
        {
            const auto& view = registry.GetEntitiesWith<ScriptComponent>();
            for (auto e : view)
            {
                Entity entity = {e, this};
                ScriptEngine::OnUpdateEntity(entity);
            }
            const auto& natives = registry.GetEntitiesWith<NativeScriptComponent>();
            for (auto e : natives)
            {
            
            }
        }
    
    }
    
    void Scene::OnFixedUpdate()
    {
    
    }
    
    void Scene::OnViewportResize(uint32 width, uint32 height)
    {
    
    }
    
    void Scene::DestroyEntity(Entity entity)
    {
        entityMap.erase(entity.GetUUID());
        registry.DestroyEntity(entity);
    
    }
    
    Entity Scene::DuplicateEntity(Entity entity)
    {
        return Entity(0, this);
    }
    
    Entity Scene::FindEntityByName(std::string_view name)
    {
        return Entity(0, this);
    }
    
    Entity Scene::GetEntityByUUID(UUID uuid)
    {
        return Entity(0, this);
    }
    
    
}
