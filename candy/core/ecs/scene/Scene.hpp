#pragma once
#include <unordered_map>
#include "../internal/Registry.hpp"
namespace Candy::ECS{
    
    class Entity;
    
    class Scene {
    private:
        friend class Entity;
        friend class SceneHierarchyPanel;
        
    private:
        Internal::Registry registry;
        std::unordered_map<UUID, Entity> entityMap;
        uint32 viewportWidth = 0, viewportHeight = 0;
        bool isRunning;
        bool isPaused;
        int stepFrames=0;
    
    private:
        template<typename T>
        void OnComponentAdded(Entity entity, T& component);
    
    public:
        Scene();
        ~Scene();
        
        static SharedPtr<Scene> Copy(SharedPtr<Scene> other);
    
    public:
        void OnRuntimeStart();
        void OnUpdateRuntime();
        void OnRuntimeStop();
        
        
        
        
        
        void OnUpdate();
        void OnFixedUpdate();
        void OnViewportResize(uint32 width, uint32 height);
        
        bool IsRunning()const{return isRunning;}
        bool IsPaused()const{return isPaused;}
        void SetPaused(bool paused){isPaused=paused;}
        
        void Step(int frames=1);
        
        
    
    public:
        Entity CreateEntity(const std::string &name = std::string());
        Entity CreateEntityWithUUID(UUID uuid, const std::string&name=std::string());
        void DestroyEntity(Entity entity);
        Entity DuplicateEntity(Entity entity);
        Entity FindEntityByName(std::string_view name);
        Entity GetEntityByUUID(UUID uuid);
        Entity GetPrimaryCameraEntity();
        
    
        
        
        
        
        
    };
    

}

