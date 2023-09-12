#pragma once

namespace Candy
{
  
  template<typename T> ColorBase<T, 4>::ColorBase() : Math::VectorBase<T, 4>(1, 1, 1, 1) {}
  template<typename T> ColorBase<T, 4>::ColorBase(const ColorBase<T, 4> &other) : Math::VectorBase<T, 4>(other.r, other.g, other.b, other.a){};
  template<typename T> ColorBase<T, 4>::ColorBase(T value) : Math::VectorBase<T, 4>(value){}
  template<typename T> ColorBase<T, 4>::ColorBase(const Math::VectorBase<T, 2> &vector) : Math::VectorBase<T, 4>(vector.x, vector.y, 0, 1){}
  template<typename T> ColorBase<T, 4>::ColorBase(const Math::VectorBase<T, 3> &vector) : Math::VectorBase<T, 4>(vector.x, vector.y, vector.z, 1) {}
  template<typename T> ColorBase<T, 4>::ColorBase(const Math::VectorBase<T, 4> &vector) : Math::VectorBase<T, 4>(vector) {}
  template<typename T> ColorBase<T, 4>::ColorBase(const Math::QuaternionBase<T> &quaternion) : Math::VectorBase<T, 4>(quaternion.x, quaternion.y, quaternion.z, quaternion.w) {}
  
  
  
  template<typename T>
  template<typename E>
  ColorBase<T, 4>::ColorBase(const Math::VectorExpression<T, E> &expr) : Math::VectorBase<T, 4>(expr) {}
  
  template<typename T>
  ColorBase<T, 4>::operator Math::VectorBase<T, 2>()const{return ToVector2();}
  template<typename T>
  ColorBase<T, 4>::operator Math::VectorBase<T, 3>()const{return ToVector3();}
  template<typename T>
  ColorBase<T, 4>::operator Math::QuaternionBase<T>()const{return ToQuaternion();}
  
  
  template<typename T>
  Math::VectorBase<T, 2> ColorBase<T, 4>::ToVector2()const
  {
    return {r, g};
  }
  template<typename T>
  Math::VectorBase<T, 3> ColorBase<T, 4>::ToVector3()const
  {
    return {r, g, b};
  }
  template<typename T>
  Math::VectorBase<T, 4> ColorBase<T, 4>::ToVector4()const
  {
    return {r, g, b, a};
  }
  template<typename T>
  Math::QuaternionBase<T> ColorBase<T, 4>::ToQuaternion() const
  {
    return {r, g, b, a};
  }
  
  
  template<typename T>
  ColorBase<T, 4> ColorBase<T, 4>::Lerp(const ColorBase<T, 4> &left, const ColorBase<T, 4> &right, T t) {
    float oneMinusT = 1 - t;
    return {left.r * oneMinusT + right.r * t, left.g * oneMinusT + right.g * t, left.b * oneMinusT + right.b, left.a * oneMinusT + right.a};
  }
  template<typename T>
  ColorBase<T, 4> ColorBase<T, 4>::LerpClamped(const ColorBase<T, 4> &a, const ColorBase<T, 4> &b, T t) {
    if (t < 0) {
      return a;
    }
    if (t > 1) {
      return b;
    }
    float oneMinusT = 1 - t;
    return {a.x * oneMinusT + b.x * t, a.y * oneMinusT + b.y * t, a.z * oneMinusT + b.z * t,
            a.w * oneMinusT + b.w * t};
  }
  template<typename T>
  ColorBase<T, 4> ColorBase<T, 4>::InverseLerp(const ColorBase<T, 4> &a, const ColorBase<T, 4> &b, T t) {
    return {(t - a.x) / (b.x - a.x), (t - a.y) / (b.y - a.y), (t - a.z) / (b.z - a.z), (t - a.w) / (b.w - a.w)};
  }
  template<typename T>
  ColorBase<T, 4> ColorBase<T, 4>::Max(const ColorBase<T, 4> &a, const ColorBase<T, 4> &b) {
    return {Math::Max(a.r, b.r), Math::Max(a.g, b.g), Math::Max(a.b, b.b), Math::Max(a.a, b.a)};
  }
  template<typename T>
  ColorBase<T, 4> ColorBase<T, 4>::Min(const ColorBase<T, 4> &a, const ColorBase<T, 4> &b) {
    return {Math::Min(a.r, b.r), Math::Min(a.g, b.g), Math::Min(a.b, b.b), Math::Min(a.a, b.a)};
  }
  template<typename T>
  ColorBase<T, 4> ColorBase<T, 4>::Average(const ColorBase<T, 4> &a, const ColorBase<T, 4> &b) {
    return (a+b)/2.0f;
  }
  template<typename T>
  ColorBase<T, 4> ColorBase<T, 4>::Normalize(const ColorBase<T, 4> &vec) {
    return vec.Normalized();
  }
  template<typename T>
  ColorBase<T, 4> ColorBase<T, 4>::Grey(T shade)
  {
    return {shade, shade, shade, 1};
  }
  
  
  
  
  
  template<typename T>
  bool ColorBase<T, 4>::operator==(const ColorBase<T, 4>& other)const
  {
    return r==other.r && g==other.g && b==other.b && a==other.a;
  }
  template<typename T>
  void ColorBase<T, 4>::Invert() {r = 1.0f-r; g=1.0f-g; b=1.0f-b;}
  
  template<typename T>
  T ColorBase<T, 4>::MaxComponent() const {return Math::Max(r, g, b, a);}
  
