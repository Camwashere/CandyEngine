#include <candy/math/curve/BezierCurve.hpp>

namespace Candy::Math
{
  
  Vector2 BezierCurve::Evaluate(float t) const
  {
    std::vector<Vector2> points = controlPoints;
    points.insert(points.begin(), start);
    points.push_back(end);
    
    size_t i, j;
    for (i = points.size() - 1; i > 0; i--) {
      for (j = 0; j < i; j++) {
        points[j] = (1 - t) * points[j] + t * points[j + 1];
      }
    }
    
    return points[0];
  }
  
  
  
  std::vector<Vector2> BezierCurve::ToLineSegments(size_t subdivisions) const
  {
    std::vector<Vector2> lineSegments;
    lineSegments.reserve(subdivisions + 1);
    
    float step = 1.0f / float(subdivisions);
    
    for (size_t i = 0; i <= subdivisions; ++i)
    {
      float t = step * float(i);
      Vector2 pointOnCurve = Evaluate(t);
      lineSegments.push_back(pointOnCurve);
    }
    
    return lineSegments;
  }
  
}