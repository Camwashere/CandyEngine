
#include "FontAtlas/Atlas/GlyphGeometry.hpp"

#include <cmath>
#include "FontAtlas/Field/ShapeDistanceFinder.hpp"
#include "FontAtlas/Atlas/FontAtlasLoader.hpp"

namespace msdf_atlas {

GlyphGeometry::GlyphGeometry() : index(), codepoint(), geometryScale(), bounds(), advance(), box() { }

bool GlyphGeometry::load(FontHandle *font, float geometryScale, GlyphIndex index, bool preprocessGeometry) {
    if (font && FontAtlasLoader::LoadGlyph(shape, font, index, &advance) && shape.validate()) {
        this->index = index.GetIndex();
        this->geometryScale = geometryScale;
        codepoint = 0;
        advance *= geometryScale;
        #ifdef MSDFGEN_USE_SKIA
            if (preprocessGeometry)
                msdfgen::resolveShapeGeometry(shape);
        #endif
        shape.normalize();
        bounds = shape.getBounds();
        #ifdef MSDFGEN_USE_SKIA
            if (!preprocessGeometry)
        #endif
        {
            // Determine if shape is winded incorrectly and reverse it in that case
            msdfgen::Point2 outerPoint(bounds.l-(bounds.r-bounds.l)-1, bounds.b-(bounds.t-bounds.b)-1);
            if (msdfgen::SimpleTrueShapeDistanceFinder::oneShotDistance(shape, outerPoint) > 0) {
                for (msdfgen::Contour &contour : shape.contours)
                    contour.Reverse();
            }
        }
        return true;
    }
    return false;
}

bool GlyphGeometry::load(FontHandle *font, float geometryScale, unicode_t codepoint, bool preprocessGeometry) {
    GlyphIndex index;
    if (FontAtlasLoader::GetGlyphIndex(index, font, codepoint)) {
        if (load(font, geometryScale, index, preprocessGeometry)) {
            this->codepoint = codepoint;
            return true;
        }
    }
    return false;
}

void GlyphGeometry::edgeColoring(void (*fn)(msdfgen::Shape &, float, unsigned long long), float angleThreshold, unsigned long long seed) {
    fn(shape, angleThreshold, seed);
}

void GlyphGeometry::wrapBox(float scale, float range, float miterLimit) {
    scale *= geometryScale;
    range /= geometryScale;
    box.range = range;
    box.scale = scale;
    if (bounds.l < bounds.r && bounds.b < bounds.t) {
        float l = bounds.l, b = bounds.b, r = bounds.r, t = bounds.t;
        l -= .5f*range, b -= .5f*range;
        r += .5f*range, t += .5f*range;
        if (miterLimit > 0)
            shape.boundMiters(l, b, r, t, .5*range, miterLimit, 1);
        float w = scale*(r-l);
        float h = scale*(t-b);
        box.rect.w = (int) ceil(w)+1;
        box.rect.h = (int) ceil(h)+1;
        box.translate.x = -l+.5f*(box.rect.w-w)/scale;
        box.translate.y = -b+.5f*(box.rect.h-h)/scale;
    } else {
        box.rect.w = 0, box.rect.h = 0;
        box.translate = msdfgen::msdfVec2();
    }
}

void GlyphGeometry::placeBox(int x, int y) {
    box.rect.x = x, box.rect.y = y;
}

void GlyphGeometry::setBoxRect(const Rectangle &rect) {
    box.rect = rect;
}

int GlyphGeometry::getIndex() const {
    return index;
}

GlyphIndex GlyphGeometry::getGlyphIndex() const {
    return GlyphIndex(index);
}

unicode_t GlyphGeometry::getCodepoint() const {
    return codepoint;
}

int GlyphGeometry::getIdentifier(GlyphIdentifierType type) const {
    switch (type) {
        case GlyphIdentifierType::GLYPH_INDEX:
            return index;
        case GlyphIdentifierType::UNICODE_CODEPOINT:
            return (int) codepoint;
    }
    return 0;
}

const msdfgen::Shape & GlyphGeometry::getShape() const {
    return shape;
}

float GlyphGeometry::getAdvance() const {
    return advance;
}

Rectangle GlyphGeometry::getBoxRect() const {
    return box.rect;
}

void GlyphGeometry::getBoxRect(int &x, int &y, int &w, int &h) const {
    x = box.rect.x, y = box.rect.y;
    w = box.rect.w, h = box.rect.h;
}

void GlyphGeometry::getBoxSize(int &w, int &h) const {
    w = box.rect.w, h = box.rect.h;
}

float GlyphGeometry::getBoxRange() const {
    return box.range;
}

msdfgen::Projection GlyphGeometry::getBoxProjection() const {
    return msdfgen::Projection(msdfgen::msdfVec2(box.scale), box.translate);
}

float GlyphGeometry::getBoxScale() const {
    return box.scale;
}
  float GlyphGeometry::getGeometryScale()const
  {
  return geometryScale;
  }
msdfgen::msdfVec2 GlyphGeometry::getBoxTranslate() const {
    return box.translate;
}

void GlyphGeometry::getQuadPlaneBounds(float &l, float &b, float &r, float &t) const {
    if (box.rect.w > 0 && box.rect.h > 0) {
        float invBoxScale = 1/box.scale;
        l = geometryScale*(-box.translate.x+.5f*invBoxScale);
        b = geometryScale*(-box.translate.y+.5f*invBoxScale);
        r = geometryScale*(-box.translate.x+(box.rect.w-.5f)*invBoxScale);
        t = geometryScale*(-box.translate.y+(box.rect.h-.5f)*invBoxScale);
    } else
        l = 0, b = 0, r = 0, t = 0;
}

void GlyphGeometry::getQuadAtlasBounds(float &l, float &b, float &r, float &t) const {
    if (box.rect.w > 0 && box.rect.h > 0) {
        l = box.rect.x+.5f;
        b = box.rect.y+.5f;
        r = box.rect.x+box.rect.w-.5f;
        t = box.rect.y+box.rect.h-.5f;
    } else
        l = 0, b = 0, r = 0, t = 0;
}

bool GlyphGeometry::isWhitespace() const {
    return shape.contours.empty();
}

GlyphGeometry::operator GlyphBox() const {
    GlyphBox box{};
    box.index = index;
    box.advance = advance;
    getQuadPlaneBounds(box.bounds.l, box.bounds.b, box.bounds.r, box.bounds.t);
    box.rect.x = this->box.rect.x, box.rect.y = this->box.rect.y, box.rect.w = this->box.rect.w, box.rect.h = this->box.rect.h;
    return box;
}

}
