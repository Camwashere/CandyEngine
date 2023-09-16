#pragma once
#include <filesystem>
#include "MeshData.hpp"
#include <candy/ecs/Scene.hpp>

namespace Candy::Graphics
{
  class ModelLoader
  {
  
  public:
  
  public:
    //std::vector<MeshData> meshes;
    SharedPtr<ECS::Scene> scene;
    
  
  
  public:
    void LoadModel(const std::filesystem::path& path);
  };
}