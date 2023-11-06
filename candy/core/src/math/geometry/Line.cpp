#include <candy/math/geometry/Line.hpp>

namespace Candy::Math
{
  Vector2 Line::Evaluate(float t)const
  {
    return start + (end - start) * t;
  }
}