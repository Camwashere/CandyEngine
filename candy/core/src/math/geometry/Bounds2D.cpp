#include <candy/math/geometry/Bounds2D.hpp>

namespace Candy::Math
{
  Bounds2D::Bounds2D() = default;
  Bounds2D::Bounds2D(const Vector2& pos, const Vector2& sizeValue) : position(pos), size(sizeValue){}
  Bounds2D::Bounds2D(const Vector2& pos, float width, float height) : position(pos), size(width, height){}
  Bounds2D::Bounds2D(float positionX, float positionY, float width, float height) : position(positionX, positionY), size(width, height)
  {
  
  }
  
  bool Bounds2D::Contains(const Vector2& point)const
  {
    return Contains(point.x, point.y);
  }
  bool Bounds2D::Contains(float x, float y)const
  {
    return x >= position.x && x <= (position.x + size.width) && y >= position.y && y <= (position.y + size.width);
  }
  bool Bounds2D::Contains(const Bounds2D& other)const
  {
    return Contains(other.position) && Contains(other.GetMax());
  }
  
  bool Bounds2D::Overlaps(const Bounds2D& other)const
  {
    return Contains(other.position) || Contains(other.GetMax());
  }
  
  
  void Bounds2D::SetPosition(const Vector2& pos)
  {
    position = pos;
  }
  void Bounds2D::SetCenter(const Vector2& center)
  {
    SetCenter(center.x, center.y);
  }
  void Bounds2D::SetCenter(float centerX, float centerY)
  {
    position.x = centerX - size.width * 0.5f;
    position.y = centerY - size.height * 0.5f;
  }
  void Bounds2D::SetWidth(float value)
  {
    size.width = value;
  }
  void Bounds2D::SetHeight(float value)
  {
    size.height = value;
  }
  void Bounds2D::SetSize(const Vector2& sizeValue)
  {
    size = sizeValue;
  }
  void Bounds2D::SetMin(const Vector2& min)
  {
    position = min;
  }
  void Bounds2D::SetMax(const Vector2& max)
  {
    size = max - position;
  }
  void Bounds2D::SetMin(float x, float y)
  {
    position.Set(x, y);
  }
  void Bounds2D::SetMax(float x, float y)
  {
    size.Set(x - position.x, y - position.y);
  }
  
  
  
  Vector2 Bounds2D::GetCenter()const
  {
     return position + size * 0.5f;
  }
  float Bounds2D::GetWidth()const
  {
    return size.width;
  }
  float Bounds2D::GetHeight()const
  {
    return size.height;
  }
  Vector2 Bounds2D::GetMin()const
  {
    return position;
  }
  Vector2 Bounds2D::GetMax()const
  {
    return position + size;
  }
  Vector2 Bounds2D::GetSize()const
  {
    return size;
  }
  float Bounds2D::GetArea()const
  {
    return size.width * size.height;
  }
  float Bounds2D::GetPerimeter()const
  {
    return 2.0f * (size.width + size.height);
  }
}