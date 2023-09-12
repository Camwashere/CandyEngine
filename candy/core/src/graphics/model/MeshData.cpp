#include <candy/graphics/model/MeshData.hpp>
#include <CandyPch.hpp>
namespace Candy::Graphics
{
  using namespace Math;
  
  static const Vector3 planeVerts[4] = {
  Vector3(-0.5f, 0.0f, -0.5f), // 0
  Vector3(0.5f, 0.0f, -0.5f), // 1
  Vector3(0.5f, 0.0f, 0.5f), // 2
  Vector3(-0.5f, 0.0f, 0.5f) // 3
  };
  
  static const Vector2 planeUVs[4] = {
  Vector2(0.0f, 0.0f),
  Vector2(1.0f, 0.0f),
  Vector2(1.0f, 1.0f),
  Vector2(0.0f, 1.0f)
  };
  
  
  
  static const Vector3 voxelVerts[8] = {
  Vector3(-0.5f, -0.5f, -0.5f), // 0
  Vector3(0.5f, -0.5f, -0.5f), // 1
  Vector3(0.5f, 0.5f, -0.5f), // 2
  Vector3(-0.5f, 0.5f, -0.5f), // 3
  Vector3(-0.5f, -0.5f, 0.5f), // 4
  Vector3(0.5f, -0.5f, 0.5f), // 5
  Vector3(0.5f, 0.5f, 0.5f), // 6
  Vector3(-0.5f, 0.5f, 0.5f) // 7
  
  };
  static const unsigned int voxelTris[6][4]= {
  
  // Back, Front, Top, Bottom, Left, Right
  
  // 0 1 2 2 1 3
  {0, 3, 1, 2}, // Back Face
  {5, 6, 4, 7}, // Front Face
  {3, 7, 2, 6}, // Top Face
  {1, 5, 0, 4}, // Bottom Face
  {4, 7, 0, 3}, // Left Face
  {1, 2, 5, 6} // Right Face
  
  };
  
  static const Vector3 voxelNormals[6]={
  Vector3(0, 0, -1),
  Vector3(0, 0, 1),
  Vector3(0, 1, 0),
  Vector3(0, -1, 0),
  Vector3(-1, 0, 0),
  Vector3(1, 0, 0)
  };
  
  static const Vector2 voxelUvs[4]= {
  
  Vector2 (0.0f, 1.0f),
  Vector2 (0.0f, 0.0f),
  Vector2 (1.0f, 1.0f),
  Vector2 (1.0f, 0.0f)
  };
  
  static const std::vector<Vector3> triangularPrismVertices = {
  // Bottom face
  { -0.5f, -0.5f,  -0.5f },
  {  0.5f, -0.5f,  -0.5f },
  {  0.0f, -0.5f,   0.5f },
  // Top face
  { -0.5f, 0.5f,  -0.5f },
  {  0.5f, 0.5f,  -0.5f },
  {  0.0f, 0.5f,   0.5f },
  // Side face 1
  { -0.5f, -0.5f,  -0.5f },
  {  0.5f, -0.5f,  -0.5f },
  { -0.5f, 0.5f,  -0.5f },
  {  0.5f, 0.5f,  -0.5f },
  // Side face 2
  {  0.5f, -0.5f,  -0.5f },
  {  0.0f, -0.5f,   0.5f },
  {  0.5f, 0.5f,  -0.5f },
  {  0.0f, 0.5f,   0.5f },
  // Side face 3
  {  0.0f, -0.5f,   0.5f },
  { -0.5f, -0.5f,  -0.5f },
  {  0.0f, 0.5f,   0.5f },
  { -0.5f, 0.5f,  -0.5f }
  };
  static const std::vector<uint32_t> triangularPrismIndices = {
  0, 1, 2,  // Bottom face
  5, 4, 3,  // Top face
  6, 8, 7,  7, 8, 9,  // Side face 1
  10, 12, 11, 11, 12, 13,  // Side face 2
  14, 16, 15, 15, 16, 17   // Side face 3
  };
  static const std::vector<Vector3> triangularPrismNormals = {
  // Bottom face
  { 0.0f, -1.0f, 0.0f },
  { 0.0f, -1.0f, 0.0f },
  { 0.0f, -1.0f, 0.0f },
  // Top face
  { 0.0f, 1.0f, 0.0f },
  { 0.0f, 1.0f, 0.0f },
  { 0.0f, 1.0f, 0.0f },
  // Side face 1
  { 0.0f, 0.0f, -1.0f },
  { 0.0f, 0.0f, -1.0f },
  { 0.0f, 0.0f, -1.0f },
  { 0.0f, 0.0f, -1.0f },
  // Side face 2
  { 1.0f, 0.0f, 0.0f },
  { 1.0f, 0.0f, 0.0f },
  { 1.0f, 0.0f, 0.0f },
  { 1.0f, 0.0f, 0.0f },
  // Side face 3
  { -1.0f, 0.0f, 0.0f },
  { -1.0f, 0.0f, 0.0f },
  { -1.0f, 0.0f, 0.0f },
  { -1.0f, 0.0f, 0.0f },
  };
  
