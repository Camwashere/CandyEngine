#include <candy/math/Quaternion.hpp>
#include <candy/math/matrix/specialization/Matrix4.hpp>
namespace Candy::Math
{
  
  Quaternion operator*(float scalar, const Quaternion& q) {
    return q * scalar;
  }
  void Quaternion::Normalize(Quaternion& a)
  {
    a.Normalize();
  }
  Quaternion Quaternion::Normalized(const Quaternion &a)
  {
    return a.Normalized();
  }
  
  float Quaternion::Angle(const Quaternion &a, const Quaternion &b)
  {
    float dot = Dot(a, b);
    return acosf(2 * dot * dot - 1);
  }
  float Quaternion::Dot(const Quaternion& a, const Quaternion& b)
  {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
  }
  Quaternion Quaternion::AngleAxis(float angle, const Vector3 &axis)
  {
    float halfAngle = angle * 0.5f;
    float s = sinf(halfAngle);
    Quaternion q;
    q.x = axis.x * s;
    q.y = axis.y * s;
    q.z = axis.z * s;
    q.w = cosf(halfAngle);
    return q;
  }
  
  Quaternion Quaternion::Euler(float x, float y, float z)
  {
    Quaternion q;
    float c1 = Math::Cos(y * 0.5f);
    float s1 = Math::Sin(y * 0.5f);
    float c2 = Math::Cos(z * 0.5f);
    float s2 = Math::Sin(z * 0.5f);
    float c3 = Math::Cos(x * 0.5f);
    float s3 = Math::Sin(x * 0.5f);
    float c1c2 = c1 * c2;
    float s1s2 = s1 * s2;
    q.w = c1c2 * c3 - s1s2 * s3;
    q.x = c1c2 * s3 + s1s2 * c3;
    q.y = s1 * c2 * c3 + c1 * s2 * s3;
    q.z = c1 * s2 * c3 - s1 * c2 * s3;
    return q;
  }
  
  Quaternion Quaternion::Euler(const Vector3 &euler)
  {
    return Euler(euler.x, euler.y, euler.z);
  }
  
  Quaternion Quaternion::FromToRotation(const Vector3 &fromDirection, const Vector3 &toDirection)
  {
    float dot = Vector3::Dot(fromDirection, toDirection);
    Vector3 cross = Vector3::Cross(fromDirection, toDirection);
    float w = Math::Sqrt(fromDirection.SqrMagnitude() * toDirection.SqrMagnitude()) + dot;
    Quaternion q;
    if (w < 1e-6f)
    {
      w = 0.0f;
      if (Abs(fromDirection.x) > Abs(fromDirection.z))
        q = Quaternion(-fromDirection.y, fromDirection.x, 0.0f, w);
      else
        q = Quaternion(0.0f, -fromDirection.z, fromDirection.y, w);
    }
    else
    {
      q = Quaternion(cross.x, cross.y, cross.z, w);
    }
    return q.Normalized();
    
  }
  
  Quaternion Quaternion::Inverse(const Quaternion &rotation)
  {
    float sqrMagnitude = rotation.SqrMagnitude();
    if (sqrMagnitude == 0.0f)
      return rotation;
    float invMagnitude = 1.0f / sqrMagnitude;
    return {-rotation.x * invMagnitude,
            -rotation.y * invMagnitude,
            -rotation.z * invMagnitude,
            rotation.w * invMagnitude};
  }
  
  Quaternion Quaternion::Lerp(const Quaternion &a, const Quaternion &b, float t)
  {
    t = (t < 0.0f) ? 0.0f : (t > 1.0f) ? 1.0f : t;
    return LerpUnclamped(a, b, t);
  }
  
  Quaternion Quaternion::LerpUnclamped(const Quaternion &a, const Quaternion &b, float t)
  {
    Quaternion q;
    if (Dot(a, b) < 0.0f)
      q = a + t * ((-b) - a);
    else
      q = a + t * (b - a);
    return q.Normalized();
    
  }
  
  Quaternion Quaternion::LookRotation(const Vector3 &forward, const Vector3 &upwards)
  {
    Vector3 z = forward.Normalized();
    Vector3 x = Vector3::Cross(upwards, z).Normalized();
    Vector3 y = Vector3::Cross(z, x).Normalized();
    
    Matrix4 m;
    m[0,0] = x.x; m[1,0] = x.y; m[2,0] = x.z;
    m[0,1] = y.x; m[1,1] = y.y; m[2,1] = y.z;
    m[0,2] = z.x; m[1,2] = z.y; m[2,2] = z.z;
    
    return Quaternion{m};
  }
  
  
  Quaternion Quaternion::RotateTowards(const Quaternion &from, const Quaternion &to, float maxDegreesDelta)
  {
    float angle = Quaternion::Angle(from, to);
    if (angle == 0.0f)
      return to;
    float t = Math::Min(1.0f, maxDegreesDelta / angle);
    return Quaternion::SlerpUnclamped(from, to, t);
  }
  
