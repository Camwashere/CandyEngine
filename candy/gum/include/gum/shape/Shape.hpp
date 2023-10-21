#pragma once
#include "gum/base/Node.hpp"
#include "candy/graphics/Color.hpp"
#include "gum/base/Layout.hpp"
namespace Candy::Gum
{
  struct ShapeVertex
  {
    Math::Vector2 position=Math::Vector2::zero;
    Color color=Color::black;
  };
  
  
  
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
    Color fillColor;
    Color strokeColor;
    float strokeWidth;
    
  protected:
    explicit Shape(ShapeType type, Math::Vector2 shapePos=Math::Vector2::zero, Math::Vector2 shapeSize=Math::Vector2::zero, const Color& fillColor=Color::clear, const Color& strokeColor=Color::black, float strokeWidth=1.0f);
    
    
  public:
    [[nodiscard]] float GetStrokeWidth() const;
    void SetStrokeWidth(float value);
    [[nodiscard]] const Color& GetStrokeColor() const;
    void SetStrokeColor(const Color& value);
    [[nodiscard]] const Color& GetFillColor() const;
    void SetFillColor(const Color& value);
    [[nodiscard]] ShapeType GetType()const;
  };
}