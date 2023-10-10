#pragma once
#include <CandyPch.hpp>
#include <entt/entt.hpp>
#include <unordered_map>
#include "SystemScheduler.hpp"
#include <candy/base/UUID.hpp>
#include "candy/graphics/camera/PerspectiveCamera.hpp"
#include <candy/graphics/camera/EditorCamera.hpp>

namespace Candy
{
  class SceneHierarchyPanel;
}

namespace Candy::Graphics
{
  class Renderer;
}
namespace Candy::ECS
{
  
  class Entity;
  class Scene
  {
  public:
    enum  SceneUpdateFlag
    {
      None = BIT(0),
      Transforms = BIT(1),
      Meshes2D = BIT(2),
      Meshes3D = BIT(3),
      
    };
  private:
    entt::registry registry;
    std::unordered_map<UUID, Entity> entityMap;
    std::vector<Entity> deletionQueue;
    std::string name = "Untitled";
    std::uint32_t viewportWidth=0, viewportHeight=0;
    bool isRunning = false;
    bool isPaused = true;
    SystemScheduler systemScheduler;
    SceneUpdateFlag updateFlag = SceneUpdateFlag::None;
  
  private:
    void MarkForDelete(Entity entity);
    
    //void RenderScene();
    void RenderScene3D();
    void RenderScene2D();
  
  public:
    Scene();
    explicit Scene(std::string sceneName);
    ~Scene();
    
    static SharedPtr<Scene> Copy(const SharedPtr<Scene>& other);
    
    template<typename T>
    void OnComponentAdded(Entity& entity, T& component);
    
    template<typename T>
    void OnComponentRemoved(Entity& entity, T& component);
    
    template<typename T>
    void OnComponentUpdated(Entity& entity, T& component);
  
  public:
    Entity CreateEntity(const std::string &tag = std::string());
    Entity CreateEntityWithUUID(UUID uuid, const std::string&tag=std::string());
    void DestroyEntity(Entity entity);
    void DestroyEntityTree(Entity parent);
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
    
    void OnUpdateEditor();
    void OnViewportResize(std::uint32_t width, std::uint32_t height);
    
  public:
    void ClearUpdateFlags();
    void AppendUpdateFlag(SceneUpdateFlag flag);
    bool IsRunning()const;
    bool IsPaused()const;
    void SetPaused(bool paused);
    
  public:
    static SharedPtr<Scene> Create(const std::string& name = "Untitled");
    
  private:
    friend class Entity;
    friend class SceneManager;
    friend class SceneSerializer;
    friend class ::Candy::SceneHierarchyPanel;
    friend class ::Candy::Graphics::Renderer;
    
  };
  
  template<typename T>
  inline void Scene::OnComponentAdded(Entity& entity, T& component){}
  template<typename T>
  inline void Scene::OnComponentRemoved(Entity& entity, T& component){}
  
  template<typename T>
  inline void Scene::OnComponentUpdated(Entity& entity, T& component){}
  
  
}




