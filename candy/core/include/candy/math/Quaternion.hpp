#pragma once
//#include "quaternion/QuaternionBase.hpp"
//#include "Matrix.hpp"
#include <xmmintrin.h>
#include <candy/math/Vector.hpp>

namespace Candy::Math
{
  //typedef QuaternionBase<float> Quaternion;
  class Matrix4;
  struct Quaternion
  {
  public:
    union
    {
      float data[4];
      struct{float x, y, z, w;};
      __m128 m128;
    };
  public:
    static void Normalize(Quaternion& a);
    static Quaternion Normalized(const Quaternion& a);
    static float Angle(const Quaternion& a, const Quaternion& b);
    static float Dot(const Quaternion& a, const Quaternion& b);
    static Quaternion AngleAxis(float angle, const Vector3& axis);
    static Quaternion Euler(float x, float y, float z);
    static Quaternion Euler(const Vector3& euler);
    static Quaternion FromToRotation(const Vector3& fromDirection, const Vector3& toDirection);
    static Quaternion Inverse(const Quaternion& rotation);
    static Quaternion Lerp(const Quaternion& a, const Quaternion& b, float t);
    static Quaternion LerpUnclamped(const Quaternion& a, const Quaternion& b, float t);
    static Quaternion LookRotation(const Vector3& forward, const Vector3& upwards = Vector3::up);
    static Quaternion RotateTowards(const Quaternion& from, const Quaternion& to, float maxDegreesDelta);
    static Quaternion Slerp(const Quaternion& a, const Quaternion& b, float t);
    static Quaternion SlerpUnclamped(const Quaternion& a, const Quaternion& b, float t);
    static Quaternion ToRadians(const Quaternion& quat);
    static Quaternion ToDegrees(const Quaternion& quat);
    static Vector3 Rotate(const Quaternion& rotation, const Vector3& point);
    //static Matrix4 ToMatrix(const Quaternion& quaternion);
    
    
  
  public:
    Quaternion();
    Quaternion(float x, float y, float z, float w);
    Quaternion(const Vector3& axis, float angle);
    Quaternion(__m128 simd);
    explicit Quaternion(const Vector4& vec);
    Quaternion(const Quaternion& other);
    
    /*template <typename E>
    constexpr Quaternion(const VectorExpression<float, E>& expr) : m128(_mm_setr_ps(expr[0], expr[1], expr[2], expr[3]))
    {
    
    }*/
    
    explicit Quaternion(const Matrix4& matrix);
  
  
  
  public:
    
    bool operator==(const Quaternion& other) const;
    bool operator!=(const Quaternion& other) const;
    
    
    float& operator[](int index);
    float operator[](int index)const;
    
    Quaternion operator+(const Quaternion& other)const;
    Quaternion operator-(const Quaternion& other)const;
    
    Quaternion operator*(const Quaternion& other)const;
    Quaternion operator*(float scalar)const;
    
    Quaternion operator/(const Quaternion& other)const;
    Quaternion operator/(float scalar)const;
    
    Quaternion operator-() const;
    void operator+=(const Quaternion &other);
    void operator-=(const Quaternion &other);
    void operator*=(const Quaternion &other);
    void operator/=(const Quaternion &other);
    
    void operator*=(float scalar);
    void operator/=(float scalar);
    
    
  
  public:
    [[nodiscard]] float Magnitude() const;
    [[nodiscard]] float SqrMagnitude() const;
    void SetFromToRotation(const Vector3& fromDirection, const Vector3& toDirection);
    void SetLookRotation(const Vector3& view, const Vector3& up = Vector3::up);
    void ToAngleAxis(float& angle, Vector3& axis);
    [[nodiscard]] Quaternion Conjugate() const;
    [[nodiscard]] Vector3 ToEuler()const;
    void Normalize();
    [[nodiscard]] Quaternion Normalized() const;
    
    
  };
  
  //Quaternion operator*(float scalar, const Quaternion& quat);
}

template<>
struct fmt::formatter<Candy::Math::Quaternion> {
  constexpr auto parse(format_parse_context& ctx) {
    return ctx.begin();
  }
  
  template <typename FormatContext>
  auto format(const Candy::Math::Quaternion& vec, FormatContext& ctx) {
    return format_to(ctx.out(), "({0}, {1}, {2}, {3})", vec.x, vec.y, vec.z, vec.w);
  }
};