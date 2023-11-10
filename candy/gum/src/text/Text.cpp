#include <gum/text/Text.hpp>
#include <candy/graphics/font/MSDFData.hpp>
#include <CandyPch.hpp>
#include <gum/render/Renderer.hpp>
#include <gum/render/TextRenderer.hpp>
#include <candy/app/Application.hpp>
#include <gum/GumSystem.hpp>
#include <utility>
namespace Candy::Gum
{
  using namespace Math;
  
  Text::Text() : fill(Color::black)
  {
  
  }
  
  Text::Text(const std::string& text) : text(text), fill(Color::black)
  {
  
  }
  Text::Text(const std::string& text, const Paint& fill) : text(text), fill(fill)
  {
  
  }
  
  
  void Text::Render(float wrap)
  {
    Renderer::GetTextRenderer().BeginText(position, fill);
    Vector2 currentPos = position;
    
    
    float ascender = font->GetAscenderPixelSize();
    float descender = font->GetDescenderPixelSize();
    float lineHeight = font->GetLineHeightPixelSize();
    const GlyphCache& glyphCache = font->GetGlyphCache(font->GetPixelSize());
    for (int i=0; i<text.size(); i++)
    {
      char character = text[i];
      const Glyph* glyph = font->GetGlyph(character);
      if (glyph == nullptr)
      {
        continue;
      }
      
      if (character == '\n') {
        // Handle newline
        currentPos.x = position.x;
        currentPos.y += lineHeight; // Move the current Y position upwards by the line height
        continue;
      }
      float kern = 0.0f;
      
      if (i < text.size()-1)
      {
        kern = glyphCache.GetKerning(character, text[i+1]);
      }
      
      float aligned_y = currentPos.y + ascender - glyph->bearing.y;
      Math::Bounds2D glyphQuadBounds = glyph->bounds;
      glyphQuadBounds.Move({currentPos.x, currentPos.y});
      Renderer::GetTextRenderer().SubmitCharacter(glyphQuadBounds, font->GetAtlas().GetUV(character));
      currentPos.x += glyph->advance + kern;
    }
    
    size.x = currentPos.x - position.x;
    Renderer::GetTextRenderer().EndText();
  }
  
  SharedPtr<FontInternal> Text::GetFont()const
  {
    return font;
  }
  void Text::SetFont(SharedPtr<FontInternal> value)
  {
    font = std::move(value);
    Renderer::SetFont(font);
  }
  float Text::GetFontSize()const
  {
    return font->GetPixelSize();
  }
  void Text::SetFontSize(float value)
  {
    font->SetPixelSize(value);
  }
  Math::Vector2 Text::GetSize()const
  {
    return size;
  }
  Math::Vector2 Text::GetPosition()const
  {
    return position;
  }
  std::string Text::GetText()const
  {
    return text;
  }
  void Text::SetText(const std::string& value)
  {
    text = value;
  }
  
  void Text::SetFill(const Paint& value)
  {
    fill = value;
  }
  Paint Text::GetFill()const
  {
    return fill;
  }
  
  float Text::GetKerning()const
  {
    return kerning;
  }
  void Text::SetKerning(float value)
  {
    kerning = value;
  }
  float Text::GetLineSpacing()const
  {
    return lineSpacing;
  }
  void Text::SetLineSpacing(float value)
  {
    lineSpacing = value;
  }
  
}