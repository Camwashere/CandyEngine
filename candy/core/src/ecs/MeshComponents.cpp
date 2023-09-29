#include <candy/ecs/Scene.hpp>
#include <candy/ecs/MeshComponents.hpp>



namespace Candy::ECS
{
  
  
  MeshFilterComponent::MeshFilterComponent()=default;
  MeshFilterComponent::MeshFilterComponent(const MeshFilterComponent& other) = default;
  MeshFilterComponent::MeshFilterComponent(const Graphics::MeshData<Graphics::MeshVertex> &data) : meshData(data)
  {
  
  }
  
  void MeshFilterComponent::SetMeshData(const Graphics::MeshData<Graphics::MeshVertex> &data)
  {
    meshData = data;
  }
  
  const Graphics::MeshData<Graphics::MeshVertex> &MeshFilterComponent::GetMeshData() const
  {
    return meshData;
  }
  
  Graphics::MeshData<Graphics::MeshVertex> &MeshFilterComponent::GetMeshData()
  {
    return meshData;
  }
  
  
}

