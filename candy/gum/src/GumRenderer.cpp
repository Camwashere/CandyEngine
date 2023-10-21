#include <gum/GumRenderer.hpp>
#include <candy/graphics/shader/Shader.hpp>
#include <candy/graphics/shader/ShaderLibrary.hpp>
#include <candy/math/Vector.hpp>
#include <candy/math/Matrix.hpp>
#include <candy/graphics/shader/Shader.hpp>
#include <candy/graphics/VertexArray.hpp>
#include <candy/graphics/RenderCommand.hpp>
#include <candy/graphics/Renderer.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <candy/graphics/font/Font.hpp>
#include <candy/graphics/font/MSDFData.hpp>
#include <candy/graphics/GraphicsContext.hpp>
#include <gum/GumInstance.hpp>
namespace Candy::Gum
{
  using namespace Graphics;
  using namespace Math;
  static constexpr Vector2 rectVertPositions[4] ={
  {-0.5f, -0.5f},
  {-0.5f, 0.5f},
  {0.5f, 0.5f},
  {0.5f, -0.5f} };
  
  static constexpr uint32_t rectIndices[6] = {0, 2, 1, 0, 3, 2};
  
  struct RectData
  {
    ShapeVertex outerVertices[4];
    ShapeVertex innerVertices[4];
    int32_t vertexOffsetOuter=0;
    int32_t vertexOffsetInner=0;
    Math::Vector2 positionInParent;
    Math::Vector2 size;
    Matrix3 transform;
    
    RectData(const Matrix3& model, const Color& fillColor, const Color& strokeColor, int32_t& currentVertexOffset)
    {
      transform = model;
      vertexOffsetOuter = currentVertexOffset;
      for (int i=0; i<4; i++)
      {
        outerVertices[i].position = rectVertPositions[i];
        outerVertices[i].color = strokeColor;
      }
      currentVertexOffset += 4;
      vertexOffsetInner = currentVertexOffset;
      for (int i=0; i<4; i++)
      {
        innerVertices[i].position = rectVertPositions[i] * 0.9f;
        innerVertices[i].color = fillColor;
      }
      currentVertexOffset += 4;
      
    }
    
  };
  struct GumRenderData
  {
    static const uint32_t maxQuads = 20000;
    static const uint32_t maxVertices = maxQuads * 4;
    static const uint32_t maxIndices = maxQuads * 6;
    static const uint32_t maxTextureSlots = 32; // TODO: RenderCaps
    
    SceneGraph* currentScene=nullptr;
    int currentVertexOffset=0;
    SharedPtr<Shader> rectShader;
    SharedPtr<VertexArray> rectVertexArray;
    SharedPtr<VertexBuffer> rectVertexBuffer;
    SharedPtr<IndexBuffer> rectIndexBuffer;
    SharedPtr<Texture> whiteTexture;
    std::vector<RectData> rectData;
    std::vector<ShapeVertex> rectVerts;
    std::vector<uint32_t> rectIndices;
    
  };
  static GumRenderData data;
  
