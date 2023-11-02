#include <gum/text/Text.hpp>
#include <candy/graphics/font/MSDFData.hpp>
#include <CandyPch.hpp>
#include <gum/render/Renderer.hpp>
#include <gum/render/TextRenderer.hpp>
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
    const auto& fontGeometry = font->GetMSDFData()->fontGeometry;
    const auto& metrics = fontGeometry.getMetrics();
    SharedPtr<Graphics::Texture> fontAtlas = font->GetAtlasTexture();
    
    
    float x = 0.0f;
    float fsScale = fontSize / (metrics.ascenderY - metrics.descenderY);
    float y = 0.0f;
    
    const float spaceGlyphAdvance = fontGeometry.getGlyph(' ')->getAdvance();
    Vector2 texelSize = GetTexelSize();
    
    for (size_t i = 0; i < text.size(); i++)
    {
      char character = text[i];
      if (wrap > 0.0f && x > wrap)
      {
        x = 0;
        y -= fsScale * metrics.lineHeight + lineSpacing;
        
      }
      if (character == '\r')
        continue;
      
      if (character == '\n')
      {
        x = 0;
        y -= fsScale * metrics.lineHeight + lineSpacing;
        continue;
      }
      
      if (character == ' ')
      {
        float advance = spaceGlyphAdvance;
        if (i < text.size() - 1)
        {
          char nextCharacter = text[i + 1];
          float dAdvance;
          fontGeometry.getAdvance(dAdvance, character, nextCharacter);
          
          advance = (float)dAdvance;
        }
        
        x += fsScale * advance + kerning;
        continue;
      }
      
      if (character == '\t')
      {
        // NOTE(Yan): is this right?
        x += 4.0f * (fsScale * spaceGlyphAdvance + kerning);
        continue;
      }
      
      auto glyph = fontGeometry.getGlyph(character);
      
      if (!glyph)
      {
        glyph = fontGeometry.getGlyph('?');
        
      }
      
      if (!glyph)
      {
        return;
      }
      if (wrap > 0.0f && x > wrap)
      {
        x = 0;
        y -= fsScale * metrics.lineHeight + lineSpacing;
      }
      
      float al, ab, ar, at;
      glyph->getQuadAtlasBounds(al, ab, ar, at);
      
      Vector2 texCoordMin(al, ab);
      Vector2 texCoordMax(ar, at);
      
      float pl, pb, pr, pt;
      glyph->getQuadPlaneBounds(pl, pb, pr, pt);
      
      Vector2 quadMin(pl, pb);
      Vector2 quadMax(pr, pt);
      
      quadMin *= fsScale, quadMax *= fsScale;
      quadMin += Vector2(x, y);
      quadMax += Vector2(x, y);
      
      
      texCoordMin *= texelSize;
      texCoordMax *= texelSize;
      
      Bounds2D quadBounds;
      quadBounds.SetMin(quadMin);
      quadBounds.SetMax(quadMax);
      
      
      
      Bounds2D uvBounds;
      uvBounds.SetMin(texCoordMin);
      uvBounds.SetMax(texCoordMax);
      
      // render here
      Renderer::GetTextRenderer().SubmitCharacter(quadBounds, uvBounds);
      
      if (i < text.size() - 1)
      {
        float advance = glyph->getAdvance();
        
        char nextCharacter = text[i + 1];
        fontGeometry.getAdvance(advance, character, nextCharacter);
        x += fsScale * advance + kerning;
        if (wrap > 0.0f && x > wrap)
        {
          x = 0;
          y -= fsScale * metrics.lineHeight + lineSpacing;
        }
      }
      
      
      
    }
    
    
    
    Renderer::GetTextRenderer().EndText(size);
  }
  
  
 
  Math::Vector2 Text::GetTexelSize()const
  {
    SharedPtr<Graphics::Texture> fontAtlas = font->GetAtlasTexture();
    float texelWidth = 1.0f / fontAtlas->GetWidth();
    float texelHeight = 1.0f / fontAtlas->GetHeight();
    return {texelWidth, texelHeight};
  }
  float Text::GetFontSizeScale()const
  {
    const auto& fontGeometry = font->GetMSDFData()->fontGeometry;
    const auto& metrics = fontGeometry.getMetrics();
    return 1.0f / (metrics.ascenderY - metrics.descenderY);
  }
  
  void Text::SetFont(const SharedPtr<Graphics::Font>& value)
  {
    font = value;
  }
  SharedPtr<Graphics::Font> Text::GetFont()const
  {
    return font;
  }
  float Text::GetFontSize()const
  {
    return fontSize;
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