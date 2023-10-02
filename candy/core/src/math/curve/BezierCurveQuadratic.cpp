#include <candy/math/curve/BezierCurveQuadratic.hpp>

namespace Candy::Math
{
  Vector2 BezierCurveQuadratic::Evaluate(float t)const
  {
    float oneMinusT = 1.0f - t;
    float oneMinusTSquare = oneMinusT * oneMinusT;
    float tSquare = t * t;
    
    return oneMinusTSquare * start
           + 2 * oneMinusT * t * control
           + tSquare * end;
  }
  float BezierCurveQuadratic::StartToEndLength()const
  {
    return Vector2::Length(start - end);
  }
  float BezierCurveQuadratic::ControlPathLength()const
  {
    return Vector2::Length(start - control) + Vector2::Length(control - end);
  }
  float BezierCurveQuadratic::Length(float curvatureThreshold, size_t minSubdivisions, size_t maxSubdivisions)const
  {
    
    
    // Calculate curvature of curve here (simplified to absolute difference of tangent vectors here)
    Vector2 startTangent = Vector2::Normalized(control - start);
    Vector2 endTangent = Vector2::Normalized(end - control);
    float curvature = Vector2::Magnitude(startTangent-endTangent);
    
    // Calculate adaptive number of subdivisions based on curvature
    size_t n = minSubdivisions + static_cast<int>(curvature/curvatureThreshold);
    n = Math::Clamp(n, minSubdivisions, maxSubdivisions); // Clamp to [min_n, max_n]
    
    float length = 0.0f;
    Vector2 prev = Evaluate(0.0f);
    
    for(int i = 1; i <= n; ++i)
    {
      float t = (float)i/(float)n; // Calculate parameter t
      Vector2 curr = Evaluate(t);
      length += Vector2::Length(curr - prev);
      prev = curr;
    }
    
    return length;
  }
  Vector2 BezierCurveQuadratic::Tangent(float t)const
  {
    return 2 * (1 - t) * (control - start) + 2 * t * (end - control); // calculating the tangent
  }
  Vector2 BezierCurveQuadratic::ClosestPoint(const Vector2& point, size_t iterations)const
  {
    const float step = 1.0 / (float)iterations;
    
    float closestT = 0;
    float closestDistance = std::numeric_limits<float>::max();
    
    for (int i = 0; i <= iterations; ++i)
    {
      float t = step * (float)i;
      Vector2 p = Evaluate(t);
      float d = Vector2::SqrDistance(point, p);
      
      if (d < closestDistance)
      {
        closestDistance = d;
        closestT = t;
      }
    }
    
    return Evaluate(closestT);
  }
  
  std::vector<Vector2> BezierCurveQuadratic::ToLineSegments(float curvatureThreshold, size_t minSubdivisions, size_t maxSubdivisions)const
  {
    // Calculate curvature of curve here (simplified to absolute difference of tangent vectors here)
    Vector2 startTangent = Vector2::Normalized(control - start);
    Vector2 endTangent = Vector2::Normalized(end - control);
    float curvature = Vector2::Magnitude(startTangent-endTangent);
    
    // Calculate adaptive number of subdivisions based on curvature
    size_t n = minSubdivisions + static_cast<int>(curvature / curvatureThreshold);
    n = Clamp(n, minSubdivisions, maxSubdivisions); // Clamp to [min_n, max_n]
    
    std::vector<Vector2> lineSegments;
    lineSegments.reserve(n + 1);
    
    for (size_t i = 0; i <= n; ++i)
    {
      float t = (float)i / (float)n;
      Vector2 pointOnCurve = Evaluate(t);
      lineSegments.push_back(pointOnCurve);
    }
    
    return lineSegments;
  }
  float BezierCurveQuadratic::Determinant()const
  {
    return start.x * (control.y - end.y)
           + control.x * (end.y - start.y)
           + end.x * (start.y - control.y);
  }
  Concavity BezierCurveQuadratic::GetConcavity(float threshold)const
  {
    float determinant = Determinant();
    
    if (Abs(determinant) < threshold)
    {
      return Concavity::Straight;
    }
    else if (determinant > 0.0f)
    {
      return Concavity::Concave;
    }
    else
    {
      return Concavity::Convex;
    }
  }
  bool BezierCurveQuadratic::IsStraightLine(float threshold)const
  {
    return GetConcavity(threshold) == Concavity::Straight;
  }
  bool BezierCurveQuadratic::IsConvex(float threshold)const
  {
    return GetConcavity(threshold) == Concavity::Convex;
  }
  bool BezierCurveQuadratic::IsConcave(float threshold)const
  {
    return GetConcavity(threshold) == Concavity::Concave;
  }
}