  static const std::vector<Vector2> triangularPrismUvs = {
  // Bottom face
  { 0.0f, 1.0f },
  { 1.0f, 1.0f },
  { 0.5f, 0.0f },
  // Top face
  { 0.0f, 1.0f },
  { 1.0f, 1.0f },
  { 0.5f, 0.0f },
  // Side face 1
  { 0.0f, 1.0f },
  { 1.0f, 1.0f },
  { 0.0f, 0.0f },
  { 1.0f, 0.0f },
  // Side face 2
  { 0.0f, 1.0f },
  { 1.0f, 1.0f },
  { 0.0f, 0.0f },
  { 1.0f, 0.0f },
  // Side face 3
  { 0.0f, 1.0f },
  { 1.0f, 1.0f },
  { 0.0f, 0.0f },
  { 1.0f, 0.0f }
  };
  
  
  MeshVertex::MeshVertex() : position(Vector3::zero), color(Color::white), normal(Vector3::up), uv(Vector2::zero)
  {
  
  }
  
  MeshVertex::MeshVertex(const MeshVertex& other) : position(other.position), color(other.color), normal(other.normal), uv(other.uv)
  {
  
  }
  MeshVertex::MeshVertex(const Math::Vector3& positionValue, const Color& colorValue, const Math::Vector3& normalValue, const Math::Vector2& uvValue) : position(positionValue), color(colorValue), normal(normalValue), uv(uvValue)
  {
  
  }
  
  MeshVertex& MeshVertex::operator=(const MeshVertex& other)
  {
    position = other.position;
    color = other.color;
    normal = other.normal;
    uv = other.uv;
    return *this;
  }
  bool MeshVertex::operator==(const MeshVertex& other)const
  {
    return position == other.position && color == other.color && normal == other.normal && uv == other.uv;
  }
  bool MeshVertex::operator!=(const MeshVertex& other)const
  {
    return !(*this == other);
  }
  
  std::string MeshVertex::ToString()const
  {
    
    std::string str = "Position: " + position.ToString() + ", " + "Color: " + color.ToString() + ", " + "Normal: " + normal.ToString() + ", " + "UV: " + uv.ToString();
    return str;
    
  }
  
  MeshData::MeshData() : vertices{}, indices{}
  {
  
  }
  MeshData::MeshData(const MeshData& other) : vertices(other.vertices), indices(other.indices)
  {
  
  }
  MeshData::MeshData(const std::vector<MeshVertex>& verticesValue, const std::vector<uint32_t>& indicesValue) : vertices(verticesValue), indices(indicesValue)
  {
  
  }
  
