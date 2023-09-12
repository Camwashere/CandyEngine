#pragma once
#include <filesystem>
#include "MeshData.hpp"


namespace Candy::Graphics
{
  class ModelLoader
  {
  public:
    std::vector<MeshData> meshes;
    
  
  
  public:
    void LoadModel(const std::filesystem::path& path);
  };
}