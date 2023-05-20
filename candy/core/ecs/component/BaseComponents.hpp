#pragma once

#include "../../../include/Candy/Math.hpp"


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
            ScriptableEntity(*InstantiateScript)();
            void(*DestroyScript)(NativeScriptComponent*);
            
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
            ComponentGroup<TransformComponent, ScriptComponent,
                    NativeScriptComponent>;
}
