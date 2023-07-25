#pragma once

#include "ColorBase.hpp"
#include "candy/math/Vector.hpp"
#include "candy/math/Quaternion.hpp"
namespace Candy {
  template<>
  struct ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> : public Math::VectorBase<float, 4>{
  public:
    static const ColorBase red;
    static const ColorBase green;
    static const ColorBase blue;
    static const ColorBase black;
    static const ColorBase white;
    static const ColorBase grey;
    static const ColorBase clear;
    
    static const ColorBase teal;
    static const ColorBase magenta;
    static const ColorBase yellow;
    static const ColorBase orange;
    static const ColorBase purple;
    static const ColorBase brown;
    static const ColorBase coral;
  
  public:
    static ColorBase Lerp(const ColorBase& left, const ColorBase& right, float t);
    static ColorBase LerpClamped(const ColorBase &a, const ColorBase &b, float t);
    static ColorBase InverseLerp(const ColorBase &a, const ColorBase &b, float t);
    static ColorBase Max(const ColorBase &a, const ColorBase &b);
    static ColorBase Min(const ColorBase &a, const ColorBase &b);
    static ColorBase Average(const ColorBase &a, const ColorBase &b);
    static ColorBase Normalize(const ColorBase &vec);
    static ColorBase Grey(float shade);
  
  
  
  
  public:
    ColorBase();
    explicit ColorBase(float value);
    ColorBase(float redValue, float greenValue, float blueValue, float alphaValue = 1.0f) : Math::VectorBase<float, 4>(redValue, greenValue, blueValue, alphaValue){}
    ColorBase(const ColorBase &other);
    //explicit ColorBase(const float* data);
    explicit ColorBase(const std::string& hex);
    explicit ColorBase(const Math::Vector2& vector);
    explicit ColorBase(const Math::Vector3& vector);
    explicit ColorBase(const Math::Vector4& vector);
    explicit ColorBase(const Math::Quaternion& quaternion);
    
    template<typename E>
    ColorBase(const VectorExpression<float, E> &expr) : VectorBase<float, 4>(expr) {}
  
  
  public:
    
    using VectorBase<float, 4>::operator==;
    using VectorBase<float, 4>::operator!=;
    using VectorBase<float, 4>::operator+=;
    using VectorBase<float, 4>::operator-=;
    using VectorBase<float, 4>::operator*=;
    using VectorBase<float, 4>::operator/=;
    
    
    
    
    
    explicit operator Math::Vector2()const;
    explicit operator Math::Vector3()const;
    explicit operator Math::Quaternion()const;
  
  public:
    void Invert();
    [[nodiscard]] float Grayscale() const;
  
  public:
    [[nodiscard]] float MaxComponent()const;
    [[nodiscard]] ColorBase Inverted()const;
    [[nodiscard]] ColorBase ReversedRGB()const;
    [[nodiscard]] ColorBase ReversedRGBA()const;
  
  public:
    [[nodiscard]] Math::Vector2 ToVector2()const;
    [[nodiscard]] Math::Vector3 ToVector3()const;
    [[nodiscard]] Math::Vector4 ToVector4()const;
    [[nodiscard]] Math::Quaternion ToQuaternion()const;
    [[nodiscard]] std::string ToString()const;
    [[nodiscard]] ColorBase rr() const;
    [[nodiscard]] ColorBase rg() const;
    [[nodiscard]] ColorBase rb() const;
    [[nodiscard]] ColorBase gr() const;
    [[nodiscard]] ColorBase gg() const;
    [[nodiscard]] ColorBase gb() const;
    [[nodiscard]] ColorBase br() const;
    [[nodiscard]] ColorBase bg() const;
    [[nodiscard]] ColorBase bb() const;
    [[nodiscard]] ColorBase rrr() const;
    [[nodiscard]] ColorBase rrg() const;
    [[nodiscard]] ColorBase rrb() const;
    [[nodiscard]] ColorBase rgr() const;
    [[nodiscard]] ColorBase rgg() const;
    [[nodiscard]] ColorBase rgb() const;
    [[nodiscard]] ColorBase rbr() const;
    [[nodiscard]] ColorBase rbg() const;
    [[nodiscard]] ColorBase rbb() const;
    [[nodiscard]] ColorBase grr() const;
    [[nodiscard]] ColorBase grg() const;
    [[nodiscard]] ColorBase grb() const;
    [[nodiscard]] ColorBase ggr() const;
    [[nodiscard]] ColorBase ggg() const;
    [[nodiscard]] ColorBase ggb() const;
    [[nodiscard]] ColorBase gbr() const;
    [[nodiscard]] ColorBase gbg() const;
    [[nodiscard]] ColorBase gbb() const;
    [[nodiscard]] ColorBase brr() const;
    [[nodiscard]] ColorBase brg() const;
    [[nodiscard]] ColorBase brb() const;
    [[nodiscard]] ColorBase bgr() const;
    [[nodiscard]] ColorBase bgg() const;
    [[nodiscard]] ColorBase bgb() const;
    [[nodiscard]] ColorBase bbr() const;
    [[nodiscard]] ColorBase bbg() const;
    [[nodiscard]] ColorBase bbb() const;
    
    
  };
}

