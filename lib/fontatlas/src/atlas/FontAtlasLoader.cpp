#include "FontAtlas/Atlas/FontAtlasLoader.hpp"



#include "tinyxml2.h"
#include <png.h>


#include "ft2build.h"
#include FT_FREETYPE_H"freetype/freetype.h"
#include FT_OUTLINE_H"freetype/ftoutln.h"
#include FT_MULTIPLE_MASTERS_H"freetype/ftmm.h"
#include "FontAtlas/Field/msdfVec2.hpp"
#include "FontAtlas/Field/Shape.hpp"
#include "FontAtlas/Field/BitmapRef.hpp"
#include "FontAtlas/Field/Arithmetics.hpp"
#include "FontAtlas/Field/PixelConversion.hpp"



namespace msdf_atlas
{
  
  using namespace msdfgen;
  
  
  struct GlobalFontData
  {
    FT_Library library;
  };
  
  static GlobalFontData globalData{};
  
  bool FontAtlasLoader::Init()
  {
    FT_Error result = FT_Init_FreeType(&globalData.library);
    if (result)
    {
      return false;
    }
    return true;
    
  }
  
  bool FontAtlasLoader::Shutdown()
  {
    FT_Error result = FT_Done_FreeType(globalData.library);
    if (result)
    {
      return false;
    }
    return true;
    
  }
  
  
  
  ///*** PNG ***///
  class PngGuard {
    png_structp png;
    png_infop info;
    FILE *file;
  
  public:
    inline PngGuard(png_structp png, png_infop info) : png(png), info(info), file(NULL) { }
    inline ~PngGuard() {
      png_destroy_write_struct(&png, &info);
      fclose(file);
    }
    inline void setFile(FILE *file) {
      this->file = file;
    }
    
  };
  
  static void pngIgnoreError(png_structp, png_const_charp) { }
  
  static void pngWrite(png_structp png, png_bytep data, png_size_t length) {
    if (fwrite(data, 1, length, reinterpret_cast<FILE *>(png_get_io_ptr(png))) != length)
      png_error(png, "File write error");
  }
  
  static void pngFlush(png_structp png) {
    fflush(reinterpret_cast<FILE *>(png_get_io_ptr(png)));
  }
  
  static bool pngSave(const byte *pixels, int width, int height, int channels, int colorType, const char *filename) {
    if (!(pixels && width && height))
      return false;
    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, &pngIgnoreError, &pngIgnoreError);
    if (!png)
      return false;
    png_infop info = png_create_info_struct(png);
    PngGuard guard(png, info);
    if (!info)
      return false;
    FILE *file = fopen(filename, "wb");
    if (!file)
      return false;
    guard.setFile(file);
    
    std::vector<const byte *> rows(height);
    for (int y = 0; y < height; ++y)
      rows[y] = pixels+channels*width*(height-y-1);
    if (setjmp(png_jmpbuf(png)))
      return false;
    png_set_write_fn(png, file, &pngWrite, &pngFlush);
    
    png_set_IHDR(png, info, width, height, 8, colorType, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_set_compression_level(png, 9);
    png_set_rows(png, info, const_cast<png_bytepp>(&rows[0]));
    
    png_write_png(png, info, PNG_TRANSFORM_IDENTITY, nullptr);
    return true;
  }
  
  static bool pngSave(const float *pixels, int width, int height, int channels, int colorType, const char *filename) {
    if (!(pixels && width && height))
      return false;
    int subpixels = channels*width*height;
    std::vector<byte> bytePixels(subpixels);
    for (int i = 0; i < subpixels; ++i)
      bytePixels[i] = pixelFloatToByte(pixels[i]);
    return pngSave(&bytePixels[0], width, height, channels, colorType, filename);
  }
  
  bool FontAtlasLoader::SavePng(const BitmapConstRef<uint8_t, 1> &bitmap, const char *filename)
  {
    return pngSave(bitmap.pixels, bitmap.width, bitmap.height, 1, PNG_COLOR_TYPE_GRAY, filename);
  }
  
  bool FontAtlasLoader::SavePng(const BitmapConstRef<uint8_t, 3> &bitmap, const char *filename)
  {
    return pngSave(bitmap.pixels, bitmap.width, bitmap.height, 3, PNG_COLOR_TYPE_RGB, filename);
  }
  
  bool FontAtlasLoader::SavePng(const BitmapConstRef<uint8_t, 4> &bitmap, const char *filename)
  {
    return pngSave(bitmap.pixels, bitmap.width, bitmap.height, 4, PNG_COLOR_TYPE_RGB_ALPHA, filename);
  }
  