  Quaternion Quaternion::Slerp(const Quaternion &a, const Quaternion &b, float t)
  {
    if (t <= 0.0f)
      return a;
    if (t >= 1.0f)
      return b;
    return SlerpUnclamped(a, b, t);
  }
  
  Quaternion Quaternion::SlerpUnclamped(const Quaternion &a, const Quaternion &b, float t)
  {
    float cosAngle = Quaternion::Dot(a, b);
    float sign = cosAngle >= 0.0f ? 1.0f : -1.0f;
    cosAngle *= sign;
    if (cosAngle >= 1.0f - 1e-6f)
      return LerpUnclamped(a, b, t);
    float angle = Math::Acos(cosAngle);
    float sinAngle = Math::Sin(angle);
    float t0 = Math::Sin((1.0f - t) * angle) / sinAngle;
    float t1 = Math::Sin(t * angle) / sinAngle * sign;
    return {a.x * t0 + b.x * t1,
            a.y * t0 + b.y * t1,
            a.z * t0 + b.z * t1,
            a.w * t0 + b.w * t1};
  }
  
  Quaternion Quaternion::ToRadians(const Quaternion &quat)
  {
    return {Math::ToRadians(quat.x), Math::ToRadians(quat.y), Math::ToRadians(quat.z), Math::ToRadians(quat.w)};
  }
  
  Quaternion Quaternion::ToDegrees(const Quaternion &quat)
  {
    return {Math::ToDegrees(quat.x), Math::ToDegrees(quat.y), Math::ToDegrees(quat.z), Math::ToDegrees(quat.w)};
  }
  
  Vector3 Quaternion::Rotate(const Quaternion &rotation, const Vector3 &point)
  {
    // Convert the vector into a pure quaternion
    Quaternion vecQuat(0, point.x, point.y, point.z);
    
    // Calculate qvq^(-1)
    Quaternion resultQuat = rotation * vecQuat * rotation.Conjugate();
    
    // Return the x, y, z components as a Vector3
    return Vector3(resultQuat.x, resultQuat.y, resultQuat.z);
  }
  
  /*Matrix4 Quaternion::ToMatrix(const Quaternion &quaternion)
  {
    Matrix4 result(0.0f);
    float sqw = quaternion.w * quaternion.w;
    float sqx = quaternion.x * quaternion.x;
    float sqy = quaternion.y * quaternion.y;
    float sqz = quaternion.z * quaternion.z;
    
    // invs (inverse square length) is only required if quaternion is not already normalised
    float invs = 1 / (sqx + sqy + sqz + sqw);
    result.Entry(0) = (sqx - sqy - sqz + sqw) * invs; // since sqw + sqx + sqy + sqz =1/invs*invs
    result.Entry(5) = (-sqx + sqy - sqz + sqw) * invs;
    result.Entry(10) = (-sqx - sqy + sqz + sqw) * invs;
    
    float tmp1 = quaternion.x * quaternion.y;
    float tmp2 = quaternion.z * quaternion.w;
    result.Entry(1) = 2.0f * (tmp1 + tmp2) * invs;
    result.Entry(4) = 2.0f * (tmp1 - tmp2) * invs;
    
    tmp1 = quaternion.x * quaternion.z;
    tmp2 = quaternion.y * quaternion.w;
    result.Entry(3) = 2.0f * (tmp1 - tmp2) * invs;
    result.Entry(8) = 2.0f * (tmp1 + tmp2) * invs;
    tmp1 = quaternion.y * quaternion.z;
    tmp2 = quaternion.x * quaternion.w;
    result.Entry(6) = 2.0f * (tmp1 + tmp2) * invs;
    result.Entry(9) = 2.0f * (tmp1 - tmp2) * invs;
    return result;
  }*/
  
  Quaternion::Quaternion() : x(0), y(0), z(0), w(0)
  {
  
  }
  
  Quaternion::Quaternion(float x, float y, float z, float w) : data{x, y, z, w}
  {
  
  }
  
  Quaternion::Quaternion(const Vector3 &axis, float angle) : x(axis.x), y(axis.y), z(axis.z), w(angle)
  {
  
  }
  Quaternion::Quaternion(__m128 simd) : m128(simd)
  {
  
  }
  Quaternion::Quaternion(const Vector4 &vec) : x(vec.x), y(vec.y), z(vec.z), w(vec.w)
  {
  
  }
  
  Quaternion::Quaternion(const Quaternion &other)=default;
  
