#include <gum/base/Region.hpp>
#include <utility>

namespace Candy::Gum
{
  
  Region::Region(SceneGraph& sceneGraph) : Node(sceneGraph), baseShape(Math::Vector2(10, 10))
  {
  
  }
  
  
  
  void Region::SetShape(SharedPtr<Shape> shape)
  {
    customShape = std::move(shape);
  }
  Rectangle& Region::GetBaseShape()
  {
    return baseShape;
  }
  Shape& Region::GetShape()
  {
    if (customShape)
    {
      return *customShape;
    }
    else
    {
      return baseShape;
    }
    
  }
  const Rectangle& Region::GetBaseShape()const
  {
    return baseShape;
  }
  const Shape& Region::GetShape()const
  {
    if (customShape)
    {
      return *customShape;
    }
    else
    {
      return baseShape;
    }
  }
  
 
  
}