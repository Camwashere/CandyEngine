#pragma once

namespace Candy::Math
{
  template<typename T>
  QuaternionBase<T> QuaternionBase<T>::Normalize(const QuaternionBase<T>& a)
  {
    T mag = a.Magnitude();
    return {a.x/mag, a.y/mag, a.z/mag, a.w/mag};
  }
  template<typename T>
  T QuaternionBase<T>::Angle(const QuaternionBase<T> &a, const QuaternionBase<T> &b)
  {
    T dot = Dot(a, b);
    return acosf(2 * dot * dot - 1);
  }
  template<typename T>
  QuaternionBase<T> QuaternionBase<T>::AngleAxis(T angle, const VectorBase<T, 3> &axis)
  {
    T halfAngle = angle * 0.5f;
    T s = sinf(halfAngle);
    QuaternionBase<T> q;
    q.x = axis.x * s;
    q.y = axis.y * s;
    q.z = axis.z * s;
    q.w = cosf(halfAngle);
    return q;
  }
  
  
  template<typename T>
  QuaternionBase<T> QuaternionBase<T>::Euler(T x, T y, T z)
  {
    QuaternionBase<T> q;
    T c1 = Math::Cos(y * 0.5f);
    T s1 = Math::Sin(y * 0.5f);
    T c2 = Math::Cos(z * 0.5f);
    T s2 = Math::Sin(z * 0.5f);
    T c3 = Math::Cos(x * 0.5f);
    T s3 = Math::Sin(x * 0.5f);
    T c1c2 = c1 * c2;
    T s1s2 = s1 * s2;
    q.w = c1c2 * c3 - s1s2 * s3;
    q.x = c1c2 * s3 + s1s2 * c3;
    q.y = s1 * c2 * c3 + c1 * s2 * s3;
    q.z = c1 * s2 * c3 - s1 * c2 * s3;
    return q;
    
  }
  template<typename T>
  QuaternionBase<T> QuaternionBase<T>::Euler(const VectorBase<T, 3>& euler)
  {
    return Euler(euler.x, euler.y, euler.z);
  }
  
  
  
  template<typename T>
  QuaternionBase<T> QuaternionBase<T>::FromToRotation(const VectorBase<T, 3> &fromDirection, const VectorBase<T, 3> &toDirection)
  {
    T dot = VectorBase<T, 3>::Dot(fromDirection, toDirection);
    VectorBase<T, 3> cross = VectorBase<T, 3>::Cross(fromDirection, toDirection);
    T w = Math::Sqrt(fromDirection.SqrMagnitude() * toDirection.SqrMagnitude()) + dot;
    QuaternionBase<T> q;
    if (w < 1e-6f)
    {
      w = 0.0f;
      if (abs(fromDirection.x) > abs(fromDirection.z))
        q = QuaternionBase<T>(-fromDirection.y, fromDirection.x, 0.0f, w);
      else
        q = QuaternionBase<T>(0.0f, -fromDirection.z, fromDirection.y, w);
    }
    else
    {
      q = QuaternionBase<T>(cross.x, cross.y, cross.z, w);
    }
    q.Normalize();
    return q;
    
  }
  template<typename T>
  QuaternionBase<T> QuaternionBase<T>::Inverse(const QuaternionBase<T> &rotation)
  {
    T sqrMagnitude = rotation.SqrMagnitude();
    if (sqrMagnitude == 0.0f)
      return rotation;
    T invMagnitude = 1.0f / sqrMagnitude;
    return {-rotation.x * invMagnitude,
            -rotation.y * invMagnitude,
            -rotation.z * invMagnitude,
            rotation.w * invMagnitude};
    
  }
  template<typename T>
  QuaternionBase<T> QuaternionBase<T>::Lerp(const QuaternionBase<T> &a, const QuaternionBase<T> &b, T t)
  {
    t = (t < 0.0f) ? 0.0f : (t > 1.0f) ? 1.0f : t;
    return LerpUnclamped(a, b, t);
  }
  template<typename T>
  QuaternionBase<T> QuaternionBase<T>::LerpUnclamped(const QuaternionBase<T> &a, const QuaternionBase<T> &b, T t)
  {
    QuaternionBase<T> q;
    if (Dot(a, b) < 0.0f)
      q = a + t * ((-b) - a);
    else
      q = a + t * (b - a);
    q.Normalize();
    return q;
  }
  template<typename T>
  QuaternionBase<T> QuaternionBase<T>::LookRotation(const VectorBase<T, 3>& forward, const VectorBase<T, 3>& upwards)
  {
    VectorBase<T, 3> z = forward.Normalized();
    VectorBase<T, 3> x = VectorBase<T, 3>::Cross(upwards, z).Normalized();
    VectorBase<T, 3> y = VectorBase<T, 3>::Cross(z, x).Normalized();
    
    Matrix4 m;
    m[0,0] = x.x; m[1,0] = x.y; m[2,0] = x.z;
    m[0,1] = y.x; m[1,1] = y.y; m[2,1] = y.z;
    m[0,2] = z.x; m[1,2] = z.y; m[2,2] = z.z;
    
    return QuaternionBase<T>(m);
    
  }
  
