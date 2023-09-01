#include <candy/graphics/Renderer2D.hpp>
#include <candy/math/Vector.hpp>
#include <candy/math/Matrix.hpp>
#include <candy/graphics/shader/Shader.hpp>
#include <candy/graphics/VertexArray.hpp>
#include <candy/graphics/RenderCommand.hpp>
#include <candy/graphics/Renderer.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <candy/ecs/BaseComponents.hpp>
namespace Candy::Graphics
{
  using namespace Math;
  struct QuadVertex
  {
    Vector3 position;
    Vector4 color;
    Vector2 uv;
    float textureIndex;
    float tilingFactor;
    int entityID=-1;
  };
  struct CircleVertex
  {
    Vector3 position;
    Vector4 color;
    Vector2 uv;
    float thickness;
    float fade;
    int entityID=-1;
    
    
  };
  
  struct LineVertex
  {
    Vector3 position;
    Vector4 color;
    
    // Editor-only
    int entityID;
  };
  
  
  struct RenderData2D
  {
    static const uint32_t maxQuads = 20000;
    static const uint32_t maxVertices = maxQuads * 4;
    static const uint32_t maxIndices = maxQuads * 6;
    static const uint32_t maxTextureSlots = 32; // TODO: RenderCaps
    
    Renderer2D::Stats stats{};
    SharedPtr<Shader> quadShader;
    SharedPtr<VertexArray> quadVertexArray;
    SharedPtr<VertexBuffer> quadVertexBuffer;
    SharedPtr<IndexBuffer> quadIB;
    SharedPtr<Texture> whiteTexture;
    
    SharedPtr<Shader> circleShader;
    SharedPtr<VertexArray> circleVertexArray;
    SharedPtr<VertexBuffer> circleVertexBuffer;
    //SharedPtr<IndexBuffer> circleIB;
    
    SharedPtr<VertexArray> lineVertexArray;
    SharedPtr<VertexBuffer> lineVertexBuffer;
    SharedPtr<Shader> lineShader;
    
    SharedPtr<Shader> selectionShader;
    
    
    uint32_t quadIndexCount = 0;
    QuadVertex* quadVertexBufferBase = nullptr;
    QuadVertex* quadVertexBufferPtr = nullptr;
    
    uint32_t circleIndexCount = 0;
    CircleVertex* circleVertexBufferBase = nullptr;
    CircleVertex* circleVertexBufferPtr = nullptr;
    
    uint32_t lineVertexCount = 0;
    LineVertex* lineVertexBufferBase = nullptr;
    LineVertex* lineVertexBufferPtr = nullptr;
    
    float lineWidth = 2.0f;
    
    std::array<SharedPtr<Texture>, maxTextureSlots> textureSlots;
    uint32_t textureSlotIndex = 1; // 0 = white texture
    
    Vector3 quadVertexPositions[4];
    Vector2 circleTexCoords[4];
  };
  
  static RenderData2D data;
  void Renderer2D::Init()
  {
    InitQuads();
    InitCircles();
    InitLines();
    InitTextures();
    
    
    
    
    
    
    
    
    
    
  }
  
