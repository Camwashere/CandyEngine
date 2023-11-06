#pragma once
#include <candy/math/Vector.hpp>
namespace Candy::Math
{
  
  
  struct BezierCurve
  {
    Vector2 start;
    std::vector<Vector2> controlPoints;
    Vector2 end;
    
    
  public:
    [[nodiscard]] Vector2 Evaluate(float t) const;
    [[nodiscard]] std::vector<Vector2> ToLineSegments(size_t subdivisions) const;
  };
  
  
  
}