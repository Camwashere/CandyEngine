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
    int pointSize;
    bool bold;
    bool italic;
    
    // You'll need to specify a less-than operator for std::map keys
    bool operator<(const FontAttributes& other) const {
      return std::tie(pointSize, bold, italic) < std::tie(other.pointSize, other.bold, other.italic);
    }
  };
  struct Glyph
  {
    float advance;
    Math::Bounds2D bounds;
    std::vector<Math::Contour> contours;
  };
  
  class GlyphCache
  {
  private:
    FontAttributes fontAttributes;
    std::unordered_map<unicode_t, Glyph> glyphs;
    
  private:
    void LoadGlyphContours(Glyph& glyph, const FT_Outline_& outline);
  public:
    GlyphCache(FT_FaceRec_* face, const Charset& charset, const FontAttributes& attributes);
    const Glyph* GetGlyph(unicode_t codepoint)const;
  };
}