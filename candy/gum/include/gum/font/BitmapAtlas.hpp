#pragma once
#include <vector>
#include <cstdint>
#include <candy/math/Vector.hpp>
#include <gum/font/Charset.hpp>
#include <candy/math/geometry/Bounds2D.hpp>
#include <unordered_map>
struct FT_FaceRec_;
namespace Candy::Gum
{
  class BitmapAtlas
  {
  private:
    Math::Vector2u size;
    std::vector<uint8_t> data;
    std::unordered_map<unicode_t, Math::Bounds2D> glyphUVs;
    
    void CalculateSize(FT_FaceRec_* face, const Charset& charset);
    
  public:
    void Clear();
    void Load(FT_FaceRec_* face, const Charset& charset);
    Math::Bounds2D GetUV(unicode_t codepoint)const;
    [[nodiscard]] const Math::Vector2u& GetSize()const;
    [[nodiscard]] const std::vector<uint8_t>& GetData()const;
    
  };
}