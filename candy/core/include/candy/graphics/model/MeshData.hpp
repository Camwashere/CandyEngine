#pragma once
#include <candy/math/Vector.hpp>
#include <candy/graphics/Color.hpp>
namespace Candy::Graphics
{
  struct MeshVertex
  {
    Math::Vector3 position = Math::Vector3::zero;
    Color color = Color::white;
    Math::Vector3 normal = Math::Vector3::zero;
    Math::Vector2 uv = Math::Vector2::zero;
  };
  
  
  
  struct MeshData
  {
    std::vector<MeshVertex> vertices{};
    std::vector<uint32_t> indices{};
    
    [[nodiscard]] bool IsValid()const;
    [[nodiscard]] bool Empty()const;
    [[nodiscard]] size_t VertexCount()const;
    [[nodiscard]] size_t IndexCount()const;
    
    static const MeshData plane;
    static const MeshData cube;
    static const MeshData triangularPrism;
    
    //static MeshData CreatePlaneMeshData();
    //static MeshData CreateCubeMeshData();
    //static MeshData CreateTriangularPrismMeshData();
  };
}