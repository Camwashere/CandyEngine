#pragma once
#include <candy/base/PrimitiveTypes.hpp>
#include <candy/math/Vector.hpp>
#include <candy/math/Rectangle.hpp>

namespace Candy::Graphics
{
  struct Rect
  {
    Math::Vector2i position;
    Math::Vector2i size;
  };
  class Glyph
  {
  private:
    
    double geometryScale=1.0f;
    unicode_t codepoint;
   
   
    double advance=0.0f;
    
    struct {
      Rect rect;
      float range=0.0f;
      float scale=0.0f;
      Math::Vector2 translate;
    } box;
    
  public:
    Glyph(unicode_t codepoint);
  public:
    /// Sets the glyph's box's position in the atlas
    void SetAtlasPosition(int x, int y);
    
    void SetAtlasSize(int width, int height);
    /// Sets the glyph's box's rectangle in the atlas
    void SetAtlasRect(const Rect &rect);
    

    /// Returns the glyph's advance
    float GetAdvance() const;
    /// Returns the glyph's box in the atlas
    Rect GetAtlasRect() const;
    /// Outputs the position and dimensions of the glyph's box in the atlas
    void GetAtlasRect(int &x, int &y, int &w, int &h) const;
    /// Outputs the dimensions of the glyph's box in the atlas
    void GetAtlasSize(int &w, int &h) const;
    /// Returns the range needed to generate the glyph's SDF
    double GetAtlasRange() const;

    /// Returns the scale needed to generate the glyph's bitmap
    double GetAtlasScale() const;
    /// Returns the translation vector needed to generate the glyph's bitmap
    Math::Vector2 GetAtlasTranslate() const;
    /// Outputs the bounding box of the glyph as it should be placed on the baseline
    void GetQuadPlaneBounds(double &l, double &b, double &r, double &t) const;
    /// Outputs the bounding box of the glyph in the atlas
    void GetQuadAtlasBounds(double &l, double &b, double &r, double &t) const;
    /// Returns the Unicode codepoint represented by the glyph or 0 if unknown
    [[nodiscard]] unicode_t GetCodepoint()const;
    /// Returns true if the glyph is a whitespace and has no geometry
    [[nodiscard]] bool IsWhitespace()const;
  
  };
}