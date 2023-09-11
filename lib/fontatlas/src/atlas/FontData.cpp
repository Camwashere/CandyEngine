#include "FontAtlas/Atlas/FontData.hpp"
namespace msdf_atlas
{
  GlyphIndex::GlyphIndex(unsigned i) : index(i)
  {
  
  }
  unsigned GlyphIndex::GetIndex() const
  {
    return index;
  }
  
  
}