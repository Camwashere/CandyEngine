#pragma once
#include "Vector.hpp"

namespace Candy::Math
{
  struct Rectangle
  {
  public:
    Vector2 min;
    Vector2 max;
  
  
  public:
    Rectangle() : min(0, 0), max(0, 0){};
    Rectangle(const Vector2& rectMin, const Vector2& rectMax) : min(rectMin), max(rectMax) {}
    explicit Rectangle(const Vector4& v) : min(v.x, v.y), max(v.x2, v.y2){}
    Rectangle(float x1, float y1, float x2, float y2)  : min(x1, y1), max(x2, y2){}
  
  
  
  public:
    bool operator==(const Rectangle& other) const;
    bool operator!=(const Rectangle& other) const;
    
    bool operator<(const Rectangle& other) const;
    bool operator<=(const Rectangle& other)const;
    bool operator>(const Rectangle& other) const;
    bool operator>=(const Rectangle& other) const;
  
  
  
  public:
    [[nodiscard]] Vector2 GetCenter() const;
    [[nodiscard]] Vector2 GetSize() const;
    [[nodiscard]] float GetWidth() const;
    [[nodiscard]] float GetHeight() const;
    [[nodiscard]] float GetArea() const;
    
    [[nodiscard]] Vector2 GetTopLeft() const;
    [[nodiscard]] Vector2 GetTopRight() const;
    [[nodiscard]] Vector2 GetBottomLeft() const;
    [[nodiscard]] Vector2 GetBottomRight() const;
    [[nodiscard]] bool Contains(const Vector2& p) const;
    [[nodiscard]] bool Contains(const Rectangle& r) const;
    [[nodiscard]] bool Overlaps(const Rectangle& r) const;
    void Add(const Vector2& p);
    void Add(const Rectangle& r);
    void Expand(float amount);
    void Expand(const Vector2& amount);
    void Translate(const Vector2& d);
    void TranslateX(float dx);
    void TranslateY(float dy);
    void Floor();
    [[nodiscard]] bool IsInverted() const;
    [[nodiscard]] Vector4 ToVector4() const;
    [[nodiscard]] Vector2 NormalizePoint(const Math::Vector2& point)const;
    
    
    
    
    
  };
}