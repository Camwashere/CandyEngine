#include <utility>

#include "gum/shape/Shape.hpp"
#include "gum/GumSystem.hpp"
namespace Candy::Gum
{
  
  Shape::Shape(ShapeType shapeType, Math::Vector2 shapePos, Math::Vector2 shapeSize,  Paint  fillColor, Paint  strokeColor, float strokeWidth)
  : type(shapeType), fill(std::move(fillColor)), stroke(std::move(strokeColor)), strokeWidth(strokeWidth)
  {
    layoutPosition = shapePos;
    SetSize(shapeSize);
  }
  
  
  
  /*float Shape::GetStrokeWidth() const
  {
    return strokeWidth;
  }
  void Shape::SetStrokeWidth(float value)
  {
    strokeWidth = value;
  }*/
  
  Shape::ShapeType Shape::GetType()const
  {
    return type;
  }
}