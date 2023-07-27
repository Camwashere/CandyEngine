#include <candy/graphics/color/ColorRGBA.hpp>


namespace Candy {
  using namespace Math;
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::ColorBase() : Math::VectorBase<float, 4>() {}
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::ColorBase(const ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> &other) = default;
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::ColorBase(float value) : Math::VectorBase<float, 4>(value){}
  //ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::ColorBase(const float *data) : VectorBase<float, 4>(data) {}
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::ColorBase(const Math::Vector2 &vector) : VectorBase<float, 4>(vector.x, vector.y, 0, 1){}
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::ColorBase(const Math::Vector3 &vector) : VectorBase<float, 4>(vector.x, vector.y, vector.z, 1) {}
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::ColorBase(const Math::Vector4 &vector) : VectorBase<float, 4>(vector) {}
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::ColorBase(const Math::Quaternion &quaternion) : VectorBase<float, 4>(quaternion.x, quaternion.y, quaternion.z, quaternion.w) {}
  
  const ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::red(1, 0, 0);
  const ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::green(0, 1, 0);
  const ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::blue(0, 0, 1);
  const ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::black(0.0f, 0.0f, 0.0f, 1.0f);
  const ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::white(1, 1, 1);
  const ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::grey(0.5f, 0.5f, 0.5f);
  const ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::clear(0, 0, 0, 0);
  
  const ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::teal(0, 1, 1);
  const ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::magenta(1, 0, 1);
  const ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::yellow(1.0f, 0.92f, 0.016);
  const ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::orange(1.0f, 0.647f, 0.0f);
  const ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::purple(0.627f, 0.125f, 0.941f);
  const ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::brown(0.588f, 0.294f, 0.0f);
  const ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::coral(1.0f, 0.5f, 0.31f);
  
  
  
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::operator Math::Vector2()const{return ToVector2();}
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::operator Math::Vector3()const{return ToVector3();}
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::operator Math::Quaternion()const{return ToQuaternion();}
  
  
  
  Math::Vector2 ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::ToVector2()const
  {
    return {r, g};
  }
  Math::Vector3 ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::ToVector3()const
  {
    return {r, g, b};
  }
  Math::Vector4 ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::ToVector4()const
  {
    return {r, g, b, a};
  }
  Math::Quaternion ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::ToQuaternion() const
  {
    return {r, g, b, a};
  }
  
  std::string ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::ToString()const
  {
    return std::string("Color(") + std::to_string(r) + ", " + std::to_string(g) + ", " + std::to_string(b) + ", " + std::to_string(a) + ")";
  }
  
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::Lerp(const ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> &left, const ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> &right, float t) {
    float oneMinusT = 1 - t;
    return {left.r * oneMinusT + right.r * t, left.g * oneMinusT + right.g * t, left.b * oneMinusT + right.b, left.a * oneMinusT + right.a};
  }
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::LerpClamped(const ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> &a, const ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> &b, float t) {
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
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::InverseLerp(const ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> &a, const ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> &b, float t) {
    return {(t - a.x) / (b.x - a.x), (t - a.y) / (b.y - a.y), (t - a.z) / (b.z - a.z), (t - a.w) / (b.w - a.w)};
  }
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::Max(const ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> &a, const ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> &b) {
    return {Math::Max(a.r, b.r), Math::Max(a.g, b.g), Math::Max(a.b, b.b), Math::Max(a.a, b.a)};
  }
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::Min(const ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> &a, const ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> &b) {
    return {Math::Min(a.r, b.r), Math::Min(a.g, b.g), Math::Min(a.b, b.b), Math::Min(a.a, b.a)};
  }
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::Average(const ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> &a, const ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> &b) {
    return (a+b)/2.0f;
  }
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::Normalize(const ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> &vec) {
    return vec.Normalized();
  }
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::Grey(float shade)
  {
    return {shade, shade, shade, 1.0f};
  }
  
  
  
  
  
  
  bool ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::operator==(const ColorBase& other)const
  {
    return r==other.r && g==other.g && b==other.b && a==other.a;
  }
  
  void ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::Invert() {r = 1.0f-r; g=1.0f-g; b=1.0f-b;}
  
  float ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::MaxComponent() const {return Math::Max(r, g, b, a);}
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::Inverted() const {return {1.0f-r, 1.0f-g, 1.0f-b};}
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::ReversedRGB() const {return {b, g, r, a};}
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::ReversedRGBA() const {return {a, b, g, r};}
  
  
  float Saturate(float f){ return (f < 0.0f) ? 0.0f : (f > 1.0f) ? 1.0f : f; }
  
  float ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::Grayscale() const { return (0.299f * r) + (0.587f * g) + (0.114f * b); }
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::rr() const {
    return {r, r, 0, a};
  }
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::rg() const {
    return {r, g, 0, a};
  }
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::rb() const {
    return {r, b, 0, a};
  }
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::gr() const {
    return {g, r, 0, a};
  }
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::gg() const {
    return {g, g, 0, a};
  }
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::gb() const {
    return {g, b, 0, a};
  }
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::br() const {
    return {b, r, 0, a};
  }
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::bg() const {
    return {b, g, 0, a};
  }
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::bb() const {
    return {b, b, 0, a};
  }
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::rrr() const {
    return {r, r, r, a};
  }
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::rrg() const {
    return {r, r, g, a};
  }
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::rrb() const {
    return {r, r, b, a};
  }
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::rgr() const {
    return {r, g, r, a};
  }
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::rgg() const {
    return {r, g, g, a};
  }
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::rgb() const {
    return {r, g, b, a};
  }
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::rbr() const {
    return {r, b, r, a};
  }
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::rbg() const {
    return {r, b, g, a};
  }
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::rbb() const {
    return {r, b, b, a};
  }
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::grr() const {
    return {g, r, r, a};
  }
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::grg() const {
    return {g, r, g, a};
  }
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::grb() const {
    return {g, r, b, a};
  }
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::ggr() const {
    return {g, g, r, a};
  }
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::ggg() const {
    return {g, g, g, a};
  }
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::ggb() const {
    return {g, g, b, a};
  }
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::gbr() const {
    return {g, b, r, a};
  }
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::gbg() const {
    return {g, b, g, a};
  }
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::gbb() const {
    return {g, b, b, a};
  }
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::brr() const {
    return {b, r, r, a};
  }
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::brg() const {
    return {b, r, g, a};
  }
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::brb() const {
    return {b, r, b, a};
  }
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::bgr() const {
    return {b, g, r, a};
  }
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::bgg() const {
    return {b, g, g, a};
  }
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::bgb() const {
    return {b, g, b, a};
  }
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::bbr() const {
    return {b, b, r, a};
  }
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::bbg() const {
    return {b, b, g, a};
  }
  
  ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT>::bbb() const {
    return {b, b, b, a};
  }
  
}



