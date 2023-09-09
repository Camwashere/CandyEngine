
#pragma once

#include "FontAtlas/msdfgen.hpp"

#include "atlas-gen-types.hpp"
#include "FontGeometry.hpp"

namespace msdf_atlas {

/// Generates a Shadron script that displays a string using the generated atlas
bool generateShadronPreview(const FontGeometry *fonts, int fontCount, ImageType atlasType, int atlasWidth, int atlasHeight, float pxRange, const unicode_t *text, const char *imageFilename, bool fullRange, const char *outputFilename);

}
