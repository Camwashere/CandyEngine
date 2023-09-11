#include <candy/graphics/model/Mesh.hpp>
#include <candy/graphics/Renderer3D.hpp>
namespace Candy::Graphics
{
  using namespace Math;
  
  Mesh::Mesh()
  {
  
  }
  
  bool Mesh::IsValid()const
  {
    return data.IsValid();
  }
  
  
}