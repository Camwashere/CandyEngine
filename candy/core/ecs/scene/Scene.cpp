#include "Scene.hpp"
#include <iostream>
#include <Candy/ECS.hpp>
#include <Candy/Graphics.hpp>

namespace Candy::ECS {
    
    
    
    Scene::Scene()=default;
    
    Scene::~Scene() = default;
    
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
    
    SharedPtr<Scene> Scene::Copy(SharedPtr<Scene> other)
    {
        SharedPtr<Scene> newScene = CreateSharedPtr<Scene>();
        newScene->viewportWidth = other->viewportWidth;
        newScene->viewportHeight = other->viewportHeight;
        
        auto& srcSceneRegistry = other->registry;
        auto& dstSceneRegistry = newScene->registry;
        std::unordered_map<UUID, entt::entity> enttMap;
        
        auto idView = srcSceneRegistry.view<IDComponent>();
        for(auto e : idView)
        {
            UUID uuid = srcSceneRegistry.get<IDComponent>(e).id;
            const auto& name = srcSceneRegistry.get<NameComponent>(e).name;
            Entity newEntity = newScene->CreateEntityWithUUID(uuid, name);
            enttMap[uuid] = (entt::entity)newEntity;
        }
        // Copy components (except IDComponent and TagComponent)
        CopyComponent(AllComponents{}, dstSceneRegistry, srcSceneRegistry, enttMap);
        return newScene;
    }
    
    
    
    void Scene::RenderScene(Graphics::EditorCamera& camera)
    {
        Graphics::Renderer2D::BeginScene(camera);
        
        
        // Draw sprites
        {
            auto group = registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
            for (auto entity : group)
            {
                auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
                Graphics::Renderer2D::DrawSprite(transform.GetTransform(), sprite, (int)entity);
            }
        }
        
        // Draw circles
        {
            auto view = registry.view<TransformComponent, CircleRendererComponent>();
            for (auto entity : view)
            {
                auto [transform, circle] = view.get<TransformComponent, CircleRendererComponent>(entity);
                
                Graphics::Renderer2D::DrawCircle(transform.GetTransform(), circle.color, circle.thickness, circle.fade, (int)entity);
            }
        }
        Graphics::Renderer2D::EndScene();
        
    
    }
    
    Entity Scene::CreateEntity(const std::string& name)
    {
        return CreateEntityWithUUID(UUID(), name);
    }
    
    Entity Scene::CreateEntityWithUUID(UUID uuid, const std::string& name)
    {
        Entity entity = { registry.create(), this };
        entity.AddComponent<IDComponent>(uuid);
        auto& tag = entity.AddComponent<NameComponent>();
        tag.name = name.empty() ? "Entity" : name;
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
        std::string name = entity.GetName();
        Entity newEntity = CreateEntity(name);
        CopyComponentIfExists(AllComponents{}, newEntity, entity);
        return newEntity;
    }
    
    Entity Scene::FindEntityByName(std::string_view name)
    {
        auto view = registry.view<NameComponent>();
        for (auto entity : view)
        {
            const NameComponent& tc = view.get<NameComponent>(entity);
            if (tc.name == name)
                return Entity{ entity, this };
        }
        return {};
    }
    
    Entity Scene::GetEntityByUUID(UUID uuid)
    {
        // TODO(Yan): Maybe should be assert
        if (entityMap.find(uuid) != entityMap.end())
            return { entityMap.at(uuid), this };
        
        return {};
    }
    
    bool Scene::IsRunning()const{return isRunning;}
    bool Scene::IsPaused()const{return isPaused;}
    void Scene::SetPaused(bool paused){isPaused=paused;}
    
    
   
   
    
    
    
    void Scene::Step(int frames)
    {
        stepFrames=frames;
    }
    
    
    
    Entity Scene::GetPrimaryCameraEntity()
    {
        auto view = registry.view<CameraComponent>();
        
        for (auto entity : view)
        {
            const auto& camera = view.get<CameraComponent>(entity);
            if(camera.primary)
            {
                return Entity{entity, this};
            }
        }
        return {};
    }
    
   
    
