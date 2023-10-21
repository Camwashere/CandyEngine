#pragma once
#include "Node.hpp"
#include <candy/base/Base.hpp>
#include <gum/shape/Rectangle.hpp>
namespace Candy::Gum
{
  class Region : public Node
  {
  private:
    bool needsLayout=true;
    
    
  protected:
    Rectangle baseShape;
    SharedPtr<Shape> customShape;
    
  protected:
    explicit Region(SceneGraph& sceneGraph);
    
    
  public:
    void SetShape(SharedPtr<Shape> shape);
    Rectangle& GetBaseShape();
    Shape& GetShape();
    [[nodiscard]] const Rectangle& GetBaseShape()const;
    [[nodiscard]] const Shape& GetShape()const;
    
    
    
    
  
  };
}