#pragma once
#include <Candy/CandyEngineBase.hpp>
#include <Candy/ECS.hpp>

#include <filesystem>
#include <FileWatch.hpp>
#include <mono/utils/mono-forward.h>

extern "C" {
typedef struct _MonoClass MonoClass;
typedef struct _MonoObject MonoObject;
typedef struct _MonoMethod MonoMethod;
typedef struct _MonoAssembly MonoAssembly;
typedef struct _MonoImage MonoImage;
typedef struct _MonoClassField MonoClassField;
}

namespace Candy
{
    class Project;
}

namespace Candy::Scripting
{
    
    enum class ScriptFieldType
    {
        None = 0,
        Float, Double,
        Bool, Char, Byte, Short, Int, Long,
        UByte, UShort, UInt, ULong,
        Vector2, Vector3, Vector4,
        Entity
    };
    
    struct ScriptField
    {
        ScriptFieldType type;
        std::string name;
        MonoClassField *classField;
        
    };
    
    struct ScriptFieldInstance
    {
    private:
        uint8 buffer[16]{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        ScriptField field;
        friend class ScriptEngine;
        friend class ScriptInstance;
    
    public:
        ScriptFieldInstance()=default;
    
    public:
        template<typename T>
        T GetValue()
        {
            static_assert(sizeof(T) <= 16, "Type Exceeds Size Limit");
            return *(T*)buffer;
        }
        template<typename T>
        void SetValue(T value)
        {
            static_assert(sizeof(T) <= 16, "Type Exceeds Size Limit");
            memcpy(buffer, &value, sizeof(T));
        }
    };
    class ScriptClass
    {
    private:
        std::string classNamespace;
        std::string className;
        std::map<std::string, ScriptField> fields;
        MonoClass* monoClass=nullptr;
    
    public:
        ScriptClass()=default;
        ScriptClass(std::string  classNamespaceValue, std::string  classNameValue, bool isCore=false);
        MonoObject* Instantiate();
        MonoMethod* GetMethod(const std::string& name, int parameterCount);
        MonoObject* InvokeMethod(MonoObject* instance, MonoMethod* method, void** params=nullptr);
        
        const std::map<std::string, ScriptField>& GetFields()const;
        
    private:
        friend class ScriptEngine;
    };
    
    class ScriptInstance
    {
    private:
        SharedPtr<ScriptClass> scriptClass;
        MonoObject* instance=nullptr;
        MonoMethod* constructor = nullptr;
        MonoMethod* onCreateMethod = nullptr;
        MonoMethod* onUpdateMethod = nullptr;
        inline static char fieldValueBuffer[16];
        
        friend class ScriptEngine;
        friend struct ScriptFieldInstance;
    
    private:
        bool GetFieldValueInternal(const std::string& name, void* buffer);
        bool SetFieldValueInternal(const std::string& name, const void* value);
    
    public:
        ScriptInstance(SharedPtr<ScriptClass> scriptClassValue, ECS::Entity entity);
        
        void InvokeOnCreate();
        void InvokeOnUpdate();
        
        SharedPtr<ScriptClass> GetScriptClass();
        
        template<typename T>
        T GetFieldValue(const std::string& name)
        {
            static_assert(sizeof(T) <= 16, "Type Exceeds Size Limit");
            
            bool success = GetFieldValueInternal(name, fieldValueBuffer);
            if (! success)
            {
                return T();
            }
            return *(T*)fieldValueBuffer;
        }
        template<typename T>
        void SetFieldValue(const std::string& name, T value)
        {
            static_assert(sizeof(T) <= 16, "Type too large!");
            
            SetFieldValueInternal(name, &value);
        }
        
        MonoObject* GetManagedObject();
        
    };
    
    struct ScriptEngineData
    {
        MonoDomain* rootDomain = nullptr;
        MonoDomain* appDomain = nullptr;
        
        MonoAssembly* coreAssembly = nullptr;
        MonoImage* coreAssemblyImage = nullptr;
        
        MonoAssembly* appAssembly = nullptr;
        MonoImage* appAssemblyImage = nullptr;
        
        
        std::filesystem::path coreAssemblyPath;
        std::filesystem::path appAssemblyPath;
        
        ScriptClass entityClass;
        
        std::unordered_map<std::string, SharedPtr<ScriptClass>>  entityClasses;
        std::unordered_map<uint, SharedPtr<ScriptInstance>> entityInstances;
        std::unordered_map<uint, std::unordered_map<std::string, ScriptFieldInstance>> entityScriptFields;
        
