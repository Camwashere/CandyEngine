#include "SceneSerializer.hpp"
#include <Candy/Math.hpp>
#include <ryml.hpp>
#include <ryml_std.hpp>
#include <c4/format.hpp>
#include <Candy/ECS.hpp>
#include <sstream>
using namespace Candy::Math;
namespace ryml
{
    // define a conversion function for Vector3
    size_t to_chars(substr buf, const Vector2& v)
    {
        return ryml::format(buf, "({},{})", v.x, v.y);
    }
    
    // define a conversion function for Vector3
    bool from_chars(csubstr buf, Vector2 *v)
    {
        return ryml::unformat(buf, "({},{})", v->x, v->y);
    }
    // define a conversion function for Vector3
    size_t to_chars(substr buf, const Vector3& v)
    {
        return ryml::format(buf, "({},{},{})", v.x, v.y, v.z);
    }

    // define a conversion function for Vector3
    bool from_chars(csubstr buf, Vector3 *v)
    {
        return ryml::unformat(buf, "({},{},{})", v->x, v->y, v->z);
    }
    
    // define a conversion function for Vector3
    size_t to_chars(substr buf, const Vector4& v)
    {
        return ryml::format(buf, "({},{},{},{})", v.x, v.y, v.z, v.w);
    }
    
    // define a conversion function for Vector3
    bool from_chars(csubstr buf, Vector4 *v)
    {
        return ryml::unformat(buf, "({},{},{},{})", v->x, v->y, v->z, v->w);
    }
    
    // define a conversion function for UUID
    size_t to_chars(substr buf, const Candy::UUID& v)
    {
        return ryml::format(buf, "{}", v);
    }
    
    // define a conversion function for UUID
    bool from_chars(csubstr buf, Candy::UUID *v)
    {
        return ryml::unformat(buf, "{}", v);
    }
    
}
namespace Candy::ECS
{
    SceneSerializer::SceneSerializer(const SharedPtr<Scene>& sceneVal)
    : scene(sceneVal)
    {
    
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
        
        scene->registry.each([&](auto entityID)
        {
           Entity entity={entityID, scene.get()};
           if (!entity)
           {
               return;
           }
           //SerializeEntity(root["Scene"]["Entities"], entity);
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
        std::ifstream fin("sugar/SandboxProject/Assets/Scenes/ExampleScene.candy");
        std::stringstream buffer;
        buffer << fin.rdbuf();
        std::string yaml_str = buffer.str();
        
        if (yaml_str.empty())
        {
            CANDY_CORE_INFO("EMPTY YAML STRING WITH PATH: {}", filepath);
        }
        else
        {
            CANDY_CORE_INFO("YAML STRING CONTENTS: {}", yaml_str);
        }
        // parse the YAML string
        ryml::Tree tree = ryml::parse_in_arena(ryml::to_csubstr(yaml_str));
        ryml::NodeRef root = tree.rootref();
        
        CANDY_CORE_INFO("CREATED ROOT AND TREE");
        
        auto projectNode = root["Scene"];
        
        if (projectNode.empty())
        {
            CANDY_CORE_INFO("EMPTY PROJECT NODE");
            return false;
        }
        else
        {
            CANDY_CORE_INFO("PROJECT NODE SOLID");
        }
        auto nameNode = projectNode.val();
        
        scene->name.assign(nameNode.begin(), nameNode.end());
        CANDY_CORE_TRACE("Deserializing scene '{0}'", scene->name);
        CANDY_CORE_WARN("Not finished implementing");
        
        return true;
    
    }
    bool SceneSerializer::DeserializeRuntime(const std::string& filepath)
    {
        //Not implemented
        CANDY_CORE_ASSERT(false);
        return false;
    }
}

