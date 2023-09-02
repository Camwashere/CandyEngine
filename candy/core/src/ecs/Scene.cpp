#include <candy/ecs/Scene.hpp>
#include <candy/ecs/BaseComponents.hpp>
#include <candy/ecs/Entity.hpp>
#include <candy/graphics/Renderer.hpp>
#include <candy/graphics/Renderer3D.hpp>
#include <candy/graphics/Renderer2D.hpp>
namespace Candy::ECS
{
  using namespace Graphics;
  using namespace Math;
  Scene::Scene()=default;
  Scene::Scene(std::string sceneName) : name(std::move(sceneName)){}
  Scene::~Scene()=default;
  
  template<typename... Component>
  static void CopyComponent(entt::registry& dst, entt::registry& src, const std::unordered_map<UUID, entt::entity>& enttMap)
  {
    ([&]()
    {
    auto view = src.view<Component>();
    for (auto srcEntity : view)
    {
      entt::entity dstEntity = enttMap.at(src.get<IDComponent>(srcEntity).id);
      
      auto& srcComponent = src.get<Component>(srcEntity);
      dst.emplace_or_replace<Component>(dstEntity, srcComponent);
    }
    }(), ...);
  }
  
  template<typename... Component>
  static void CopyComponent(ComponentGroup<Component...>, entt::registry& dst, entt::registry& src, const std::unordered_map<UUID, entt::entity>& enttMap)
  {
    CopyComponent<Component...>(dst, src, enttMap);
  }
  
  template<typename... Component>
  static void CopyComponentIfExists(Entity dst, Entity src)
  {
    ([&]()
    {
    if (src.HasComponent<Component>())
      dst.AddOrReplaceComponent<Component>(src.GetComponent<Component>());
    }(), ...);
  }
  
  template<typename... Component>
  static void CopyComponentIfExists(ComponentGroup<Component...>, Entity dst, Entity src)
  {
    CopyComponentIfExists<Component...>(dst, src);
  }
  
  SharedPtr<Scene> Scene::Copy(const SharedPtr<Scene>& other)
  {
    SharedPtr<Scene> newScene = CreateSharedPtr<Scene>();
    newScene->name = other->name;
    newScene->viewportWidth = other->viewportWidth;
    newScene->viewportHeight = other->viewportHeight;
    
    auto& srcSceneRegistry = other->registry;
    auto& dstSceneRegistry = newScene->registry;
    std::unordered_map<UUID, entt::entity> enttMap;
    
    auto idView = srcSceneRegistry.view<IDComponent>();
    for(auto e : idView)
    {
      UUID uuid = srcSceneRegistry.get<IDComponent>(e).id;
      const auto& tag = srcSceneRegistry.get<TagComponent>(e).tag;
      Entity newEntity = newScene->CreateEntityWithUUID(uuid, tag);
      enttMap[uuid] = (entt::entity)newEntity;
    }
    // Copy components (except IDComponent and TagComponent)
    CopyComponent(AllComponents{}, dstSceneRegistry, srcSceneRegistry, enttMap);
    return newScene;
  }
  
  Entity Scene::CreateEntity(const std::string& tag)
  {
    return CreateEntityWithUUID(UUID(), tag);
  }
  
  Entity Scene::CreateEntityWithUUID(UUID uuid, const std::string& tag)
  {
    Entity entity = { registry.create(), this };
    entity.AddComponent<IDComponent>(uuid);
    auto& tc = entity.AddComponent<TagComponent>();
    tc.tag = tag.empty() ? "Entity" : tag;
    entity.AddComponent<TransformComponent>();
    
    entityMap[uuid] = entity;
    
    return entity;
  }
 
  void Scene::DestroyEntity(Entity entity)
  {
    entityMap.erase(entity.GetUUID());
    registry.destroy(entity);
  }
  
  Entity Scene::DuplicateEntity(Entity entity)
  {
    // Copy name because we're going to modify component data structure
    std::string tag = entity.GetTag();
    Entity newEntity = CreateEntity(tag);
    CopyComponentIfExists(AllComponents{}, newEntity, entity);
    return newEntity;
  }
  
