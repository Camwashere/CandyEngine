#include <gum/text/Text.hpp>
#include <candy/graphics/font/MSDFData.hpp>
#include <CandyPch.hpp>
#include <gum/render/Renderer.hpp>
#include <gum/render/TextRenderer.hpp>
#include <candy/app/Application.hpp>
#include <gum/GumSystem.hpp>
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
  
  Bounds2D GetUVBounds(const msdf_atlas::GlyphGeometry* glyph, Math::Vector2 texelSize)
  {
    float al, ab, ar, at;
    glyph->getQuadAtlasBounds(al, ab, ar, at);
    
    Vector2 texCoordMin(al, ab);
    Vector2 texCoordMax(ar, at);
    
    texCoordMin *= texelSize;
    texCoordMax *= texelSize;
    
    Bounds2D uvBounds;
    uvBounds.SetMin(texCoordMin);
    uvBounds.SetMax(texCoordMax);
    return uvBounds;
  }
  Bounds2D GetQuadBounds(const msdf_atlas::GlyphGeometry* glyph, float fsScale)
  {
    float pl, pb, pr, pt;
    glyph->getQuadPlaneBounds(pl, pb, pr, pt);
    Vector2 bottomLeft = {pl, pb};
    Vector2 topRight = {pr, pt};
    
    bottomLeft *= (fsScale);
    topRight *= (fsScale);
    
    Bounds2D quadBounds;
    quadBounds.SetMin(bottomLeft);
    quadBounds.SetMax(topRight);
    return quadBounds;
  }
  void Text::Render(float wrap)
  {
    
    Renderer::GetTextRenderer().BeginText(position, fill);
    Vector2 currentPos = position;
    float pixelSize = font->GetPixelSize();
    Vector2 glyphSize = {pixelSize, pixelSize};
    for (int i=0; i<text.size(); i++)
    {
      char character = text[i];
      
      Renderer::GetTextRenderer().SubmitCharacter(Math::Bounds2D{currentPos, size}, font->atlas.GetUV(character));
      //currentPos += s;
      
    }
    
    Renderer::GetTextRenderer().EndText(size);
  }
  /*void Text::Render(float wrap)
  {
   Renderer::GetTextRenderer().BeginText(position, fill);
    const auto& fontGeometry = font->GetMSDFData()->fontGeometry;
    const auto& metrics = fontGeometry.getMetrics();
    
    SharedPtr<Graphics::Texture> fontAtlas = font->GetAtlasTexture();
    
    
    Vector2 texelSize = GetTexelSize();
    Vector2 currentPos = Vector2::zero;
    
    Vector2 sceneSize = GumSystem::GetCurrentContext().sceneGraph.GetSceneSize();
   
    float fsScale = fontSize / (metrics.ascenderY - metrics.descenderY);
    //fsScale *= fontGeometry.getGeometryScale();
    //CANDY_CORE_INFO("FS Scale: {}", fsScale);
    float runningWidth = 0.0f;
    float characterHeightInPixels = (metrics.ascenderY - metrics.descenderY) * fsScale;
    for (int i=0; i<text.size(); i++)
    {
      char character = text[i];
      
      const msdf_atlas::GlyphGeometry* glyph = fontGeometry.getGlyph(character);
      float advance = glyph->getAdvance();
      
      float character_width_pixels = glyph->getAdvance() * fsScale;
      
      
      Bounds2D uvBounds = GetUVBounds(glyph, texelSize);
      Bounds2D quadBounds = GetQuadBounds(glyph, fsScale);
      //runningWidth += quadBounds.GetWidth();
      quadBounds.SetMin(currentPos);
      runningWidth += (quadBounds.GetPosition().x - runningWidth) + quadBounds.GetWidth();
      //size.width += (size.width - quadBounds.GetPosition().x) + quadBounds.GetWidth();
      
      // render here
      Renderer::GetTextRenderer().SubmitCharacter(quadBounds, uvBounds);
      
      // advance the current position by the geometryScale * fontSizeInPixels * glyph advance
      
      
      if (i < text.size() - 1)
      {
        
        char nextCharacter = text[i + 1];
        //float advance = glyph->getAdvance();
        fontGeometry.getAdvance(advance, character, nextCharacter);
       
        currentPos.x += advance * fsScale + kerning;
      }
      
      
      
     
    }
    
    //runningWidth *= sceneSize.width;
    //characterHeightInPixels *= sceneSize.height;
    
    CANDY_CORE_INFO("Running width: {}", runningWidth);
   
    
    //runningWidth *= 0.5f;
    //size.y = fsScale * metrics.lineHeight;
    //size *= Application::PixelsPerPoint();
    //CANDY_CORE_INFO("TEXT SIZE IN PIXELS: {}", size);
    Renderer::GetTextRenderer().EndText({runningWidth, characterHeightInPixels});
    
  }*/
  /*void Text::Render(float wrap)
  {
    Renderer::GetTextRenderer().BeginText(position, fill);
    const auto& fontGeometry = font->GetMSDFData()->fontGeometry;
    
    const auto& metrics = fontGeometry.getMetrics();
    SharedPtr<Graphics::Texture> fontAtlas = font->GetAtlasTexture();
    
    
    float x = 0.0f;
    //float fontSizeInPoints = fontSize * (Application::PPI() / 72);
    //float fsScale = fontSizeInPoints * (Application::PPI()/72);
    float fsScale = fontSize / (metrics.ascenderY - metrics.descenderY);
    float y = 0.0f;
    
    // Convert the fontSize from pixels to points
    
    const float spaceGlyphAdvance = fontGeometry.getGlyph(' ')->getAdvance();
    Vector2 texelSize = GetTexelSize();
    
    for (size_t i = 0; i < text.size(); i++)
    {
      char character = text[i];
      
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
      }
      
      
      
    }
    
    CANDY_CORE_INFO("X: {}, Y: {}", x, y);
    
    Renderer::GetTextRenderer().EndText();
  }*/
  
  
 
  Math::Vector2 Text::GetTexelSize()const
  {
    SharedPtr<Graphics::Texture> fontAtlas = font->GetAtlasTexture();
    float texelWidth = 1.0f / fontAtlas->GetWidth();
    float texelHeight = 1.0f / fontAtlas->GetHeight();
    return {texelWidth, texelHeight};
  }
  float Text::GetFontSizeScale()const
  {
    //const auto& fontGeometry = font->GetMSDFData()->fontGeometry;
    //const auto& metrics = fontGeometry.getMetrics();
    //return 1.0f / (metrics.ascenderY - metrics.descenderY);
    return 1.0f;
  }
  
  
  SharedPtr<FontInternal> Text::GetFont()const
  {
    return font;
  }
  void Text::SetFont(const SharedPtr<FontInternal>& value)
  {
    font = value;
    Renderer::SetFont(font);
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