#include <candy/graphics/font/Glyph.hpp>
namespace Candy::Graphics
{
  using namespace Math;
  Glyph::Glyph(unicode_t cp) : codepoint(cp)
  {
  
  }
  void Glyph::SetAtlasPosition(int x, int y){
    box.rect.position.x = x, box.rect.position.y = y;
  }
  void Glyph::SetAtlasSize(int x, int y)
  {
    box.rect.size.width = x;
    box.rect.size.height = y;
  }
  void Glyph::SetAtlasRect(const Rect &rect) {
    box.rect = rect;
  }
  
  

  
  float Glyph::GetAdvance() const {
    return advance;
  }
  
  Rect Glyph::GetAtlasRect() const {
    return box.rect;
  }
  
  void Glyph::GetAtlasRect(int &x, int &y, int &w, int &h) const {
    x = box.rect.position.x, y = box.rect.position.y;
    w = box.rect.size.width, h = box.rect.size.height;
  }
  
  void Glyph::GetAtlasSize(int &w, int &h) const {
    w = box.rect.size.width, h = box.rect.size.height;
  }
  
  double Glyph::GetAtlasRange() const {
    return box.range;
  }
  

  
  double Glyph::GetAtlasScale() const {
    return box.scale;
  }
  
  Math::Vector2 Glyph::GetAtlasTranslate() const {
    return box.translate;
  }
  
  void Glyph::GetQuadPlaneBounds(double &l, double &b, double &r, double &t) const {
    if (box.rect.size.width > 0 && box.rect.size.height > 0) {
      double invBoxScale = 1/box.scale;
      l = geometryScale*(-box.translate.x+.5*invBoxScale);
      b = geometryScale*(-box.translate.y+.5*invBoxScale);
      r = geometryScale*(-box.translate.x+(box.rect.size.width-.5)*invBoxScale);
      t = geometryScale*(-box.translate.y+(box.rect.size.height-.5)*invBoxScale);
    } else
      l = 0, b = 0, r = 0, t = 0;
  }
  
  void Glyph::GetQuadAtlasBounds(double &l, double &b, double &r, double &t) const {
    if (box.rect.size.width > 0 && box.rect.size.height > 0) {
      l = box.rect.position.x+.5;
      b = box.rect.position.y+.5;
      r = box.rect.position.x+box.rect.size.width-.5;
      t = box.rect.position.y+box.rect.size.height-.5;
    } else
      l = 0, b = 0, r = 0, t = 0;
  }
  
  
  
  unicode_t Glyph::GetCodepoint()const
  {
    return codepoint;
  }
  bool Glyph::IsWhitespace()const
  {
   
    return codepoint == ' ' || codepoint == '\t' || codepoint == '\n';
  }
}