#pragma once
#include "Node.hpp"
#include <candy/base/Base.hpp>
#include <gum/shape/Rectangle.hpp>
namespace Candy::Gum
{
  class Region : public Node
  {
  private:
    SharedPtr<Shape> shape;
    Color backgroundColor;
    
  protected:
    virtual void OnLayout()override;
    virtual void OnRender()override;
    virtual void OnSetSize(Math::Vector2 oldValue, Math::Vector2 newValue)override;
    virtual void OnSetLayoutPosition(Math::Vector2 oldValue, Math::Vector2 newValue)override;
  protected:
    Region();
    
    
  public:
    Color GetBackgroundColor()const;
    void SetBackgroundColor(Color value);
    void SetShape(SharedPtr<Shape> shape);
    Shape& GetShape();
    [[nodiscard]] const Shape& GetShape()const;
    virtual bool Contains(Math::Vector2 localPoint)const override;
    
    
    
    
  
  };
}