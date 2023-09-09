#pragma once

/*
 * MULTI-CHANNEL SIGNED DISTANCE FIELD GENERATOR
 * ---------------------------------------------
 * A utility by Viktor Chlumsky, (c) 2014 - 2023
 *
 * The technique used to generate multi-channel distance fields in this code
 * has been developed by Viktor Chlumsky in 2014 for his master's thesis,
 * "Shape Decomposition for Multi-Channel Distance Fields". It provides improved
 * quality of sharp corners in glyphs and other 2D shapes compared to monochrome
 * distance fields. To reconstruct an image of the shape, apply the median of three
 * operation on the triplet of sampled signed distance values.
 *
 */

#include "Field/Arithmetics.hpp"
#include "Field/msdfVec2.hpp"
#include "Field/Projection.hpp"
#include "Field/Scanline.hpp"
#include "Field/Shape.hpp"
#include "Field/BitmapRef.hpp"
#include "Field/Bitmap.hpp"
#include "Field/BitmapInterpolation.hpp"
#include "Field/PixelConversion.hpp"
#include "Field/EdgeColoring.hpp"
#include "Field/GeneratorConfig.hpp"
#include "Field/msdf-error-correction.hpp"
#include "Field/RenderSdf.hpp"
#include "Field/Rasterization.hpp"
#include "Field/sdf-error-estimation.hpp"
#include "Field/save-bmp.hpp"
#include "Field/save-tiff.hpp"
#include "Field/ShapeDescription.hpp"

namespace msdfgen {

/// Generates a conventional single-channel signed distance field.
  void generateSDF(const BitmapRef<float, 1> &output, const Shape &shape, const Projection &projection, float range, const GeneratorConfig &config = GeneratorConfig());

/// Generates a single-channel signed pseudo-distance field.
  void generatePseudoSDF(const BitmapRef<float, 1> &output, const Shape &shape, const Projection &projection, float range, const GeneratorConfig &config = GeneratorConfig());

/// Generates a multi-channel signed distance field. Edge colors must be assigned first! (See edgeColoringSimple)
  void generateMSDF(const BitmapRef<float, 3> &output, const Shape &shape, const Projection &projection, float range, const MSDFGeneratorConfig &config = MSDFGeneratorConfig());

/// Generates a multi-channel signed distance field with true distance in the alpha channel. Edge colors must be assigned first.
  void generateMTSDF(const BitmapRef<float, 4> &output, const Shape &shape, const Projection &projection, float range, const MSDFGeneratorConfig &config = MSDFGeneratorConfig());

// Old version of the function API's kept for backwards compatibility
  void generateSDF(const BitmapRef<float, 1> &output, const Shape &shape, float range, const msdfVec2 &scale, const msdfVec2 &translate, bool overlapSupport = true);
  void generatePseudoSDF(const BitmapRef<float, 1> &output, const Shape &shape, float range, const msdfVec2 &scale, const msdfVec2 &translate, bool overlapSupport = true);
  void generateMSDF(const BitmapRef<float, 3> &output, const Shape &shape, float range, const msdfVec2 &scale, const msdfVec2 &translate, const ErrorCorrectionConfig &errorCorrectionConfig = ErrorCorrectionConfig(), bool overlapSupport = true);
  void generateMTSDF(const BitmapRef<float, 4> &output, const Shape &shape, float range, const msdfVec2 &scale, const msdfVec2 &translate, const ErrorCorrectionConfig &errorCorrectionConfig = ErrorCorrectionConfig(), bool overlapSupport = true);

// Original simpler versions of the previous functions, which work well under normal circumstances, but cannot deal with overlapping contours.
  void generateSDF_legacy(const BitmapRef<float, 1> &output, const Shape &shape, float range, const msdfVec2 &scale, const msdfVec2 &translate);
  void generatePseudoSDF_legacy(const BitmapRef<float, 1> &output, const Shape &shape, float range, const msdfVec2 &scale, const msdfVec2 &translate);
  void generateMSDF_legacy(const BitmapRef<float, 3> &output, const Shape &shape, float range, const msdfVec2 &scale, const msdfVec2 &translate, ErrorCorrectionConfig errorCorrectionConfig = ErrorCorrectionConfig());
  void generateMTSDF_legacy(const BitmapRef<float, 4> &output, const Shape &shape, float range, const msdfVec2 &scale, const msdfVec2 &translate, ErrorCorrectionConfig errorCorrectionConfig = ErrorCorrectionConfig());
  
}
