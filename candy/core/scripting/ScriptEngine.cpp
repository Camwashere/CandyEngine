#include "ScriptEngine.hpp"
#include <Candy/App.hpp>
#include <Candy/Utils.hpp>
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include "mono/metadata/mono-debug.h"
#include <mono/metadata/object.h>
#include "mono/metadata/tabledefs.h"
#include <mono/metadata/threads.h>
#define MONO_HOME "C:/Program Files/Mono"
namespace Candy::Scripting
{
    ScriptEngineData* ScriptEngine::data = new ScriptEngineData();
    static std::unordered_map<std::string, ScriptFieldType> s_ScriptFieldTypeMap =
            {
                    { "System.Single", ScriptFieldType::Float },
                    { "System.Double", ScriptFieldType::Double },
                    { "System.Boolean", ScriptFieldType::Bool },
                    { "System.Char", ScriptFieldType::Char },
                    { "System.Int16", ScriptFieldType::Short },
                    { "System.Int32", ScriptFieldType::Int },
                    { "System.Int64", ScriptFieldType::Long },
                    { "System.Byte", ScriptFieldType::Byte },
                    { "System.UInt16", ScriptFieldType::UShort },
                    { "System.UInt32", ScriptFieldType::UInt },
                    { "System.UInt64", ScriptFieldType::ULong },
                    
                    { "Candy.Vector2", ScriptFieldType::Vector2 },
                    { "Candy.Vector3", ScriptFieldType::Vector3 },
                    { "Candy.Vector4", ScriptFieldType::Vector4 },
                    
                    { "Candy.Entity", ScriptFieldType::Entity },
            };
    
    namespace Utils {
        
        static MonoAssembly* LoadMonoAssembly(const std::filesystem::path& assemblyPath, bool loadPDB = false)
        {
            ScopedBuffer fileData = Candy::Utils::FileSystem::ReadFileBinary(assemblyPath);
            
            // NOTE: We can't use this image for anything other than loading the assembly because this image doesn't have a reference to the assembly
            MonoImageOpenStatus status;
            MonoImage* image = mono_image_open_from_data_full(fileData.As<char>(), fileData.Size(), 1, &status, 0);
            
            if (status != MONO_IMAGE_OK)
            {
                const char* errorMessage = mono_image_strerror(status);
                // Log some error message using the errorMessage data
                return nullptr;
            }
            
            if (loadPDB)
            {
                std::filesystem::path pdbPath = assemblyPath;
                pdbPath.replace_extension(".pdb");
                
                if (std::filesystem::exists(pdbPath))
                {
                    ScopedBuffer pdbFileData = Candy::Utils::FileSystem::ReadFileBinary(pdbPath);
                    mono_debug_open_image_from_memory(image, pdbFileData.As<const mono_byte>(), pdbFileData.Size());
                    std::string loadedAssembly = pdbPath.string();
                    CANDY_CORE_INFO("Loaded PDB for assembly: {}", loadedAssembly);
                }
            }
            
            std::string pathString = assemblyPath.string();
            MonoAssembly* assembly = mono_assembly_load_from_full(image, pathString.c_str(), &status, 0);
            mono_image_close(image);
            
            return assembly;
        }
        
        void PrintAssemblyTypes(MonoAssembly* assembly)
        {
            MonoImage* image = mono_assembly_get_image(assembly);
            const MonoTableInfo* typeDefinitionsTable = mono_image_get_table_info(image, MONO_TABLE_TYPEDEF);
            int32 numTypes = mono_table_info_get_rows(typeDefinitionsTable);
            
            for (int32 i = 0; i < numTypes; i++)
            {
                uint32_t cols[MONO_TYPEDEF_SIZE];
                mono_metadata_decode_row(typeDefinitionsTable, i, cols, MONO_TYPEDEF_SIZE);
                
                const char* nameSpace = mono_metadata_string_heap(image, cols[MONO_TYPEDEF_NAMESPACE]);
                const char* name = mono_metadata_string_heap(image, cols[MONO_TYPEDEF_NAME]);
                CANDY_CORE_TRACE("{}.{}", nameSpace, name);
            }
        }
        
        ScriptFieldType MonoTypeToScriptFieldType(MonoType* monoType)
        {
            std::string typeName = mono_type_get_name(monoType);
            
            auto it = s_ScriptFieldTypeMap.find(typeName);
            if (it == s_ScriptFieldTypeMap.end())
            {
                CANDY_CORE_ERROR("Unknown type: {}", typeName);
                return ScriptFieldType::None;
            }
            
            return it->second;
        }
        
    }
    
