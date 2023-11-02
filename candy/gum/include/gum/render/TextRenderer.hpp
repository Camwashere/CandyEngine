#pragma once
#include <candy/graphics/Color.hpp>
#include <candy/graphics/font/Font.hpp>
#include <gum/widget/Label.hpp>
#include <gum/text/Text.hpp>
namespace Candy::Gum
{
  class TextRenderer
  {
  private:
    const uint32_t maxQuads;
    const uint32_t maxVertices;
    const uint32_t maxIndices;
    SharedPtr<Graphics::Shader> shader;
    SharedPtr<Graphics::VertexArray> vertexArray;
    SharedPtr<Graphics::VertexBuffer> vertexBuffer;
    SharedPtr<Graphics::IndexBuffer> indexBuffer;
    
    struct TextVertex;
    struct TextData;
    std::vector<TextData> textData;
    std::vector<TextVertex> verts;
    int currentVertexOffset=0;
  public:
    TextRenderer(uint32_t gumRenderPassIndex, uint32_t maxQuads);
    
  public:
    void BeginText(Math::Vector2 position, const Paint& fill);
    void SubmitCharacter(const Math::Bounds2D& quad, const Math::Bounds2D& uv);
    void EndText(Math::Vector2 size);
    //void SubmitText(const Text& text);
    //void SubmitLabel(const Label& label, const SharedPtr<Graphics::Font>& font);
    
    void Flush(Math::Vector2 sceneSize);
    void Reset();
  
  };
}