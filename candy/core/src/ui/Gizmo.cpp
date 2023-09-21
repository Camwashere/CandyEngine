#include <candy/ui/Gizmo.hpp>
#include <candy/graphics/model/MeshData.hpp>


namespace Candy
{
  using namespace Graphics;
  using namespace Math;
  
  struct GizmoVertex
  {
    Vector3 position;
    Color color;
  };
  
  
  
  struct GizmoMeshData
  {
    std::vector<GizmoVertex> vertices;
    std::vector<uint32_t> indices;
  };
  
  static GizmoMeshData CreateTranslationMesh(const Color& color, int N=8, float r=0.05f, float h=1.0f, float arrowHeight=0.2f, float arrowRadius=0.1f)
  {
    
    
    std::vector<GizmoVertex> vertices;

// Generate the cylinder
    for (int i = 0; i <= N; i++)
    {
      // Angle along the circle
      float theta = (float)i * 2.0f * Math::PI / (float)N;
      
      // X and Y coordinates of the point on the circle
      float x = r * Cos(theta);
      float z = r * Sin(theta);
      
      // Two vertices at each point along the circle to form the cylinder
      vertices.push_back(GizmoVertex(Vector3(x, 0, z), color));
      vertices.push_back(GizmoVertex(Vector3(x, h, z), color));
    }

// Generate the cone for the arrow
    for (int i = 0; i <= N; i++)
    {
      float theta = (float)i * 2.0f * Math::PI / (float)N;
      
      float x = arrowRadius*Cos(theta);
      float z = arrowRadius*Sin(theta);
      
      // Vertex at the base of the arrowhead
      vertices.push_back(GizmoVertex(Vector3(x, h, z), color));
      
      // Tip of the arrowhead
      if (i < N)
        vertices.push_back(GizmoVertex(Vector3(0, h+arrowHeight, 0), color));
    }
    
    
    std::vector<uint32_t> indices;

// Generate the cylinder
    for (unsigned int i = 0; i < N; i++)
    {
      // Four vertices form a "quad" of the cylinder side
      indices.push_back(i*2);
      indices.push_back(i*2+1);
      indices.push_back(((i+1)%N)*2+1);
      
      indices.push_back(((i+1)%N)*2+1);
      indices.push_back(((i+1)%N)*2);
      indices.push_back(i*2);
    }
    
    unsigned int baseIndexForCone = N*2; // each end of the cylinder had 2*N vertices

// Generate the cone (arrow head)
    for (unsigned int i = 0; i < N; i++)
    {
      // Base of the cone
      indices.push_back(baseIndexForCone + (i*2));
      indices.push_back(baseIndexForCone + (((i+1)%N)*2));
      indices.push_back(baseIndexForCone + (i*2+1));
      
      // Side of the cone
      indices.push_back(baseIndexForCone + (i*2+1));
      indices.push_back(baseIndexForCone + (((i+1)%N)*2));
      indices.push_back(baseIndexForCone + (((i+1)%N)*2+1));
    }
    
    return GizmoMeshData{vertices, indices};
  }
  
  
  Gizmo::Gizmo()
  {
  
  }
}