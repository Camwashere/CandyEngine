#pragma once
#include "color/ColorRGBA.hpp"
#include "color/ColorRGBA8.hpp"
namespace Candy {
    typedef ColorBase<ColorLayout::RGBA, ColorDataType::FLOAT> Color;
    typedef ColorBase<ColorLayout::RGBA, ColorDataType::UNSIGNED_BYTE> Color32u;
  
}