  bool FontAtlasLoader::SavePng(const BitmapConstRef<float, 1> &bitmap, const char *filename)
  {
    return pngSave(bitmap.pixels, bitmap.width, bitmap.height, 1, PNG_COLOR_TYPE_GRAY, filename);
  }
  
  bool FontAtlasLoader::SavePng(const BitmapConstRef<float, 3> &bitmap, const char *filename)
  {
    return pngSave(bitmap.pixels, bitmap.width, bitmap.height, 3, PNG_COLOR_TYPE_RGB, filename);
  }
  
  bool FontAtlasLoader::SavePng(const BitmapConstRef<float, 4> &bitmap, const char *filename)
  {
    return pngSave(bitmap.pixels, bitmap.width, bitmap.height, 4, PNG_COLOR_TYPE_RGB_ALPHA, filename);
  }
  
  
  ///*** SVG ***///
  
  constexpr auto ARC_SEGMENTS_PER_PI=2;
  constexpr auto ENDPOINT_SNAP_RANGE_PROPORTION=(1/16384.f);
  
  #if defined(_DEBUG) || !NDEBUG
#define REQUIRE(cond) { if (!(cond)) { fprintf(stderr, "SVG Parse Error (%s:%d): " #cond "\n", __FILE__, __LINE__); return false; } }
  #else
#define REQUIRE(cond) { if (!(cond)) return false; }
  #endif
  static void skipExtraChars(const char *&pathDef) {
    while (*pathDef == ',' || *pathDef == ' ' || *pathDef == '\t' || *pathDef == '\r' || *pathDef == '\n')
      ++pathDef;
  }
  
  static bool readNodeType(char &output, const char *&pathDef) {
    skipExtraChars(pathDef);
    char nodeType = *pathDef;
    if (nodeType && nodeType != '+' && nodeType != '-' && nodeType != '.' && nodeType != ',' && (nodeType < '0' || nodeType > '9')) {
      ++pathDef;
      output = nodeType;
      return true;
    }
    return false;
  }
  
  static bool readCoord(Point2 &output, const char *&pathDef) {
    skipExtraChars(pathDef);
    int shift;
    float x, y;
    if (sscanf(pathDef, "%lf%lf%n", &x, &y, &shift) == 2 || sscanf(pathDef, "%lf , %lf%n", &x, &y, &shift) == 2) {
      output.x = x;
      output.y = y;
      pathDef += shift;
      return true;
    }
    return false;
  }
  
  /*static bool readDouble(float &output, const char *&pathDef) {
    skipExtraChars(pathDef);
    int shift;
    float v;
    if (sscanf(pathDef, "%lf%n", &v, &shift) == 1) {
      pathDef += shift;
      output = v;
      return true;
    }
    return false;
  }*/
  
  static bool readFloat(float &output, const char *&pathDef) {
    skipExtraChars(pathDef);
    int shift;
    float v;
    if (sscanf(pathDef, "%f%n", &v, &shift) == 1) {
      pathDef += shift;
      output = v;
      return true;
    }
    return false;
  }
  
  static bool readBool(bool &output, const char *&pathDef) {
    skipExtraChars(pathDef);
    int shift;
    int v;
    if (sscanf(pathDef, "%d%n", &v, &shift) == 1) {
      pathDef += shift;
      output = v != 0;
      return true;
    }
    return false;
  }
  
  static float arcAngle(msdfVec2 u, msdfVec2 v) {
    return nonZeroSign(crossProduct(u, v))*acos(clamp(dotProduct(u, v)/(u.length()*v.length()), -1.f, +1.f));
  }
  
  static msdfVec2 rotateVector(msdfVec2 v, msdfVec2 direction) {
    return msdfVec2(direction.x*v.x-direction.y*v.y, direction.y*v.x+direction.x*v.y);
  }
  
