
#pragma once

#include "msdfVec2.hpp"
#include "Shape.hpp"
#include "Projection.hpp"
#include "Scanline.hpp"
#include "BitmapRef.hpp"

namespace msdfgen {

/// Rasterizes the shape into a monochrome bitmap.
  void rasterize(const BitmapRef<float, 1> &output, const Shape &shape, const Projection &projection, FillRule fillRule = FILL_NONZERO);
/// Fixes the sign of the input signed distance field, so that it matches the shape's rasterized fill.
  void distanceSignCorrection(const BitmapRef<float, 1> &sdf, const Shape &shape, const Projection &projection, FillRule fillRule = FILL_NONZERO);
  void distanceSignCorrection(const BitmapRef<float, 3> &sdf, const Shape &shape, const Projection &projection, FillRule fillRule = FILL_NONZERO);
  void distanceSignCorrection(const BitmapRef<float, 4> &sdf, const Shape &shape, const Projection &projection, FillRule fillRule = FILL_NONZERO);

// Old version of the function API's kept for backwards compatibility
  void rasterize(const BitmapRef<float, 1> &output, const Shape &shape, const msdfVec2 &scale, const msdfVec2 &translate, FillRule fillRule = FILL_NONZERO);
  void distanceSignCorrection(const BitmapRef<float, 1> &sdf, const Shape &shape, const msdfVec2 &scale, const msdfVec2 &translate, FillRule fillRule = FILL_NONZERO);
  void distanceSignCorrection(const BitmapRef<float, 3> &sdf, const Shape &shape, const msdfVec2 &scale, const msdfVec2 &translate, FillRule fillRule = FILL_NONZERO);
  void distanceSignCorrection(const BitmapRef<float, 4> &sdf, const Shape &shape, const msdfVec2 &scale, const msdfVec2 &translate, FillRule fillRule = FILL_NONZERO);
  
}
