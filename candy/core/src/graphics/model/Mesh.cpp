#include <candy/graphics/model/Mesh.hpp>
#include <candy/graphics/Renderer3D.hpp>
namespace Candy::Graphics
{
  using namespace Math;
  
  Mesh::Mesh()
  {
    //vertexBuffer = nullptr;
    //indexBuffer = nullptr;
    vertexArray = nullptr;
  }
  
  void Mesh::Apply()
  {
    CANDY_CORE_ASSERT(data.IsValid(), "Mesh is not valid!");
    vertexArray = VertexArray::Create();
    
    SharedPtr<VertexBuffer> vertexBuffer = VertexBuffer::Create(layout, data.vertices.size());
    vertexBuffer->SetData<float>(data.vertices, data.normals, data.uvs);
    //vertexBuffer->SetData<float>(vertices, uvs);
    
    SharedPtr<IndexBuffer> indexBuffer = IndexBuffer::Create(data.triangles.data(), data.triangles.size());
    
    vertexArray->AddVertexBuffer(vertexBuffer);
    vertexArray->SetIndexBuffer(indexBuffer);
    
  }
  
  bool Mesh::IsValid()const
  {
    return data.IsValid()&&vertexArray!=nullptr;
    
  }
  
  Mesh Mesh::CreatePlaneMesh()
  {
    Mesh mesh{};
    mesh.layout = Renderer3D::GetBufferLayout();
    mesh.data = MeshData::CreatePlaneMeshData();
    mesh.Apply();
    return mesh;
  }
  
  Mesh Mesh::CreateCubeMesh()
  {

    Mesh mesh{};
    mesh.layout = Renderer3D::GetBufferLayout();
    mesh.data = MeshData::CreateCubeMeshData();
    mesh.Apply();
    return mesh;
  }
  Mesh Mesh::CreateTriangularPrismMesh()
  {
    Mesh mesh{};
    mesh.layout = Renderer3D::GetBufferLayout();
    mesh.data = MeshData::CreateTriangularPrismMeshData();
    mesh.Apply();
    return mesh;
  }
}