#pragma once
#include "ColorBase.hpp"
#include <candy/math/Vector.hpp>

namespace Candy {
  template<>
  struct ColorBase<ColorLayout::RGBA, ColorDataType::UNSIGNED_BYTE> : public Math::VectorBase<std::uint8_t, 4> {
  private:
    static std::uint8_t ClampValue(std::uint8_t value);
    
    static ColorBase CLAMP(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a);
  
  public:
    static constexpr std::uint32_t RED_SHIFT = 0;
    static constexpr std::uint32_t GREEN_SHIFT = 8;
    static constexpr std::uint32_t BLUE_SHIFT =16;
    static constexpr std::uint32_t ALPHA_SHIFT=24;
    static constexpr std::uint32_t ALPHA_MASK=0xFF000000;
  
  public:
    ColorBase();
    
    ColorBase(std::uint8_t redValue, std::uint8_t greenValue, std::uint8_t blueValue, std::uint8_t alphaValue = 255);
    
    ColorBase(const ColorBase &other);
    
    template<typename E>
    ColorBase(const VectorExpression<std::uint8_t, E> &expr) : VectorBase<std::uint8_t, 4>(expr) {}
  
  
  public:
    using Math::Vector4ub::operator==;
    using Math::Vector4ub::operator[];
    using Math::Vector4ub::operator!=;
    using Math::Vector4ub::operator+=;
    using Math::Vector4ub::operator-=;
    using Math::Vector4ub::operator*=;
    using Math::Vector4ub::operator/=;
    
    
    
    
  

    
  };
}




