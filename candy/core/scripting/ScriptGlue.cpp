
#include "ScriptGlue.hpp"
#include "ScriptEngine.hpp"


#include <Candy/Events.hpp>
#include <Candy/ECS.hpp>
#include <Candy/Math.hpp>
#include "mono/metadata/object.h"
#include "mono/metadata/reflection.h"



namespace Candy::Scripting {
    
    static std::unordered_map<MonoType*, std::function<bool(ECS::Entity)>> entityHasComponentFuncs;

#define CANDY_ADD_INTERNAL_CALL(Name) mono_add_internal_call("candy.InternalCalls::" #Name, (void*)Name)
    
    static void NativeLog(MonoString* string, int parameter)
    {
        char* cStr = mono_string_to_utf8(string);
        std::string str(cStr);
        mono_free(cStr);
        std::cout << str << ", " << parameter << std::endl;
    }
    
    static void NativeLog_Vector(Math::Vector3* parameter, Math::Vector3* outResult)
    {
        CANDY_CORE_WARN("Value: {0}", (std::string)*parameter);
        *outResult = Math::Vector3::Normalize(*parameter);
    }
    
    static float NativeLog_VectorDot(Math::Vector3* parameter)
    {
        CANDY_CORE_WARN("Value: {0}", (std::string)*parameter);
        return Math::Vector3::Dot(*parameter, *parameter);
    }
    
    static MonoObject* GetScriptInstance(UUID entityID)
    {
        return ScriptEngine::GetManagedInstance(entityID);
    }
    
    static bool Entity_HasComponent(UUID entityID, MonoReflectionType* componentType)
    {
        ECS::Scene* scene = ScriptEngine::GetSceneContext();
        CANDY_CORE_ASSERT(scene);
        ECS::Entity entity = scene->GetEntityByUUID(entityID);
        CANDY_CORE_ASSERT(entity);
        
        MonoType* managedType = mono_reflection_type_get_type(componentType);
        CANDY_CORE_ASSERT(entityHasComponentFuncs.find(managedType) != entityHasComponentFuncs.end());
        return entityHasComponentFuncs.at(managedType)(entity);
    }
    
    static uint64_t Entity_FindEntityByName(MonoString* name)
    {
        char* nameCStr = mono_string_to_utf8(name);
        
        ECS::Scene* scene = ScriptEngine::GetSceneContext();
        CANDY_CORE_ASSERT(scene);
        ECS::Entity entity = scene->FindEntityByName(nameCStr);
        mono_free(nameCStr);
        
        if (!entity)
            return 0;
        
        return entity.GetUUID();
    }
    
    static void TransformComponent_GetPosition(UUID entityID, Math::Vector3* outTranslation)
    {
        ECS::Scene* scene = ScriptEngine::GetSceneContext();
        CANDY_CORE_ASSERT(scene);
        ECS::Entity entity = scene->GetEntityByUUID(entityID);
        CANDY_CORE_ASSERT(entity);
        
        *outTranslation = entity.GetComponent<ECS::TransformComponent>().position;
    }
    
    static void TransformComponent_SetPosition(UUID entityID, Math::Vector3* translation)
    {
        ECS::Scene* scene = ScriptEngine::GetSceneContext();
        CANDY_CORE_ASSERT(scene);
        ECS::Entity entity = scene->GetEntityByUUID(entityID);
        CANDY_CORE_ASSERT(entity);
        
        entity.GetComponent<ECS::TransformComponent>().position = *translation;
    }
    
    
    static bool Input_IsKeyDown(KeyCode keycode)
    {
        return Input::IsKeyPressed(keycode);
    }
    
    template<typename... Component>
    static void RegisterComponent()
    {
        ([]()
        {
            std::string_view typeName = typeid(Component).name();
            size_t pos = typeName.find_last_of(':');
            std::string_view structName = typeName.substr(pos + 1);
            std::string managedTypename = fmt::format("Hazel.{}", structName);
            
            MonoType* managedType = mono_reflection_type_from_name(managedTypename.data(), ScriptEngine::GetCoreAssemblyImage());
            if (!managedType)
            {
                CANDY_CORE_ERROR("Could not find component type {}", managedTypename);
                return;
            }
            entityHasComponentFuncs[managedType] = [](ECS::Entity entity) { return entity.HasComponent<Component>(); };
        }(), ...);
    }
    
    template<typename... Component>
    static void RegisterComponent(ECS::ComponentGroup<Component...>)
    {
        RegisterComponent<Component...>();
    }
    
    void ScriptGlue::RegisterComponents()
    {
        entityHasComponentFuncs.clear();
        RegisterComponent(ECS::AllComponents{});
    }
    
    void ScriptGlue::RegisterFunctions()
    {
        CANDY_ADD_INTERNAL_CALL(NativeLog);
        CANDY_ADD_INTERNAL_CALL(NativeLog_Vector);
        CANDY_ADD_INTERNAL_CALL(NativeLog_VectorDot);
        
        CANDY_ADD_INTERNAL_CALL(GetScriptInstance);
        
        CANDY_ADD_INTERNAL_CALL(Entity_HasComponent);
        CANDY_ADD_INTERNAL_CALL(Entity_FindEntityByName);
        
        CANDY_ADD_INTERNAL_CALL(TransformComponent_GetPosition);
        CANDY_ADD_INTERNAL_CALL(TransformComponent_SetPosition);
        
        CANDY_ADD_INTERNAL_CALL(Input_IsKeyDown);
    }
    
}