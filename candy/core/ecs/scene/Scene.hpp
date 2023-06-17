#pragma once
#include <unordered_map>
#include <Candy/CandyEngineBase.hpp>
#include "../../graphics/rendering/camera/EditorCamera.hpp"
#include <entt/entt.hpp>

namespace Candy{
    class SceneHierarchyPanel;
}

namespace Candy::ECS{
    class Entity;
    
    
    class Scene {
    
        
    private:
        
        entt::registry registry;
        std::unordered_map<UUID, Entity> entityMap;
        
        std::string name="Untitled";
        uint32 viewportWidth = 0, viewportHeight = 0;
        bool isRunning=false;
        bool isPaused=true;
        int stepFrames=0;
    
    private:
        template<typename T>
        void OnComponentAdded(Entity entity, T& component);
        
        void RenderScene(Graphics::EditorCamera& camera);
    
    
    public:
        Scene();
        ~Scene();
        
        static SharedPtr<Scene> Copy(SharedPtr<Scene> other);
    
    public:
        Entity CreateEntity(const std::string &name = std::string());
        Entity CreateEntityWithUUID(UUID uuid, const std::string&name=std::string());
        void DestroyEntity(Entity entity);
        Entity DuplicateEntity(Entity entity);
        Entity FindEntityByName(std::string_view name);
        Entity GetEntityByUUID(UUID uuid);
        Entity GetPrimaryCameraEntity();
        
    
    public:
        void OnRuntimeStart();
        void OnUpdateRuntime();
        void OnRuntimeStop();
        
        void OnSimulationStart();
        void OnUpdateSimulation(Graphics::EditorCamera& camera);
        void OnSimulationStop();
        
        void OnUpdateEditor(Graphics::EditorCamera& camera);
        
        void OnViewportResize(uint32 width, uint32 height);
        
        bool IsRunning()const;
        bool IsPaused()const;
        void SetPaused(bool paused);
        
        void Step(int frames=1);
    
    private:
        friend class Entity;
        friend class SceneSerializer;
        friend class ::Candy::SceneHierarchyPanel;
        
        
    
    
        
    
        
        
        
        
        
    };
    

}