  static void addArcApproximate(Contour &contour, Point2 startPoint, Point2 endPoint, msdfVec2 radius, float rotation, bool largeArc, bool sweep) {
    if (endPoint == startPoint)
      return;
    if (radius.x == 0 || radius.y == 0)
      return contour.AddEdge(new LinearSegment(startPoint, endPoint));
    
    radius.x = fabs(radius.x);
    radius.y = fabs(radius.y);
    msdfVec2 axis(cos(rotation), sin(rotation));
    
    msdfVec2 rm = rotateVector(.5*(startPoint-endPoint), msdfVec2(axis.x, -axis.y));
    msdfVec2 rm2 = rm*rm;
    msdfVec2 radius2 = radius*radius;
    float radiusGap = rm2.x/radius2.x+rm2.y/radius2.y;
    if (radiusGap > 1) {
      radius *= sqrt(radiusGap);
      radius2 = radius*radius;
    }
    float dq = (radius2.x*rm2.y+radius2.y*rm2.x);
    float pq = radius2.x*radius2.y/dq-1;
    float q = (largeArc == sweep ? -1.f : +1.f)*std::sqrt(max(pq, 0.f));
    msdfVec2 rc(q*radius.x*rm.y/radius.y, -q*radius.y*rm.x/radius.x);
    Point2 center = .5*(startPoint+endPoint)+rotateVector(rc, axis);
    
    float angleStart = arcAngle(msdfVec2(1, 0), (rm-rc)/radius);
    float angleExtent = arcAngle((rm-rc)/radius, (-rm-rc)/radius);
    if (!sweep && angleExtent > 0)
      angleExtent -= 2*M_PI;
    else if (sweep && angleExtent < 0)
      angleExtent += 2*M_PI;
    
    int segments = (int) ceil(ARC_SEGMENTS_PER_PI/M_PI*fabs(angleExtent));
    float angleIncrement = angleExtent/segments;
    float cl = 4/3.*sin(.5*angleIncrement)/(1+cos(.5*angleIncrement));
    
    Point2 prevNode = startPoint;
    float angle = angleStart;
    for (int i = 0; i < segments; ++i) {
      Point2 controlPoint[2];
      msdfVec2 d(cos(angle), sin(angle));
      controlPoint[0] = center+rotateVector(msdfVec2(d.x-cl*d.y, d.y+cl*d.x)*radius, axis);
      angle += angleIncrement;
      d.set(cos(angle), sin(angle));
      controlPoint[1] = center+rotateVector(msdfVec2(d.x+cl*d.y, d.y-cl*d.x)*radius, axis);
      Point2 node = i == segments-1 ? endPoint : center+rotateVector(d*radius, axis);
      contour.AddEdge(new CubicSegment(prevNode, controlPoint[0], controlPoint[1], node));
      prevNode = node;
    }
  }
  static constexpr bool FLAGS_FINAL(int flags)
  {
    return (flags & (FontAtlasLoader::SvgImportFlags::SUCCESS|FontAtlasLoader::SvgImportFlags::INCOMPLETE|FontAtlasLoader::SvgImportFlags::UNSUPPORTED_FEATURE)) == (FontAtlasLoader::SvgImportFlags::SUCCESS|FontAtlasLoader::SvgImportFlags::INCOMPLETE|FontAtlasLoader::SvgImportFlags::UNSUPPORTED_FEATURE);
    //(((flags)&(SVG_IMPORT_SUCCESS_FLAG|SVG_IMPORT_INCOMPLETE_FLAG|SVG_IMPORT_UNSUPPORTED_FEATURE_FLAG)) == (SVG_IMPORT_SUCCESS_FLAG|SVG_IMPORT_INCOMPLETE_FLAG|SVG_IMPORT_UNSUPPORTED_FEATURE_FLAG));
  }
  static void findPathByForwardIndex(tinyxml2::XMLElement *&path, int &flags, int &skips, tinyxml2::XMLElement *parent, bool hasTransformation) {
    for (tinyxml2::XMLElement *cur = parent->FirstChildElement(); cur && !FLAGS_FINAL(flags); cur = cur->NextSiblingElement()) {
      if (!strcmp(cur->Name(), "path")) {
        if (!skips--) {
          path = cur;
          flags |= FontAtlasLoader::SvgImportFlags::SUCCESS;
          if (hasTransformation || cur->Attribute("transform"))
            flags |= FontAtlasLoader::SvgImportFlags::TRANSFORMATION_IGNORED;
        } else if (flags&FontAtlasLoader::SvgImportFlags::SUCCESS)
          flags |= FontAtlasLoader::SvgImportFlags::INCOMPLETE;
      } else if (!strcmp(cur->Name(), "g"))
        findPathByForwardIndex(path, flags, skips, cur, hasTransformation || cur->Attribute("transform"));
      else if (!strcmp(cur->Name(), "rect") || !strcmp(cur->Name(), "circle") || !strcmp(cur->Name(), "ellipse") || !strcmp(cur->Name(), "polygon"))
        flags |= FontAtlasLoader::SvgImportFlags::INCOMPLETE;
      else if (!strcmp(cur->Name(), "mask") || !strcmp(cur->Name(), "use"))
        flags |= FontAtlasLoader::SvgImportFlags::UNSUPPORTED_FEATURE;
    }
  }
  