    void ScriptEngine::OnAppAssemblyFileSystemEvent(const std::string& path, const filewatch::Event change_type)
    {
        if (!data->assemblyReloadPending && change_type == filewatch::Event::modified)
        {
            data->assemblyReloadPending = true;
            
            Application::Instance().SubmitToMainThread([]()
                                                  {
                                                      data->appAssemblyFileWatcher.reset();
                                                      ReloadAssembly();
                                                  });
        }
    }
    ScriptClass::ScriptClass(std::string  classNamespaceValue, std::string  classNameValue, bool isCore) : classNamespace(std::move(classNamespaceValue)), className(std::move(classNameValue))
    {
        monoClass = mono_class_from_name(isCore ? ScriptEngine::data->coreAssemblyImage : ScriptEngine::data->appAssemblyImage, classNamespace.c_str(), className.c_str());
    }
    MonoObject* ScriptClass::Instantiate()
    {
        return ScriptEngine::InstantiateClass(monoClass);
    }
    MonoMethod* ScriptClass::GetMethod(const std::string& name, int parameterCount)
    {
        return mono_class_get_method_from_name(monoClass, name.c_str(), parameterCount);
    }
    MonoObject* ScriptClass::InvokeMethod(MonoObject* instance, MonoMethod* method, void** params)
    {
        MonoObject* exception = nullptr;
        return mono_runtime_invoke(method, instance, params, &exception);
    }
    
    const std::map<std::string, ScriptField>& ScriptClass::GetFields()const{return fields;}
    
    
    
    
    ScriptInstance::ScriptInstance(SharedPtr<ScriptClass> scriptClassValue, ECS::Entity entity) : scriptClass(scriptClassValue)
    {
        instance = scriptClass->Instantiate();
        constructor = scriptClass->GetMethod(".ctor", 0);
        onCreateMethod = scriptClass->GetMethod("OnCreate", 0);
        onUpdateMethod = scriptClass->GetMethod("OnUpdate", 0);
        
        // Call Constructor
        {
            UUID entityID = entity.GetUUID();
            void* param = &entityID;
            scriptClass->InvokeMethod(instance, constructor, &param);
        }
    }
    
    void ScriptInstance::InvokeOnCreate()
    {
        if (onCreateMethod)
        {
            scriptClass->InvokeMethod(instance, onCreateMethod);
        }
    }
    void ScriptInstance::InvokeOnUpdate()
    {
        if (onUpdateMethod)
        {
            float val = Application::DeltaTime();
            void* param = &val;
            scriptClass->InvokeMethod(instance, onUpdateMethod, &param);
        }
    }
    
    SharedPtr<ScriptClass> ScriptInstance::GetScriptClass(){return scriptClass;}
    bool ScriptInstance::GetFieldValueInternal(const std::string& name, void* buffer)
    {
        const auto& fields = scriptClass->GetFields();
        auto it = fields.find(name);
        if (it == fields.end())
            return false;
        
        const ScriptField& field = it->second;
        mono_field_get_value(instance, field.classField, buffer);
        return true;
    
    }
    bool ScriptInstance::SetFieldValueInternal(const std::string& name, const void* value)
    {
        const auto& fields = scriptClass->GetFields();
        auto it = fields.find(name);
        if (it == fields.end())
            return false;
        
        const ScriptField& field = it->second;
        mono_field_set_value(instance, field.classField, (void*)value);
        return true;
    }
    
    MonoObject* ScriptInstance::GetManagedObject(){return instance;}
    
