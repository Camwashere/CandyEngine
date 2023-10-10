#pragma once
#include <candy/base/Base.hpp>
#include <candy/math/vector/VectorBase.hpp>
namespace Candy
{
    enum class ColorLayout : uint8_t
    {
        NONE = 0,
        RGBA,
        RGB,
        HSV,
        HSL,
        CMYK,
        YIQ,
       
    };
    enum class ColorDataType : uint8_t
    {
      NONE=0,
      FLOAT,
      DOUBLE,
      BYTE,
      UNSIGNED_BYTE,
    };
    
    
    enum class ColorChannels
    {
      NONE=-1,
      R=BIT(0),
      G=BIT(1),
      B=BIT(2),
      A=BIT(3),
      
      RED=R,
      GREEN=G,
      BLUE=B,
      ALPHA=A,
      
      ALL=R|G|B|A,
      RGBA=ALL,
      
      
    };
    
    template<typename T, uint8_t CHANNELS>
    struct ColorBase : public Math::VectorBase<T, CHANNELS>
    {
      T data[CHANNELS];
    
    };
    
}