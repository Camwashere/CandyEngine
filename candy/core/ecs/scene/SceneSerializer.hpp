#pragma once
#include "Scene.hpp"

namespace Candy::ECS
{
    class SceneSerializer
    {
    private:
        SharedPtr<Scene> scene;
        
    public:
        explicit SceneSerializer(const SharedPtr<Scene>& scene);
        
    public:
        void Serialize(const std::string& filepath);
        void SerializeRuntime(const std::string& filepath);
        
        bool Deserialize(const std::string& filepath);
        bool DeserializeRuntime(const std::string& filepath);
    };
}