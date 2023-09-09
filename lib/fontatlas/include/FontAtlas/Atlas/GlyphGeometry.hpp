
#pragma once

#include "FontAtlas/msdfgen.hpp"
#include "FontData.hpp"
#include "atlas-gen-types.hpp"
#include "Rectangle.hpp"
#include "GlyphBox.hpp"

namespace msdf_atlas {

/// Represents the shape geometry of a single glyph as well as its configuration
class GlyphGeometry {

public:
    GlyphGeometry();
    /// Loads glyph geometry from font
    bool load(FontHandle *font, float geometryScale, GlyphIndex index, bool preprocessGeometry = true);
    bool load(FontHandle *font, float geometryScale, unicode_t codepoint, bool preprocessGeometry = true);
    /// Applies edge coloring to glyph shape
    void edgeColoring(void (*fn)(msdfgen::Shape &, float, unsigned long long), float angleThreshold, unsigned long long seed);
    /// Computes the dimensions of the glyph's box as well as the transformation for the generator function
    void wrapBox(float scale, float range, float miterLimit);
    /// Sets the glyph's box's position in the atlas
    void placeBox(int x, int y);
    /// Sets the glyph's box's rectangle in the atlas
    void setBoxRect(const Rectangle &rect);
    /// Returns the glyph's index within the font
    int getIndex() const;
    /// Returns the glyph's index as a msdfgen::GlyphIndex
    GlyphIndex getGlyphIndex() const;
    /// Returns the Unicode codepoint represented by the glyph or 0 if unknown
    unicode_t getCodepoint() const;
    /// Returns the glyph's identifier specified by the supplied identifier type
    int getIdentifier(GlyphIdentifierType type) const;
    /// Returns the glyph's shape
    const msdfgen::Shape & getShape() const;
    /// Returns the glyph's advance
    float getAdvance() const;
    /// Returns the glyph's box in the atlas
    Rectangle getBoxRect() const;
    /// Outputs the position and dimensions of the glyph's box in the atlas
    void getBoxRect(int &x, int &y, int &w, int &h) const;
    /// Outputs the dimensions of the glyph's box in the atlas
    void getBoxSize(int &w, int &h) const;
    /// Returns the range needed to generate the glyph's SDF
    float getBoxRange() const;
    /// Returns the projection needed to generate the glyph's bitmap
    msdfgen::Projection getBoxProjection() const;
    /// Returns the scale needed to generate the glyph's bitmap
    float getBoxScale() const;
    /// Returns the translation vector needed to generate the glyph's bitmap
    msdfgen::msdfVec2 getBoxTranslate() const;
    /// Outputs the bounding box of the glyph as it should be placed on the baseline
    void getQuadPlaneBounds(float &l, float &b, float &r, float &t) const;
    /// Outputs the bounding box of the glyph in the atlas
    void getQuadAtlasBounds(float &l, float &b, float &r, float &t) const;
    /// Returns true if the glyph is a whitespace and has no geometry
    bool isWhitespace() const;
    /// Simplifies to GlyphBox
    operator GlyphBox() const;

private:
    int index;
    unicode_t codepoint;
    float geometryScale;
    msdfgen::Shape shape;
    msdfgen::Shape::Bounds bounds;
    float advance;
    struct {
        Rectangle rect;
        float range;
        float scale;
        msdfgen::msdfVec2 translate;
    } box;

};

}
