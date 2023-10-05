#include <gum/shape/GumShape.hpp>

#include <utility>
#include "CandyPch.hpp"
namespace Candy::Gum
{
  using namespace Math;
  GumShape::GumShape(ShapeMutability shapeMutability) : dataRegistryID(GumID::NULL_ID), mutability(shapeMutability)
  {
  
  }
  
  GumShape::GumShape(const GumShape& other) = default;
  
  GumShape::~GumShape() = default;
  bool GumShape::Contains(const Math::Vector2& point) const
  {
    if (BoundingBoxContains(point))
    {
      return ShapeContains(point);
    }
    return false;
  }
  
  bool GumShape::BoundingBoxContains(const Math::Vector2& point)const
  {
    return boundingBox.Contains(point);
  }
  
  void GumShape::ReCalculateBoundingBox()
  {
    const GumShapeDataInternal& data = GetInternalData();
    
    if (data.vertices.empty() || data.indices.empty())
    {
      CANDY_CORE_WARN("GumShape::CalculateBoundingBox() called on empty shape to calculate bounding box!");
      return;
    }
    boundingBox = Math::Bounds2D();
    float minX = Limit<float>::Max();
    float minY = Limit<float>::Max();
    float maxX = Limit<float>::Min();
    float maxY = Limit<float>::Min();
    
    for (const auto& vertex : data.vertices)
    {
      if (vertex.position.x<minX)
      {
        minX = vertex.position.x;
      }
      if (vertex.position.y<minY)
      {
        minY = vertex.position.y;
      }
      if (vertex.position.x>maxX)
      {
        maxX = vertex.position.x;
      }
      if (vertex.position.y>maxY)
      {
        maxY = vertex.position.y;
      }
    }
    
    boundingBox.SetMin(minX, minY);
    boundingBox.SetMax(maxX, maxY);
  }
  
  const Math::Bounds2D& GumShape::GetBoundingBox() const
  {
    return boundingBox;
  }
  
  const GumShapeDataInternal& GumShape::GetInternalData() const
  {
    return GumShapeDataRegistry::GetShapeData(dataRegistryID);
  }
  
  
  std::string GumShape::GetName() const
  {
    return GumShapeDataRegistry::GetShapeName(dataRegistryID);
  }
 
}