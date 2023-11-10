#pragma once
#include <candy/math/geometry/Bounds2D.hpp>
#include <candy/math/geometry/Contour.hpp>
#include <unordered_map>
#include <candy/base/PrimitiveTypes.hpp>
#include <gum/font/Charset.hpp>
struct FT_FaceRec_;
struct FT_Outline_;
namespace Candy::Gum
{
  struct FontAttributes
  {
    int pointSize=0;
    bool bold=false;
    bool italic=false;
    
    FontAttributes() : pointSize(0), bold(false), italic(false){}
    // You'll need to specify a less-than operator for std::map keys
    bool operator<(const FontAttributes& other) const {
      return std::tie(pointSize, bold, italic) < std::tie(other.pointSize, other.bold, other.italic);
    }
  };
  struct Glyph
  {
    float advance;
    Math::Vector2 bearing;
    Math::Bounds2D bounds;
    
    
  };
  
  class GlyphCache
  {
  private:
    FontAttributes fontAttributes;
    std::unordered_map<unicode_t, Glyph> glyphs;
    FT_FaceRec_* face;
  private:
    //void LoadGlyphContours(Glyph& glyph, const FT_Outline_& outline);
  public:
    GlyphCache(FT_FaceRec_* face, const FontAttributes& attributes, const Charset& charset=Charset::ASCII);
    const Glyph* GetGlyph(unicode_t codepoint)const;
    float GetKerning(unicode_t left, unicode_t right)const;
  };
}