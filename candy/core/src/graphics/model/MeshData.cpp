#include <candy/graphics/model/MeshData.hpp>
#include <CandyPch.hpp>
namespace Candy::Graphics
{
  using namespace Math;
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
  
  
  bool MeshData::IsValid()const
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
  }
}