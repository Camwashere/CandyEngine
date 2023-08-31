#pragma once
#include "Scene.hpp"
namespace Candy::ECS
{
  class SceneSerializer
  {
  private:
    SharedPtr<Scene> scene;
  
  
  public:
    explicit SceneSerializer(SharedPtr<Scene> scene);
    
    bool Serialize(const std::filesystem::path& filepath);
    bool Deserialize(const std::filesystem::path& filepath);
    
  };
}