  void GumRenderer::Init()
  {
    CANDY_CORE_INFO("Initializing GumRenderer");
    ShaderSettings shaderSettings;
    
    shaderSettings.sourceFilePath = ShaderLibrary::GetInternalSourceDirectory() / "gum/Rect.glsl";
    auto& profileSettings = shaderSettings.profileSettings;
    profileSettings.renderPassIndex = Renderer::GetGumPassIndex();
    profileSettings.SetDepthStencil(false);
    profileSettings.AddBlendAttachment(true);
    
    data.rectShader=Shader::Create(shaderSettings);
    
    data.rectVertexArray=VertexArray::Create();
    data.rectVertexBuffer=VertexBuffer::Create(data.rectShader->GetBufferLayout(), GumRenderData::maxVertices);
    data.rectVertexArray->AddVertexBuffer(data.rectVertexBuffer);
    
    
    data.rectIndexBuffer = IndexBuffer::Create(GumRenderData::maxIndices);
    data.rectVertexArray->SetIndexBuffer(data.rectIndexBuffer);
    for (int i=0; i<6; i++)
    {
      data.rectIndices.push_back(rectIndices[i]);
    }
    
    
    
    CANDY_CORE_INFO("Initialized GumRenderer");
  }
  
  
  void GumRenderer::Flush()
  {
    if (data.currentScene == nullptr)
    {
      return;
    }
    //CANDY_CORE_INFO("Flushing gum render data");
    data.rectVertexBuffer->SetData(data.rectVerts.data(), sizeof(ShapeVertex)*data.rectVerts.size());
    data.rectIndexBuffer->SetData(data.rectIndices.data(), data.rectIndices.size());
    data.rectShader->Bind();
    data.rectVertexArray->Bind();
    
    Math::Vector2 sceneSize = data.currentScene->GetSceneSize();
    Math::Vector2 sceneSizeHalf = sceneSize * 0.5f;
    
    
    //Math::Matrix3 model = Math::Matrix3::IDENTITY;
    
    for (int i=0; i<data.rectData.size(); i++)
    {
      // Convert rect size from framebuffer coordinates to shader coordinates
      Vector2 sizeInShaderCoordinates = (data.rectData[i].size / sceneSize);
      
      // Adjust the position so that an object's lower left corner corresponds to positionInParent
      Vector2 lowerLeftOriginPosition = data.rectData[i].positionInParent / sceneSize;
      // Adjust the position so that object's bottom left corner corresponds to position
      Vector2 bottomLeftOriginPosition = ((data.rectData[i].positionInParent * 2.0f) + data.rectData[i].size) / sceneSize;
      
      // Adjust the position to change the origin to the center
      Vector2 centrifiedPosition = ((data.rectData[i].positionInParent + sizeInShaderCoordinates * 0.5f) / sceneSizeHalf) - Vector2(1.0f);
      
      CANDY_CORE_INFO("Size in shader coords: {0}, centrified position: {1}, bottom-left position: {2}", sizeInShaderCoordinates, centrifiedPosition, bottomLeftOriginPosition);
      
      //Math::Matrix3 translate = Matrix3::Translate(Matrix3::IDENTITY, centrifiedPosition);
      Math::Matrix3 translate = Matrix3::Translate(Matrix3::IDENTITY, lowerLeftOriginPosition * 2.0f - Vector2(1.0f));
      Math::Matrix3 scale = Matrix3::Scale(Matrix3::IDENTITY, sizeInShaderCoordinates);
      
      
      //Math::Matrix3 model = Matrix3::Translate(Matrix3::IDENTITY, data.rectData[i].positionInParent);
      Math::Matrix3 model = translate * scale;
      //model[1,1] *= -1.0f;
      data.rectShader->PushMatrix3("model", model);
      RenderCommand::DrawIndexed(6, 1, 0, data.rectData[i].vertexOffsetOuter, 0);
      data.rectShader->PushMatrix3("model", model);
      RenderCommand::DrawIndexed(6, 1, 0, data.rectData[i].vertexOffsetInner, 0);
    }
    
  }
  void GumRenderer::BeginScene(SceneGraph& sceneGraph)
  {
    //CANDY_CORE_INFO("Beginning gum scene");
    data.rectVerts.clear();
    //data.rectIndices.clear();
    data.rectData.clear();
    data.currentVertexOffset=0;
    data.currentScene = &sceneGraph;
  }
  void GumRenderer::EndScene()
  {
    Flush();
    //CANDY_CORE_INFO("Ended gum scene");
  }
  
  
  void GumRenderer::SubmitRectangle(const Math::Matrix3& transform, const Rectangle& rectangle, int depthIndex)
  {
    //data.model = transform;
   /* for (int i=0; i<4; i++)
    {
      ShapeVertex v{};
      v.position = rectVertPositions[i];
      v.color = rectangle.GetFillColor();
      data.rectVerts.push_back(v);
    }
    for (int i=0; i<6; i++)
    {
      data.rectIndices.push_back(rectIndices[i]);
    }*/
    RectData rect(transform, rectangle.GetFillColor(), rectangle.GetStrokeColor(), data.currentVertexOffset);
    rect.positionInParent = rectangle.GetPosition();
    rect.size = rectangle.GetSize();
    //data.rectVerts.insert(data.rectVerts.end(), rect.outerVertices, rect.outerVertices+4);
    //data.rectVerts.insert(data.rectVerts.end(), rect.innerVertices, rect.innerVertices+4);
    for (int i=0; i<4; i++)
    {
      data.rectVerts.push_back(rect.outerVertices[i]);
    }
    for (int i=0; i<4; i++)
    {
      data.rectVerts.push_back(rect.innerVertices[i]);
    }
    /*for (int i=0; i<6; i++)
    {
      data.rectIndices.push_back(rectIndices[i]);
    }
    for (int i=0; i<6; i++)
    {
      data.rectIndices.push_back(rectIndices[i]);
    }*/
    data.rectData.push_back(rect);
  }
  
}