  void Renderer2D::InitQuads()
  {
    data.quadShader=Shader::Create("assets/shaders/renderer2D/Quad.glsl", Renderer::GetOverlayPassIndex(), false);
    data.selectionShader = Shader::Create("assets/shaders/renderer2D/SelectionOverlay.glsl", Renderer::GetSelectionPassIndex(), false);
    data.quadVertexArray=VertexArray::Create();
    data.quadVertexBuffer=VertexBuffer::Create(data.quadShader->GetBufferLayout(), RenderData2D::maxVertices);
    
    data.quadVertexArray->AddVertexBuffer(data.quadVertexBuffer);
    
    data.quadVertexBufferBase = new QuadVertex[RenderData2D::maxVertices];
    
    uint32_t* quadIndices = new uint32_t[RenderData2D::maxIndices];
    
    uint32_t offset = 0;
    for (uint32_t i = 0; i<RenderData2D::maxIndices; i += 6)
    {
      quadIndices[i + 0] = offset + 0;
      quadIndices[i + 1] = offset + 1;
      quadIndices[i + 2] = offset + 2;
      
      quadIndices[i + 3] = offset + 2;
      quadIndices[i + 4] = offset + 3;
      quadIndices[i + 5] = offset + 0;
      
      offset += 4;
    }
    
    data.quadIB = IndexBuffer::Create(quadIndices, RenderData2D::maxIndices);
    data.quadVertexArray->SetIndexBuffer(data.quadIB);
    delete[] quadIndices;
    
    data.quadVertexPositions[0] = { -0.5f, -0.5f, 0.0f};
    data.quadVertexPositions[1] = {  0.5f, -0.5f, 0.0f};
    data.quadVertexPositions[2] = {  0.5f,  0.5f, 0.0f};
    data.quadVertexPositions[3] = { -0.5f,  0.5f, 0.0f};
  }
  void Renderer2D::InitCircles()
  {
    // Circles
    data.circleShader = Shader::Create("assets/shaders/renderer2D/Circle.glsl", Renderer::GetOverlayPassIndex(), false);
    data.circleVertexArray = VertexArray::Create();
    data.circleVertexBuffer=VertexBuffer::Create(data.circleShader->GetBufferLayout(), RenderData2D::maxVertices);
    data.circleVertexArray->AddVertexBuffer(data.circleVertexBuffer);
    
    data.circleVertexBufferBase = new CircleVertex[RenderData2D::maxVertices];
    /*uint32_t* quadIndices = new uint32_t[RenderData2D::maxIndices];
    
    uint32_t offset = 0;
    for (uint32_t i = 0; i<RenderData2D::maxIndices; i += 6)
    {
      quadIndices[i + 0] = offset + 0;
      quadIndices[i + 1] = offset + 1;
      quadIndices[i + 2] = offset + 2;
      
      quadIndices[i + 3] = offset + 2;
      quadIndices[i + 4] = offset + 3;
      quadIndices[i + 5] = offset + 0;
      
      offset += 4;
    }*/
    
    //data.circleIB = IndexBuffer::Create(quadIndices, RenderData2D::maxIndices);
    data.circleVertexArray->SetIndexBuffer(data.quadIB);
    
    data.circleTexCoords[0] = {  0.0f,  0.0f};
    data.circleTexCoords[1] = {  1.0f,  0.0f};
    data.circleTexCoords[2] = {  1.0f,  1.0f};
    data.circleTexCoords[3] = {  0.0f,  1.0f};
    //delete[] quadIndices;
    
    
    
  }
  void Renderer2D::InitLines()
  {
    // Lines
    /*s_Data.LineVertexArray = VertexArray::Create();
    
    s_Data.LineVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(LineVertex));
    s_Data.LineVertexBuffer->SetLayout({
                                       { ShaderDataType::Float3, "a_Position" },
                                       { ShaderDataType::Float4, "a_Color"    },
                                       { ShaderDataType::Int,    "a_EntityID" }
                                       });
    s_Data.LineVertexArray->AddVertexBuffer(s_Data.LineVertexBuffer);
    s_Data.LineVertexBufferBase = new LineVertex[s_Data.MaxVertices];*/
  }
  
