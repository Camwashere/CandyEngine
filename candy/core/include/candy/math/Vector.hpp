#pragma once
#include "vector/VectorBase.hpp"
#include "vector/Vector2Base.hpp"
#include "vector/Vector3Base.hpp"
#include "vector/Vector4Base.hpp"

namespace Candy::Math
{
  typedef VectorBase<float, 2> Vector2;
  typedef VectorBase<float, 3> Vector3;
  typedef VectorBase<float, 4> Vector4;
  
  typedef VectorBase<double, 2> Vector2d;
  typedef VectorBase<double, 3> Vector3d;
  typedef VectorBase<double, 4> Vector4d;
  
  typedef VectorBase<int8_t, 2> Vector2b;
  typedef VectorBase<int8_t, 3> Vector3b;
  typedef VectorBase<int8_t, 4> Vector4b;
  
  typedef VectorBase<uint8_t, 2> Vector2ub;
  typedef VectorBase<uint8_t, 3> Vector3ub;
  typedef VectorBase<uint8_t, 4> Vector4ub;
  
  
  typedef VectorBase<int32_t, 2> Vector2i;
  typedef VectorBase<int32_t, 3> Vector3i;
  typedef VectorBase<int32_t, 4> Vector4i;
  
  
  typedef VectorBase<uint32_t, 2> Vector2u;
  typedef VectorBase<uint32_t, 3> Vector3u;
  typedef VectorBase<uint32_t, 4> Vector4u;
  
  
  
}
