#include <candy/ecs/Scene.hpp>
#include <candy/ecs/MeshComponents.hpp>



namespace Candy::ECS
{
  
  
  MeshFilterComponent::MeshFilterComponent()=default;
  MeshFilterComponent::MeshFilterComponent(const MeshFilterComponent& other) = default;
  MeshFilterComponent::MeshFilterComponent(const Graphics::MeshData &data) : meshData(data)
  {
  
  }
  
  void MeshFilterComponent::SetMeshData(const Graphics::MeshData &data)
  {
    meshData = data;
  }
  
  const Graphics::MeshData &MeshFilterComponent::GetMeshData() const
  {
    return meshData;
  }
  
  Graphics::MeshData &MeshFilterComponent::GetMeshData()
  {
    return meshData;
  }
  
  
}

