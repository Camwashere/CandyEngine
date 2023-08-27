#pragma once
#include "../VertexArray.hpp"
#include "MeshData.hpp"
namespace Candy::Graphics
{
  class Mesh
  {

    
  public:
    MeshData data;
    BufferLayout layout;
   SharedPtr<VertexArray> vertexArray;
   
   
  public:
    Mesh();
   
   
   static Mesh CreatePlaneMesh();
   static Mesh CreateCubeMesh();
   static Mesh CreateTriangularPrismMesh();
    
   [[nodiscard]] bool IsValid()const;
   
   void Apply();
  };
}