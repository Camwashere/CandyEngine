#include <candy/math/curve/BezierCurve.hpp>

namespace Candy::Math
{
  
  
  
  
  
  
  Vector2 BezierCurve::Evaluate(float t) const
  {
    std::vector<Vector2> points = controlPoints;
    points.insert(points.begin(), start);
    points.push_back(end);
    
    return EvaluateRecursive(points, t);
  }
  
  Vector2 BezierCurve::EvaluateRecursive(const std::vector<Vector2>& points, float t) const
  {
    if (points.size() == 2)
    {
      return (1 - t) * points[0] + t * points[1];
    }
    
    std::vector<Vector2> newPoints;
    for (size_t i = 0; i < points.size() - 1; ++i)
    {
      newPoints.push_back((1 - t) * points[i] + t * points[i + 1]);
    }
    
    return EvaluateRecursive(newPoints, t);
  }
  
  std::vector<Vector2> BezierCurve::ToLineSegments(size_t subdivisions) const
  {
    std::vector<Vector2> lineSegments;
    lineSegments.reserve(subdivisions + 1);
    
    float step = 1.0 / float(subdivisions);
    
    for (size_t i = 0; i <= subdivisions; ++i)
    {
      float t = step * float(i);
      Vector2 pointOnCurve = Evaluate(t);
      lineSegments.push_back(pointOnCurve);
    }
    
    return lineSegments;
  }
  
}