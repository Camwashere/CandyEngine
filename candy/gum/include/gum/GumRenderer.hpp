#pragma once
#include <candy/math/Matrix.hpp>
#include <candy/graphics/Color.hpp>
#include "gum/shape/Shape.hpp"
#include <gum/shape/Rectangle.hpp>
namespace Candy::Gum
{
  class GumRenderer
  {
  public:
    static void Init();
    static void Flush();
    static void BeginScene(SceneGraph& sceneGraph);
    static void EndScene();
    
    
    static void SubmitRectangle(const Math::Matrix3& transform, const Rectangle& rectangle, int depthIndex=0);
    
  };
}