        UniquePtr<filewatch::FileWatch<std::string>> appAssemblyFileWatcher;
        bool assemblyReloadPending = false;
        
        #ifdef CANDY_DEBUG
        bool enableDebugging=true;
        #else
        bool enableDebugging=false;
        #endif
        
        ECS::Scene* sceneContext=nullptr;
    };
    
    class ScriptEngine
    {
    public:
        static ScriptEngineData* data;
        
    private:
        static void InitMono();
        static void ShutdownMono();
        static MonoObject* InstantiateClass(MonoClass* monoClass);
        static void LoadAssemblyClasses();
        static void OnAppAssemblyFileSystemEvent(const std::string& path, const filewatch::Event change_type);
        
        
    public:
        static void Init();
        static void Shutdown();
        static bool LoadAssembly(const std::filesystem::path& filepath);
        static bool LoadAppAssembly(const std::filesystem::path& filepath);
        
        static void ReloadAssembly();
        
        static void OnRuntimeStart(ECS::Scene* scene);
        static void OnRuntimeStop();
        
        static bool EntityClassExists(const std::string& fullClassName);
        static void OnCreateEntity(ECS::Entity entity);
        static void OnUpdateEntity(ECS::Entity entity);
        
        static ECS::Scene* GetSceneContext();
        static SharedPtr<ScriptInstance> GetEntityScriptInstance(uint entityID);
        
        static SharedPtr<ScriptClass> GetEntityClass(const std::string& name);
        static std::unordered_map<std::string, SharedPtr<ScriptClass>> GetEntityClasses();
        static std::unordered_map<std::string, ScriptFieldInstance>& GetScriptFieldMap(ECS::Entity entity);
        
        static MonoImage* GetCoreAssemblyImage();
        
        static MonoObject* GetManagedInstance(UUID uuid);
        
    private:
        friend class ScriptClass;
        
    
    };
    
    namespace Utils
    {
        inline const char* ScriptFieldTypeToString(ScriptFieldType fieldType)
        {
            switch (fieldType)
            {
                case ScriptFieldType::None:    return "None";
                case ScriptFieldType::Float:   return "Float";
                case ScriptFieldType::Double:  return "Double";
                case ScriptFieldType::Bool:    return "Bool";
                case ScriptFieldType::Char:    return "Char";
                case ScriptFieldType::Byte:    return "Byte";
                case ScriptFieldType::Short:   return "Short";
                case ScriptFieldType::Int:     return "Int";
                case ScriptFieldType::Long:    return "Long";
                case ScriptFieldType::UByte:   return "UByte";
                case ScriptFieldType::UShort:  return "UShort";
                case ScriptFieldType::UInt:    return "UInt";
                case ScriptFieldType::ULong:   return "ULong";
                case ScriptFieldType::Vector2: return "Vector2";
                case ScriptFieldType::Vector3: return "Vector3";
                case ScriptFieldType::Vector4: return "Vector4";
                case ScriptFieldType::Entity:  return "Entity";
            }
            CANDY_CORE_ASSERT(false, "Unknown ScriptFieldType");
            return "None";
        }
        
        inline ScriptFieldType ScriptFieldTypeFromString(std::string_view fieldType)
        {
            if (fieldType == "None")    return ScriptFieldType::None;
            if (fieldType == "Float")   return ScriptFieldType::Float;
            if (fieldType == "Double")  return ScriptFieldType::Double;
            if (fieldType == "Bool")    return ScriptFieldType::Bool;
            if (fieldType == "Char")    return ScriptFieldType::Char;
            if (fieldType == "Byte")    return ScriptFieldType::Byte;
            if (fieldType == "Short")   return ScriptFieldType::Short;
            if (fieldType == "Int")     return ScriptFieldType::Int;
            if (fieldType == "Long")    return ScriptFieldType::Long;
            if (fieldType == "UByte")   return ScriptFieldType::UByte;
            if (fieldType == "UShort")  return ScriptFieldType::UShort;
            if (fieldType == "UInt")    return ScriptFieldType::UInt;
            if (fieldType == "ULong")   return ScriptFieldType::ULong;
            if (fieldType == "Vector2") return ScriptFieldType::Vector2;
            if (fieldType == "Vector3") return ScriptFieldType::Vector3;
            if (fieldType == "Vector4") return ScriptFieldType::Vector4;
            if (fieldType == "Entity")  return ScriptFieldType::Entity;
            
            CANDY_CORE_ASSERT(false, "Unknown ScriptFieldType");
            return ScriptFieldType::None;
        }
    }
    
}