  Entity Scene::FindEntityByTag(std::string_view tag)
  {
    auto view = registry.view<TagComponent>();
    for (auto entity : view)
    {
      const TagComponent& tc = view.get<TagComponent>(entity);
      if (tc.tag == tag)
        return Entity{ entity, this };
    }
    return {};
  }
  
  Entity Scene::GetEntityByUUID(UUID uuid)
  {
    CANDY_CORE_ASSERT(entityMap.find(uuid) != entityMap.end(), "Entity not found in registry");
    return { entityMap.at(uuid), this };
  }
  
  void Scene::AttachSystem(System* system)
  {
    systemScheduler.AttachSystem(system);
  }
  
  bool Scene::IsRunning()const{return isRunning;}
  bool Scene::IsPaused()const{return isPaused;}
  void Scene::SetPaused(bool paused){isPaused=paused;}
  
  void Scene::OnStartRuntime(){}
  void Scene::OnUpdateRuntime(){}
  void Scene::OnStopRuntime(){}
  
  void Scene::OnStartSimulation(){}
  void Scene::OnUpdateSimulation(){}
  void Scene::OnStopSimulation(){}
  
  void Scene::OnViewportResize(std::uint32_t width, std::uint32_t height)
  {
    if (viewportWidth == width && viewportHeight == height)
    {
      return;
    }
    
    viewportWidth = width;
    viewportHeight = height;
  }
  
  
  void Scene::OnUpdateEditor()
  {
    //systemScheduler.Update((void*)&camera);
    RenderScene();
    
  }
  void Scene::RenderScene()
  {
    RenderScene3D();
    RenderScene2D();
    Renderer3D::RenderSelectionBuffer();
    Renderer2D::RenderSelectionBuffer();
  }
  void Scene::RenderScene3D()
  {
    Renderer3D::BeginScene();
    
    auto view = registry.view<TransformComponent, MeshFilterComponent, MeshRendererComponent>();
    for (auto entity : view)
    {
      
      auto [transform, mesh, meshRenderer] = view.get<TransformComponent, MeshFilterComponent, MeshRendererComponent>(entity);
      Renderer3D::SubmitMesh((uint32_t)entity, mesh.mesh, meshRenderer.texture, transform.GetMatrix());
    }
    
    Renderer3D::EndScene();
  }
  void Scene::RenderScene2D()
  {
    Renderer2D::BeginScene();
    
    // Draw Sprites
    {
      auto view = registry.view<TransformComponent, SpriteRendererComponent>();
      
      for (auto entity : view)
      {
        auto [transform, sprite] = view.get<TransformComponent, SpriteRendererComponent>(entity);
        Renderer2D::DrawSprite(transform.GetMatrix(), sprite, (int)entity);
      }
    }
    
    
    // Draw Circles
    {
      auto view = registry.view<TransformComponent, CircleRendererComponent>();
      
      for (auto entity : view)
      {
        auto [transform, circle] = view.get<TransformComponent, CircleRendererComponent>(entity);
        Renderer2D::DrawCircle(transform.GetMatrix(), circle.color, circle.thickness, circle.fade, (int)entity);
      }
    }
    
    // Draw Lines
    {
      auto view = registry.view<TransformComponent, LineRendererComponent>();
      
      for (auto entity : view)
      {
        auto [transform, line] = view.get<TransformComponent, LineRendererComponent>(entity);
        Vector3 start = transform.GetMatrix()*line.start;
        Vector3 end = transform.GetMatrix()*line.end;
        //Renderer2D::DrawLine(start, end, line.color, line.thickness, (int)entity);
        Renderer2D::DrawLine(transform.GetMatrix(), line.start, line.end, line.color, line.thickness, (int)entity);
      }
    }
    
    Renderer2D::EndScene();
  
  }
  SharedPtr<Scene> Scene::Create(const std::string& name)
  {
    return CreateSharedPtr<Scene>(name);
  }
  template<typename T>
  void Scene::OnComponentAdded(Entity entity, T& component)
  {
  
  }
  
  
  template<>
  void Scene::OnComponentAdded<IDComponent>(Entity entity, IDComponent& component)
  {
  }
  
  template<>
  void Scene::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& component)
  {
  }
  
  template<>
  void Scene::OnComponentAdded<TagComponent>(Entity entity, TagComponent& component)
  {
  }
  
  
  
  
}