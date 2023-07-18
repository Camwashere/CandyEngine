#pragma once
#include <CandyPch.hpp>
#include <entt/entt.hpp>
#include <unordered_map>
#include "SystemScheduler.hpp"
#include <candy/base/UUID.hpp>
#include <candy/graphics/camera/Camera.hpp>
namespace Candy::ECS
{
  class Entity;
  class Scene
  {
  private:
    entt::registry registry;
    std::unordered_map<UUID, Entity> entityMap;
    std::string name = "Untitled";
    std::uint32_t viewportWidth=0, viewportHeight=0;
    bool isRunning = false;
    bool isPaused = true;
    SystemScheduler systemScheduler;
  
  private:
    template<typename T>
    void OnComponentAdded(Entity entity, T& component);
  
  public:
    Scene();
    explicit Scene(std::string sceneName);
    ~Scene();
    
    static SharedPtr<Scene> Copy(const SharedPtr<Scene>& other);
  
  public:
    Entity CreateEntity(const std::string &tag = std::string());
    Entity CreateEntityWithUUID(UUID uuid, const std::string&tag=std::string());
    void DestroyEntity(Entity entity);
    Entity DuplicateEntity(Entity entity);
    Entity FindEntityByTag(std::string_view tag);
    Entity GetEntityByUUID(UUID uuid);
  
  public:
    void AttachSystem(System* system);
  
  public:
    void OnStartRuntime();
    void OnUpdateRuntime();
    void OnStopRuntime();
    
    void OnStartSimulation();
    void OnUpdateSimulation();
    void OnStopSimulation();
    
    void OnUpdateEditor(Graphics::Camera& camera);
    
    void OnViewportResize(std::uint32_t width, std::uint32_t height);
    
    bool IsRunning()const;
    bool IsPaused()const;
    void SetPaused(bool paused);
    
  private:
    friend class Entity;
    friend class SceneManager;
    
  };
}
