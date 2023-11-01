#pragma once
#include "gum/base/Node.hpp"
#include "candy/graphics/Color.hpp"
#include <gum/style/Paint.hpp>
namespace Candy::Gum
{
  
  
  class Shape : public Node
  {
  public:
    enum ShapeType
    {
      None=0,
      Rectangle,
      Circle,
    };
  private:
    ShapeType type;
    
  public:
    Paint fill;
    Paint stroke;
    float strokeWidth;
    
  protected:
    explicit Shape(ShapeType type, Math::Vector2 shapePos=Math::Vector2::zero, Math::Vector2 shapeSize=Math::Vector2::zero, Paint  fill=Color::clear, Paint  stroke=Color::black, float strokeWidth=0.01f);
    
  public:
    /*[[nodiscard]] float GetStrokeWidth() const;
    void SetStrokeWidth(float value);
    [[nodiscard]] const Paint& GetStroke() const;
    void SetStroke(const Color& value);
    [[nodiscard]] const Paint& GetFill() const;
    void SetFill(const Paint& value);*/
    [[nodiscard]] ShapeType GetType()const;
    
    friend class Region;
  };
}