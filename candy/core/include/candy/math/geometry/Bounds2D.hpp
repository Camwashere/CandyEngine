#pragma once
#include <candy/math/Vector.hpp>
namespace Candy::Math
{
  class Bounds2D
  {
  private:
    Vector2 min;
    Vector2 max;
    
  public:
    Bounds2D();
    Bounds2D(const Vector2& min, const Vector2& max);
    Bounds2D(float minX, float minY, float maxX, float maxY);
    Bounds2D(const Bounds2D& other)=default;
    
    
  public:
    [[nodiscard]] bool Contains(const Vector2& point)const;
    [[nodiscard]] bool Contains(float x, float y)const;
    [[nodiscard]] bool Contains(const Bounds2D& other)const;
    
    [[nodiscard]] bool Overlaps(const Bounds2D& other)const;
    void Move(const Vector2& position);
    void Translate(const Vector2& translation);
    void Translate(float x, float y);
    void TranslateCenter(float centerX, float centerY);
    void TranslateCenter(const Vector2& centerPos);
    
    
  public:
    [[nodiscard]] std::vector<Vector2> GetCorners()const;
    void SetFromOrigin(const Vector2& origin, const Vector2& size);
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
    
    [[nodiscard]] Vector2 GetPosition()const;
    [[nodiscard]] Vector2 GetCenter()const;
    [[nodiscard]] float GetWidth()const;
    [[nodiscard]] float GetHeight()const;
    [[nodiscard]] Vector2 GetMin()const;
    [[nodiscard]] Vector2 GetMax()const;
    [[nodiscard]] Vector2 GetSize()const;
    [[nodiscard]] Vector2 GetHalfSize()const;
    [[nodiscard]] float GetArea()const;
    [[nodiscard]] float GetPerimeter()const;
    
    
  };
}

template<>
struct fmt::formatter<Candy::Math::Bounds2D> {
  constexpr auto parse(format_parse_context& ctx) {
    return ctx.begin();
  }
  
  template <typename FormatContext>
  auto format(const Candy::Math::Bounds2D& bounds, FormatContext& ctx) {
    return format_to(ctx.out(), "Pos: {0}, Size: {1}, BottomLeft: {2}, BottomRight: {3}, TopLeft: {4}, TopRight: {5}",
    bounds.GetPosition(), bounds.GetSize(), bounds.GetBottomLeft(), bounds.GetBottomRight(), bounds.GetTopLeft(), bounds.GetTopRight());
  }
};