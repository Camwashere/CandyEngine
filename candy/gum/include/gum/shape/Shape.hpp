#pragma once
#include "gum/base/Node.hpp"
#include "candy/graphics/Color.hpp"
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
    Color fillColor;
    Color strokeColor;
    float strokeWidth;
    
  protected:
    explicit Shape(ShapeType type, Math::Vector2 shapePos=Math::Vector2::zero, Math::Vector2 shapeSize=Math::Vector2::zero, const Color& fillColor=Color::clear, const Color& strokeColor=Color::black, float strokeWidth=0.01f);
    
  public:
    [[nodiscard]] float GetStrokeWidth() const;
    void SetStrokeWidth(float value);
    [[nodiscard]] const Color& GetStrokeColor() const;
    void SetStrokeColor(const Color& value);
    [[nodiscard]] const Color& GetFillColor() const;
    void SetFillColor(const Color& value);
    [[nodiscard]] ShapeType GetType()const;
    
    friend class Region;
  };
}