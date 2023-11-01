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
    Paint backgroundColor;
    
    
  protected:
    virtual void OnBoundsCalculated()override;
    virtual void OnLayout()override;
    virtual void OnRender()override;
    virtual void OnSetSize(Math::Vector2 oldValue, Math::Vector2 newValue)override;
    virtual void OnSetLayoutPosition(Math::Vector2 oldValue, Math::Vector2 newValue)override;
  protected:
    Region();
    
    
  public:
    Paint GetBackgroundFill()const;
    void SetBackgroundFill(const Paint& value);
    void SetShape(SharedPtr<Shape> shape);
    Shape& GetShape();
    [[nodiscard]] const Shape& GetShape()const;
    virtual bool Contains(Math::Vector2 localPoint)const override;
    
    
    
    
  
  };
}