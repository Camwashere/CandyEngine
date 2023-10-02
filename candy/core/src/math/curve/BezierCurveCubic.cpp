#include <candy/math/curve/BezierCurveCubic.hpp>

namespace Candy::Math
{
  Vector2 BezierCurveCubic::Evaluate(float t)const
  {
    float oneMinusT = 1.0f - t;
    float oneMinusTSquare = oneMinusT * oneMinusT;
    float oneMinusTCube = oneMinusTSquare * oneMinusT;
    float tSquare = t * t;
    float tCube = tSquare * t;
    
    return oneMinusTCube * start
           + 3.0f * oneMinusTSquare * t * control1
           + 3.0f * oneMinusT * tSquare * control2
           + tCube * end;
  }
}