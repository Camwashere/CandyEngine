#pragma once

#include "ColorForwardDef.hpp"
#include "../../../include/Candy/Math.hpp"
namespace Candy{
    struct ColorHSL : public ColorBase<ColorFormat::HSL>, public Math::VectorBase<float, 4>
    {
        float h, s, l, a;
        
        ColorHSL();
        ColorHSL(float hue, float saturation, float lightness, float alpha=1.0);
    };
}
