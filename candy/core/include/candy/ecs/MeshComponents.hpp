#pragma once
#include <candy/graphics/model/MeshData.hpp>
#include <candy/graphics/texture/Texture.hpp>
#include "Scene.hpp"
namespace Candy::ECS
{
  class MeshFilterComponent
  {
  private:
    Graphics::MeshData meshData;
    
  public:
    MeshFilterComponent();
    MeshFilterComponent(const MeshFilterComponent& other);
    explicit MeshFilterComponent(const Graphics::MeshData& data);
    
    
  public:
    void SetMeshData(const Graphics::MeshData& data);
    [[nodiscard]] const Graphics::MeshData& GetMeshData() const;
    Graphics::MeshData& GetMeshData();
    
    
  };
  
  struct MeshRendererComponent
  {
    SharedPtr<Graphics::Texture> texture;
  };
  
  
}
namespace Candy::ECS
{
  template<>
  inline void Scene::OnComponentAdded<MeshFilterComponent>(Entity& entity, MeshFilterComponent& component)
  {
    CANDY_CORE_INFO("Added mesh component!");
    AppendUpdateFlag(SceneUpdateFlag::Meshes3D);
    
  }
  
  template<>
  inline void Scene::OnComponentRemoved<MeshFilterComponent>(Entity& entity, MeshFilterComponent& component)
  {
    AppendUpdateFlag(SceneUpdateFlag::Meshes3D);
  }
}

