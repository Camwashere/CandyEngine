#pragma once

#include "ColorBase.hpp"
#include "ColorBaseStaticData.hpp"
#include "candy/math/Vector.hpp"
#include "candy/math/Quaternion.hpp"
namespace Candy {
  
  template<typename T>
  struct ColorBase<T, 4> : public Math::VectorBase<T, 4>, public ColorBaseStaticData<T, 4>{
  public:
    
    
    using Math::VectorBase<T, 4>::r;
    using Math::VectorBase<T, 4>::g;
    using Math::VectorBase<T, 4>::b;
    using Math::VectorBase<T, 4>::a;
  
  public:
    static ColorBase Lerp(const ColorBase& left, const ColorBase& right, T t);
    static ColorBase LerpClamped(const ColorBase &a, const ColorBase &b, T t);
    static ColorBase InverseLerp(const ColorBase &a, const ColorBase &b, T t);
    static ColorBase Max(const ColorBase &a, const ColorBase &b);
    static ColorBase Min(const ColorBase &a, const ColorBase &b);
    static ColorBase Average(const ColorBase &a, const ColorBase &b);
    static ColorBase Normalize(const ColorBase &vec);
    static ColorBase Grey(T shade);
  
  
  
  
  public:
    ColorBase();
    explicit ColorBase(T value);
    ColorBase(T redValue, T greenValue, T blueValue, T alphaValue = 1.0f) : Math::VectorBase<T, 4>(redValue, greenValue, blueValue, alphaValue){}
    ColorBase(const ColorBase &other);
    //explicit ColorBase(const T* data);
    explicit ColorBase(const Math::VectorBase<T, 2>& vector);
    explicit ColorBase(const Math::VectorBase<T, 3>& vector);
    explicit ColorBase(const Math::VectorBase<T, 4>& vector);
    
    
    template<typename E>
    ColorBase(const Math::VectorExpression<T, E> &expr);
  
  
  public:
    
    using Math::VectorBase<T, 4>::operator==;
    using Math::VectorBase<T, 4>::operator!=;
    using Math::VectorBase<T, 4>::operator+=;
    using Math::VectorBase<T, 4>::operator-=;
    using Math::VectorBase<T, 4>::operator*=;
    using Math::VectorBase<T, 4>::operator/=;
    
    
    //bool operator==(const ColorBase<T, 4>& other)const;
    bool operator==(const ColorBase<T, 4>& other)const;
    
    explicit operator Math::VectorBase<T, 2>()const;
    explicit operator Math::VectorBase<T, 3>()const;
    
  
  public:
    void Invert();
    [[nodiscard]] T Grayscale() const;
  
  public:
    [[nodiscard]] T MaxComponent()const;
    [[nodiscard]] ColorBase Inverted()const;
    [[nodiscard]] ColorBase ReversedRGB()const;
    [[nodiscard]] ColorBase ReversedRGBA()const;
  
  public:
    [[nodiscard]] Math::VectorBase<T, 2> ToVector2()const;
    [[nodiscard]] Math::VectorBase<T, 3> ToVector3()const;
    [[nodiscard]] Math::VectorBase<T, 4> ToVector4()const;
    
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

#include "ColorRGBA.inl"