  void Renderer2D::InitTextures()
  {
    data.whiteTexture = Texture::Create(TextureSpecification());
    uint32_t whiteTextureData = 0xffffffff;
    data.whiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));
    
    data.textureSlots[0] = data.whiteTexture;
  }
  void Renderer2D::StartBatch()
  {
    data.quadIndexCount = 0;
    data.quadVertexBufferPtr = data.quadVertexBufferBase;
    
    data.circleIndexCount = 0;
    data.circleVertexBufferPtr = data.circleVertexBufferBase;
    
    data.lineVertexCount = 0;
    data.lineVertexBufferPtr = data.lineVertexBufferBase;
    
    
    ResetStats();
    data.textureSlotIndex = 1;
    
    
    
  }
  void Renderer2D::ResetStats()
  {
    data.stats.drawCalls = 0;
    data.stats.quadCount = 0;
    data.stats.vertexCount = 0;
    data.stats.indexCount = 0;
  }
  void Renderer2D::NextBatch()
  {
    Flush();
    StartBatch();
  }
  void Renderer2D::Flush()
  {
    if (data.quadIndexCount)
    {
      data.quadShader->Bind();
      
      uint32_t dataSize = (uint32_t)((uint8_t*)data.quadVertexBufferPtr - (uint8_t*)data.quadVertexBufferBase);
      data.quadVertexBuffer->SetData(data.quadVertexBufferBase, dataSize);
      
      
      // Bind textures
      std::vector<VkDescriptorImageInfo> imageInfos{};
      for (uint32_t i=0; i<data.textureSlotIndex; i++)
      {
        CANDY_CORE_ASSERT(data.textureSlots[i] != nullptr);
        
        VkDescriptorImageInfo imageInfo = data.textureSlots[i]->GetDescriptorImageInfo();
        imageInfos.push_back(imageInfo);
      }
      for (uint32_t i=data.textureSlotIndex; i<RenderData2D::maxTextureSlots; i++)
      {
        VkDescriptorImageInfo imageInfo = data.whiteTexture->GetDescriptorImageInfo();
        imageInfos.push_back(imageInfo);
      }
      DescriptorBuilder builder = DescriptorBuilder::Begin();
      builder.AddImageArrayWrite(0, imageInfos, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, MATERIAL_SET);
      builder.Write();
      data.quadShader->Commit();
      data.quadVertexArray->Bind();
      
      RenderCommand::DrawIndexed(data.quadVertexArray);
      data.stats.drawCalls++;
    }
    
    if (data.circleIndexCount)
    {
      data.circleShader->Bind();
      uint32_t dataSize = (uint32_t)((uint8_t*)data.circleVertexBufferPtr - (uint8_t*)data.circleVertexBufferBase);
      
      data.circleVertexBuffer->SetData(data.circleVertexBufferBase, dataSize);
      
      
      //data.circleShader->Commit();
      data.circleVertexArray->Bind();
      RenderCommand::DrawIndexed(data.circleVertexArray);
      data.stats.drawCalls++;
    }
    
    if (data.lineVertexCount)
    {
      /*uint32_t dataSize = (uint32_t)((uint8_t*)data.LineVertexBufferPtr - (uint8_t*)data.LineVertexBufferBase);
      data.LineVertexBuffer->SetData(data.LineVertexBufferBase, dataSize);
      
      data.LineShader->Bind();
      RenderCommand::SetLineWidth(data.LineWidth);
      RenderCommand::DrawLines(data.LineVertexArray, data.LineVertexCount);
      data.Stats.DrawCalls++;*/
    }
    
  }
  void Renderer2D::RenderSelectionBuffer()
  {
    data.selectionShader->Bind();
    data.selectionShader->Commit();
    
    data.quadVertexArray->Bind();
    RenderCommand::DrawIndexed(data.quadVertexArray);
    
  
  }
  void Renderer2D::BeginScene()
  {
    Renderer::BeginOverlayPass();
    
    
    StartBatch();
    
  }
  void Renderer2D::EndScene()
  {
    Flush();
  
  }
  
  void Renderer2D::DrawQuad(const Math::Vector2& position, const Math::Vector2& size, const Math::Vector4& color)
  {
    DrawQuad({ position.x, position.y, 0.0f }, size, color);
  }
  void Renderer2D::DrawQuad(const Math::Vector3& position, const Math::Vector2& size, const Math::Vector4& color, int entityID)
  {
    Matrix4 transform = Matrix4::Translate(Matrix4::IDENTITY, position)
                          * Matrix4::Scale(Matrix4::IDENTITY, { size.x, size.y, 1.0f });
    
    DrawQuad(transform, color, entityID);
  }
  
  
  void Renderer2D::DrawQuad(const Math::Matrix4& transform, const Math::Vector4& color, int entityID)
  {
    constexpr size_t quadVertexCount = 4;
    const float textureIndex = 0.0f; // White Texture
    constexpr Vector2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
    const float tilingFactor = 1.0f;
    
    if (data.quadIndexCount >= RenderData2D::maxIndices)
      NextBatch();
    
    for (size_t i = 0; i < quadVertexCount; i++)
    {
      data.quadVertexBufferPtr->position = transform * data.quadVertexPositions[i];
      data.quadVertexBufferPtr->color = color;
      
      data.quadVertexBufferPtr->entityID = entityID;
      data.quadVertexBufferPtr->uv = textureCoords[i];
      data.quadVertexBufferPtr->textureIndex = textureIndex;
      data.quadVertexBufferPtr->tilingFactor = tilingFactor;
      data.quadVertexBufferPtr->entityID = entityID;
      data.quadVertexBufferPtr++;
    }
    
    data.quadIndexCount += 6;
    
    data.stats.quadCount++;
  }
  
  void Renderer2D::DrawQuad(const Math::Matrix4& transform, const SharedPtr<Texture>& texture, float tilingFactor, const Math::Vector4& tintColor, int entityID)
  {
    CANDY_PROFILE_FUNCTION();
    
    constexpr size_t quadVertexCount = 4;
    constexpr Math::Vector2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
    
    if (data.quadIndexCount >= RenderData2D::maxIndices)
      NextBatch();
    
    float textureIndex = 0.0f;
    for (uint32_t i = 1; i < data.textureSlotIndex; i++)
    {
      if (*data.textureSlots[i] == *texture)
      {
        textureIndex = (float)i;
        break;
      }
    }
    
    if (textureIndex == 0.0f)
    {
      if (data.textureSlotIndex >= RenderData2D::maxTextureSlots)
        NextBatch();
      
      textureIndex = (float)data.textureSlotIndex;
      data.textureSlots[data.textureSlotIndex] = texture;
      data.textureSlotIndex++;
    }
    
    for (size_t i = 0; i < quadVertexCount; i++)
    {
      data.quadVertexBufferPtr->position = transform * data.quadVertexPositions[i];
      data.quadVertexBufferPtr->color = tintColor;
      data.quadVertexBufferPtr->uv = textureCoords[i];
      data.quadVertexBufferPtr->textureIndex = textureIndex;
      data.quadVertexBufferPtr->tilingFactor = tilingFactor;
      data.quadVertexBufferPtr->entityID = entityID;
      data.quadVertexBufferPtr++;
    }
    
    data.quadIndexCount += 6;
    
    data.stats.quadCount++;
  }
  void Renderer2D::DrawRotatedQuad(const Math::Vector2& position, const Math::Vector2& size, float rotation, const Math::Vector4& color)
  {
    DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, color);
  }
  void Renderer2D::DrawRotatedQuad(const Math::Vector3& position, const Math::Vector2& size, float rotation, const Math::Vector4& color)
  {
    CANDY_PROFILE_FUNCTION();
    
    Matrix4 transform = Matrix4::Translate(Matrix4::IDENTITY, position)
                          * Matrix4::Rotate(Matrix4::IDENTITY, Math::ToRadians(rotation), { 0.0f, 0.0f, 1.0f })
                          * Matrix4::Scale(Matrix4::IDENTITY, { size.x, size.y, 1.0f });
    
    DrawQuad(transform, color);
  }
  void Renderer2D::DrawRotatedQuad(const Math::Vector2& position, const Math::Vector2& size, float rotation, const SharedPtr<Texture>& texture, float tilingFactor, const Math::Vector4& tintColor)
  {
    DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture, tilingFactor, tintColor);
  }
  void Renderer2D::DrawRotatedQuad(const Math::Vector3& position, const Math::Vector2& size, float rotation, const SharedPtr<Texture>& texture, float tilingFactor, const Math::Vector4& tintColor)
  {
    CANDY_PROFILE_FUNCTION();
    
    Matrix4 transform = Matrix4::Translate(Matrix4::IDENTITY, position)
                          * Matrix4::Rotate(Matrix4::IDENTITY, Math::ToRadians(rotation), { 0.0f, 0.0f, 1.0f })
                          * Matrix4::Scale(Matrix4::IDENTITY, { size.x, size.y, 1.0f });
    
    DrawQuad(transform, texture, tilingFactor, tintColor);
  }
  
  void Renderer2D::DrawCircle(const Matrix4& transform, const Vector4& color, float thickness, float fade, int entityID)
  {
    CANDY_PROFILE_FUNCTION();
    
    // TODO: implement for circles
    // if (data.QuadIndexCount >= Renderer2DData::MaxIndices)
    // 	NextBatch();
    float thick = thickness;
    float fad = fade;
    float total = (thickness+fade);
    thick /= total;
    fad /= total;
    /*if (total >= 1.0f)
    {
      thick /= total;
      fad /= total;
    }*/
    thick *= 0.5f;
    fad *= 0.5f;
    for (size_t i = 0; i < 4; i++)
    {
      data.circleVertexBufferPtr->position = transform*data.quadVertexPositions[i];
      data.circleVertexBufferPtr->color = color;
      data.circleVertexBufferPtr->uv = data.circleTexCoords[i];
      data.circleVertexBufferPtr->thickness = thick;
      data.circleVertexBufferPtr->fade = fad;
      data.circleVertexBufferPtr->entityID = entityID;
      data.circleVertexBufferPtr++;
    }
    
    data.circleIndexCount += 6;
    
    data.stats.quadCount++;
  }
  
  void Renderer2D::DrawLine(const Vector3& p0, Vector3& p1, const Vector4& color, int entityID)
  {
    data.lineVertexBufferPtr->position = p0;
    data.lineVertexBufferPtr->color = color;
    data.lineVertexBufferPtr->entityID = entityID;
    data.lineVertexBufferPtr++;
    
    data.lineVertexBufferPtr->position = p1;
    data.lineVertexBufferPtr->color = color;
    data.lineVertexBufferPtr->entityID = entityID;
    data.lineVertexBufferPtr++;
    
    data.lineVertexCount += 2;
  }
  
  void Renderer2D::DrawRect(const Vector3& position, const Vector2& size, const Vector4& color, int entityID)
  {
    Vector3 p0 = Vector3(position.x - size.x * 0.5f, position.y - size.y * 0.5f, position.z);
    Vector3 p1 = Vector3(position.x + size.x * 0.5f, position.y - size.y * 0.5f, position.z);
    Vector3 p2 = Vector3(position.x + size.x * 0.5f, position.y + size.y * 0.5f, position.z);
    Vector3 p3 = Vector3(position.x - size.x * 0.5f, position.y + size.y * 0.5f, position.z);
    
    DrawLine(p0, p1, color, entityID);
    DrawLine(p1, p2, color, entityID);
    DrawLine(p2, p3, color, entityID);
    DrawLine(p3, p0, color, entityID);
  }
  
  void Renderer2D::DrawRect(const Matrix4& transform, const Vector4& color, int entityID)
  {
    Vector3 lineVertices[4];
    for (size_t i = 0; i < 4; i++)
      lineVertices[i] = transform * data.quadVertexPositions[i];
    
    DrawLine(lineVertices[0], lineVertices[1], color, entityID);
    DrawLine(lineVertices[1], lineVertices[2], color, entityID);
    DrawLine(lineVertices[2], lineVertices[3], color, entityID);
    DrawLine(lineVertices[3], lineVertices[0], color, entityID);
  }
  
  
  void Renderer2D::DrawSprite(const Math::Matrix4& transform, ECS::SpriteRendererComponent& src, int entityID)
  {
    if (src.texture)
      DrawQuad(transform, src.texture, src.tilingFactor, src.color, entityID);
    else
      DrawQuad(transform, src.color, entityID);
  }
  
  
  float Renderer2D::GetLineWidth()
  {
    return data.lineWidth;
  }
  
  void Renderer2D::SetLineWidth(float width)
  {
    data.lineWidth = width;
  }
  Renderer2D::Stats Renderer2D::GetStats()
  {
    return data.stats;
  }
}