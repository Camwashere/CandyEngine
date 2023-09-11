#pragma once
#include "../VertexArray.hpp"
#include "MeshData.hpp"
namespace Candy::Graphics
{
  class Mesh
  {
  public:
    MeshData data;
    
  public:
    Mesh();
   [[nodiscard]] bool IsValid()const;
  };
}