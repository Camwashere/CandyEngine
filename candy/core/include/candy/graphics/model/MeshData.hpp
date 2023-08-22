#pragma once
#include <candy/math/Vector.hpp>
namespace Candy::Graphics
{
  struct MeshData
  {
    std::vector<Math::Vector3> vertices{};
    std::vector<Math::Vector3> normals{};
    std::vector<Math::Vector2> uvs{};
    std::vector<uint32_t> triangles{};
    
    [[nodiscard]] bool IsValid()const;
    [[nodiscard]] bool Empty()const;
    static MeshData CreatePlaneMeshData();
    static MeshData CreateCubeMeshData();
    static MeshData CreateTriangularPrismMeshData();
  };
}