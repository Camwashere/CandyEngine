#include <candy/math/geometry/Bounds2D.hpp>

namespace Candy::Math
{
  Bounds2D::Bounds2D() = default;
  
  Bounds2D::Bounds2D(const Vector2& min, const Vector2& max) : min(min), max(max){}
  Bounds2D::Bounds2D(float minX, float minY, float maxX, float maxY) : min(minX, minY), max(maxX, maxY){}
  bool Bounds2D::Contains(const Vector2& point)const
  {
    bool xWithin = point.x >= GetMin().x && point.x <= GetMax().x;
    bool yWithin = point.y >= GetMin().y && point.y <= GetMax().y;
    return xWithin && yWithin;
    
  }
  bool Bounds2D::Contains(float x, float y)const
  {
    return Contains({x, y});
  }
  bool Bounds2D::Contains(const Bounds2D& other)const
  {
    return Contains(other.min) && Contains(other.max);
  }
  
  bool Bounds2D::Overlaps(const Bounds2D& other)const
  {
    return Contains(other.min) || Contains(other.max);
  }
  void Bounds2D::Translate(const Vector2& translation)
  {
    min += translation;
    max += translation;
  }
  
  void Bounds2D::TranslateCenter(const Vector2& centerPos)
  {
    Vector2 center = GetCenter();
    Vector2 translation = centerPos - center;
    Translate(translation);
  }
  void Bounds2D::Translate(float x, float y)
  {
    Translate({x, y});
  }
  void Bounds2D::TranslateCenter(float centerX, float centerY)
  {
    TranslateCenter({centerX, centerY});
  }
  std::vector<Vector2> Bounds2D::GetCorners()const
  {
    std::vector<Vector2> corners;
    corners.push_back(GetBottomLeft());
    corners.push_back(GetBottomRight());
    corners.push_back(GetTopLeft());
    corners.push_back(GetTopRight());
    return corners;
  }
  
  void Bounds2D::SetFromOrigin(const Vector2& origin, const Vector2& size)
  {
    min = origin;
    max = origin + size;
  }
  void Bounds2D::SetWidth(float value)
  {
    max.x = min.x + value;
  }
  void Bounds2D::SetHeight(float value)
  {
    max.y = min.y + value;
  }
  void Bounds2D::SetSize(const Vector2& sizeValue)
  {
    max = min + sizeValue;
  }
  void Bounds2D::SetMin(const Vector2& value)
  {
    min = value;
  }
  void Bounds2D::SetMax(const Vector2& value)
  {
    max = value;
  }
  void Bounds2D::SetMin(float x, float y)
  {
    min.Set(x, y);
  }
  void Bounds2D::SetMax(float x, float y)
  {
    max.Set(x, y);
  }
  
  std::vector<Bounds2D> Bounds2D::Split()const
  {
    std::vector<Bounds2D> result;
    result.push_back(GetBottomLeftQuad());
    result.push_back(GetBottomRightQuad());
    result.push_back(GetTopLeftQuad());
    result.push_back(GetTopRightQuad());
    return result;
  }
  Bounds2D Bounds2D::GetBottomLeftQuad()const
  {
    return {min, GetCenter()};
  }
  Bounds2D Bounds2D::GetBottomRightQuad()const
  {
    return Bounds2D{{max.x, min.y}, GetCenter()};
  }
  Bounds2D Bounds2D::GetTopLeftQuad()const
  {
    return Bounds2D{{min.x, max.y}, GetCenter()};
  }
  Bounds2D Bounds2D::GetTopRightQuad()const
  {
    return {GetCenter(), max};
  }
  Vector2 Bounds2D::GetBottomLeft()const
  {
    return min;
  }
  Vector2 Bounds2D::GetBottomRight()const
  {
    return {max.x, min.y};
  }
  Vector2 Bounds2D::GetTopLeft()const
  {
    return {min.x, max.y};
  }
  Vector2 Bounds2D::GetTopRight()const
  {
    return max;
  }
  Vector2 Bounds2D::GetPosition()const
  {
    return min;
  }
  Vector2 Bounds2D::GetCenter()const
  {
    return min + GetHalfSize();
  }
  float Bounds2D::GetWidth()const
  {
    return GetSize().width;
  }
  float Bounds2D::GetHeight()const
  {
    return GetSize().height;
  }
  Vector2 Bounds2D::GetMin()const
  {
    return min;
  }
  Vector2 Bounds2D::GetMax()const
  {
    return max;
  }
  Vector2 Bounds2D::GetSize()const
  {
    return max-min;
  }
  Vector2 Bounds2D::GetHalfSize()const
  {
    return GetSize() * 0.5f;
  }
  float Bounds2D::GetArea()const
  {
    return GetSize().Product();
  }
  float Bounds2D::GetPerimeter()const
  {
    return 2.0f * (GetSize().Sum());
  }
}