    void ScriptEngine::InitMono()
    {
        mono_set_dirs(MONO_HOME "/lib", MONO_HOME "/etc");
        
        MonoDomain* rootDomain = mono_jit_init("CandyJITRuntime");
        CANDY_CORE_ASSERT(rootDomain);
        data->rootDomain = rootDomain;
        mono_thread_set_main(mono_thread_current());
    }
    void ScriptEngine::ShutdownMono()
    {
        mono_domain_set(mono_get_root_domain(), false);
        
        mono_domain_unload(data->appDomain);
        data->appDomain = nullptr;
        
        mono_jit_cleanup(data->rootDomain);
        data->rootDomain = nullptr;
    }
    MonoObject* ScriptEngine::InstantiateClass(MonoClass* monoClass)
    {
        MonoObject* instance = mono_object_new(data->appDomain, monoClass);
        mono_runtime_object_init(instance);
        return instance;
    }
    void ScriptEngine::LoadAssemblyClasses()
    {
        data->entityClasses.clear();
        const MonoTableInfo* typeDefinitionsTable = mono_image_get_table_info(data->appAssemblyImage, MONO_TABLE_TYPEDEF);
        int32 numTypes = mono_table_info_get_rows(typeDefinitionsTable);
        MonoClass* entityClass = mono_class_from_name(data->coreAssemblyImage, "candy", "Entity");
        
        for (int32 i=0; i<numTypes; i++)
        {
            uint32 cols[MONO_TYPEDEF_SIZE];
            mono_metadata_decode_row(typeDefinitionsTable, i, cols, MONO_TYPEDEF_SIZE);
            const char* nameSpace = mono_metadata_string_heap(data->appAssemblyImage, cols[MONO_TYPEDEF_NAMESPACE]);
            const char* className = mono_metadata_string_heap(data->appAssemblyImage, cols[MONO_TYPEDEF_NAME]);
            std::string fullName;
            if (strlen(nameSpace) != 0)
            {
                fullName = fmt::format("{}.{}", nameSpace, className);
            }
            else
            {
                fullName = className;
            }
            
            MonoClass* monoClass = mono_class_from_name(data->appAssemblyImage, nameSpace, className);
            if (monoClass == entityClass)
            {
                continue;
            }
            bool isEntity = mono_class_is_subclass_of(monoClass, entityClass, false);
            if (!isEntity)
            {
                continue;
            }
            
            SharedPtr<ScriptClass> scriptClass=CreateSharedPtr<ScriptClass>(nameSpace, className);
            data->entityClasses[fullName] = scriptClass;
            
            // This routine is an iterator routine for retrieving the fields in a class.
            // You must pass a gpointer that points to zero and is treated as an opaque handle
            // to iterate over all of the elements. When no more values are available, the return value is NULL.
            
            int fieldCount = mono_class_num_fields(monoClass);
            CANDY_CORE_WARN("{} has {} fields:", className, fieldCount);
            void* iterator = nullptr;
            while (MonoClassField* field = mono_class_get_fields(monoClass, &iterator))
            {
                const char* fieldName = mono_field_get_name(field);
                uint32 flags = mono_field_get_flags(field);
                if (flags & FIELD_ATTRIBUTE_PUBLIC)
                {
                    MonoType* type = mono_field_get_type(field);
                    ScriptFieldType fieldType = Utils::MonoTypeToScriptFieldType(type);
                    CANDY_CORE_WARN("  {} ({})", fieldName, Utils::ScriptFieldTypeToString(fieldType));
                    
                    scriptClass->fields[fieldName] = { fieldType, fieldName, field };
                }
            }
        }
        auto& entityClasses = data->entityClasses;
    }
    
    void ScriptEngine::Init()
    {
        InitMono();
        // Script Glue register functions
        
        bool status = LoadAssembly("Resources/Scripts/candy-ScriptCore.dll");
        if (! status)
        {
            CANDY_CORE_ERROR("[ScriptEngine] Could not load candy-ScriptCore assembly");
            return;
        }
        auto scriptModulePath = Project::GetAssetDirectory() / Project::GetActive()->GetConfig().scriptModulePath;
        status = LoadAppAssembly(scriptModulePath);
        if (!status)
        {
            CANDY_CORE_ERROR("[ScriptEngine] Could not load app assembly");
            return;
        }
        LoadAssemblyClasses();
        
        // ScriptGlue register components
        
        //Retrieve and instantiate class
        data->entityClass = ScriptClass("Candy", "Entity", true);
    }
    void ScriptEngine::Shutdown()
    {
        ShutdownMono();
        delete data;
    }
    bool ScriptEngine::LoadAssembly(const std::filesystem::path& filepath)
    {
        data->appAssemblyPath = filepath;
        data->appAssembly = Utils::LoadMonoAssembly(filepath, data->enableDebugging);
        if (data->coreAssembly==nullptr)
        {
            return false;
        }
        data->coreAssemblyImage = mono_assembly_get_image(data->coreAssembly);
        return true;
    }
    bool ScriptEngine::LoadAppAssembly(const std::filesystem::path& filepath)
    {
        data->appAssemblyPath = filepath;
        data->appAssembly = Utils::LoadMonoAssembly(filepath, data->enableDebugging);
        if (data->appAssembly==nullptr)
        {
            return false;
        }
        data->appAssemblyImage = mono_assembly_get_image(data->appAssembly);
        data->appAssemblyFileWatcher = CreateUniquePtr<filewatch::FileWatch<std::string>>(filepath.string(), OnAppAssemblyFileSystemEvent);
        data->assemblyReloadPending=false;
        return true;
    }
    
