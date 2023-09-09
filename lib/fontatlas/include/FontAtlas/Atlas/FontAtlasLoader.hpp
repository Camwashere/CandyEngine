#pragma once

#include <cstdint>
#include "FontAtlas/Field/BitmapRef.hpp"
#include "FontAtlas/Field/Shape.hpp"
#include "FontData.hpp"

namespace msdf_atlas
{
  struct FontAtlasLoader
  {
    
    
    enum SvgImportFlags
    {
      FAILURE = 0,
      SUCCESS = 1<<1,
      PARTIAL_FAILURE = 1<<2,
      INCOMPLETE = 1<<3,
      UNSUPPORTED_FEATURE = 1<<4,
      TRANSFORMATION_IGNORED = 1<<5
    };
    
    static bool Init();
    static bool Shutdown();
    
    static bool SavePng(const msdfgen::BitmapConstRef<uint8_t, 1> &bitmap, const char *filename);
    static bool SavePng(const msdfgen::BitmapConstRef<uint8_t, 3> &bitmap, const char *filename);
    static bool SavePng(const msdfgen::BitmapConstRef<uint8_t, 4> &bitmap, const char *filename);
    static bool SavePng(const msdfgen::BitmapConstRef<float, 1> &bitmap, const char *filename);
    static bool SavePng(const msdfgen::BitmapConstRef<float, 3> &bitmap, const char *filename);
    static bool SavePng(const msdfgen::BitmapConstRef<float, 4> &bitmap, const char *filename);
    /// Builds a shape from an SVG path string
    static bool BuildShapeFromSvgPath(msdfgen::Shape &shape, const char *pathDef, float endpointSnapRange = 0);
    
    /// Reads a single <path> element found in the specified SVG file and converts it to output Shape
    static bool LoadSvgShape(msdfgen::Shape &output, const char *filename, int pathIndex = 0, msdfgen::msdfVec2 *dimensions = nullptr);
    
    /// New version - if Skia is available, reads the entire geometry of the SVG file into the output Shape, otherwise may only read one path, returns SVG import flags
    static int LoadSvgShape(msdfgen::Shape &output, msdfgen::Shape::Bounds &viewBox, const char *filename);




    /// Loads a font file and returns its handle.
    static FontHandle *LoadFont(const char *filename);
    /// Loads a font from binary data and returns its handle.
    static FontHandle *LoadFontData(const uint8_t *data, int length);
    /// Unloads a font file.
    static void DestroyFont(FontHandle *font);
    /// Outputs the metrics of a font file.
    static bool GetFontMetrics(FontMetrics &metrics, FontHandle *font);
    /// Outputs the width of the space and tab characters.
    static bool GetFontWhitespaceWidth(float &spaceAdvance, float &tabAdvance, FontHandle *font);
    /// Outputs the glyph index corresponding to the specified Unicode character.
    static bool GetGlyphIndex(GlyphIndex &glyphIndex, FontHandle *font, unicode_t unicode);
    /// Loads the geometry of a glyph from a font file.
    static bool LoadGlyph(msdfgen::Shape &output, FontHandle *font, GlyphIndex glyphIndex, float *advance = NULL);
    static bool LoadGlyph(msdfgen::Shape &output, FontHandle *font, unicode_t unicode, float *advance = NULL);
    /// Outputs the kerning distance adjustment between two specific glyphs.
    static bool GetKerning(float &output, FontHandle *font, GlyphIndex glyphIndex1, GlyphIndex glyphIndex2);
    static bool GetKerning(float &output, FontHandle *font, unicode_t unicode1, unicode_t unicode2);


    /// Sets a single variation axis of a variable font.
    static bool SetFontVariationAxis(FontHandle *font, const char *name, float coordinate);
    /// Lists names and ranges of variation axes of a variable font.
    static bool ListFontVariationAxes(std::vector<FontVariationAxis> &axes, FontHandle *font);
    
    /// Resolves any intersections within the shape by subdividing its contours using the Skia library and makes sure its contours have a consistent winding.
    //static bool ResolveShapeGeometry(msdfgen::Shape &shape);
  };
  
  #ifdef FT_LOAD_DEFAULT // FreeType included    /// Creates a FontHandle from FT_Face that was loaded by the user. destroyFont must still be called but will not affect the FT_Face.
  static FontHandle *AdoptFreetypeFont(FT_Face ftFace);
    /// Converts the geometry of FreeType's FT_Outline to a Shape object.
    static FT_Error ReadFreetypeOutline(msdfgen::Shape &output, FT_Outline *outline);
  #endif
}