  Quaternion::Quaternion(const Matrix4 &matrix)
  {
    // Compute the trace of the matrix
    float trace = matrix.Entry(0) + matrix.Entry(5) + matrix.Entry(10);
    
    if(trace > 0)
    {
      float s = 0.5f / sqrtf(trace+ 1.0f);
      this->w = 0.25f / s;
      this->x = (matrix.Entry(9) - matrix.Entry(6)) * s;
      this->y = (matrix.Entry(2) - matrix.Entry(8)) * s;
      this->z = (matrix.Entry(4) - matrix.Entry(1)) * s;
    }
    else
    {
      if (matrix.Entry(0) > matrix.Entry(5) && matrix.Entry(0) > matrix.Entry(10))
      {
        float s = 2.0f * sqrtf(1.0f + matrix.Entry(0) - matrix.Entry(5) - matrix.Entry(10));
        this->w = (matrix.Entry(9) - matrix.Entry(6)) / s;
        this->x = 0.25f * s;
        this->y = (matrix.Entry(1) + matrix.Entry(4)) / s;
        this->z = (matrix.Entry(2) + matrix.Entry(8)) / s;
      }
      else if (matrix.Entry(5) > matrix.Entry(10))
      {
        float s = 2.0f * sqrtf(1.0f + matrix.Entry(5) - matrix.Entry(0) - matrix.Entry(10));
        this->w = (matrix.Entry(2) - matrix.Entry(8)) / s;
        this->x = (matrix.Entry(1) + matrix.Entry(4)) / s;
        this->y = 0.25f * s;
        this->z = (matrix.Entry(6) + matrix.Entry(9)) / s;
      }
      else
      {
        float s = 2.0f * sqrtf(1.0f + matrix.Entry(10) - matrix.Entry(0) - matrix.Entry(5));
        this->w = (matrix.Entry(4) - matrix.Entry(1)) / s;
        this->x = (matrix.Entry(2) + matrix.Entry(8)) / s;
        this->y = (matrix.Entry(6) + matrix.Entry(9)) / s;
        this->z = 0.25f * s;
      }
    }
  }
  
  bool Quaternion::operator==(const Quaternion &other) const
  {
    __m128 result = _mm_cmpeq_ps(m128, other.m128); // Compare
    int mask = _mm_movemask_ps(result); // Move the most significant bit of each byte to an integer
    return mask == 0xf; // If all bytes are equal, mask will be 0xf.
  }
  
  bool Quaternion::operator!=(const Quaternion &other) const
  {
    return !((*this) == other);
  }
  
  
  
  float &Quaternion::operator[](int index)
  {
    return data[index];
  }
  
  float Quaternion::operator[](int index) const
  {
    return data[index];
  }
  
  Quaternion Quaternion::operator*(const Quaternion &other) const
  {
    float nx = w * other.x + x * other.w + y * other.z - z * other.y;
    float ny = w * other.y - x * other.z + y * other.w + z * other.x;
    float nz = w * other.z + x * other.y - y * other.x + z * other.w;
    float nw = w * other.w - x * other.x - y * other.y - z * other.z;
    return {nx, ny, nz, nw};
  }
  
  Quaternion Quaternion::operator+(const Quaternion& other)const
  {
    return {_mm_add_ps(m128, other.m128)};
  }
  Quaternion Quaternion::operator-(const Quaternion& other)const
  {
    return {_mm_sub_ps(m128, other.m128)};
  }
  
  Quaternion Quaternion::operator*(float scalar) const
  {
    return {_mm_mul_ps(m128, _mm_set1_ps(scalar))};
  }
  
  Quaternion Quaternion::operator/(float scalar)const
  {
    return {_mm_div_ps(m128, _mm_set1_ps(scalar))};
  }
  
  Quaternion Quaternion::operator/(const Quaternion& other)const
  {
    float norm = other.x * other.x + other.y * other.y + other.z * other.z + other.w * other.w;
    Quaternion conjugate{ other.x / norm, -other.y / norm, -other.z / norm, -other.w / norm };
    
    return *this * conjugate;
  }
  
  Quaternion Quaternion::operator-() const
  {
    return {-x, -y, -z, -w};
  }
  
  void Quaternion::operator+=(const Quaternion &other)
  {
    m128 = _mm_add_ps(m128, other.m128);
  }
  
  void Quaternion::operator-=(const Quaternion &other)
  {
    m128 = _mm_sub_ps(m128, other.m128);
  }
  
  void Quaternion::operator*=(const Quaternion &other)
  {
    x = w * other.x + x * other.w + y * other.z - z * other.y;
    y = w * other.y - x * other.z + y * other.w + z * other.x;
    z = w * other.z + x * other.y - y * other.x + z * other.w;
    w = w * other.w - x * other.x - y * other.y - z * other.z;
  }
  
  void Quaternion::operator/=(const Quaternion &other)
  {
    float norm = other.x * other.x + other.y * other.y + other.z * other.z + other.w * other.w;
    Quaternion conjugate{ other.x / norm, -other.y / norm, -other.z / norm, -other.w / norm };
    
    *this *= conjugate;
  }
  