  static void findPathByBackwardIndex(tinyxml2::XMLElement *&path, int &flags, int &skips, tinyxml2::XMLElement *parent, bool hasTransformation) {
    for (tinyxml2::XMLElement *cur = parent->LastChildElement(); cur && !FLAGS_FINAL(flags); cur = cur->PreviousSiblingElement()) {
      if (!strcmp(cur->Name(), "path")) {
        if (!skips--) {
          path = cur;
          flags |= FontAtlasLoader::SvgImportFlags::SUCCESS;
          if (hasTransformation || cur->Attribute("transform"))
            flags |= FontAtlasLoader::SvgImportFlags::TRANSFORMATION_IGNORED;
        } else if (flags&FontAtlasLoader::SvgImportFlags::SUCCESS)
          flags |= FontAtlasLoader::SvgImportFlags::INCOMPLETE;
      } else if (!strcmp(cur->Name(), "g"))
        findPathByBackwardIndex(path, flags, skips, cur, hasTransformation || cur->Attribute("transform"));
      else if (!strcmp(cur->Name(), "rect") || !strcmp(cur->Name(), "circle") || !strcmp(cur->Name(), "ellipse") || !strcmp(cur->Name(), "polygon"))
        flags |= FontAtlasLoader::SvgImportFlags::INCOMPLETE;
      else if (!strcmp(cur->Name(), "mask") || !strcmp(cur->Name(), "use"))
        flags |= FontAtlasLoader::SvgImportFlags::UNSUPPORTED_FEATURE;
    }
  }
  bool FontAtlasLoader::BuildShapeFromSvgPath(Shape &shape, const char *pathDef, float endpointSnapRange)
  {
    char nodeType = '\0';
    char prevNodeType = '\0';
    Point2 prevNode(0, 0);
    bool nodeTypePreread = false;
    while (nodeTypePreread || readNodeType(nodeType, pathDef)) {
      nodeTypePreread = false;
      Contour &contour = shape.addContour();
      bool contourStart = true;
      
      Point2 startPoint;
      Point2 controlPoint[2];
      Point2 node;
      
      while (*pathDef) {
        switch (nodeType) {
          case 'M': case 'm':
            if (!contourStart) {
              nodeTypePreread = true;
              goto NEXT_CONTOUR;
            }
            REQUIRE(readCoord(node, pathDef));
            if (nodeType == 'm')
              node += prevNode;
            startPoint = node;
            --nodeType; // to 'L' or 'l'
            break;
          case 'Z': case 'z':
            REQUIRE(!contourStart);
            goto NEXT_CONTOUR;
          case 'L': case 'l':
            REQUIRE(readCoord(node, pathDef));
            if (nodeType == 'l')
              node += prevNode;
            contour.AddEdge(new LinearSegment(prevNode, node));
            break;
          case 'H': case 'h':
            REQUIRE(readFloat(node.x, pathDef));
            if (nodeType == 'h')
              node.x += prevNode.x;
            contour.AddEdge(new LinearSegment(prevNode, node));
            break;
          case 'V': case 'v':
            REQUIRE(readFloat(node.y, pathDef));
            if (nodeType == 'v')
              node.y += prevNode.y;
            contour.AddEdge(new LinearSegment(prevNode, node));
            break;
          case 'Q': case 'q':
            REQUIRE(readCoord(controlPoint[0], pathDef));
            REQUIRE(readCoord(node, pathDef));
            if (nodeType == 'q') {
              controlPoint[0] += prevNode;
              node += prevNode;
            }
            contour.AddEdge(new QuadraticSegment(prevNode, controlPoint[0], node));
            break;
          case 'T': case 't':
            if (prevNodeType == 'Q' || prevNodeType == 'q' || prevNodeType == 'T' || prevNodeType == 't')
              controlPoint[0] = node+node-controlPoint[0];
            else
              controlPoint[0] = node;
            REQUIRE(readCoord(node, pathDef));
            if (nodeType == 't')
              node += prevNode;
            contour.AddEdge(new QuadraticSegment(prevNode, controlPoint[0], node));
            break;
          case 'C': case 'c':
            REQUIRE(readCoord(controlPoint[0], pathDef));
            REQUIRE(readCoord(controlPoint[1], pathDef));
            REQUIRE(readCoord(node, pathDef));
            if (nodeType == 'c') {
              controlPoint[0] += prevNode;
              controlPoint[1] += prevNode;
              node += prevNode;
            }
            contour.AddEdge(new CubicSegment(prevNode, controlPoint[0], controlPoint[1], node));
            break;
          case 'S': case 's':
            if (prevNodeType == 'C' || prevNodeType == 'c' || prevNodeType == 'S' || prevNodeType == 's')
              controlPoint[0] = node+node-controlPoint[1];
            else
              controlPoint[0] = node;
            REQUIRE(readCoord(controlPoint[1], pathDef));
            REQUIRE(readCoord(node, pathDef));
            if (nodeType == 's') {
              controlPoint[1] += prevNode;
              node += prevNode;
            }
            contour.AddEdge(new CubicSegment(prevNode, controlPoint[0], controlPoint[1], node));
            break;
          case 'A': case 'a':
          {
            msdfVec2 radius;
            float angle;
            bool largeArg;
            bool sweep;
            REQUIRE(readCoord(radius, pathDef));
            REQUIRE(readFloat(angle, pathDef));
            REQUIRE(readBool(largeArg, pathDef));
            REQUIRE(readBool(sweep, pathDef));
            REQUIRE(readCoord(node, pathDef));
            if (nodeType == 'a')
              node += prevNode;
            angle *= M_PI/180.0;
            addArcApproximate(contour, prevNode, node, radius, angle, largeArg, sweep);
          }
            break;
          default:
            REQUIRE(!"Unknown node type");
        }
        contourStart &= nodeType == 'M' || nodeType == 'm';
        prevNode = node;
        prevNodeType = nodeType;
        readNodeType(nodeType, pathDef);
      }
      NEXT_CONTOUR:
      // Fix contour if it isn't properly closed
      if (!contour.edges.empty() && prevNode != startPoint) {
        if ((contour.edges.back()->point(1)-contour.edges[0]->point(0)).length() < endpointSnapRange)
          contour.edges.back()->moveEndPoint(contour.edges[0]->point(0));
        else
          contour.AddEdge(new LinearSegment(prevNode, startPoint));
      }
      prevNode = startPoint;
      prevNodeType = '\0';
    }
    return true;
  }
  
