#include <candy/graphics/model/Mesh.hpp>
#include <candy/graphics/Renderer3D.hpp>
namespace Candy::Graphics
{
  using namespace Math;
  static const Vector3 voxelVerts[8] = {
  
  /*Vector3(0, 0, 0), // 0
  Vector3(0.5f, 0, 0), // 1
  Vector3(0.5f, 0.5f, 0), // 2
  Vector3(0, 0.5f, 0), // 3
  Vector3(0, 0, 0.5f), // 4
  Vector3(0.5f, 0, 0.5f), // 5
  Vector3(0.5f, 0.5f, 0.5f), // 6
  Vector3(0, 0.5f, 0.5f) // 7*/
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
  
  Vector2 (0.0f, 0.0f),
  Vector2 (0.0f, 1.0f),
  Vector2 (1.0f, 0.0f),
  Vector2 (1.0f, 1.0f)
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
  void Mesh::Apply()
  {
    CANDY_CORE_ASSERT(IsValid(), "Mesh is not valid!");
    vertexArray = VertexArray::Create();
    
    vertexBuffer = VertexBuffer::Create(layout, vertices.size());
    vertexBuffer->SetData<float>(vertices, normals, uvs);
    //vertexBuffer->SetData<float>(vertices, uvs);
    
    indexBuffer = IndexBuffer::Create(triangles.data(), triangles.size());
    
    vertexArray->AddVertexBuffer(vertexBuffer);
    vertexArray->SetIndexBuffer(indexBuffer);
    
  }
  
  bool Mesh::IsValid()const
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
  
  Mesh Mesh::CreateCubeMesh()
  {
    unsigned int vertexIndex=0;
    Mesh mesh{};
    mesh.layout = Renderer3D::GetBufferLayout();
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
    CANDY_CORE_INFO("Indices size: {}", mesh.triangles.size());
    mesh.Apply();
    return mesh;
  }
}