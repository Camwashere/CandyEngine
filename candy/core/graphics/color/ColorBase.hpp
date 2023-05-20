#pragma once

namespace Candy
{
    enum ColorFormat
    {
        RGB=0,
        RGB32,
        HSV,
        HSL,
        CMYK,
        YIQ,
    };
    
    template<ColorFormat COLOR_TYPE>
    struct ColorBase
    {
        constexpr ColorFormat GetColorType()const{return COLOR_TYPE;}
        
    };

    
} // candy


