#include <gum/shape/Rectangle.hpp>
#include <gum/GumRenderer.hpp>
#include "CandyPch.hpp"
namespace Candy::Gum
{
  
  
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
  float EllipseDist(Math::Vector2 mousePos, Math::Vector2 ellipseCenter, Math::Vector2 radii)
  {
    float p = (Math::Pow2(mousePos.x - ellipseCenter.x) / Math::Pow2(radii.width))
              + (Math::Pow2((mousePos.y - ellipseCenter.y)) / Math::Pow2(radii.height));
    return p;
    
    /*Math::Vector2 r = (Math::Vector2::Max((mousePos - ellipseCenter+radii), Math::Vector2::zero) / radii);
    return (r.x*r.x + r.y*r.y);*/
    
  }
  bool Rectangle::ShapeContains(Math::Vector2 localPoint) const
  {
    if (arcSize.x < Math::Epsilon<float>() || arcSize.y < Math::Epsilon<float>())
    {
      return true;
    }
    else
    {
      float dist = EllipseDist(localPoint, GetBoundsInParent().GetCenter(), arcSize);
      CANDY_CORE_INFO("Ellipse dist: {0}, at local point: {1}", dist, localPoint);
      return dist <= 1.0f;
    }
  }
  
  void Rectangle::SetX(float value)
  {
    layoutPosition.x = value;
  }
  void Rectangle::SetY(float value)
  {
    layoutPosition.y = value;
  }
  void Rectangle::SetPosition(Math::Vector2 value)
  {
    layoutPosition = value;
  }
  void Rectangle::SetPosition(float x, float y)
  {
    layoutPosition.x = x;
    layoutPosition.y = y;
  }
  
  
  void Rectangle::SetArcWidth(float value)
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
    
  }
  float Rectangle::GetX() const
  {
    return GetLayoutPosition().x;
  }
  float Rectangle::GetY() const
  {
    return GetLayoutPosition().y;
  }
  Math::Vector2 Rectangle::GetPosition() const
  {
    return GetLayoutPosition();
  }
  float Rectangle::GetWidth() const
  {
    return GetSize().width;
  }
  float Rectangle::GetHeight() const
  {
    return GetSize().height;
  }
  
  Math::Vector2 Rectangle::GetArcSize() const
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
  }
  
  
  void Rectangle::LayoutChildren()
  {
  
  }
  
  Math::Bounds2D CalcBoundsHelper(Math::Vector2 size, const Math::Matrix3& transform)
  {
    Math::Vector2 corners[4];
    corners[0] = Math::Vector2(0, 0);
    corners[1] = Math::Vector2(size.x, 0);
    corners[2] = Math::Vector2(0, size.y);
    corners[3] = Math::Vector2(size.x, size.y);
    
    // Transform the corner points
    for(int i = 0; i < 4; ++i)
    {
      corners[i] = transform * corners[i];
    }
    
    // Set initial min and max corners
    Math::Vector2 minCorner = corners[0];
    Math::Vector2 maxCorner = corners[0];
    
    // Compute the bounding box
    for(int i = 1; i < 4; ++i)
    {
      minCorner = Math::Min(minCorner, corners[i]);
      maxCorner = Math::Max(maxCorner, corners[i]);
    }
    
    // Return the computed bounding box
    Math::Bounds2D bounds;
    bounds.SetMin(minCorner);
    bounds.SetMax(maxCorner);
    return bounds;
  }
  /*void Rectangle::CalculateBounds()
  {
    //localBounds = CalcBoundsHelper(layoutSize, localTransform);
    //boundsInParent = CalcBoundsHelper(size, localToParentTransform);
    
    boundsInParent.SetPosition(position);
    boundsInParent.SetSize(size);
    boundsInScene.SetPosition(parent->GetBoundsInScene().GetMin() + position);
    boundsInScene.SetSize(size);
  }*/
  
  void Rectangle::OnRender()
  {
    //CANDY_CORE_INFO("Rendering rectangle");
    GumRenderer::SubmitRectangle(transform, *this);
  }
}