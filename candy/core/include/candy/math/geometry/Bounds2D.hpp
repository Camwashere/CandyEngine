#pragma once
#include <candy/math/Vector.hpp>
namespace Candy::Math
{
  class Bounds2D
  {
  private:
    
    Vector2 position;
    Vector2 size;
    
  public:
    Bounds2D();
    Bounds2D(const Vector2& position, const Vector2& size);
    Bounds2D(const Vector2& position, float width, float height);
    Bounds2D(float positionX, float positionY, float width, float height);
    
  public:
    bool Contains(const Vector2& point)const;
    bool Contains(float x, float y)const;
    bool Contains(const Bounds2D& other)const;
    
    bool Overlaps(const Bounds2D& other)const;
    
    
  public:
    void SetCenter(const Vector2& center);
    void SetCenter(float centerX, float centerY);
    void SetWidth(float value);
    void SetHeight(float value);
    void SetSize(const Vector2& size);
    void SetMin(const Vector2& min);
    void SetMax(const Vector2& max);
    void SetMin(float x, float y);
    void SetMax(float x, float y);
    
    
    
    Vector2 GetCenter()const;
    float GetWidth()const;
    float GetHeight()const;
    Vector2 GetMin()const;
    Vector2 GetMax()const;
    Vector2 GetSize()const;
    float GetArea()const;
    float GetPerimeter()const;
    
    
  };
}