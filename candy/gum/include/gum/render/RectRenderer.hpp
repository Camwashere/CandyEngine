#pragma once
#include <candy/graphics/shader/Shader.hpp>
#include <candy/graphics/VertexArray.hpp>
#include <gum/shape/Rectangle.hpp>
namespace Candy::Gum
{
  class RectRenderer
  {
  private:
    const uint32_t maxQuads;
    const uint32_t maxVertices = maxQuads;
    SharedPtr<Graphics::Shader> shader;
    SharedPtr<Graphics::VertexArray> vertexArray;
    SharedPtr<Graphics::VertexBuffer> vertexBuffer;
    SharedPtr<Graphics::IndexBuffer> indexBuffer;
    int currentVertexOffset=0;
    
    struct RectVertex;
    struct RectData;
    
    std::vector<RectData> rectData;
    std::vector<RectVertex> verts;
    
    
  public:
    RectRenderer(uint32_t gumRenderPassIndex, uint32_t maxQuads);
    void Submit(const Rectangle& rectangle);
    void Flush(Math::Vector2 sceneSize);
    void Reset();
  };
}