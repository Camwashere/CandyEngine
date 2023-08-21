#pragma once
#include <candy/math/Vector.hpp>
#include <candy/math/Matrix.hpp>
namespace Candy::Math
{
  struct Ray3
  {
    Vector3 origin;
    Vector3 end;
    
    static Ray3 GenerateFromScreenPoint(const Vector2& screenPoint, const Matrix4& viewMatrix, const Matrix4& projectionMatrix, const Vector2& screenSize);
  };
}