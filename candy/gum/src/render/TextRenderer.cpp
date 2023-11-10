#include <gum/render/TextRenderer.hpp>
#include <candy/graphics/font/MSDFData.hpp>
#include <candy/graphics/shader/ShaderLibrary.hpp>
#include <gum/GumSystem.hpp>
#include <candy/app/Application.hpp>
namespace Candy::Gum
{
  using namespace Math;
  using namespace Graphics;
  struct TextRenderer::TextVertex
  {
    Vector2 position;
    Vector2 uv;
  };
  
  struct TextRenderer::TextData
  {
    Math::Vector2 positionInScene;
    Math::Vector2 size;
    int32_t vertexOffset=0;
    int32_t quadCount=0;
    Paint fill;
  };
  
  static const std::vector<uint32_t> rectIndices{0, 2, 1, 0, 3, 2};
  TextRenderer::TextRenderer(uint32_t gumRenderPassIndex, uint32_t maxQuads) : maxQuads(maxQuads), maxVertices(maxQuads*4), maxIndices(maxQuads * 6)
  {
    ShaderSettings shaderSettings;
    
    shaderSettings.sourceFilePath = ShaderLibrary::GetInternalSourceDirectory() / "gum/Text.glsl";
    auto& profileSettings = shaderSettings.profileSettings;
    profileSettings.renderPassIndex = gumRenderPassIndex;
    profileSettings.SetDepthStencil(false);
    profileSettings.AddBlendAttachment(true);
    
    shader=Shader::Create(shaderSettings);
    
    vertexArray=VertexArray::Create();
    vertexBuffer=VertexBuffer::Create(shader->GetBufferLayout(), maxVertices);
    vertexArray->AddVertexBuffer(vertexBuffer);
    
    
    indexBuffer = IndexBuffer::Create(rectIndices.size());
    vertexArray->SetIndexBuffer(indexBuffer);
    indexBuffer->SetData(rectIndices.data(), rectIndices.size());
  }
  
  
  void TextRenderer::Flush(Math::Vector2 sceneSize)
  {
    shader->Bind();
    vertexBuffer->SetData(verts.data(), verts.size()*sizeof(TextVertex));
    vertexArray->Bind();
    for (const auto& text : textData)
    {
      for (int i=0; i<text.quadCount; i++)
      {
        shader->PushVector4("fillColor", text.fill.color);
        RenderCommand::DrawIndexed(6, 1, 0, text.vertexOffset+i*4, 0);
      }
    }
  }
  void TextRenderer::Reset()
  {
    verts.clear();
    textData.clear();
    currentVertexOffset = 0;
  }

