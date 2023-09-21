#pragma once
#include <candy/math/Vector.hpp>
#include <candy/graphics/Color.hpp>
namespace Candy::Graphics
{
  struct MeshVertex
  {
    Math::Vector3 position;
    Color color;
    Math::Vector3 normal;
    Math::Vector2 uv;
    
    MeshVertex();
    MeshVertex(const MeshVertex& other);
    MeshVertex(const Math::Vector3& positionValue, const Color& colorValue, const Math::Vector3& normalValue, const Math::Vector2& uvValue);
    
    MeshVertex& operator=(const MeshVertex& other);
    bool operator==(const MeshVertex& other)const;
    bool operator!=(const MeshVertex& other)const;
    
    [[nodiscard]] std::string ToString()const;
    
  };
  
  
  
  struct MeshData
  {
    std::vector<MeshVertex> vertices;
    std::vector<uint32_t> indices;
    
    
    MeshData();
    MeshData(const MeshData& other);
    MeshData(const std::vector<MeshVertex>& verticesValue, const std::vector<uint32_t>& indicesValue);
    
    MeshData& operator=(const MeshData& other);
    bool operator==(const MeshData& other)const;
    bool operator!=(const MeshData& other)const;
    
    
    [[nodiscard]] bool IsValid()const;
    [[nodiscard]] bool Empty()const;
    [[nodiscard]] size_t VertexCount()const;
    [[nodiscard]] size_t IndexCount()const;
    [[nodiscard]] std::string ToString()const;
    
    
    
    /*static MeshData CreatePlaneMeshData();
    static MeshData CreateCubeMeshData();
    static MeshData CreateTriangularPrismMeshData();*/
    
    static const MeshData plane;
    static const MeshData cube;
    static const MeshData triangularPrism;
    
  };
}