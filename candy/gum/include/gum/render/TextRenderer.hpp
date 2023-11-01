#pragma once
#include <candy/graphics/Color.hpp>
#include <candy/graphics/font/Font.hpp>
namespace Candy::Gum
{
  class TextRenderer
  {
  private:
  
  public:
    struct TextParams
    {
      Color color=Color::red;
      float kerning = 0.0f;
      float lineSpacing = 0.0f;
    };
  
    void DrawString(const std::string& string, const SharedPtr<Graphics::Font>& font, const Math::Matrix4& transform, const TextParams& textParams, int entityID)
  
  };
}