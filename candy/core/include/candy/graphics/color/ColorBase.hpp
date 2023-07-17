#pragma once

namespace Candy {
    struct Color;
    struct Color32;
    struct ColorHSV;
    struct ColorHSL;
    struct ColorCMYK;
    struct ColorYIQ;
}
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
        NONE,
    };
    
    
    template<ColorFormat COLOR_FORMAT>
    class ColorBase
    {
    
    public:
        [[nodiscard]] constexpr ColorFormat GetFormat()const{return COLOR_FORMAT;}
        
    };
    
    
}