  void Quaternion::operator*=(float scalar)
  {
    m128 = _mm_mul_ps(m128, _mm_set1_ps(scalar));
  }
  
  void Quaternion::operator/=(float scalar)
  {
    m128 = _mm_div_ps(m128, _mm_set1_ps(scalar));
  }
  float Quaternion::Magnitude() const
  {
    return Math::Sqrt(x * x + y * y + z * z + w * w);
  }
  float Quaternion::SqrMagnitude() const
  {
    return x * x + y * y + z * z + w * w;
  }
  void Quaternion::SetFromToRotation(const Vector3 &fromDirection, const Vector3 &toDirection)
  {
    float dot = Vector3::Dot(fromDirection, toDirection);
    Vector3 cross = Vector3::Cross(fromDirection, toDirection);
    w = Math::Sqrt(fromDirection.SqrMagnitude() * toDirection.SqrMagnitude()) + dot;
    if (w < 1e-6f)
    {
      w = 0.0f;
      if (abs(fromDirection.x) > abs(fromDirection.z))
        cross = Vector3(-fromDirection.y, fromDirection.x, 0.0f);
      else
        cross = Vector3(0.0f, -fromDirection.z, fromDirection.y);
    }
    x = cross.x;
    y = cross.y;
    z = cross.z;
    Normalize();
  }
  
  void Quaternion::SetLookRotation(const Vector3 &view, const Vector3 &up)
  {
    Vector3 a = view;
    a.Normalize();
    Vector3 b = Vector3::Cross(up, a);
    b.Normalize();
    Vector3 c = Vector3::Cross(a, b);
    c.Normalize();
    
    float m00 = b.x;
    float m01 = c.x;
    float m02 = a.x;
    float m10 = b.y;
    float m11 = c.y;
    float m12 = a.y;
    float m20 = b.z;
    float m21 = c.z;
    float m22 = a.z;
    
    float num8 = (m00 + m11) + m22;
    if (num8 > 0.0f)
    {
      float num = Math::Sqrt(num8 + 1.0f);
      w = num * 0.5f;
      num = 0.5f / num;
      x = (m12 - m21) * num;
      y = (m20 - m02) * num;
      z = (m01 - m10) * num;
      return;
    }
    if ((m00 >= m11) && (m00 >= m22))
    {
      float num7 = Math::Sqrt(((1.0f + m00) - m11) - m22);
      float num4 = 0.5f / num7;
      x = 0.5f * num7;
      y = (m01 + m10) * num4;
      z = (m02 + m20) * num4;
      w = (m12 - m21) * num4;
      return;
    }
    if (m11 > m22)
    {
      float num6 = Math::Sqrt(((1.0f + m11) - m00) - m22);
      float num3 = 0.5f / num6;
      x = (m10 + m01) * num3;
      y = 0.5f * num6;
      z = (m21 + m12) * num3;
      w = (m20 - m02) * num3;
      return;
    }
    float num5 = Math::Sqrt(((1.0f + m22) - m00) - m11);
    float num2 = 0.5f / num5;
    x = (m20 + m02) * num2;
    y = (m21 + m12) * num2;
    z = 0.5f * num5;
    w = (m01 - m10) * num2;
  }
  
  void Quaternion::ToAngleAxis(float &angle, Vector3 &axis)
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
  
  Quaternion Quaternion::Conjugate() const
  {
    return {-x, -y, -z, w};
  }
  
  Vector3 Quaternion::ToEuler() const
  {
    Vector3 angles;
    
    // roll (x-axis rotation)
    float sinr_cosp = 2.0f * (w * x + y * z);
    float cosr_cosp = 1.0f - 2.0f * (x * x + y * y);
    angles.z = Atan2(sinr_cosp, cosr_cosp);
    
    // pitch (y-axis rotation)
    float sinp = 2.0f * (w * y - z * x);
    if (Abs(sinp) >= 1)
      angles.y = copysignf(Math::PI / 2.f, sinp); // use 90 degrees if out of range
    else
      angles.y = Asin(sinp);
    
    // yaw (z-axis rotation)
    float siny_cosp = 2.0f * (w * z + x * y);
    float cosy_cosp = 1.0f - 2.0f * (y * y + z * z);
    angles.x = Atan2(siny_cosp, cosy_cosp);
    
    return angles;
  }
  void Quaternion::Normalize()
  {
    float magnitude = Magnitude();
    x /= magnitude;
    y /= magnitude;
    z /= magnitude;
    w /= magnitude;
  }
  Quaternion Quaternion::Normalized() const
  {
    float magnitude = Magnitude();
    return {x / magnitude, y / magnitude, z / magnitude, w / magnitude};
    
  }
  
  
  
}