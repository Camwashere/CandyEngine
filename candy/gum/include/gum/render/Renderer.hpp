#pragma once
#include <candy/math/Matrix.hpp>
#include <candy/graphics/Color.hpp>
#include "gum/shape/Shape.hpp"
#include <gum/shape/Rectangle.hpp>
#include <gum/widget/Label.hpp>
namespace Candy::Gum
{
  class TextRenderer;
  class Renderer
  {
  private:
    static void SubmitRectangle(const Math::Matrix3& transform, const Rectangle& rectangle, int depthIndex=0);
  public:
    static void Init();
    static void Flush();
    static void BeginScene(SceneGraph& sceneGraph);
    static void EndScene();
    
    static TextRenderer& GetTextRenderer();
    static void SetFont(const SharedPtr<FontInternal>& font);
    static void SubmitShape(const Math::Matrix3& transform, const Shape& shape, int depthIndex=0);
    
    //static void SubmitLabel(const Label& label, int depthIndex=0);
    
    
  };
}