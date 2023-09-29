#include <candy/ui/Gizmo.hpp>
#include <candy/graphics/model/MeshData.hpp>


namespace Candy
{
  using namespace Graphics;
  using namespace Math;
  
  
  
  static MeshData<MeshVertex> CreateTranslationMesh(const Color& color, int N=8, float r=0.05f, float h=1.0f, float arrowHeight=0.2f, float arrowRadius=0.1f)
  {
    
    MeshData<MeshVertex> meshData{};
    //std::vector<MeshVertexColored> vertices;

// Generate the cylinder
    for (int i = 0; i <= N; i++)
    {
      // Angle along the circle
      float theta = (float)i * 2.0f * Math::PI / (float)N;
      
      // X and Y coordinates of the point on the circle
      float x = r * Cos(theta);
      float z = r * Sin(theta);
      
      // Two vertices at each point along the circle to form the cylinder
      meshData.vertices.emplace_back(Vector3(x, 0, z), color, Vector3::zero, Vector2::zero);
      meshData.vertices.emplace_back(Vector3(x, h, z), color, Vector3::zero, Vector2::zero);
    }

// Generate the cone for the arrow
    for (int i = 0; i <= N; i++)
    {
      float theta = (float)i * 2.0f * Math::PI / (float)N;
      
      float x = arrowRadius*Cos(theta);
      float z = arrowRadius*Sin(theta);
      
      // Vertex at the base of the arrowhead
      meshData.vertices.emplace_back(Vector3(x, h, z), color, Vector3::zero, Vector2::zero);
      
      // Tip of the arrowhead
      if (i < N)
        meshData.vertices.emplace_back(Vector3(0, h+arrowHeight, 0), color, Vector3::zero, Vector2::zero);
    }
    
    
    //std::vector<uint32_t> indices;

// Generate the cylinder
    for (unsigned int i = 0; i < N; i++)
    {
      // Four vertices form a "quad" of the cylinder side
      meshData.indices.push_back(i*2);
      meshData.indices.push_back(i*2+1);
      meshData.indices.push_back(((i+1)%N)*2+1);
      
      meshData.indices.push_back(((i+1)%N)*2+1);
      meshData.indices.push_back(((i+1)%N)*2);
      meshData.indices.push_back(i*2);
    }
    
    unsigned int baseIndexForCone = N*2; // each end of the cylinder had 2*N vertices

// Generate the cone (arrow head)
    for (unsigned int i = 0; i < N; i++)
    {
      // Base of the cone
      meshData.indices.push_back(baseIndexForCone + (i*2));
      meshData.indices.push_back(baseIndexForCone + (((i+1)%N)*2));
      meshData.indices.push_back(baseIndexForCone + (i*2+1));
      
      // Side of the cone
      meshData.indices.push_back(baseIndexForCone + (i*2+1));
      meshData.indices.push_back(baseIndexForCone + (((i+1)%N)*2));
      meshData.indices.push_back(baseIndexForCone + (((i+1)%N)*2+1));
    }
    
    return meshData;
  }
  
  
  Gizmo::Gizmo()
  {
    translationMesh = CreateTranslationMesh(Color::red);
  
  }
  
  void Gizmo::SetTarget(ECS::TransformComponent* transformTarget)
  {
    target = transformTarget;
  }
  int Gizmo::GetTargetEntity()const
  {
    if (target)
    {
      return (int)target->GetEntity();
    }
    else
    {
      return -1;
    }
  }
  const Graphics::MeshData<Graphics::MeshVertex>& Gizmo::GetTranslationMesh()const
  {
    return translationMesh;
  }
}