#pragma once
#include <filesystem>
#include "MeshData.hpp"
#include <candy/ecs/Scene.hpp>
#include "candy/graphics/texture/Texture.hpp"
namespace Assimp
{
  class Importer;
}
struct aiMesh;
struct aiNode;
struct aiScene;

namespace Candy::Graphics
{
  class ModelLoader
  {
  private:
    SharedPtr<ECS::Scene> scene;
    Assimp::Importer* importer;
    
  private:
    void ProcessNode(aiNode* node, const aiScene* aiScene, const ECS::Entity& parent, const SharedPtr<Texture>& texture);
    
  public:
    explicit ModelLoader(const SharedPtr<ECS::Scene>& sceneValue);
    ~ModelLoader();
    
    
  public:
    void LoadModel(const std::filesystem::path& path);
  };
}