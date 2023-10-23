#pragma once
#include "Shape.hpp"

namespace Candy::Gum
{
  class Rectangle : public Shape
  {
  private:
    Math::Vector2 arcSize;
    
  public:
    Rectangle();
    Rectangle(float width, float height);
    explicit Rectangle(Math::Vector2 size);
    Rectangle(Math::Vector2 position, Math::Vector2 size);
    Rectangle(float x, float y, float width, float height);
    Rectangle(float x, float y, Math::Vector2 size);
    
    
  protected:
    void LayoutChildren() override;
    //void CalculateBounds() override;
    void OnRender() override;
    
  public:
    [[nodiscard]] bool ShapeContains(Math::Vector2 localPoint) const override;
    
    [[nodiscard]] float GetX()const;
    [[nodiscard]] float GetY()const;
    void SetX(float value);
    void SetY(float value);
    [[nodiscard]] Math::Vector2 GetPosition()const;
    void SetPosition(Math::Vector2 value);
    void SetPosition(float x, float y);
    
    [[nodiscard]] float GetWidth()const;
    [[nodiscard]] float GetHeight()const;
   
    
    
    
    
    
    [[nodiscard]] Math::Vector2 GetArcSize()const;
    [[nodiscard]] float GetArcWidth()const;
    [[nodiscard]] float GetArcHeight()const;
    void SetArcWidth(float value);
    void SetArcHeight(float value);
    void SetArcSize(Math::Vector2 value);
    void SetArcSize(float arcWidth, float arcHeight);
  };
}