  template<typename T>
  QuaternionBase<T> QuaternionBase<T>::Normalized(const QuaternionBase<T> &a)
  {
    T mag = a.Magnitude();
    return {a.x/mag, a.y/mag, a.z/mag, a.w/mag};
  }
  
  template<typename T>
  QuaternionBase<T> QuaternionBase<T>::RotateTowards(const QuaternionBase<T> &from, const QuaternionBase<T> &to, T maxDegreesDelta)
  {
    T angle = QuaternionBase<T>::Angle(from, to);
    if (angle == 0.0f)
      return to;
    T t = Math::Min(1.0f, maxDegreesDelta / angle);
    return QuaternionBase<T>::SlerpUnclamped(from, to, t);
  }
  template<typename T>
  QuaternionBase<T> QuaternionBase<T>::Slerp(const QuaternionBase<T> &a, const QuaternionBase<T> &b, T t)
  {
    if (t <= 0.0f)
      return a;
    if (t >= 1.0f)
      return b;
    return SlerpUnclamped(a, b, t);
    
  }
  template<typename T>
  QuaternionBase<T> QuaternionBase<T>::SlerpUnclamped(const QuaternionBase<T> &a, const QuaternionBase<T> &b, T t)
  {
    T cosAngle = QuaternionBase<T>::Dot(a, b);
    T sign = cosAngle >= 0.0f ? 1.0f : -1.0f;
    cosAngle *= sign;
    if (cosAngle >= 1.0f - 1e-6f)
      return LerpUnclamped(a, b, t);
    T angle = Math::Acos(cosAngle);
    T sinAngle = Math::Sin(angle);
    T t0 = Math::Sin((1.0f - t) * angle) / sinAngle;
    T t1 = Math::Sin(t * angle) / sinAngle * sign;
    return {a.x * t0 + b.x * t1,
            a.y * t0 + b.y * t1,
            a.z * t0 + b.z * t1,
            a.w * t0 + b.w * t1};
  }
  template<typename T>
  QuaternionBase<T> QuaternionBase<T>::ToRadians(const QuaternionBase<T>& quat)
  {
    return {Math::ToRadians(quat.x), Math::ToRadians(quat.y), Math::ToRadians(quat.z), Math::ToRadians(quat.w)};
  }
  template<typename T>
  QuaternionBase<T> QuaternionBase<T>::ToDegrees(const QuaternionBase<T>& quat)
  {
    return {Math::ToDegrees(quat.x), Math::ToDegrees(quat.y), Math::ToDegrees(quat.z), Math::ToDegrees(quat.w)};
  }
  template<typename T>
  VectorBase<T, 3> QuaternionBase<T>::Rotate(const QuaternionBase<T>& rotation, const VectorBase<T, 3>& point)
  {
    // Convert the vector into a pure quaternion
    QuaternionBase<T> vecQuat(0, point.x, point.y, point.z);
   
    // Calculate qvq^(-1)
    QuaternionBase<T> resultQuat = rotation * vecQuat * rotation.Conjugate();
    
    // Return the x, y, z components as a Vector3
    return Vector3(resultQuat.x, resultQuat.y, resultQuat.z);
  }
  template<typename T>
  AbstractMatrixBase<T, 4, 4> QuaternionBase<T>::ToMatrix(const QuaternionBase<T>& quaternion)
  {
    Matrix4 result(0.0f);
    float sqw = quaternion.w * quaternion.w;
    float sqx = quaternion.x * quaternion.x;
    float sqy = quaternion.y * quaternion.y;
    float sqz = quaternion.z * quaternion.z;
    
    // invs (inverse square length) is only required if quaternion is not already normalised
    float invs = 1 / (sqx + sqy + sqz + sqw);
    result[0] = (sqx - sqy - sqz + sqw) * invs; // since sqw + sqx + sqy + sqz =1/invs*invs
    result[5] = (-sqx + sqy - sqz + sqw) * invs;
    result[10] = (-sqx - sqy + sqz + sqw) * invs;
    
    float tmp1 = quaternion.x * quaternion.y;
    float tmp2 = quaternion.z * quaternion.w;
    result[1] = 2.0f * (tmp1 + tmp2) * invs;
    result[4] = 2.0f * (tmp1 - tmp2) * invs;
    
    tmp1 = quaternion.x * quaternion.z;
    tmp2 = quaternion.y * quaternion.w;
    result[3] = 2.0f * (tmp1 - tmp2) * invs;
    result[8] = 2.0f * (tmp1 + tmp2) * invs;
    tmp1 = quaternion.y * quaternion.z;
    tmp2 = quaternion.x * quaternion.w;
    result[6] = 2.0f * (tmp1 + tmp2) * invs;
    result[9] = 2.0f * (tmp1 - tmp2) * invs;
    return result;
  }
  template<typename T>
  QuaternionBase<T>::QuaternionBase()=default;
  template<typename T>
  QuaternionBase<T>::QuaternionBase(T x, T y, T z, T w) : VectorBase<T, 4>(x, y, z, w){}
  template<typename T>
  QuaternionBase<T>::QuaternionBase(const VectorBase<T, 3>& axis, T angle) : VectorBase<T, 4>(axis, angle){}
  template<typename T>
  QuaternionBase<T>::QuaternionBase(const VectorBase<T, 4>& vec) : VectorBase<T, 4>(vec){}
  template<typename T>
  QuaternionBase<T>::QuaternionBase(const QuaternionBase<T>& other) : VectorBase<T, 4>(other){}
  