  template<typename T>
  ColorBase<T, 4> ColorBase<T, 4>::Inverted() const {return {1.0f-r, 1.0f-g, 1.0f-b};}
  
  template<typename T>
  ColorBase<T, 4> ColorBase<T, 4>::ReversedRGB() const {return {b, g, r, a};}
  
  template<typename T>
  ColorBase<T, 4> ColorBase<T, 4>::ReversedRGBA() const {return {a, b, g, r};}
  
  template<typename T>
  T Saturate(T f){ return (f < 0.0f) ? 0.0f : (f > 1.0f) ? 1.0f : f; }
  
  template<typename T>
  T ColorBase<T, 4>::Grayscale() const { return (0.299f * r) + (0.587f * g) + (0.114f * b); }
  
  template<typename T>
  ColorBase<T, 4> ColorBase<T, 4>::rr() const {
    return {r, r, 0, a};
  }
  
  template<typename T> ColorBase<T, 4> ColorBase<T, 4>::rg() const {
    return {r, g, 0, a};
  }
  
  template<typename T> ColorBase<T, 4> ColorBase<T, 4>::rb() const {
    return {r, b, 0, a};
  }
  
  template<typename T> ColorBase<T, 4> ColorBase<T, 4>::gr() const {
    return {g, r, 0, a};
  }
  
  template<typename T> ColorBase<T, 4> ColorBase<T, 4>::gg() const {
    return {g, g, 0, a};
  }
  
  template<typename T> ColorBase<T, 4> ColorBase<T, 4>::gb() const {
    return {g, b, 0, a};
  }
  
  template<typename T> ColorBase<T, 4> ColorBase<T, 4>::br() const {
    return {b, r, 0, a};
  }
  
  template<typename T> ColorBase<T, 4> ColorBase<T, 4>::bg() const {
    return {b, g, 0, a};
  }
  
  template<typename T> ColorBase<T, 4> ColorBase<T, 4>::bb() const {
    return {b, b, 0, a};
  }
  
  template<typename T> ColorBase<T, 4> ColorBase<T, 4>::rrr() const {
    return {r, r, r, a};
  }
  
  template<typename T> ColorBase<T, 4> ColorBase<T, 4>::rrg() const {
    return {r, r, g, a};
  }
  
  template<typename T> ColorBase<T, 4> ColorBase<T, 4>::rrb() const {
    return {r, r, b, a};
  }
  
  template<typename T> ColorBase<T, 4> ColorBase<T, 4>::rgr() const {
    return {r, g, r, a};
  }
  
  template<typename T> ColorBase<T, 4> ColorBase<T, 4>::rgg() const {
    return {r, g, g, a};
  }
  
  template<typename T> ColorBase<T, 4> ColorBase<T, 4>::rgb() const {
    return {r, g, b, a};
  }
  
  template<typename T> ColorBase<T, 4> ColorBase<T, 4>::rbr() const {
    return {r, b, r, a};
  }
  
  template<typename T> ColorBase<T, 4> ColorBase<T, 4>::rbg() const {
    return {r, b, g, a};
  }
  
  template<typename T> ColorBase<T, 4> ColorBase<T, 4>::rbb() const {
    return {r, b, b, a};
  }
  
  template<typename T> ColorBase<T, 4> ColorBase<T, 4>::grr() const {
    return {g, r, r, a};
  }
  
  template<typename T> ColorBase<T, 4> ColorBase<T, 4>::grg() const {
    return {g, r, g, a};
  }
  
  template<typename T> ColorBase<T, 4> ColorBase<T, 4>::grb() const {
    return {g, r, b, a};
  }
  
  template<typename T> ColorBase<T, 4> ColorBase<T, 4>::ggr() const {
    return {g, g, r, a};
  }
  
  template<typename T> ColorBase<T, 4> ColorBase<T, 4>::ggg() const {
    return {g, g, g, a};
  }
  
  template<typename T> ColorBase<T, 4> ColorBase<T, 4>::ggb() const {
    return {g, g, b, a};
  }
  
  template<typename T> ColorBase<T, 4> ColorBase<T, 4>::gbr() const {
    return {g, b, r, a};
  }
  
  template<typename T> ColorBase<T, 4> ColorBase<T, 4>::gbg() const {
    return {g, b, g, a};
  }
  
  template<typename T> ColorBase<T, 4> ColorBase<T, 4>::gbb() const {
    return {g, b, b, a};
  }
  
  template<typename T> ColorBase<T, 4> ColorBase<T, 4>::brr() const {
    return {b, r, r, a};
  }
  
  template<typename T> ColorBase<T, 4> ColorBase<T, 4>::brg() const {
    return {b, r, g, a};
  }
  
  template<typename T> ColorBase<T, 4> ColorBase<T, 4>::brb() const {
    return {b, r, b, a};
  }
  
  template<typename T> ColorBase<T, 4> ColorBase<T, 4>::bgr() const {
    return {b, g, r, a};
  }
  
  template<typename T> ColorBase<T, 4> ColorBase<T, 4>::bgg() const {
    return {b, g, g, a};
  }
  
  template<typename T> ColorBase<T, 4> ColorBase<T, 4>::bgb() const {
    return {b, g, b, a};
  }
  
  template<typename T> ColorBase<T, 4> ColorBase<T, 4>::bbr() const {
    return {b, b, r, a};
  }
  
  template<typename T> ColorBase<T, 4> ColorBase<T, 4>::bbg() const {
    return {b, b, g, a};
  }
  
  template<typename T> ColorBase<T, 4> ColorBase<T, 4>::bbb() const {
    return {b, b, b, a};
  }
}