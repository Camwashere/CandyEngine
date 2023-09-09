
#pragma once

#include "Rectangle.hpp"

namespace msdf_atlas {

/// The glyph box - its bounds in plane and atlas
struct GlyphBox {
    int index;
    float advance;
    struct {
        float l, b, r, t;
    } bounds;
    Rectangle rect;

};

}
