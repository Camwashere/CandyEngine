#pragma once

#include "ColorForwardDef.hpp"
#include "../../../include/Candy/Math.hpp"
namespace Candy {
    struct ColorHSV : public ColorBase<ColorFormat::HSV>, public Math::VectorBase<float, 4>{
        
        float h, s, v, a;
        
        ColorHSV();
        ColorHSV(float hue, float saturation, float value, float alpha);
        
    };
}


