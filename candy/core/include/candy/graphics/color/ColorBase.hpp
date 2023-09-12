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
    
    
    
    /*template<ColorLayout COLOR_FORMAT, ColorDataType COLOR_DATA_TYPE>
    class ColorBase
    {
    
    public:
        [[nodiscard]] ColorLayout GetLayout()const{return COLOR_FORMAT;}
        [[nodiscard]] ColorDataType GetDataType()const{return COLOR_DATA_TYPE;}
        
    };*/
    
    template<typename T, uint8_t CHANNELS>
    struct ColorBase : public Math::VectorBase<T, CHANNELS>
    {
      T data[CHANNELS];
    
    };
    
}