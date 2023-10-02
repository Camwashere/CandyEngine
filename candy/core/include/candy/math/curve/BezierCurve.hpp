#pragma once
#include <candy/math/Vector.hpp>
namespace Candy::Math
{
  
  
  struct BezierCurve
  {
    Vector2 start;
    std::vector<Vector2> controlPoints;
    Vector2 end;
    
  private:
    [[nodiscard]] Vector2 EvaluateRecursive(const std::vector<Vector2>& points, float t) const;
    
  public:
    [[nodiscard]] Vector2 Evaluate(float t) const;
    [[nodiscard]] std::vector<Vector2> ToLineSegments(size_t subdivisions) const;
  };
  
  
  
}