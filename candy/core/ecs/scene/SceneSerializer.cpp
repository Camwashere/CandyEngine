#include "SceneSerializer.hpp"
#include <Candy/Math.hpp>
/*
namespace YAML
{
    template<>
    struct convert<Candy::Math::Vector2>
    {
        static Node encode(const Candy::Math::Vector2& rhs)
        {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.SetStyle(EmitterStyle::Flow);
            return node;
        }
        static bool decode(const Node& node, Candy::Math::Vector2& rhs)
        {
            if (!node.IsSequence() || node.size() != 2)
                return false;
            
            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            return true;
        }
    };
    template<>
    struct convert<Candy::Math::Vector3>
    {
        static Node encode(const Candy::Math::Vector3& rhs)
        {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.push_back(rhs.z);
            node.SetStyle(EmitterStyle::Flow);
            return node;
        }
        
        static bool decode(const Node& node, Candy::Math::Vector3& rhs)
        {
            if (!node.IsSequence() || node.size() != 3)
                return false;
            
            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            rhs.z = node[2].as<float>();
            return true;
        }
    };
    
    template<>
    struct convert<Candy::Math::Vector4>
    {
        static Node encode(const Candy::Math::Vector4& rhs)
        {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.push_back(rhs.z);
            node.push_back(rhs.w);
            node.SetStyle(EmitterStyle::Flow);
            return node;
        }
        
        static bool decode(const Node& node, Candy::Math::Vector4& rhs)
        {
            if (!node.IsSequence() || node.size() != 4)
                return false;
            
            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            rhs.z = node[2].as<float>();
            rhs.w = node[3].as<float>();
            return true;
        }
    };
    
    template<>
    struct convert<Candy::UUID>
    {
        static Node encode(const Candy::UUID& uuid)
        {
            Node node;
            node.push_back((uint64_t)uuid);
            return node;
        }
        
        static bool decode(const Node& node, Candy::UUID& uuid)
        {
            uuid = node.as<uint64_t>();
            return true;
        }
    };
}*/
namespace Candy::ECS
{
    SceneSerializer::SceneSerializer(const SharedPtr<Scene>& scene)
    {
    
    }
    
    void SceneSerializer::Serialize(const std::string& filepath)
    {
    
    }
    void SceneSerializer::SerializeRuntime(const std::string& filepath)
    {
    
    }
    
    bool SceneSerializer::Deserialize(const std::string& filepath)
    {
    
    }
    bool SceneSerializer::DeserializeRuntime(const std::string& filepath)
    {
    
    }
}

