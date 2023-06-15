#include "SceneSerializer.hpp"
#include <Candy/Math.hpp>
#include <ryml_std.hpp>
#include <ryml.hpp>
#include <c4/format.hpp>
#include <Candy/ECS.hpp>
#include "SceneCamera.hpp"
#include <sstream>



// define a conversion function for Vector2
size_t to_chars(c4::substr buf, const Candy::Math::Vector2& v)
{
    return c4::format(buf, "[{},{}]", v.x, v.y);
}

// define a conversion function for Candy::Math::Vector2
bool from_chars(c4::csubstr buf, Candy::Math::Vector2 *v)
{
    return c4::unformat(buf, "[{},{}]", v->x, v->y);
}
// define a conversion function for Candy::Math::Vector3
size_t to_chars(c4::substr buf, Candy::Math::Vector3& v)
{
    return c4::format(buf, "[{},{},{}]", v.x, v.y, v.z);
}

// define a conversion function for Candy::Math::Vector3
bool from_chars(c4::csubstr buf, Candy::Math::Vector3& v)
{
    std::size_t ret = c4::unformat(buf, "[{},{},{}]", v.x, v.y, v.z);
    return ret != c4::csubstr::npos;
}



// define a conversion function for Candy::Math::Vector4
size_t to_chars(c4::substr buf, const Candy::Math::Vector4& v)
{
    return c4::format(buf, "[{},{},{},{}]", v.x, v.y, v.z, v.w);
}

// define a conversion function for Candy::Math::Vector4
bool from_chars(c4::csubstr buf, Candy::Math::Vector4 *v)
{
    return c4::unformat(buf, "[{},{},{},{}]", v->x, v->y, v->z, v->w);
}

// define a conversion function for Candy::Math::Vector4
size_t to_chars(c4::substr buf, const Candy::Math::Quaternion& v)
{
    return c4::format(buf, "[{},{},{},{}]", v.x, v.y, v.z, v.w);
}

// define a conversion function for Candy::Math::Vector4
bool from_chars(c4::csubstr buf, Candy::Math::Quaternion *v)
{
    return c4::unformat(buf, "[{},{},{},{}]", v->x, v->y, v->z, v->w);
}




namespace Candy::ECS
{
    
    using namespace Candy::Math;
    using namespace Graphics;
    
    
    SceneSerializer::SceneSerializer(const SharedPtr<Scene>& sceneVal)
    : scene(sceneVal)
    {
    
    }
    
    static void SerializeEntity(c4::yml::NodeRef& root, Entity entity)
    {
        CANDY_CORE_ASSERT(entity.HasComponent<IDComponent>());
        auto ref = root["Scene"]["Entities"];
        ref["Entity"] |= c4::yml::MAP;
        ref["Entity"] << (uint64_t)entity.GetUUID();
        
        if (entity.HasComponent<NameComponent>())
        {
            ref["Entity"]["NameComponent"] |= c4::yml::MAP;
            ref["Entity"]["NameComponent"] << entity.GetName();
        }
        if (entity.HasComponent<TransformComponent>())
        {
            auto& transform = entity.GetComponent<TransformComponent>();
            ref["Entity"]["TransformComponent"] |= c4::yml::MAP;
            ref["Entity"]["TransformComponent"]["Position"] << &transform.position;
            ref["Entity"]["TransformComponent"]["Rotation"] << &transform.rotation;
            ref["Entity"]["TransformComponent"]["Scale"] << &transform.scale;
            
            
        }
        if (entity.HasComponent<CameraComponent>())
        {
            ref["Entity"]["CameraComponent"] |= c4::yml::MAP;
            
            auto& cameraComponent = entity.GetComponent<CameraComponent>();
            auto& camera = cameraComponent.camera;
            
            ref["Entity"]["CameraComponent"]["Camera"] |= c4::yml::MAP;
            ref["Entity"]["CameraComponent"]["Camera"]["ProjectionType"] << (int)camera.GetProjectionType();
            
            ref["Entity"]["CameraComponent"]["PerspectiveFOV"] << camera.GetPerspectiveVerticalFov();
            ref["Entity"]["CameraComponent"]["PerspectiveNear"] << camera.GetPerspectiveNearClip();
            ref["Entity"]["CameraComponent"]["PerspectiveFar"] << camera.GetPerspectiveFarClip();
            ref["Entity"]["CameraComponent"]["OrthographicSize"]  << camera.GetOrthographicSize();
            ref["Entity"]["CameraComponent"]["OrthographicNear"] << camera.GetOrthographicNearClip();
            ref["Entity"]["CameraComponent"]["OrthographicFar"] << camera.GetOrthographicFarClip();
            
            ref["Entity"]["CameraComponent"]["Primary"] << cameraComponent.primary;
            ref["Entity"]["CameraComponent"]["FixedAspectRatio"] << cameraComponent.fixedAspectRatio;
            
        }
    }
    
    void SceneSerializer::Serialize(const std::string& filepath)
    {
        CANDY_CORE_INFO("Serializing scene");
        c4::yml::Tree tree;
        c4::yml::NodeRef root = tree.rootref();
        
        root |= c4::yml::MAP;
        root["Scene"] |= c4::yml::MAP;
        root["Scene"]["Name"] << scene->name;
        root["Scene"]["Entities"] |= c4::yml::SEQ;
        
        
        scene->registry.each([this, &root](auto entityID)
        {
           Entity entity={entityID, scene.get()};
           if (!entity)
           {
               return;
           }
           
           SerializeEntity(root, entity);
        });
        
        std::ofstream fout(filepath);
        fout << c4::yml::emit_yaml(tree);
    
    }
    void SceneSerializer::SerializeRuntime(const std::string& filepath)
    {
        //Not implemented
        CANDY_CORE_ASSERT(false);
    
    }
    
