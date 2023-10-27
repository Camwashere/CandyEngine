#include <gum/base/Region.hpp>
#include <utility>
#include <CandyPch.hpp>
namespace Candy::Gum
{
  
  Region::Region()
  {
    
    name = "Region";
    transform = Math::Matrix3::IDENTITY;
    shape = CreateSharedPtr<Rectangle>(0, 0, 500, 500);
    shape->SetName("RegionShape");
    SetLayoutPosition({0, 0});
    AddChild(shape);
    SetBackgroundColor(Color::clear);
  }
  
  void Region::OnLayout()
  {
    //CANDY_CORE_INFO("Region::OnLayout");
    shape->SetLayoutPosition({0, 0});
    shape->SetSize(GetSize());
  }
  
  void Region::OnRender()
  {
    shape->OnRender();
  }
  
  void Region::OnSetSize(Math::Vector2 oldValue, Math::Vector2 newValue)
  {
    shape->SetSize(newValue);
  }
  void Region::OnSetLayoutPosition(Math::Vector2 oldValue, Math::Vector2 newValue)
  {
    shape->SetLayoutPosition({0, 0});
  }
  
  bool Region::Contains(Math::Vector2 localPoint)const
  {
    if (GetBoundsInParent().Contains(localPoint))
    {
      return shape->Contains(localPoint);
    }
    return false;
    
  }
  Color Region::GetBackgroundColor()const
  {
    return backgroundColor;
  }
  void Region::SetBackgroundColor(Color value)
  {
    backgroundColor = value;
    shape->SetFillColor(backgroundColor);
  }
  void Region::SetShape(SharedPtr<Shape> value)
  {
    shape = std::move(value);
  }
  
  Shape& Region::GetShape()
  {
    return *shape;
    
  }
  
  const Shape& Region::GetShape()const
  {
    return *shape;
  }
  
 
  
}