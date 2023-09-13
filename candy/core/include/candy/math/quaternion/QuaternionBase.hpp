#pragma once
#include "../vector/Vector4Base.hpp"
#include "../Matrix.hpp"
#include "../MathOps.hpp"
namespace Candy::Math
{
  template<typename T>
  struct QuaternionBase : public VectorBase<T, 4>
  {
  public:
    
    static QuaternionBase<T> Normalize(const QuaternionBase<T>& a);
    static T Angle(const QuaternionBase<T>& a, const QuaternionBase<T>& b);
    static QuaternionBase<T> AngleAxis(T angle, const VectorBase<T, 3>& axis);
    static QuaternionBase<T> Euler(T x, T y, T z);
    static QuaternionBase<T> Euler(const VectorBase<T, 3>& euler);
    static QuaternionBase<T> FromToRotation(const VectorBase<T, 3>& fromDirection, const VectorBase<T, 3>& toDirection);
    static QuaternionBase<T> Inverse(const QuaternionBase<T>& rotation);
    static QuaternionBase<T> Lerp(const QuaternionBase<T>& a, const QuaternionBase<T>& b, T t);
    static QuaternionBase<T> LerpUnclamped(const QuaternionBase<T>& a, const QuaternionBase<T>& b, T t);
    static QuaternionBase<T> LookRotation(const VectorBase<T, 3>& forward, const VectorBase<T, 3>& upwards = VectorBase<T, 3>::up);
    static QuaternionBase<T> Normalized(const QuaternionBase<T>& a);
    static QuaternionBase<T> RotateTowards(const QuaternionBase<T>& from, const QuaternionBase<T>& to, T maxDegreesDelta);
    static QuaternionBase<T> Slerp(const QuaternionBase<T>& a, const QuaternionBase<T>& b, T t);
    static QuaternionBase<T> SlerpUnclamped(const QuaternionBase<T>& a, const QuaternionBase<T>& b, T t);
    static QuaternionBase<T> ToRadians(const QuaternionBase<T>& quat);
    static QuaternionBase<T> ToDegrees(const QuaternionBase<T>& quat);
    static VectorBase<T, 3> Rotate(const QuaternionBase<T>& rotation, const VectorBase<T, 3>& point);
    static AbstractMatrixBase<T, 4, 4> ToMatrix(const QuaternionBase<T>& quaternion);
    
    using VectorBase<T, 4>::x;
    using VectorBase<T, 4>::y;
    using VectorBase<T, 4>::z;
    using VectorBase<T, 4>::w;
    using VectorBase<T, 4>::data;
  
  public:
    QuaternionBase();
    QuaternionBase(T x, T y, T z, T w);
    QuaternionBase(const VectorBase<T, 3>& axis, T angle);
    explicit QuaternionBase(const VectorBase<T, 4>& vec);
    QuaternionBase(const QuaternionBase<T>& other);
    
    template <typename E>
    constexpr QuaternionBase(const VectorExpression<T, E>& expr); //NOLINT
    
    QuaternionBase(const AbstractMatrixBase<T, 4, 4, LayoutPolicyTopToBottom>& matrix);
  
  
  
  public:
    QuaternionBase<T> operator*(const QuaternionBase<T>& other)const;
    QuaternionBase<T> operator*(T scalar)const;
    using VectorBase<T, 4>::operator[];
    using VectorBase<T, 4>::operator==;
    using VectorBase<T, 4>::operator!=;
    using VectorBase<T, 4>::operator-;
  
  public:
    void SetFromToRotation(const VectorBase<T, 3>& fromDirection, const VectorBase<T, 3>& toDirection);
    void SetLookRotation(const VectorBase<T, 3>& view, const VectorBase<T, 3>& up = VectorBase<T, 3>::up);
    void ToAngleAxis(T& angle, VectorBase<T, 3>& axis);
    QuaternionBase<T> Conjugate() const;
    VectorBase<T, 3> ToEuler()const;
    
    [[nodiscard]] QuaternionBase<T> Normalized() const; //NOLINT
    
    
  };
  
}

template <typename T>
struct fmt::formatter<Candy::Math::QuaternionBase<T>> {
  constexpr auto parse(format_parse_context& ctx) {
    return ctx.begin();
  }
  
  template <typename FormatContext>
  auto format(const Candy::Math::QuaternionBase<T>& vec, FormatContext& ctx) {
    return format_to(ctx.out(), "({0}, {1}, {2}, {3})", vec.x, vec.y, vec.z, vec.w);
  }
};
#include "QuaternionBase.inl"