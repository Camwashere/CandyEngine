#pragma once
#include <candy/math/Vector.hpp>
namespace Candy::Math
{
  struct Line
  {
    Vector2 start;
    Vector2 end;
    
    [[nodiscard]] Vector2 Evaluate(float t)const;
  };
}