#pragma once
#include <candy/math/Matrix.hpp>
#include <candy/graphics/Color.hpp>
#include "shape/GumShape.hpp"
namespace Candy::Gum
{
  class GumRenderer
  {
  public:
    static void Init();
    static void Flush();
    static void BeginScene();
    static void EndScene();
    
    static void SubmitShape(const Math::Matrix3& transform, const GumShape* shape, int depthIndex=0);
  };
}