  bool FontAtlasLoader::LoadSvgShape(Shape &output, const char *filename, int pathIndex, msdfVec2 *dimensions)
  {
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(filename))
      return false;
    tinyxml2::XMLElement *root = doc.FirstChildElement("svg");
    if (!root)
      return false;
    
    tinyxml2::XMLElement *path = nullptr;
    int flags = 0;
    int skippedPaths = abs(pathIndex)-(pathIndex != 0);
    if (pathIndex > 0)
      findPathByForwardIndex(path, flags, skippedPaths, root, false);
    else
      findPathByBackwardIndex(path, flags, skippedPaths, root, false);
    if (!path)
      return false;
    const char *pd = path->Attribute("d");
    if (!pd)
      return false;
    
    msdfVec2 dims(root->FloatAttribute("width"), root->FloatAttribute("height"));
    float left, top;
    const char *viewBox = root->Attribute("viewBox");
    if (viewBox)
      sscanf(viewBox, "%f %f %f %f", &left, &top, &dims.x, &dims.y);
    if (dimensions)
      *dimensions = dims;
    output.contours.clear();
    output.inverseYAxis = true;
    return BuildShapeFromSvgPath(output, pd, ENDPOINT_SNAP_RANGE_PROPORTION*dims.length());
  }
  
  int FontAtlasLoader::LoadSvgShape(Shape &output, Shape::Bounds &viewBox, const char *filename)
  {
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(filename))
      return FontAtlasLoader::SvgImportFlags::FAILURE;
    tinyxml2::XMLElement *root = doc.FirstChildElement("svg");
    if (!root)
      return FontAtlasLoader::SvgImportFlags::FAILURE;
    
    tinyxml2::XMLElement *path = nullptr;
    int flags = 0;
    int skippedPaths = 0;
    findPathByBackwardIndex(path, flags, skippedPaths, root, false);
    if (!(path && (flags&FontAtlasLoader::SvgImportFlags::SUCCESS)))
      return FontAtlasLoader::SvgImportFlags::FAILURE;
    const char *pd = path->Attribute("d");
    if (!pd)
      return FontAtlasLoader::SvgImportFlags::FAILURE;
    
    viewBox.l = 0, viewBox.b = 0;
    msdfVec2 dims(root->FloatAttribute("width"), root->FloatAttribute("height"));
    const char *viewBoxStr = root->Attribute("viewBox");
    if (viewBoxStr)
      sscanf(viewBoxStr, "%f %f %f %f", &viewBox.l, &viewBox.b, &dims.x, &dims.y);
    viewBox.r = viewBox.l+dims.x;
    viewBox.t = viewBox.b+dims.y;
    output.contours.clear();
    output.inverseYAxis = true;
    if (!BuildShapeFromSvgPath(output, pd, ENDPOINT_SNAP_RANGE_PROPORTION*dims.length()))
      return FontAtlasLoader::SvgImportFlags::FAILURE;
    return flags;
  }
  
  ///*** FONT ***///
  
  class FontHandle {
    
    friend FontHandle * AdoptFreetypeFont(FT_Face ftFace);
    friend FontHandle * FontAtlasLoader::LoadFont(const char *filename);
    friend FontHandle * FontAtlasLoader::LoadFontData(const byte *data, int length);
    friend void FontAtlasLoader::DestroyFont(FontHandle *font);
    friend bool FontAtlasLoader::GetFontMetrics(FontMetrics &metrics, FontHandle *font);
    friend bool FontAtlasLoader::GetFontWhitespaceWidth(float &spaceAdvance, float &tabAdvance, FontHandle *font);
    friend bool FontAtlasLoader::GetGlyphIndex(GlyphIndex &glyphIndex, FontHandle *font, unicode_t unicode);
    friend bool FontAtlasLoader::LoadGlyph(Shape &output, FontHandle *font, GlyphIndex glyphIndex, float *advance);
    friend bool FontAtlasLoader::LoadGlyph(Shape &output, FontHandle *font, unicode_t unicode, float *advance);
    friend bool FontAtlasLoader::GetKerning(float &output, FontHandle *font, GlyphIndex glyphIndex1, GlyphIndex glyphIndex2);
    friend bool FontAtlasLoader::GetKerning(float &output, FontHandle *font, unicode_t unicode1, unicode_t unicode2);
    friend bool FontAtlasLoader::SetFontVariationAxis(FontHandle *font, const char *name, float coordinate);
    friend bool FontAtlasLoader::ListFontVariationAxes(std::vector<FontVariationAxis> &axes, FontHandle *font);
    friend std::string FontAtlasLoader::GetFontFamily(FontHandle *font);
    friend std::string FontAtlasLoader::GetFontStyle(FontHandle* font);
    
    FT_Face face;
    bool ownership;
    
  };
  
  std::string FontAtlasLoader::GetFontFamily(FontHandle *font)
  {
    std::string str = font->face->family_name;
    return str;
  }
  std::string FontAtlasLoader::GetFontStyle(FontHandle* font)
  {
    std::string str = font->face->style_name;
    return str;
  }
  
  static constexpr float F26DOT6_TO_DOUBLE(auto x) {return 1/64.*float(x);}
  static constexpr float  F16DOT16_TO_DOUBLE(auto x) {return 1/65536.*float(x);}
  static constexpr FT_Fixed DOUBLE_TO_F16DOT16(float x) {return FT_Fixed(65536.*x);}
  
  struct FtContext {
    Point2 position;
    Shape *shape;
    Contour *contour;
  };
  
  static Point2 ftPoint2(const FT_Vector &vector) {
    return Point2(F26DOT6_TO_DOUBLE(vector.x), F26DOT6_TO_DOUBLE(vector.y));
  }
  
  static int ftMoveTo(const FT_Vector *to, void *user) {
    FtContext *context = reinterpret_cast<FtContext *>(user);
    if (!(context->contour && context->contour->edges.empty()))
      context->contour = &context->shape->addContour();
    context->position = ftPoint2(*to);
    return 0;
  }
  
  static int ftLineTo(const FT_Vector *to, void *user) {
    FtContext *context = reinterpret_cast<FtContext *>(user);
    Point2 endpoint = ftPoint2(*to);
    if (endpoint != context->position) {
      context->contour->AddEdge(new LinearSegment(context->position, endpoint));
      context->position = endpoint;
    }
    return 0;
  }
  
  static int ftConicTo(const FT_Vector *control, const FT_Vector *to, void *user) {
    FtContext *context = reinterpret_cast<FtContext *>(user);
    context->contour->AddEdge(new QuadraticSegment(context->position, ftPoint2(*control), ftPoint2(*to)));
    context->position = ftPoint2(*to);
    return 0;
  }
  
  static int ftCubicTo(const FT_Vector *control1, const FT_Vector *control2, const FT_Vector *to, void *user) {
    FtContext *context = reinterpret_cast<FtContext *>(user);
    context->contour->AddEdge(new CubicSegment(context->position, ftPoint2(*control1), ftPoint2(*control2), ftPoint2(*to)));
    context->position = ftPoint2(*to);
    return 0;
  }

  FontHandle* AdoptFreetypeFont(FT_Face ftFace)
  {
    auto *handle = new FontHandle;
    handle->face = ftFace;
    handle->ownership = false;
    return handle;
  }
  
  FT_Error ReadFreetypeOutline(Shape &output, FT_Outline *outline)
  {
    output.contours.clear();
    output.inverseYAxis = false;
    FtContext context = { };
    context.shape = &output;
    FT_Outline_Funcs ftFunctions;
    ftFunctions.move_to = &ftMoveTo;
    ftFunctions.line_to = &ftLineTo;
    ftFunctions.conic_to = &ftConicTo;
    ftFunctions.cubic_to = &ftCubicTo;
    ftFunctions.shift = 0;
    ftFunctions.delta = 0;
    
    FT_Error error = FT_Outline_Decompose(outline, &ftFunctions, &context);
    if (!output.contours.empty() && output.contours.back().edges.empty())
      output.contours.pop_back();
    return error;
  }

  FontHandle *FontAtlasLoader::LoadFont(const char *filename)
  {
    if (!globalData.library)
      return nullptr;
    auto *handle = new FontHandle;
    FT_Error error = FT_New_Face(globalData.library, filename, 0, &handle->face);
    if (error) {
      delete handle;
      return nullptr;
    }
    handle->ownership = true;
    return handle;
  }
  
  FontHandle *FontAtlasLoader::LoadFontData(const uint8_t *data, int length)
  {
    if (!globalData.library)
      return nullptr;
    auto *handle = new FontHandle;
    FT_Error error = FT_New_Memory_Face(globalData.library, data, length, 0, &handle->face);
    if (error) {
      delete handle;
      return nullptr;
    }
    handle->ownership = true;
    return handle;
  }
  
  void FontAtlasLoader::DestroyFont(FontHandle *font)
  {
    if (font->ownership)
      FT_Done_Face(font->face);
    delete font;
  }
  
  bool FontAtlasLoader::GetFontMetrics(FontMetrics &metrics, FontHandle *font)
  {
    
    metrics.emSize = F26DOT6_TO_DOUBLE(font->face->units_per_EM);
    metrics.ascenderY = F26DOT6_TO_DOUBLE(font->face->ascender);
    metrics.descenderY = F26DOT6_TO_DOUBLE(font->face->descender);
    metrics.lineHeight = F26DOT6_TO_DOUBLE(font->face->height);
    metrics.underlineY = F26DOT6_TO_DOUBLE(font->face->underline_position);
    metrics.underlineThickness = F26DOT6_TO_DOUBLE(font->face->underline_thickness);
    return true;
  }
  
  bool FontAtlasLoader::GetFontWhitespaceWidth(float &spaceAdvance, float &tabAdvance, FontHandle *font)
  {
    FT_Error error = FT_Load_Char(font->face, ' ', FT_LOAD_NO_SCALE);
    if (error)
      return false;
    spaceAdvance = F26DOT6_TO_DOUBLE(font->face->glyph->advance.x);
    error = FT_Load_Char(font->face, '\t', FT_LOAD_NO_SCALE);
    if (error)
      return false;
    tabAdvance = F26DOT6_TO_DOUBLE(font->face->glyph->advance.x);
    return true;
  }
  
  bool FontAtlasLoader::GetGlyphIndex(GlyphIndex &glyphIndex, FontHandle *font, unicode_t unicode)
  {
    glyphIndex = GlyphIndex(FT_Get_Char_Index(font->face, unicode));
    return glyphIndex.GetIndex() != 0;
  }
  
  bool FontAtlasLoader::LoadGlyph(Shape &output, FontHandle *font, GlyphIndex glyphIndex, float *advance)
  {
    if (!font)
      return false;
    FT_Error error = FT_Load_Glyph(font->face, glyphIndex.GetIndex(), FT_LOAD_NO_SCALE);
    if (error)
      return false;
    if (advance)
      *advance = F26DOT6_TO_DOUBLE(font->face->glyph->advance.x);
    return !ReadFreetypeOutline(output, &font->face->glyph->outline);
  }
  
  bool FontAtlasLoader::LoadGlyph(Shape &output, FontHandle *font, unicode_t unicode, float *advance)
  {
    return LoadGlyph(output, font, GlyphIndex(FT_Get_Char_Index(font->face, unicode)), advance);
  }
  
  bool FontAtlasLoader::GetKerning(float &output, FontHandle *font, GlyphIndex glyphIndex1, GlyphIndex glyphIndex2)
  {
    FT_Vector kerning;
    if (FT_Get_Kerning(font->face, glyphIndex1.GetIndex(), glyphIndex2.GetIndex(), FT_KERNING_UNSCALED, &kerning)) {
      output = 0;
      return false;
    }
    output = F26DOT6_TO_DOUBLE(kerning.x);
    return true;
  }
  
  bool FontAtlasLoader::GetKerning(float &output, FontHandle *font, unicode_t unicode1, unicode_t unicode2)
  {
    return GetKerning(output, font, GlyphIndex(FT_Get_Char_Index(font->face, unicode1)), GlyphIndex(FT_Get_Char_Index(font->face, unicode2)));
  }
  
  bool FontAtlasLoader::SetFontVariationAxis(FontHandle *font, const char *name, float coordinate)
  {
    bool success = false;
    if (font->face->face_flags&FT_FACE_FLAG_MULTIPLE_MASTERS) {
      FT_MM_Var *master = nullptr;
      if (FT_Get_MM_Var(font->face, &master))
        return false;
      if (master && master->num_axis) {
        std::vector<FT_Fixed> coords(master->num_axis);
        if (!FT_Get_Var_Design_Coordinates(font->face, FT_UInt(coords.size()), &coords[0])) {
          for (FT_UInt i = 0; i < master->num_axis; ++i) {
            if (!strcmp(name, master->axis[i].name)) {
              coords[i] = DOUBLE_TO_F16DOT16(coordinate);
              success = true;
              break;
            }
          }
        }
        if (FT_Set_Var_Design_Coordinates(font->face, FT_UInt(coords.size()), &coords[0]))
          success = false;
      }
      FT_Done_MM_Var(globalData.library, master);
    }
    return success;
  }
  
  bool FontAtlasLoader::ListFontVariationAxes(std::vector<FontVariationAxis> &axes, FontHandle *font)
  {
    if (font->face->face_flags&FT_FACE_FLAG_MULTIPLE_MASTERS) {
      FT_MM_Var *master = nullptr;
      if (FT_Get_MM_Var(font->face, &master))
        return false;
      axes.resize(master->num_axis);
      for (FT_UInt i = 0; i < master->num_axis; i++) {
        FontVariationAxis &axis = axes[i];
        axis.name = master->axis[i].name;
        axis.minValue = master->axis[i].minimum;
        axis.maxValue = master->axis[i].maximum;
        axis.defaultValue = master->axis[i].def;
      }
      FT_Done_MM_Var(globalData.library, master);
      return true;
    }
    return false;
  }
  
  
  ///*** RESOLVE ***///
  
  
  
  /*void shapeToSkiaPath(SkPath &skPath, const Shape &shape) {
    for (std::vector<Contour>::const_iterator contour = shape.contours.begin(); contour != shape.contours.end(); ++contour) {
      if (!contour->edges.empty()) {
        skPath.moveTo(contour->edges.front()->point(0));
        for (std::vector<EdgeHolder>::const_iterator edge = contour->edges.begin(); edge != contour->edges.end(); ++edge) {
          const Point2 *p = (*edge)->controlPoints();
          switch ((*edge)->type()) {
            case (int) LinearSegment::EDGE_TYPE:
              skPath.lineTo(p[1]);
              break;
            case (int) QuadraticSegment::EDGE_TYPE:
              skPath.quadTo(p[1], p[2]);
              break;
            case (int) CubicSegment::EDGE_TYPE:
              skPath.cubicTo(p[1], p[2], p[3]);
              break;
          }
        }
      }
    }
  }
  
  void shapeFromSkiaPath(Shape &shape, const SkPath &skPath) {
    shape.contours.clear();
    Contour *contour = &shape.addContour();
    SkPath::Iter pathIterator(skPath, true);
    Point2 edgePoints[4];
    for (SkPath::Verb op; (op = pathIterator.next(edgePoints)) != SkPath::kDone_Verb;) {
      switch (op) {
        case SkPath::kMove_Verb:
          if (!contour->edges.empty())
            contour = &shape.addContour();
          break;
        case SkPath::kLine_Verb:
          contour->addEdge(new LinearSegment(edgePoints[0], edgePoints[1]));
          break;
        case SkPath::kQuad_Verb:
          contour->addEdge(new QuadraticSegment(edgePoints[0], edgePoints[1], edgePoints[2]));
          break;
        case SkPath::kCubic_Verb:
          contour->addEdge(new CubicSegment(edgePoints[0], edgePoints[1], edgePoints[2], edgePoints[3]));
          break;
        case SkPath::kConic_Verb:
        {
          Point2 quadPoints[5];
          SkPath::ConvertConicToQuads(edgePoints[0], edgePoints[1], edgePoints[2], pathIterator.conicWeight(), quadPoints, 1);
          contour->addEdge(new QuadraticSegment(quadPoints[0], quadPoints[1], quadPoints[2]));
          contour->addEdge(new QuadraticSegment(quadPoints[2], quadPoints[3], quadPoints[4]));
        }
          break;
        case SkPath::kClose_Verb:
        case SkPath::kDone_Verb:
          break;
      }
    }
    if (contour->edges.empty())
      shape.contours.pop_back();
  }
  
  bool FontAtlasLoader::ResolveShapeGeometry(Shape &shape) {
    SkPath skPath;
    shapeToSkiaPath(skPath, shape);
    if (!Simplify(skPath, &skPath))
      return false;
    // Skia's AsWinding doesn't seem to work for unknown reasons
    shapeFromSkiaPath(shape, skPath);
    shape.orientContours();
    return true;
  }*/
  
}