  void TextRenderer::SubmitCharacter(const Math::Bounds2D& quad, const Math::Bounds2D& uv)
  {
    CANDY_PROFILE_FUNCTION();
    
    Math::Vector2 positions[4] = {quad.GetMin(), quad.GetTopLeft(), quad.GetTopRight(), quad.GetBottomRight()};
    Math::Vector2 texCoords[4] = {
    {uv.GetBottomLeft()}, // Bottom-left
    {uv.GetTopLeft()},  // Top-left
    {uv.GetTopRight()}, // Top-right
    {uv.GetBottomRight()} // Bottom-right
    };
    
    for (int i=0; i<4; i++)
    {
      TextVertex vertex;
      Vector2 normalized = positions[i] / camera->GetViewportSize();
      Vector2 clipSpace = normalized * 2.0f - Vector2(1.0f);
      vertex.position = clipSpace;
      vertex.uv = texCoords[i];
      verts.push_back(vertex);
    }
    textData.back().quadCount++;
    
    
  }
  void TextRenderer::BeginScene(const Graphics::OrthographicCamera& cam)
  {
    camera = &cam;
  }
  void TextRenderer::BeginText(Math::Vector2 position, const Paint& fill)
  {
    TextData txtData;
    txtData.fill = fill;
    txtData.positionInScene = position;
    txtData.size = Vector2::zero;
    txtData.vertexOffset = currentVertexOffset;
    txtData.quadCount = 0;
    textData.push_back(txtData);
  }
  void TextRenderer::EndText()
  {
    textData.back().size = textData.back().size - textData.back().positionInScene;
    currentVertexOffset += textData.back().quadCount * 4;
  }
  /*void TextRenderer::SubmitText(const Text& text)
  {
    TextData txtData;
    txtData.fill = text.GetFill();
    txtData.positionInScene = text.GetPosition();
    txtData.size = text.GetSize();
    txtData.vertexOffset = currentVertexOffset;
    
    txtData.quadCount = 0;
    
    const SharedPtr<Graphics::Font>& font = text.GetFont();
    const auto& fontGeometry = font->GetMSDFData()->fontGeometry;
    const auto& metrics = fontGeometry.getMetrics();
    SharedPtr<Graphics::Texture> fontAtlas = font->GetAtlasTexture();
    
    
    float x = 0.0f;
    float fsScale = text.GetFontSizeScale();
    float y = 0.0f;
    
    
    std::string string = text.GetText();
    
    for (size_t i = 0; i < string.size(); i++)
    {
      Math::Vector2 spaceOffset = text.GetCharacterSpaceOffset(i);
      x += spaceOffset.x;
      y += spaceOffset.y;
      char character = text.GetCharAt(i);
      Bounds2D quadBounds = text.GetGeometryBounds(character, {x, y});
      Bounds2D uvBounds = text.GetUVBounds(character);
      
      // render here
      DrawCharacter(text.GetFill(), quadBounds, uvBounds);
      txtData.quadCount++;
      if (i < string.size() - 1)
      {
        float advance = text.GetAdvance(i);
        
        char nextCharacter = string[i + 1];
        fontGeometry.getAdvance(advance, character, nextCharacter);
        
        
        x += fsScale * advance + text.GetKerning();
      }
      
    }
    
    
    currentVertexOffset += txtData.quadCount * 4;
    textData.push_back(txtData);
  }*/
  /*void TextRenderer::SubmitLabel(const Label& label, const SharedPtr<Graphics::Font>& font)
  {
    CANDY_PROFILE_FUNCTION();
    TextData txtData;
    txtData.fill = label.GetFill();
    txtData.positionInScene = label.GetBoundsInScene().GetPosition();
    txtData.size = label.GetSize();
    txtData.vertexOffset = currentVertexOffset;
    
    txtData.quadCount = 0;
    
    
    const auto& fontGeometry = font->GetMSDFData()->fontGeometry;
    const auto& metrics = fontGeometry.getMetrics();
    SharedPtr<Graphics::Texture> fontAtlas = font->GetAtlasTexture();
    
    
    float x = 0.0f;
    float fsScale = 1.0f / (metrics.ascenderY - metrics.descenderY);
    float y = 0.0f;
    
    const float spaceGlyphAdvance = fontGeometry.getGlyph(' ')->getAdvance();
    
    std::string string = label.GetText();
    
    for (size_t i = 0; i < string.size(); i++)
    {
      char character = string[i];
      if (character == '\r')
        continue;
      
      if (character == '\n')
      {
        x = 0;
        y -= fsScale * metrics.lineHeight + label.GetLineSpacing();
        continue;
      }
      
      if (character == ' ')
      {
        float advance = spaceGlyphAdvance;
        if (i < string.size() - 1)
        {
          char nextCharacter = string[i + 1];
          float dAdvance;
          fontGeometry.getAdvance(dAdvance, character, nextCharacter);
          
          advance = (float)dAdvance;
        }
        
        x += fsScale * advance + label.GetKerning();
        continue;
      }
      
      if (character == '\t')
      {
        // NOTE(Yan): is this right?
        x += 4.0f * (fsScale * spaceGlyphAdvance + label.GetKerning());
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
      
      float texelWidth = 1.0f / fontAtlas->GetWidth();
      float texelHeight = 1.0f / fontAtlas->GetHeight();
      texCoordMin *= Vector2(texelWidth, texelHeight);
      texCoordMax *= Vector2(texelWidth, texelHeight);
      
      Bounds2D quadBounds;
      quadBounds.SetMin(quadMin);
      quadBounds.SetMax(quadMax);
      
      Bounds2D uvBounds;
      uvBounds.SetMin(texCoordMin);
      uvBounds.SetMax(texCoordMax);
      // render here
      DrawCharacter(label.GetFill(), quadBounds, uvBounds);
      txtData.quadCount++;
      if (i < string.size() - 1)
      {
        float advance = glyph->getAdvance();
        
        char nextCharacter = string[i + 1];
        fontGeometry.getAdvance(advance, character, nextCharacter);
        
        
        x += fsScale * advance + label.GetKerning();
      }
      
    }
    
    
    currentVertexOffset += txtData.quadCount * 4;
    textData.push_back(txtData);
  }*/
}