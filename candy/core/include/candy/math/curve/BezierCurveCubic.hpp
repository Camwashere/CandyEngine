#pragma once
#include <candy/math/Vector.hpp>

namespace Candy::Math
{
  struct BezierCurveCubic
  {
    Vector2 start;
    Vector2 control1;
    Vector2 control2;
    Vector2 end;
    
    /**
     * @brief Evaluate the point on the curve between the start and end at time t
     * @param t A value between 0 and 1, inclusive. 0 returns the start point, 1 returns the end point.
     * @return The 2D point on the curve at time t
     */
    [[nodiscard]] Vector2 Evaluate(float t)const;
    
    
  };
}