#pragma once
#include <Candy/Math.hpp>
#include "../scene/SceneCamera.hpp"

namespace Candy::ECS{
        struct IDComponent {
            UUID id;
        };
        
        struct NameComponent {
            std::string name;
        };
        
        struct TransformComponent {
            Math::Vector3 position;
            Math::Quaternion rotation;
            Math::Vector3 scale;
            
            Math::Matrix4 GetTransform() const {
                Math::Matrix4 rot = Math::Matrix4::Rotated(rotation);
                return Math::Matrix4::Translation(position) * rot * Math::Matrix4::Scaled(scale);
            }
        };
        
        struct CameraComponent
        {
            Graphics::SceneCamera camera;
            bool primary=true;
            bool fixedAspectRatio=false;
            
            CameraComponent()=default;
            CameraComponent(const CameraComponent&)=default;
        };
        
        struct TestComponent
        {
            std::string name;
            int value;
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
            ComponentGroup<TransformComponent, ScriptComponent, NativeScriptComponent>;
}
