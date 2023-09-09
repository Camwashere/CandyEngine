
#pragma once

#include "msdfVec2.hpp"
#include "Projection.hpp"
#include "Shape.hpp"
#include "BitmapRef.hpp"
#include "GeneratorConfig.hpp"

namespace msdfgen {

/// Predicts potential artifacts caused by the interpolation of the MSDF and corrects them by converting nearby texels to single-channel.
  void msdfErrorCorrection(const BitmapRef<float, 3> &sdf, const Shape &shape, const Projection &projection, float range, const MSDFGeneratorConfig &config = MSDFGeneratorConfig());
  void msdfErrorCorrection(const BitmapRef<float, 4> &sdf, const Shape &shape, const Projection &projection, float range, const MSDFGeneratorConfig &config = MSDFGeneratorConfig());

/// Applies the simplified error correction to all discontiunous distances (INDISCRIMINATE mode). Does not need shape or translation.
  void msdfFastDistanceErrorCorrection(const BitmapRef<float, 3> &sdf, const Projection &projection, float range, float minDeviationRatio = ErrorCorrectionConfig::defaultMinDeviationRatio);
  void msdfFastDistanceErrorCorrection(const BitmapRef<float, 4> &sdf, const Projection &projection, float range, float minDeviationRatio = ErrorCorrectionConfig::defaultMinDeviationRatio);

/// Applies the simplified error correction to edges only (EDGE_ONLY mode). Does not need shape or translation.
  void msdfFastEdgeErrorCorrection(const BitmapRef<float, 3> &sdf, const Projection &projection, float range, float minDeviationRatio = ErrorCorrectionConfig::defaultMinDeviationRatio);
  void msdfFastEdgeErrorCorrection(const BitmapRef<float, 4> &sdf, const Projection &projection, float range, float minDeviationRatio = ErrorCorrectionConfig::defaultMinDeviationRatio);

/// The original version of the error correction algorithm.
  void msdfErrorCorrection_legacy(const BitmapRef<float, 3> &output, const msdfVec2 &threshold);
  void msdfErrorCorrection_legacy(const BitmapRef<float, 4> &output, const msdfVec2 &threshold);
  
}
