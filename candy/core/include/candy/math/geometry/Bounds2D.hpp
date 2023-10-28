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
    [[nodiscard]] bool Contains(const Vector2& point)const;
    [[nodiscard]] bool Contains(float x, float y)const;
    [[nodiscard]] bool Contains(const Bounds2D& other)const;
    
    [[nodiscard]] bool Overlaps(const Bounds2D& other)const;
    
    
  public:
    [[nodiscard]] std::vector<Vector2> GetCorners()const;
    void SetPosition(const Vector2& position);
    void SetCenter(const Vector2& center);
    void SetCenter(float centerX, float centerY);
    void SetWidth(float value);
    void SetHeight(float value);
    void SetSize(const Vector2& size);
    void SetMin(const Vector2& min);
    void SetMax(const Vector2& max);
    void SetMin(float x, float y);
    void SetMax(float x, float y);
    
    [[nodiscard]] std::vector<Bounds2D> Split()const;
    [[nodiscard]] Bounds2D GetBottomLeftQuad()const;
    [[nodiscard]] Bounds2D GetBottomRightQuad()const;
    [[nodiscard]] Bounds2D GetTopLeftQuad()const;
    [[nodiscard]] Bounds2D GetTopRightQuad()const;
    [[nodiscard]] Vector2 GetBottomLeft()const;
    [[nodiscard]] Vector2 GetBottomRight()const;
    [[nodiscard]] Vector2 GetTopLeft()const;
    [[nodiscard]] Vector2 GetTopRight()const;
    
    [[nodiscard]] Vector2 GetCenter()const;
    [[nodiscard]] float GetWidth()const;
    [[nodiscard]] float GetHeight()const;
    [[nodiscard]] Vector2 GetMin()const;
    [[nodiscard]] Vector2 GetMax()const;
    [[nodiscard]] Vector2 GetSize()const;
    [[nodiscard]] float GetArea()const;
    [[nodiscard]] float GetPerimeter()const;
    
    
  };
}