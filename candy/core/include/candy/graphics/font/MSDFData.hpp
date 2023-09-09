#pragma once
#include <vector>
#include <FontAtlas/msdf-atlas-gen.hpp>
#include "FontAtlas/Atlas/FontGeometry.hpp"
#include "FontAtlas/Atlas/GlyphGeometry.hpp"
namespace Candy::Graphics
{
  struct MSDFData
  {
    std::vector<msdf_atlas::GlyphGeometry> glyphs;
    msdf_atlas::FontGeometry fontGeometry;
  };
}