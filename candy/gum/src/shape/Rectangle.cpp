#include <gum/shape/Rectangle.hpp>
#include <gum/GumRenderer.hpp>
#include "CandyPch.hpp"
namespace Candy::Gum
{
  
  
  Rectangle::Rectangle() : Shape(ShapeType::Rectangle)
  {
    UpdateLayoutGuide();
    name = "Rectangle";
  }
  Rectangle::Rectangle(float width, float height) : Shape(ShapeType::Rectangle, {0, 0}, {width, height})
  {
    UpdateLayoutGuide();
  }
  Rectangle::Rectangle(Math::Vector2 size) : Shape(ShapeType::Rectangle, size)
  {
    UpdateLayoutGuide();
  }
  Rectangle::Rectangle(Math::Vector2 position, Math::Vector2 size) : Shape(ShapeType::Rectangle , position, size)
  {
    UpdateLayoutGuide();
  }
  Rectangle::Rectangle(float x, float y, float width, float height) : Shape(ShapeType::Rectangle, {x, y}, {width, height})
  {
    UpdateLayoutGuide();
  }
  Rectangle::Rectangle(float x, float y, Math::Vector2 size) : Shape(ShapeType::Rectangle, {x, y}, size)
  {
    UpdateLayoutGuide();
  }
  void Rectangle::UpdateLayoutGuide()
  {
    layoutGuide.minSize = size;
    layoutGuide.minPosition = position;
    
    layoutGuide.prefPosition = position;
    layoutGuide.prefSize = size;
    
    layoutGuide.maxPosition = position;
    layoutGuide.maxSize = size;
    
  }
  bool Rectangle::Contains(Math::Vector2 localPoint) const
  {
    return GetLocalBounds().Contains(localPoint);
    //return localBounds.Contains(localPoint);
  }
  
  void Rectangle::SetX(float value)
  {
    position.x = value;
    UpdateLayoutGuide();
  }
  void Rectangle::SetY(float value)
  {
    position.y = value;
    UpdateLayoutGuide();
  }
  void Rectangle::SetPosition(Math::Vector2 value)
  {
    position = value;
    UpdateLayoutGuide();
  }
  void Rectangle::SetPosition(float x, float y)
  {
    position.x = x;
    position.y = y;
    UpdateLayoutGuide();
  }
  void Rectangle::SetWidth(float value)
  {
    size.width = value;
    UpdateLayoutGuide();
  }
  void Rectangle::SetHeight(float value)
  {
    size.height = value;
    UpdateLayoutGuide();
  }
  
  void Rectangle::SetArcWidth(float value)
  {
    arcSize.width = value;
    UpdateLayoutGuide();
  }
  void Rectangle::SetArcHeight(float value)
  {
    arcSize.height = value;
    UpdateLayoutGuide();
  }
  void Rectangle::SetArcSize(Math::Vector2 value)
  {
    arcSize = value;
    UpdateLayoutGuide();
  }
  void Rectangle::SetArcSize(float arcWidth, float arcHeight)
  {
    arcSize.width = arcWidth;
    arcSize.height = arcHeight;
    UpdateLayoutGuide();
  }
  float Rectangle::GetX() const
  {
    return position.x;
  }
  float Rectangle::GetY() const
  {
    return position.y;
  }
  Math::Vector2 Rectangle::GetPosition() const
  {
    return position;
  }
  float Rectangle::GetWidth() const
  {
    return size.width;
  }
  float Rectangle::GetHeight() const
  {
    return size.height;
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
  void Rectangle::CalculateBounds()
  {
    //localBounds = CalcBoundsHelper(layoutSize, localTransform);
    boundsInParent = CalcBoundsHelper(size, localToParentTransform);
  }
  
  void Rectangle::OnRender()
  {
    //CANDY_CORE_INFO("Rendering rectangle");
    GumRenderer::SubmitRectangle(localTransform, *this);
  }
}