    bool SceneSerializer::Deserialize(const std::string& filepath)
    {
        CANDY_CORE_INFO("DESERIALIZING SCENE");
        // read the file into a string
        std::ifstream fin(filepath);
        std::stringstream buffer;
        buffer << fin.rdbuf();
        std::string yaml_str = buffer.str();
        
        if (yaml_str.empty())
        {
            CANDY_CORE_ERROR("EMPTY YAML STRING WITH PATH: {}", filepath);
        }
        
        // parse the YAML string
        ryml::Tree tree = ryml::parse_in_arena(ryml::to_csubstr(yaml_str));
        ryml::NodeRef root = tree.rootref();
        
        
        auto projectNode = root["Scene"];
        
        if (projectNode.empty())
        {
            CANDY_CORE_ERROR("EMPTY PROJECT NODE");
            return false;
        }
        
        projectNode >> scene->name;
        CANDY_CORE_INFO("SCENE NAME: {}", scene->name);
        auto entitiesNode = root["Entities"];
        
        if (entitiesNode.valid())
        {
            CANDY_CORE_INFO("ENTITIES NODE VALID");
            for (auto entity : entitiesNode)
            {
                uint64_t uuid;
                entity["Entity"] >> uuid;
                CANDY_CORE_INFO("ENTITY VALID");
                
                std::string name;
                auto nameComponent = entity["NameComponent"]["Name"];
                CANDY_CORE_INFO("NAME COMPONENT VALID");
                if (nameComponent.valid())
                {
                    nameComponent >> name;
                    //name.assign(nameComponent.val().begin(), nameComponent.val().end());
                }
                CANDY_CORE_TRACE("Deserialized entity with ID = {0}, name = {1}", uuid, name);
                
                Entity deserializedEntity = scene->CreateEntityWithUUID(uuid, name);
                
                auto transformComponent = entity["TransformComponent"];
                
                if (transformComponent.has_key())
                {
                    CANDY_CORE_INFO("TRANSFORM COMPONENT VALID");
                    auto& tc = deserializedEntity.GetComponent<TransformComponent>();
                    CANDY_CORE_INFO("GOT TRANSFORM COMPONENT");
                    Vector3* pos = &tc.position;
                    Quaternion* rot = &tc.rotation;
                    Vector3* scale = &tc.scale;
                    //emit_yaml(transformComponent);
                    transformComponent["Position"][0] >> pos->x;
                    transformComponent["Position"][1] >> pos->y;
                    transformComponent["Position"][2] >> pos->z;
                    
                    transformComponent["Rotation"][0] >> rot->x;
                    transformComponent["Rotation"][1] >> rot->y;
                    transformComponent["Rotation"][2] >> rot->z;
                    
                    /*transformComponent["Position"] >> pos;
                    transformComponent["Rotation"] >> rot;
                    transformComponent["Scale"] >> scale;
                    CANDY_CORE_INFO("TRANSFORM COMPONENT ASSIGNED");
                    //tc.position = *pos;
                    //tc.rotation = *rot;
                    //tc.scale = *scale;
                    CANDY_CORE_INFO("DESERIALIZED TRANSFORM COMPONENT");*/
                }
                
                /*auto cameraComponent = entity["CameraComponent"];
                if (!cameraComponent.empty())
                {
                    auto& cc = deserializedEntity.AddComponent<CameraComponent>();
                    
                    auto cameraProps = cameraComponent["Camera"];
                    
                    emit_yaml(cameraProps);
                    int projectionType=1;
                    //cameraProps["ProjectionType"] >> projectionType;
                    CANDY_CORE_INFO("ADDED PROJECTION TYPE");
                    
                    cc.camera.SetProjectionType((SceneCamera::ProjectionType)projectionType);
                    
                    float perspectiveFov;
                    float perspectiveNear;
                    float perspectiveFar;
                    float orthographicSize;
                    float orthographicNear;
                    float orthographicFar;
                    
                    cameraProps["PerspectiveFOV"] >> perspectiveFov;
                    cameraProps["PerspectiveNear"] >> perspectiveNear;
                    cameraProps["PerspectiveFar"] >> perspectiveFar;
                    cameraProps["OrthographicSize"] >> orthographicSize;
                    cameraProps["OrthographicNear"] >> orthographicNear;
                    cameraProps["OrthographicFar"] >> orthographicFar;
                    cc.camera.SetPerspectiveVerticalFov(perspectiveFov);
                    cc.camera.SetPerspectiveNearClip(perspectiveNear);
                    cc.camera.SetPerspectiveFarClip(perspectiveFar);
                    
                    cc.camera.SetOrthographicSize(orthographicSize);
                    cc.camera.SetOrthographicNearClip(orthographicNear);
                    cc.camera.SetOrthographicFarClip(orthographicFar);
                    CANDY_CORE_INFO("ADDED CAMERA PROPS");
                    
                    
                    
                }*/
                
            }
        }
        
        
        
        
        return true;
    
    }
    bool SceneSerializer::DeserializeRuntime(const std::string& filepath)
    {
        //Not implemented
        CANDY_CORE_ASSERT(false);
        return false;
    }
}