  MeshData& MeshData::operator=(const MeshData& other)
  {
    vertices.resize(other.vertices.size());
    indices.resize(other.indices.size());
    for (int i=0; i<other.vertices.size(); i++)
    {
      vertices[i] = other.vertices[i];
    }
    for (int i=0; i<other.indices.size(); i++)
    {
      indices[i] = other.indices[i];
    }
    return *this;
  }
  bool MeshData::operator==(const MeshData& other)const
  {
    if(vertices.size() != other.vertices.size() || indices.size() != other.indices.size())
    {
      return false;
    }
    for (int i=0; i<vertices.size(); i++)
    {
      if(vertices[i] != other.vertices[i])
      {
        CANDY_CORE_ERROR("Vert not equal: {0} != {1}", vertices[i].ToString(), other.vertices[i].ToString());
        return false;
      }
    }
    for (int i=0; i<indices.size(); i++)
    {
      if(indices[i] != other.indices[i])
      {
        CANDY_CORE_ERROR("Index not equal: {0} != {1}", indices[i], other.indices[i]);
        return false;
      }
    }
    return true;
  }
  bool MeshData::operator!=(const MeshData& other)const
  {
    return !(*this == other);
  }
  static MeshData CreatePlaneMeshData()
  {
    MeshData mesh{};
    mesh.vertices.resize(4);
    
    mesh.indices = { 0, 2, 1, 0, 3, 2};
    
    for (int i=0; i<4; i++)
    {
      MeshVertex vertex{};
      vertex.position = planeVerts[i];
      vertex.uv = planeUVs[i];
      vertex.normal = Vector3::up;
      vertex.color = Color::white;
      mesh.vertices[i] = vertex;
    }
    
    return mesh;
  }
  static MeshData CreateCubeMeshData()
  {
    unsigned int vertexIndex=0;
    MeshData mesh{};
    
    for (int p=0; p<6; p++)
    {
      std::array<MeshVertex, 4> verts{};
      
      for (int i=0; i<4; i++)
      {
        verts[i].position = voxelVerts [voxelTris [p][i]];
        verts[i].normal = voxelNormals[p];
        verts[i].uv = voxelUvs[i];
        verts[i].color = Color::white;
        mesh.vertices.push_back(verts[i]);
      }
      
      
      
      mesh.indices.push_back(vertexIndex);
      mesh.indices.push_back(vertexIndex + 1);
      mesh.indices.push_back(vertexIndex + 2);
      mesh.indices.push_back(vertexIndex + 2);
      mesh.indices.push_back(vertexIndex + 1);
      mesh.indices.push_back(vertexIndex + 3);
      vertexIndex += 4;
      
      
      
    }
    
    
    return mesh;
  }
  static MeshData CreateTriangularPrismMeshData()
  {
    MeshData mesh{};
    for (int i=0; i<triangularPrismVertices.size(); i++)
    {
      MeshVertex vertex{};
      vertex.position = triangularPrismVertices[i];
      vertex.color = Color::white;
      vertex.normal = triangularPrismNormals[i];
      vertex.uv = triangularPrismUvs[i];
      mesh.vertices.push_back(vertex);
    }
    
    mesh.indices = triangularPrismIndices;
    return mesh;
  }
  
  const MeshData MeshData::plane(CreatePlaneMeshData());
  const MeshData MeshData::cube(CreateCubeMeshData());
  const MeshData MeshData::triangularPrism(CreateTriangularPrismMeshData());
  
  bool MeshData::IsValid()const
  {
    if(indices.size() % 3 != 0)
    {
      return false;
    }
    
    return !(vertices.empty() || indices.empty());
    
  }
  bool MeshData::Empty()const
  {
    return vertices.empty() && indices.empty();
  }
  size_t MeshData::VertexCount()const
  {
    return vertices.size();
  }
  size_t MeshData::IndexCount()const
  {
    return indices.size();
  }
  
  std::string MeshData::ToString()const
  {
    std::string str;
    for (int i=0; i<vertices.size(); i++)
    {
      str += vertices[i].ToString() + "\n";
    }
    
    return str;
    
  }
  
}