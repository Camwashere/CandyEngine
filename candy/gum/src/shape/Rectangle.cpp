#include <gum/shape/Rectangle.hpp>
#include <gum/render/Renderer.hpp>
#include "CandyPch.hpp"
namespace Candy::Gum
{
  using namespace Math;
  
  Rectangle::Rectangle() : Shape(ShapeType::Rectangle)
  {
    name = "Rectangle";
  }
  Rectangle::Rectangle(float width, float height) : Shape(ShapeType::Rectangle, {0, 0}, {width, height})
  {
    name = "Rectangle";
  }
  Rectangle::Rectangle(Math::Vector2 size) : Shape(ShapeType::Rectangle, size)
  {
    name = "Rectangle";
  }
  Rectangle::Rectangle(Math::Vector2 position, Math::Vector2 size) : Shape(ShapeType::Rectangle , position, size)
  {
    name = "Rectangle";
  }
  Rectangle::Rectangle(float x, float y, float width, float height) : Shape(ShapeType::Rectangle, {x, y}, {width, height})
  {
    name = "Rectangle";
  }
  Rectangle::Rectangle(float x, float y, Math::Vector2 size) : Shape(ShapeType::Rectangle, {x, y}, size)
  {
    name = "Rectangle";
  }
  float EllipseDist(Math::Vector2 mousePos, Math::Vector2 cornerCenter, Math::Vector2 arcSize)
  {
    float dx = mousePos.x - cornerCenter.x;
    float dy = mousePos.y - cornerCenter.y;
    
    // ArcSize is diameter (2r), so divide by ArcSize/2 (=r)
    float normalizedX = dx / (arcSize.x);
    float normalizedY = dy / (arcSize.y);
    
    return Math::Sqrt(Math::Pow2(normalizedX) + Math::Pow2(normalizedY));
  }
  
  
  
  bool Rectangle::Contains(Math::Vector2 localPoint) const
  {
    Math::Vector2 nonRoundSize = GetSize() - GetSize()*arcSize;
    Math::Vector2 nonRoundPos = GetLayoutPosition() + GetSize()*arcSize*0.5f;
    
    Math::Bounds2D nonRoundBounds;
    nonRoundBounds.SetFromOrigin(nonRoundPos, nonRoundSize);
    //nonRoundBounds.SetPosition(nonRoundPos);
    //nonRoundBounds.SetSize(nonRoundSize);
    if (nonRoundBounds.Contains(localPoint))
    {
      return true;
    }
    
    
    if (GetBoundsInParent().Contains(localPoint)) // If the point is in the round section of the bounds
    {
      //CANDY_CORE_INFO("IN ROUND SECTION");
      return ShapeContains(localPoint);
    }
    
    return false;
  }
  bool Rectangle::ShapeContains(Math::Vector2 localPoint) const
  {
    if (arcSize.x < Math::Epsilon<float>() || arcSize.y < Math::Epsilon<float>())
    {
      return true;
    }
    else
    {
      Math::Vector2 relativePoint = localPoint-GetLayoutPosition();
      // normalize relative point
      Math::Vector2 size = GetSize();
      Math::Vector2 normalizedPoint = { relativePoint.x / size.x, relativePoint.y / size.y };
      normalizedPoint =  normalizedPoint * 2.0f - Vector2(1.0f);
      
      std::vector<Vector2> corners = {{-1.0f, -1.0f}, {-1.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, -1.0f}};
      
      bool inEllipse=true;
      for (Vector2 corner : corners)
      {
        float dist = EllipseDist(normalizedPoint, corner, arcSize);
        if (dist <= 0.5f)
        {
          inEllipse=false;
          break;
        }
      }
      return inEllipse;
    }
  }
  
 
  
  
  /*void Rectangle::SetArcWidth(float value)
  {
    arcSize.width = value;
    
  }
  void Rectangle::SetArcHeight(float value)
  {
    arcSize.height = value;
    
  }
  void Rectangle::SetArcSize(Math::Vector2 value)
  {
    arcSize = value;
    
  }
  void Rectangle::SetArcSize(float arcWidth, float arcHeight)
  {
    arcSize.width = arcWidth;
    arcSize.height = arcHeight;
    
  }*/
  float Rectangle::GetX() const
  {
    return GetLayoutPosition().x;
  }
  float Rectangle::GetY() const
  {
    return GetLayoutPosition().y;
  }
  /*Math::Vector2 Rectangle::GetPosition() const
  {
    return GetLayoutPosition();
  }*/
  float Rectangle::GetWidth() const
  {
    return GetSize().width;
  }
  float Rectangle::GetHeight() const
  {
    return GetSize().height;
  }
  
  /*Math::Vector2 Rectangle::GetArcSize() const
  {
    return arcSize;
  }
  float Rectangle::GetArcWidth() const
  {
    return arcSize.width;
  }
  float Rectangle::GetArcHeight() const
  {
    return arcSize.height;
  }*/
  
  
  
  void Rectangle::OnRender()
  {
    Renderer::SubmitShape(transform, *this);
  }
}