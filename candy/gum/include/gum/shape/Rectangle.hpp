#pragma once
#include "Shape.hpp"

namespace Candy::Gum
{
  class Rectangle : public Shape
  {
  public:
    Math::Vector2 arcSize;
    
  public:
    Rectangle();
    Rectangle(float width, float height);
    explicit Rectangle(Math::Vector2 size);
    Rectangle(Math::Vector2 position, Math::Vector2 size);
    Rectangle(float x, float y, float width, float height);
    Rectangle(float x, float y, Math::Vector2 size);
    
    
  protected:
    void OnRender() override;
    
    
  public:
    [[nodiscard]] bool Contains(Math::Vector2 localPoint) const override;
    [[nodiscard]] bool ShapeContains(Math::Vector2 localPoint) const;
    
    [[nodiscard]] float GetX()const;
    [[nodiscard]] float GetY()const;
    
    [[nodiscard]] float GetWidth()const;
    [[nodiscard]] float GetHeight()const;
   
    
    
    
    
    
   /* [[nodiscard]] Math::Vector2 GetArcSize()const;
    [[nodiscard]] float GetArcWidth()const;
    [[nodiscard]] float GetArcHeight()const;
    void SetArcWidth(float value);
    void SetArcHeight(float value);
    void SetArcSize(Math::Vector2 value);
    void SetArcSize(float arcWidth, float arcHeight);*/
  };
}