    void ScriptEngine::ReloadAssembly()
    {
        mono_domain_set(mono_get_root_domain(), false);
        mono_domain_unload(data->appDomain);
        
        LoadAssembly(data->coreAssemblyPath);
        LoadAppAssembly(data->appAssemblyPath);
        LoadAssemblyClasses();
        
        //Script glue register components
        
        data->entityClass = ScriptClass("Candy", "Entity", true);
        
    }
    
    void ScriptEngine::OnRuntimeStart(ECS::Scene* scene)
    {
        data->sceneContext = scene;
    }
    void ScriptEngine::OnRuntimeStop()
    {
        data->sceneContext = nullptr;
        data->entityInstances.clear();
    }
    
    bool ScriptEngine::EntityClassExists(const std::string& fullClassName)
    {
        return data->entityClasses.find(fullClassName) != data->entityClasses.end();
    }
    void ScriptEngine::OnCreateEntity(ECS::Entity entity)
    {
        const auto& sc = entity.GetComponent<ECS::ScriptComponent>();
        if (ScriptEngine::EntityClassExists(sc.className))
        {
            UUID entityID = entity.GetUUID();
            
            SharedPtr<ScriptInstance> instance = CreateSharedPtr<ScriptInstance>(data->entityClasses[sc.className], entity);
            data->entityInstances[entityID] = instance;
            
            // Copy field values
            if (data->entityScriptFields.find(entityID) != data->entityScriptFields.end())
            {
                const auto& fieldMap = data->entityScriptFields.at(entityID);
                for (const auto& [name, fieldInstance] : fieldMap)
                    instance->SetFieldValueInternal(name, fieldInstance.buffer);
            }
            
            instance->InvokeOnCreate();
        
        }
    }
    void ScriptEngine::OnUpdateEntity(ECS::Entity entity)
    {
        UUID entityUUID = entity.GetUUID();
        if (data->entityInstances.find(entityUUID) != data->entityInstances.end())
        {
            SharedPtr<ScriptInstance> instance = data->entityInstances[entityUUID];
            instance->InvokeOnUpdate();
        }
        else
        {
            CANDY_CORE_ERROR("[Script Engine] Could not find ScriptInstance for entity {}", entityUUID);
        }
    }
    
    ECS::Scene* ScriptEngine::GetSceneContext()
    {
        return data->sceneContext;
    }
    SharedPtr<ScriptInstance> ScriptEngine::GetEntityScriptInstance(uint entityID)
    {
        auto it = data->entityInstances.find(entityID);
        if (it == data->entityInstances.end())
        {
            return nullptr;
        }
        return it->second;
    }
    
    SharedPtr<ScriptClass> ScriptEngine::GetEntityClass(const std::string& name)
    {
        if (data->entityClasses.find(name) == data->entityClasses.end())
        {
            return nullptr;
        }
        return data->entityClasses.at(name);
    }
    std::unordered_map<std::string, SharedPtr<ScriptClass>> ScriptEngine::GetEntityClasses()
    {
        return data->entityClasses;
    }
    std::unordered_map<std::string, ScriptFieldInstance>& ScriptEngine::GetScriptFieldMap(ECS::Entity entity)
    {
        CANDY_CORE_ASSERT(entity);
        UUID entityID = entity.GetUUID();
        return data->entityScriptFields[entityID];
    }
    
    MonoImage* ScriptEngine::GetCoreAssemblyImage()
    {
        return data->coreAssemblyImage;
    }
    
    MonoObject* ScriptEngine::GetManagedInstance(UUID uuid)
    {
        CANDY_CORE_ASSERT(data->entityInstances.find(uuid) != data->entityInstances.end());
        return data->entityInstances.at(uuid)->GetManagedObject();
    }
    
    
    
    
    
}
