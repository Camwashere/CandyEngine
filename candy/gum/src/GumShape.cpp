#include "gum/shape/GumShape.hpp"

namespace Candy::Gum
{
  using namespace Math;
  
  
  bool GumShapeBase::Contains(const Math::Vector2& point) const
  {
    if (boundingBox.Contains(point))
    {
      return ShapeContains(point);
    }
    return false;
  }
  
  const Math::Bounds2D& GumShapeBase::GetBoundingBox() const
  {
    return boundingBox;
  }
  void GumShape::CalculateBoundingBox()
  {
    boundingBox = Math::Bounds2D();
    float minX = Limit<float>::Max();
    float minY = Limit<float>::Max();
    float maxX = Limit<float>::Min();
    float maxY = Limit<float>::Min();
    
    for (const auto& point : points)
    {
      if (point.x < minX)
      {
        minX = point.x;
      }
      if (point.y < minY)
      {
        minY = point.y;
      }
      if (point.x > maxX)
      {
        maxX = point.x;
      }
      if (point.y > maxY)
      {
        maxY = point.y;
      }
    }
  }
  void GumShape::AddPoint(const Math::Vector2& point)
  {
    points.push_back(point);
    
  }
  
  void GumShape::AddLine(const Math::Vector2& start, const Math::Vector2& end)
  {
    AddPoint(start);
    AddPoint(end);
  }
  
  void GumShape::AddCurve(const Math::BezierCurveQuadratic& curve, float curvatureThreshold, size_t minSubdivisions, size_t maxSubdivisions)
  {
    auto curvePoints = curve.ToLineSegments(curvatureThreshold, minSubdivisions, maxSubdivisions);
    for (auto& curvePoint : curvePoints)
    {
      points.push_back(curvePoint);
    }
    
  }
  
  bool GumShape::Contains(const Math::Vector2& point) const
  {
    if (boundingBox.Contains(point))
    {
      // Raycast from point to the right
      // Count intersections with edges
      // If odd, point is inside
      // If even, point is outside
      size_t intersections = 0;
      for (size_t i = 0; i < points.size(); ++i)
      {
        const Vector2& start = points[i];
        const Vector2& end = points[(i + 1) % points.size()];
        
        if (start.y == end.y)
        {
          continue;
        }
        
        if (start.y > point.y && end.y > point.y)
        {
          continue;
        }
        
        if (start.y < point.y && end.y < point.y)
        {
          continue;
        }
        
        if (start.x > point.x && end.x > point.x)
        {
          continue;
        }
        
        if (start.y == point.y && end.y == point.y)
        {
          continue;
        }
        
        if (start.x == point.x && end.x == point.x)
        {
          intersections++;
          continue;
        }
        
        float t = (point.y - start.y) / (end.y - start.y);
        float x = start.x + t * (end.x - start.x);
        
        if (x > point.x)
        {
          intersections++;
        }
      }
      
      return intersections % 2 == 1;
    }
    return false;
  }
  
  const std::vector<Math::Vector2>& GumShape::GetPoints() const{return points;}
  const Math::Bounds2D& GumShape::GetBoundingBox() const{return boundingBox;}
}