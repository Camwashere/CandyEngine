#include "gum/shape/Shape.hpp"
#include <gum/GumInstance.hpp>
namespace Candy::Gum
{
  
  Shape::Shape(ShapeType shapeType, Math::Vector2 shapePos, Math::Vector2 shapeSize,  const Color& fillColor, const Color& strokeColor, float strokeWidth)
  : Node(GumInstance::GetCurrentContext().sceneGraph), type(shapeType), fillColor(fillColor), strokeColor(strokeColor), strokeWidth(strokeWidth)
  {
    layoutPosition = shapePos;
    SetSize(shapeSize);
  }
  
  bool Shape::Contains(Math::Vector2 localPoint) const
  {
    if (GetBoundsInParent().Contains(localPoint))
    {
      return ShapeContains(localPoint);
    }
    return false;
  }
  
  float Shape::GetStrokeWidth() const
  {
    return strokeWidth;
  }
  void Shape::SetStrokeWidth(float value)
  {
    strokeWidth = value;
  }
  const Color& Shape::GetStrokeColor() const
  {
    return strokeColor;
  }
  void Shape::SetStrokeColor(const Color& value)
  {
    strokeColor = value;
  }
  const Color& Shape::GetFillColor() const
  {
    return fillColor;
  }
  void Shape::SetFillColor(const Color& value)
  {
    fillColor = value;
  }
  Shape::ShapeType Shape::GetType()const
  {
    return type;
  }
}