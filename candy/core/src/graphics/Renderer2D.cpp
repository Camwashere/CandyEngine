#include <candy/graphics/Renderer2D.hpp>
#include <candy/math/Vector.hpp>
#include <candy/math/Matrix.hpp>
#include <candy/graphics/shader/Shader.hpp>
#include <candy/graphics/VertexArray.hpp>
#include <candy/graphics/RenderCommand.hpp>
#include <candy/graphics/Renderer.hpp>
#include <candy/graphics/Vulkan.hpp>
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
    SharedPtr<Texture> whiteTexture;
    
    SharedPtr<Shader> selectionShader;
    
    std::vector<int> entities;
    
    std::vector<Matrix4> transforms;
    uint32_t quadIndexCount = 0;
    QuadVertex* quadVertexBufferBase = nullptr;
    QuadVertex* quadVertexBufferPtr = nullptr;
    
    std::array<SharedPtr<Texture>, maxTextureSlots> textureSlots;
    uint32_t textureSlotIndex = 1; // 0 = white texture
    
    Vector4 quadVertexPositions[4];
  };
  
  static RenderData2D data;
  void Renderer2D::Init()
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
    
    SharedPtr<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, RenderData2D::maxIndices);
    data.quadVertexArray->SetIndexBuffer(quadIB);
    delete[] quadIndices;
    
    
    
    data.whiteTexture = Texture::Create(TextureSpecification());
    uint32_t whiteTextureData = 0xffffffff;
    data.whiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));
    
    data.textureSlots[0] = data.whiteTexture;
    
    data.quadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
    data.quadVertexPositions[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
    data.quadVertexPositions[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
    data.quadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
    
    
    
  }
  void Renderer2D::StartBatch()
  {
    data.quadIndexCount = 0;
    data.quadVertexBufferPtr = data.quadVertexBufferBase;
    data.transforms.clear();
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
  void Renderer2D::DrawQuad(const Math::Vector3& position, const Math::Vector2& size, const Math::Vector4& color)
  {
    Matrix4 transform = Matrix4::Translate(Matrix4::IDENTITY, position)
                          * Matrix4::Scale(Matrix4::IDENTITY, { size.x, size.y, 1.0f });
    
    DrawQuad(transform, color);
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
  
  Renderer2D::Stats Renderer2D::GetStats()
  {
    return data.stats;
  }
}