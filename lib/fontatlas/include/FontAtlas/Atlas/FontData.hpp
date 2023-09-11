#pragma once
#include <cstdint>
#include <string>
namespace msdf_atlas
{
  typedef uint32_t unicode_t;
  struct FontMetrics {
    /// The size of one EM.
    float emSize;
    /// The vertical position of the ascender and descender relative to the baseline.
    float ascenderY, descenderY;
    /// The vertical difference between consecutive baselines.
    float lineHeight;
    /// The vertical position and thickness of the underline.
    float underlineY, underlineThickness;
  };

/// A structure to model a given axis of a variable font.
  struct FontVariationAxis {
    /// The name of the variation axis.
    const char *name;
    /// The axis's minimum coordinate value.
    float minValue;
    /// The axis's maximum coordinate value.
    float maxValue;
    /// The axis's default coordinate value. FreeType computes meaningful default values for Adobe MM fonts.
    float defaultValue;
  };
  
  class GlyphIndex
  {
  
  private:
    unsigned index;
  
  public:
    explicit GlyphIndex(unsigned index = 0);
    [[nodiscard]] unsigned GetIndex() const;
    
  };
  
  class FontHandle;
  
  
}