#include <gum/render/RectRenderer.hpp>
#include <candy/graphics/shader/ShaderLibrary.hpp>
#include <utility>

namespace Candy::Gum
{
  using namespace Math;
  using namespace Graphics;
  

  
  static constexpr Vector2 rectVertPositions[4] ={
  {-1.0f, -1.0f},
  {-1.0f, 1.0f},
  {1.0f, 1.0f},
  {1.0f, -1.0f} };
  
  static constexpr Vector2 rectVertUvs[4] ={
  {0.0f, 0.0f},
  {0.0f, 1.0f},
  {1.0f, 1.0f},
  {1.0f, 0.0f} };
  
  static const std::vector<uint32_t> rectIndices{0, 2, 1, 0, 3, 2};
  
  struct RectRenderer::RectVertex
  {
    Vector2 position;
    Vector2 uv;
  };
  
  
  static std::array<Vector2, 4> GetRectVertices(Vector2 pos, Vector2 size)
  {
    Vector2 min = pos;
    Vector2 max = min + size;
    return {
      min,
      {min.x, max.y},
      max,
      {max.x, min.y}
    };
  }
  
  struct RectRenderer::RectData
  {
    RectVertex vertices[4];
    int textureIndex=0;
    int32_t vertexOffset=0;
    Math::Vector2 positionInScene;
    Math::Vector2 size;
    float strokeWidth;
    Paint fill;
    Paint stroke;
    Math::Vector2 arcSize;
    
    RectData(const Rectangle& rect, int32_t& currentVertexOffset)
    {
      vertexOffset = currentVertexOffset;
      
      positionInScene = rect.GetBoundsInScene().GetBottomLeft();
      size = rect.GetSize();
      strokeWidth = rect.strokeWidth/(Math::Min(size.x, size.y));
      arcSize = rect.arcSize;
      arcSize = Vector2::Clamp(arcSize, Vector2(Epsilon<float>()), Vector2(1.0f));
      stroke = rect.stroke;
      fill = rect.fill;
      
      for (int i=0; i<4; i++)
      {
        
        vertices[i].position = rectVertPositions[i];
        vertices[i].uv = rectVertUvs[i];
      }
      
      currentVertexOffset += 4;
    }
    
    RectData(const Math::Vector2& positionInScene, const Math::Vector2& size, float strokeWidth, Paint  strokeColor, Paint  fillColor, Math::Vector2 arcSize, int32_t& currentVertexOffset)
    : positionInScene(positionInScene), size(size), strokeWidth(strokeWidth/(Math::Min(size.x, size.y))), stroke(std::move(strokeColor)), fill(std::move(fillColor)), arcSize(Vector2::Clamp(arcSize, Vector2(Epsilon<float>()), Vector2(1.0f)))
    {
      vertexOffset = currentVertexOffset;
      
      for (int i=0; i<4; i++)
      {
        
        vertices[i].position = rectVertPositions[i];
        vertices[i].uv = rectVertUvs[i];
      }
      
      currentVertexOffset += 4;
    }
  };
  
  
  RectRenderer::RectRenderer(uint32_t gumRenderPassIndex, uint32_t maxQuadValue) : maxQuads(maxQuadValue), maxVertices(maxQuads*4)
  {
    ShaderSettings shaderSettings;
    
    shaderSettings.sourceFilePath = ShaderLibrary::GetInternalSourceDirectory() / "gum/Rect.glsl";
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
    verts.resize(4);
    for (int i=0; i<4; i++)
    {
      verts[i].position = rectVertPositions[i];
      verts[i].uv = rectVertUvs[i];
    }
    vertexBuffer->SetData(verts.data(), sizeof(RectVertex)*verts.size());
    
  }
  
  void RectRenderer::Submit(const Rectangle& rectangle)
  {
    RectData rect(rectangle, currentVertexOffset);
    
    rectData.push_back(rect);
  }
  
  void RectRenderer::Submit(const Math::Vector2& positionInScene, const Math::Vector2& size, float strokeWidth, const Paint& strokeColor, const Paint& fillColor, Math::Vector2 arcSize, int textureIndex)
  {
    RectData rect(positionInScene, size, strokeWidth, strokeColor, fillColor, arcSize, currentVertexOffset);
    rect.textureIndex = textureIndex;
    rectData.push_back(rect);
  }
  void RectRenderer::Flush(Math::Vector2 sceneSize)
  {
    shader->Bind();
    vertexArray->Bind();
    
   
    Math::Vector2 sceneSizeHalf = sceneSize * 0.5f;
    
    
    
    for (RectData& rect : rectData)
    {
      // Convert rect size from framebuffer coordinates to shader coordinates
      Vector2 sizeInShaderCoordinates = ((rect.size/sceneSize));
      
      // Adjust the position so that an object's lower left corner corresponds to positionInParent
      Vector2 positionInSceneOffset = rect.positionInScene + (rect.size*0.5f);
      Vector2 positionInShaderCoordinates = ((positionInSceneOffset/sceneSize)*2.0f)-Vector2(1.0f);
      
      
      Math::Matrix3 translate = Matrix3::Translate(Matrix3::IDENTITY, positionInShaderCoordinates);
      Math::Matrix3 scale = Matrix3::Scale(Matrix3::IDENTITY, sizeInShaderCoordinates);
      
      
      Math::Matrix3 model = translate * scale;
      shader->PushFloat("strokeWidth", rect.strokeWidth);
      shader->PushInt("textureIndex", rect.textureIndex);
      shader->PushVector2("arcSize", rect.arcSize);
      shader->PushVector4("fillColor", rect.fill.color);
      shader->PushVector4("strokeColor", rect.stroke.color);
      shader->PushMatrix3("model", model);
      RenderCommand::DrawIndexed(6, 1, 0, 0, 0);
      
    }
  }
  
  void RectRenderer::Reset()
  {
    //verts.clear();
    rectData.clear();
    currentVertexOffset=0;
  }
}