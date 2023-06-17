#pragma once
#include <Candy/Math.hpp>
#include "../scene/SceneCamera.hpp"
#include "../../graphics/color/Color.hpp"
#include "../../graphics/rendering/data/texture/Texture.hpp"
namespace Candy::ECS{
        struct IDComponent {
            UUID id;
        };
        
        struct NameComponent {
            std::string name;
        };
        
        struct TransformComponent {
            Math::Vector3 position = {0.0f, 0.0f, 0.0f};
            Math::Quaternion rotation = {0.0f, 0.0f, 0.0f, 1.0f};
            Math::Vector3 scale={1.0f, 1.0f, 1.0f};
            
            Math::Matrix4 GetTransform() const {
                Math::Matrix4 rot = Math::Matrix4::Rotated(rotation);
                return Math::Matrix4::Translation(position) * rot * Math::Matrix4::Scaled(scale);
            }
        };
    
   struct SpriteRendererComponent
   {
       Color color=Color::white;
       SharedPtr<Graphics::Texture> texture;
       float tilingFactor=1.0f;
       
       SpriteRendererComponent()=default;
       SpriteRendererComponent(const SpriteRendererComponent&)=default;
       explicit SpriteRendererComponent(const Color& colorValue) : color(colorValue){}
   };
   
   struct CircleRendererComponent
   {
       Color color=Color::white;
       float thickness=1.0f;
       float fade=0.005f;
       
       CircleRendererComponent()=default;
       CircleRendererComponent(const CircleRendererComponent&)=default;
   };
    
    
    struct CameraComponent
        {
            Graphics::SceneCamera camera;
            bool primary=true;
            bool fixedAspectRatio=false;
            
            CameraComponent()=default;
            CameraComponent(const CameraComponent&)=default;
        };
        
        
        
        
        
        struct ScriptComponent
        {
            std::string className;
            
            ScriptComponent()=default;
            ScriptComponent(const ScriptComponent&)=default;
        };
        
        class ScriptableEntity;
        
        
        
        struct NativeScriptComponent
        {
            ScriptableEntity* instance = nullptr;
            ScriptableEntity*(*InstantiateScript)()=nullptr;
            void(*DestroyScript)(NativeScriptComponent*)=nullptr;
            template<typename T>
            void Bind()
            {
                InstantiateScript = [](){return static_cast<ScriptableEntity*>(new T());};
                DestroyScript = [](NativeScriptComponent* nativeScriptComponent){delete nativeScriptComponent->instance; nativeScriptComponent->instance=nullptr;};
            }
        };
    
        template<typename... Component>
        struct ComponentGroup
        {
        };
    
    using AllComponents =
            ComponentGroup<IDComponent, NameComponent, TransformComponent, ScriptComponent, NativeScriptComponent, SpriteRendererComponent, CircleRendererComponent>;
}
