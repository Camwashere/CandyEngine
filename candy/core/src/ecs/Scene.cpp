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
  
  
  Scene::SceneUpdateFlag operator|(Scene::SceneUpdateFlag a, Scene::SceneUpdateFlag b)
  {
    return (Scene::SceneUpdateFlag)(static_cast<int>(a) | static_cast<int>(b));
  }
  
  Scene::SceneUpdateFlag operator&(Scene::SceneUpdateFlag a, Scene::SceneUpdateFlag b)
  {
    return (Scene::SceneUpdateFlag)(static_cast<int>(a) & static_cast<int>(b));
  }
  
  template<typename... Component>
  static void CopyComponent(entt::registry& dst, entt::registry& src, const std::unordered_map<UUID, entt::entity>& enttMap)
  {
    CANDY_PROFILE_FUNCTION();
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
    CANDY_PROFILE_FUNCTION();
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
    CANDY_PROFILE_FUNCTION();
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
    CANDY_PROFILE_FUNCTION();
    return CreateEntityWithUUID(UUID(), tag);
  }
  
  Entity Scene::CreateEntityWithUUID(UUID uuid, const std::string& tag)
  {
    CANDY_PROFILE_FUNCTION();
    Entity entity = { registry.create(), this };
    entity.AddComponent<IDComponent>(uuid);
    auto& tc = entity.AddComponent<TagComponent>();
    tc.tag = tag.empty() ? "Entity" : tag;
    entity.AddComponent<TransformComponent>(entity);
    
    entityMap[uuid] = entity;
    
    return entity;
  }
 
  void Scene::DestroyEntity(Entity entity)
  {
    CANDY_PROFILE_FUNCTION();
    if (entity.HasChildren())
    {
      auto& children = entity.GetChildren().children;
      for (auto& child : children)
      {
        DestroyEntity(child);
      }
    }
    if (entity.HasParent())
    {
      Entity parent = entity.GetParent().parent;
      bool removed = parent.RemoveChild(entity);
      CANDY_CORE_ASSERT(removed);
    }
    
    
    entityMap.erase(entity.GetUUID());
    registry.destroy(entity);
    
  }
  
  Entity Scene::DuplicateEntity(Entity entity)
  {
    CANDY_PROFILE_FUNCTION();
    // Copy name because we're going to modify component data structure
    std::string tag = entity.GetTag();
    Entity newEntity = CreateEntity(tag);
    CopyComponentIfExists(AllComponents{}, newEntity, entity);
    return newEntity;
  }
  
  Entity Scene::FindEntityByTag(std::string_view tag)
  {
    CANDY_PROFILE_FUNCTION();
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
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_ASSERT(entityMap.find(uuid) != entityMap.end(), "Entity not found in registry");
    return { entityMap.at(uuid), this };
  }
  
  void Scene::AttachSystem(System* system)
  {
    CANDY_PROFILE_FUNCTION();
    systemScheduler.AttachSystem(system);
  }
  void Scene::AppendUpdateFlag(SceneUpdateFlag flag)
  {
    updateFlag = updateFlag | flag;
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
    CANDY_PROFILE_FUNCTION();
    if (viewportWidth == width && viewportHeight == height)
    {
      return;
    }
    
    viewportWidth = width;
    viewportHeight = height;
  }
  
  
  void Scene::OnUpdateEditor()
  {
    CANDY_PROFILE_FUNCTION();
    //systemScheduler.Update((void*)&camera);
    RenderScene();
    
  }
  void Scene::RenderScene()
  {
    CANDY_PROFILE_FUNCTION();
    RenderScene3D();
    RenderScene2D();
    Renderer3D::RenderSelectionBuffer();
    Renderer2D::RenderSelectionBuffer();
    
    updateFlag = SceneUpdateFlag::None;
  }
  void Scene::RenderScene3D()
  {
    CANDY_PROFILE_FUNCTION();
    Renderer3D::BeginScene();
    
    /*if (updateFlag == SceneUpdateFlag::None)
    {
      Renderer3D::EndScene();
      return;
    }*/
    
    
    
    auto view = registry.view<TransformComponent, MeshFilterComponent, MeshRendererComponent>();
    
    if (updateFlag & SceneUpdateFlag::Meshes3D)
    {
      for (auto entity : view)
      {
        
        auto [transform, mesh, meshRenderer] = view.get<TransformComponent, MeshFilterComponent, MeshRendererComponent>(entity);
        Renderer3D::SubmitMesh((uint32_t)entity, mesh.GetMeshData(), meshRenderer.texture, transform.GetWorldTransform());
      }
    }
    else
    {
      Renderer3D::skipFlush = true;
      for (auto entity : view)
      {
        auto [transform, mesh, meshRenderer] = view.get<TransformComponent, MeshFilterComponent, MeshRendererComponent>(entity);
        Renderer3D::SubmitMesh((uint32_t)entity, mesh.GetMeshData().IndexCount(), mesh.GetMeshData().VertexCount(), meshRenderer.texture, transform.GetWorldTransform());
      }
    }
    
    
    
    Renderer3D::EndScene();
  }
  void Scene::RenderScene2D()
  {
    CANDY_PROFILE_FUNCTION();
    Renderer2D::BeginScene();
    
    // Draw Sprites
    {
      auto view = registry.view<TransformComponent, SpriteRendererComponent>();
      
      for (auto entity : view)
      {
        auto [transform, sprite] = view.get<TransformComponent, SpriteRendererComponent>(entity);
        Renderer2D::DrawSprite(transform.GetWorldTransform(), sprite, (int)entity);
      }
    }
    
    
    // Draw Circles
    {
      auto view = registry.view<TransformComponent, CircleRendererComponent>();
      
      for (auto entity : view)
      {
        auto [transform, circle] = view.get<TransformComponent, CircleRendererComponent>(entity);
        Renderer2D::DrawCircle(transform.GetWorldTransform(), circle.color, circle.thickness, circle.fade, (int)entity);
      }
    }
    
    // Draw Lines
    {
      auto view = registry.view<TransformComponent, LineRendererComponent>();
      
      for (auto entity : view)
      {
        auto [transform, line] = view.get<TransformComponent, LineRendererComponent>(entity);
        Vector3 start = transform.GetWorldTransform()*line.start;
        Vector3 end = transform.GetWorldTransform()*line.end;
        //Renderer2D::DrawLine(start, end, line.color, line.thickness, (int)entity);
        Renderer2D::DrawLine(transform.GetWorldTransform(), line.start, line.end, line.color, line.thickness, (int)entity);
      }
    }
    
    // Draw Text
    {
      auto view = registry.view<TransformComponent, TextRendererComponent>();
      
      for (auto entity : view)
      {
        auto [transform, txt] = view.get<TransformComponent, TextRendererComponent>(entity);
        Renderer2D::DrawString(txt.text, transform.GetWorldTransform(), txt, (int)entity);
      }
    }
    
    Renderer2D::EndScene();
  
  }
  SharedPtr<Scene> Scene::Create(const std::string& name)
  {
    return CreateSharedPtr<Scene>(name);
  }
  
  
  
  /*template<>
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
  }*/
  
  
  
  
}