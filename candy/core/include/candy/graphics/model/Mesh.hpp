#pragma once
#include "../VertexArray.hpp"
#include <candy/math/Vector.hpp>
namespace Candy::Graphics
{
  struct Mesh
  {
    std::vector<Math::Vector3> vertices{};
    std::vector<Math::Vector3> normals{};
    std::vector<Math::Vector2> uvs{};
    std::vector<uint32_t> triangles{};
    BufferLayout layout;
    
   SharedPtr<VertexArray> vertexArray;
   SharedPtr<VertexBuffer> vertexBuffer;
   SharedPtr<IndexBuffer> indexBuffer;
    static Mesh CreateCubeMesh();
    
    [[nodiscard]] bool IsValid()const;
    
    void Apply();
  };
}