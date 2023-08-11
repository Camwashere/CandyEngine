#include <candy/ecs/Scene.hpp>
#include <candy/ecs/BaseComponents.hpp>
#include <candy/ecs/Entity.hpp>
//#include <Candy/Graphics.hpp>
#include <candy/graphics/Renderer.hpp>
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
  
  void Scene::OnUpdateEditor(Graphics::Camera& camera)
  {
    systemScheduler.Update((void*)&camera);
    Renderer::BeginScene(camera);
    auto view = registry.view<TransformComponent, MeshComponent>();
    for (auto entity : view)
    {
      auto [transform, mesh] = view.get<TransformComponent, MeshComponent>(entity);
      //Renderer::SubmitMesh(mesh.mesh, mesh.material, transform.GetTransform());
    }
    
    Renderer::EndScene();
    /*Renderer3D::BeginScene(camera);
    //Renderer3D::RenderGrid();
    // Draw Meshes
    auto view = registry.view<TransformComponent, MeshFilterComponent>();
    for (auto entity : view)
    {
      auto [transform, meshFilter] = view.get<TransformComponent, MeshFilterComponent>(entity);
      Renderer3D::SubmitMesh(meshFilter.mesh, transform.GetTransform());
    }
    
    Renderer3D::EndScene();*/
    
    
    
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