  template<typename T> template <typename E>
  constexpr QuaternionBase<T>::QuaternionBase(const VectorExpression<T, E>& expr) : VectorBase<T, 4>(expr){}
  
  template<typename T>
  QuaternionBase<T> QuaternionBase<T>::operator*(const QuaternionBase<T>& other)const
  {
    return { w * other.x + x * other.w + y * other.z - z * other.y,
             w * other.y + y * other.w + z * other.x - x * other.z,
             w * other.z + z * other.w + x * other.y - y * other.x,
             w * other.w - x * other.x - y * other.y - z * other.z };
  }
  template<typename T>
  QuaternionBase<T> QuaternionBase<T>::operator*(T scalar)const
  {
    return {x * scalar, y * scalar, z * scalar, w * scalar};
  }
  
  template<typename T>
  void QuaternionBase<T>::SetFromToRotation(const VectorBase<T, 3>& fromDirection, const VectorBase<T, 3>& toDirection)
  {
    T dot = VectorBase<T, 3>::Dot(fromDirection, toDirection);
    VectorBase<T, 3> cross = VectorBase<T, 3>::Cross(fromDirection, toDirection);
    w = Math::Sqrt(fromDirection.SqrMagnitude() * toDirection.SqrMagnitude()) + dot;
    if (w < 1e-6f)
    {
      w = 0.0f;
      if (abs(fromDirection.x) > abs(fromDirection.z))
        cross = VectorBase<T, 3>(-fromDirection.y, fromDirection.x, 0.0f);
      else
        cross = VectorBase<T, 3>(0.0f, -fromDirection.z, fromDirection.y);
    }
    x = cross.x;
    y = cross.y;
    z = cross.z;
    Normalize();
  }
  template<typename T>
  void QuaternionBase<T>::SetLookRotation(const VectorBase<T, 3>& view, const VectorBase<T, 3>& up)
  {
    VectorBase<T, 3> a = view;
    a.Normalize();
    VectorBase<T, 3> b = VectorBase<T, 3>::Cross(up, a);
    b.Normalize();
    VectorBase<T, 3> c = VectorBase<T, 3>::Cross(a, b);
    c.Normalize();
    
    T m00 = b.x;
    T m01 = c.x;
    T m02 = a.x;
    T m10 = b.y;
    T m11 = c.y;
    T m12 = a.y;
    T m20 = b.z;
    T m21 = c.z;
    T m22 = a.z;
    
    T num8 = (m00 + m11) + m22;
    if (num8 > 0.0f)
    {
      T num = Math::Sqrt(num8 + 1.0f);
      w = num * 0.5f;
      num = 0.5f / num;
      x = (m12 - m21) * num;
      y = (m20 - m02) * num;
      z = (m01 - m10) * num;
      return;
    }
    if ((m00 >= m11) && (m00 >= m22))
    {
      T num7 = Math::Sqrt(((1.0f + m00) - m11) - m22);
      T num4 = 0.5f / num7;
      x = 0.5f * num7;
      y = (m01 + m10) * num4;
      z = (m02 + m20) * num4;
      w = (m12 - m21) * num4;
      return;
    }
    if (m11 > m22)
    {
      T num6 = Math::Sqrt(((1.0f + m11) - m00) - m22);
      T num3 = 0.5f / num6;
      x = (m10 + m01) * num3;
      y = 0.5f * num6;
      z = (m21 + m12) * num3;
      w = (m20 - m02) * num3;
      return;
    }
    T num5 = Math::Sqrt(((1.0f + m22) - m00) - m11);
    T num2 = 0.5f / num5;
    x = (m20 + m02) * num2;
    y = (m21 + m12) * num2;
    z = 0.5f * num5;
    w = (m01 - m10) * num2;
  }
  template<typename T>
  void QuaternionBase<T>::ToAngleAxis(T& angle, VectorBase<T, 3>& axis)
  {
    if(w > 1)
      Normalize();
    angle=2*Math::Acos(w);
    float s=Math::Sqrt(1-w*w);
    if(s<0.001){
      axis.x=x;axis.y=y;axis.z=z;
    }else{
      axis.x=x/s;axis.y=y/s;axis.z=z/s;
    }
  }
  template<typename T>
  QuaternionBase<T> QuaternionBase<T>::Conjugate() const
  {
    return QuaternionBase<T>(w, -x, -y, -z);
  }
  
  template<typename T>
  QuaternionBase<T> QuaternionBase<T>::Normalized() const
  {
    return QuaternionBase<T>::Normalize(*this);
  }
  
}