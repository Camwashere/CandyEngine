#include <gum/font/Glyph.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <CandyPch.hpp>
namespace Candy::Gum
{
  using namespace Candy::Math;
  
  static Vector2 FreeTypeToVector2(const FT_Vector& value)
  {
    return { static_cast<float>(value.x), static_cast<float>(value.y) };
  }
  GlyphCache::GlyphCache(FT_Face face, const FontAttributes& attributes, const Charset& charset) : fontAttributes(attributes)
  {
    for (unicode_t c : charset)
    {
      FT_Error error = FT_Load_Char(face, c, FT_LOAD_DEFAULT);
      if (error)
      {
        CANDY_CORE_ERROR("Error: {}, Could not load glyph: '{}'", FT_Error_String(error), c);
        CANDY_CORE_ASSERT(false);
      }
      
      FT_Outline_ outline = face->glyph->outline;
      Glyph glyph;
      glyph.advance = face->glyph->advance.x / 64.0f;
      glyph.bounds.SetMin(0, -face->glyph->metrics.height / 64.0f);
      glyph.bounds.SetMax(face->glyph->metrics.width / 64.0f, 0);
      glyphs[c] = glyph;
      //LoadGlyphContours(glyph, outline);
      
    }
  }
  
  /*void GlyphCache::LoadGlyphContours(Glyph& glyph, const FT_Outline_& outline)
  {
    std::vector<Contour> contours;
    
    int start = 0;
    for(int i = 0; i < outline.n_contours; i++)
    {
      int end = outline.contours[i];
      // start of this contour
      FT_Vector& first = outline.points[start];
      // end of this contour
      FT_Vector& last = outline.points[end];
      
      FT_Vector* p0 = &first;
      FT_Vector* p1 = nullptr;
      //The current contour
      std::vector<FT_Vector*> current_contour;
      for(int j = start; j <= end; j++)
      {
        unsigned char point_type = outline.tags[j];
        p1 = &outline.points[j];
        
        if (point_type == FT_Curve_Tag_Conic)
        {
          // this is a control point for a quadratic curve.
          //get the second control point
          FT_Vector* p2;
          if(j < end)
            p2 = &outline.points[j + 1];
          else
            p2 = &first;
          Vector2 point1 = FreeTypeToVector2(*p0);
          Vector2 point2 = FreeTypeToVector2(*p1);
          Vector2 point3 = FreeTypeToVector2(*p2);
          contours.push_back(Contour(BezierCurveQuadratic(point1, point2, point3)));
        }
        else if (point_type == FT_Curve_Tag_Cubic)
        {
          // this is a control point for a cubic curve.
          //get the second and third control point
          FT_Vector* p2 = &outline.points[j+1];
          FT_Vector* p3 = (j+2 > end) ? &first : &outline.points[j+2];
          Vector2 point1 = FreeTypeToVector2(*p0);
          Vector2 point2 = FreeTypeToVector2(*p1);
          Vector2 point3 = FreeTypeToVector2(*p2);
          Vector2 point4 = FreeTypeToVector2(*p3);
          contours.push_back(Contour(BezierCurveCubic(point1, point2, point3, point4)));
          // Skip the next two points as they are control points
          j += 2;
          continue;
        }
        else
        {
          // This is a point on a line.
          Vector2 point = FreeTypeToVector2(*p0);
          Vector2 direction = FreeTypeToVector2(*p1);
          contours.push_back(Contour(Line(point, direction)));
        }
        
        p0 = p1;
      }
      
      // move to the starting of next contour
      start = end + 1;
    }
    
    glyph.contours = contours;
  }*/
  const Glyph* GlyphCache::GetGlyph(unicode_t codepoint)const
  {
    auto it = glyphs.find(codepoint);
    if(it != glyphs.end())
    {
      
      return &it->second;
    }
    else
    {
      return nullptr;
    }
  }
}