    void Scene::OnRuntimeStart(){isRunning=true;}
    void Scene::OnUpdateRuntime()
    {
        if (!isPaused || stepFrames-- > 0)
        {
            registry.view<NativeScriptComponent>().each([this](auto entity, auto& nsc)
            {
                if (!nsc.instance)
                {
                    nsc.instance = nsc.InstantiateScript();
                    nsc.instance->entity = Entity{entity, this};
                    nsc.instance->OnCreate();
                }
                nsc.instance->OnUpdate();
            });
        }
        // Render 2D
        Graphics::Camera* mainCamera = nullptr;
        Math::Matrix4 cameraTransform;
        {
            auto view = registry.view<TransformComponent, CameraComponent>();
            for (auto entity : view)
            {
                auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);
                
                if (camera.primary)
                {
                    mainCamera = &camera.camera;
                    cameraTransform = transform.GetTransform();
                    break;
                }
            }
        }
        if (mainCamera)
        {
            Graphics::Renderer2D::BeginScene(*mainCamera, cameraTransform);
            //Draw sprites, circles, text, etc
            {
                // Sprites
                auto group = registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
                for (auto entity : group)
                {
                    auto[transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
                    Graphics::Renderer2D::DrawSprite(transform.GetTransform(), sprite, (int)entity);
                }
                
                // Circles
                auto view = registry.view<TransformComponent, CircleRendererComponent>();
                for (auto entity : view)
                {
                    auto[transform, circle] = view.get<TransformComponent, CircleRendererComponent>(entity);
                    Graphics::Renderer2D::DrawCircle(transform.GetTransform(), circle.color, circle.thickness, circle.fade, (int)entity);
                }
                
                Graphics::Renderer2D::EndScene();
            }
        }
    }
    void Scene::OnRuntimeStop(){isRunning=false;}
    
    void Scene::OnSimulationStart()
    {
    
    }
    
    void Scene::OnUpdateSimulation(Graphics::EditorCamera& camera)
    {
        if (!isPaused || stepFrames-- > 0)
        {
        
        }
        
        // Render
        RenderScene(camera);
    
    }
    void Scene::OnSimulationStop()
    {
    
    }
    
    
    void Scene::OnUpdateEditor(Graphics::EditorCamera& camera)
    {
        RenderScene(camera);
        
    }
    
    
    
    
   
    
    void Scene::OnViewportResize(uint32 width, uint32 height)
    {
        if (viewportWidth == width && viewportHeight == height)
        {
            return;
        }
        
        viewportWidth = width;
        viewportHeight = height;
        
        auto view = registry.view<CameraComponent>();
        for (auto entity : view)
        {
            auto& cameraComponent = view.get<CameraComponent>(entity);
            if (!cameraComponent.fixedAspectRatio)
            {
                cameraComponent.camera.SetViewportSize(width, height);
            }
        }
    
    }
    
    
    
    
    
    
    template<typename T>
    void Scene::OnComponentAdded(Entity entity, T& component)
    {
        static_assert(sizeof(T)==0);
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
    void Scene::OnComponentAdded<CameraComponent>(Entity entity, CameraComponent& component)
    {
        if (viewportWidth > 0 && viewportHeight > 0)
            component.camera.SetViewportSize(viewportWidth, viewportHeight);
    }
    
    template<>
    void Scene::OnComponentAdded<ScriptComponent>(Entity entity, ScriptComponent& component)
    {
    }
    
    template<>
    void Scene::OnComponentAdded<NameComponent>(Entity entity, NameComponent& component)
    {
    }
    
    template<>
    void Scene::OnComponentAdded<CircleRendererComponent>(Entity entity, CircleRendererComponent& component)
    {
    }
    
    template<>
    void Scene::OnComponentAdded<SpriteRendererComponent>(Entity entity, SpriteRendererComponent& component)
    {
    }
    
    template<>
    void Scene::OnComponentAdded<NativeScriptComponent>(Entity entity, NativeScriptComponent& component)
    {
    }

}
