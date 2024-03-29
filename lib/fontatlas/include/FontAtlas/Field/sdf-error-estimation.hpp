
#pragma once

#include "msdfVec2.hpp"
#include "Shape.hpp"
#include "Projection.hpp"
#include "Scanline.hpp"
#include "BitmapRef.hpp"

namespace msdfgen {

/// Analytically constructs a scanline at y evaluating fill by linear interpolation of the SDF.
  void scanlineSDF(Scanline &line, const BitmapConstRef<float, 1> &sdf, const Projection &projection, float y, bool inverseYAxis = false);
  void scanlineSDF(Scanline &line, const BitmapConstRef<float, 3> &sdf, const Projection &projection, float y, bool inverseYAxis = false);
  void scanlineSDF(Scanline &line, const BitmapConstRef<float, 4> &sdf, const Projection &projection, float y, bool inverseYAxis = false);

/// Estimates the portion of the area that will be filled incorrectly when rendering using the SDF.
  float estimateSDFError(const BitmapConstRef<float, 1> &sdf, const Shape &shape, const Projection &projection, int scanlinesPerRow, FillRule fillRule = FILL_NONZERO);
  float estimateSDFError(const BitmapConstRef<float, 3> &sdf, const Shape &shape, const Projection &projection, int scanlinesPerRow, FillRule fillRule = FILL_NONZERO);
  float estimateSDFError(const BitmapConstRef<float, 4> &sdf, const Shape &shape, const Projection &projection, int scanlinesPerRow, FillRule fillRule = FILL_NONZERO);

// Old version of the function API's kept for backwards compatibility
  void scanlineSDF(Scanline &line, const BitmapConstRef<float, 1> &sdf, const msdfVec2 &scale, const msdfVec2 &translate, bool inverseYAxis, float y);
  void scanlineSDF(Scanline &line, const BitmapConstRef<float, 3> &sdf, const msdfVec2 &scale, const msdfVec2 &translate, bool inverseYAxis, float y);
  void scanlineSDF(Scanline &line, const BitmapConstRef<float, 4> &sdf, const msdfVec2 &scale, const msdfVec2 &translate, bool inverseYAxis, float y);
  float estimateSDFError(const BitmapConstRef<float, 1> &sdf, const Shape &shape, const msdfVec2 &scale, const msdfVec2 &translate, int scanlinesPerRow, FillRule fillRule = FILL_NONZERO);
  float estimateSDFError(const BitmapConstRef<float, 3> &sdf, const Shape &shape, const msdfVec2 &scale, const msdfVec2 &translate, int scanlinesPerRow, FillRule fillRule = FILL_NONZERO);
  float estimateSDFError(const BitmapConstRef<float, 4> &sdf, const Shape &shape, const msdfVec2 &scale, const msdfVec2 &translate, int scanlinesPerRow, FillRule fillRule = FILL_NONZERO);
  
}
