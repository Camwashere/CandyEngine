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
  static void MakeTriangles(std::vector<unsigned int>* tris, unsigned int* vertexIndex)
  {
    tris->push_back(*vertexIndex);
    tris->push_back(*vertexIndex + 1);
    tris->push_back(*vertexIndex + 2);
    tris->push_back(*vertexIndex + 2);
    tris->push_back(*vertexIndex + 1);
    tris->push_back(*vertexIndex + 3);
    *vertexIndex += 4;
  }
  
  
  /*bool MeshData::IsValid()const
  {
    if (vertices.empty())
    {
      return false;
    }
    if (! uvs.empty())
    {
      if (vertices.size() != uvs.size())
      {
        return false;
      }
    }
    if(triangles.size() % 3 != 0)
    {
      return false;
    }
    //CANDY_CORE_INFO("Vertices: {0}, UVS: {1}, NORMALS: {2}", vertices.size(), uvs.size(), normals.size());
    CANDY_CORE_ASSERT(vertices.size() == uvs.size() && vertices.size() == normals.size());
    
    return true;
  }
  
  bool MeshData::Empty()const
  {
    return vertices.empty() && triangles.empty() && normals.empty() && uvs.empty();
  }
  MeshData MeshData::CreatePlaneMeshData()
  {
    MeshData mesh{};
    mesh.vertices.resize(4);
    mesh.normals.resize(4);
    mesh.uvs.resize(4);
    mesh.triangles = { 0, 2, 1, 0, 3, 2};
    
    for (int i=0; i<4; i++)
    {
      mesh.vertices[i] = planeVerts[i];
      mesh.uvs[i] = planeUVs[i];
      mesh.normals[i] = Vector3::up;
    }
    
    return mesh;
    
  }
  MeshData MeshData::CreateCubeMeshData()
  {
    unsigned int vertexIndex=0;
    MeshData mesh{};
    
    for (int p=0; p<6; p++)
    {
      mesh.vertices.push_back(voxelVerts [voxelTris [p][0]]);
      mesh.vertices.push_back(voxelVerts [voxelTris [p][1]]);
      mesh.vertices.push_back(voxelVerts [voxelTris [p][2]]);
      mesh.vertices.push_back(voxelVerts [voxelTris [p][3]]);
      
      mesh.normals.push_back(voxelNormals[p]);
      mesh.normals.push_back(voxelNormals[p]);
      mesh.normals.push_back(voxelNormals[p]);
      mesh.normals.push_back(voxelNormals[p]);
      
      MakeTriangles(&mesh.triangles, &vertexIndex);
      
      mesh.uvs.push_back(voxelUvs[0]);
      mesh.uvs.push_back(voxelUvs[1]);
      mesh.uvs.push_back(voxelUvs[2]);
      mesh.uvs.push_back(voxelUvs[3]);
    }
    //CANDY_CORE_INFO("Indices size: {}", mesh.triangles.size());
    
    return mesh;
  }
  
  MeshData MeshData::CreateTriangularPrismMeshData()
  {
    MeshData mesh{};
    mesh.vertices = triangularPrismVertices;
    mesh.triangles = triangularPrismIndices;
    mesh.normals = triangularPrismNormals;
    mesh.uvs = triangularPrismUvs;
    return mesh;
  }*/
  
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
  MeshData MeshData::CreatePlaneMeshData()
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
      mesh.vertices[i] = vertex;
    }
    
    return mesh;
  }
  MeshData MeshData::CreateCubeMeshData()
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
        mesh.vertices.push_back(verts[i]);
      }
      
      /*verts[0].position = voxelVerts [voxelTris [p][0]];
      verts[1].position = voxelVerts [voxelTris [p][1]];
      verts[2].position = voxelVerts [voxelTris [p][2]];
      verts[3].position = voxelVerts [voxelTris [p][3]];
      
      verts[0].normal = voxelNormals[p];
      verts[1].normal = voxelNormals[p];
      verts[2].normal = voxelNormals[p];
      verts[3].normal = voxelNormals[p];
      
      verts[0].uv = voxelUvs[0];
      verts[1].uv = voxelUvs[1];
      verts[2].uv = voxelUvs[2];
      verts[3].uv = voxelUvs[3];*/
     
      mesh.indices.push_back(vertexIndex);
      mesh.indices.push_back(vertexIndex + 1);
      mesh.indices.push_back(vertexIndex + 2);
      mesh.indices.push_back(vertexIndex + 2);
      mesh.indices.push_back(vertexIndex + 1);
      mesh.indices.push_back(vertexIndex + 3);
      vertexIndex += 4;
      
      
     
    }
    //CANDY_CORE_INFO("Indices size: {}", mesh.triangles.size());
    
    return mesh;
  }
  MeshData MeshData::CreateTriangularPrismMeshData()
  {
    MeshData mesh{};
    for (int i=0; i<triangularPrismVertices.size(); i++)
    {
      MeshVertex vertex{};
      vertex.position = triangularPrismVertices[i];
      vertex.normal = triangularPrismNormals[i];
      vertex.uv = triangularPrismUvs[i];
      mesh.vertices.push_back(vertex);
    }
    
    mesh.indices = triangularPrismIndices;
    return mesh;
  }
}