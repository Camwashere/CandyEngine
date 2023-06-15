#include "Renderer2D.hpp"
#include <Candy/Graphics.hpp>
namespace Candy
{
    using namespace Math;
    namespace Graphics{
    struct QuadVertex
    {
        Math::Vector3 position;
        Math::Vector4 color;
        Math::Vector2 texCoord;
        float texIndex;
        float tilingFactor;
        
        // Editor-only
        int EntityID;
    };
    
    struct CircleVertex
    {
        Math::Vector3 worldPosition;
        Math::Vector3 localPosition;
        Math::Vector4 color;
        float thickness;
        float fade;
        
        // Editor-only
        int entityID;
    };
    
    struct LineVertex
    {
        Math::Vector3 position;
        Math::Vector4 color;
        
        // Editor-only
        int entityID;
    };
    
    struct Renderer2DData
    {
        static const uint32_t MAX_QUADS = 20000;
        static const uint32_t MAX_VERTICES = MAX_QUADS * 4;
        static const uint32_t MAX_INDICES = MAX_QUADS * 6;
        static const uint32_t MAX_TEXTURE_SLOTS = 32; // TODO: RenderCaps
        
        SharedPtr<VertexArray> quadVertexArray;
        SharedPtr<VertexBuffer> quadVertexBuffer;
        SharedPtr<Shader> quadShader;
        SharedPtr<Texture> whiteTexture;
        
        SharedPtr<VertexArray> circleVertexArray;
        SharedPtr<VertexBuffer> circleVertexBuffer;
        SharedPtr<Shader> circleShader;
        
        SharedPtr<VertexArray> lineVertexArray;
        SharedPtr<VertexBuffer> lineVertexBuffer;
        SharedPtr<Shader> lineShader;
        
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
        
        std::array<SharedPtr<Texture>, MAX_TEXTURE_SLOTS> textureSlots;
        uint32_t textureSlotIndex = 1; // 0 = white texture
        
        Math::Vector4 quadVertexPositions[4];
        
        Renderer2D::Statistics stats;
        
        struct CameraData
        {
            Math::Matrix4 viewProjection;
        };
        CameraData cameraBuffer;
        SharedPtr<UniformBuffer> cameraUniformBuffer;
    };
    
    static Renderer2DData rendererData;
    
    void Renderer2D::Init()
    {
       
        
        rendererData.quadVertexArray = VertexArray::Create();
        
        rendererData.quadVertexBuffer = VertexBuffer::Create(Renderer2DData::MAX_VERTICES * sizeof(QuadVertex));
        rendererData.quadVertexBuffer->SetLayout({
                                                   { ShaderDataType::Float3, "a_Position"     },
                                                   { ShaderDataType::Float4, "a_Color"        },
                                                   { ShaderDataType::Float2, "a_TexCoord"     },
                                                   { ShaderDataType::Float,  "a_TexIndex"     },
                                                   { ShaderDataType::Float,  "a_TilingFactor" },
                                                   { ShaderDataType::Int,    "a_EntityID"     }
                                           });
        rendererData.quadVertexArray->AddVertexBuffer(rendererData.quadVertexBuffer);
        
        rendererData.quadVertexBufferBase = new QuadVertex[Renderer2DData::MAX_VERTICES];
        
        uint32_t* quadIndices = new uint32_t[Renderer2DData::MAX_INDICES];
        
        
        
        uint32_t offset = 0;
        for (uint32_t i = 0; i < Renderer2DData::MAX_INDICES; i += 6)
        {
            quadIndices[i + 0] = offset + 0;
            quadIndices[i + 1] = offset + 1;
            quadIndices[i + 2] = offset + 2;
            
            quadIndices[i + 3] = offset + 2;
            quadIndices[i + 4] = offset + 3;
            quadIndices[i + 5] = offset + 0;
            
            offset += 4;
        }
        
        
        
        SharedPtr<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, Renderer2DData::MAX_INDICES);
        rendererData.quadVertexArray->SetIndexBuffer(quadIB);
        delete[] quadIndices;
        
        
        // circles
        rendererData.circleVertexArray = VertexArray::Create();
        
        rendererData.circleVertexBuffer = VertexBuffer::Create(Renderer2DData::MAX_VERTICES * sizeof(CircleVertex));
        rendererData.circleVertexBuffer->SetLayout({
                                                     { ShaderDataType::Float3, "a_WorldPosition" },
                                                     { ShaderDataType::Float3, "a_LocalPosition" },
                                                     { ShaderDataType::Float4, "a_Color"         },
                                                     { ShaderDataType::Float,  "a_Thickness"     },
                                                     { ShaderDataType::Float,  "a_Fade"          },
                                                     { ShaderDataType::Int,    "a_EntityID"      }
                                             });
        rendererData.circleVertexArray->AddVertexBuffer(rendererData.circleVertexBuffer);
        rendererData.circleVertexArray->SetIndexBuffer(quadIB); // Use quad IB
        rendererData.circleVertexBufferBase = new CircleVertex[Renderer2DData::MAX_VERTICES];
        
        
        
        // lines
        rendererData.lineVertexArray = VertexArray::Create();
        
        rendererData.lineVertexBuffer = VertexBuffer::Create(Renderer2DData::MAX_VERTICES * sizeof(LineVertex));
        rendererData.lineVertexBuffer->SetLayout({
                                                   { ShaderDataType::Float3, "a_Position" },
                                                   { ShaderDataType::Float4, "a_Color"    },
                                                   { ShaderDataType::Int,    "a_EntityID" }
                                           });
        rendererData.lineVertexArray->AddVertexBuffer(rendererData.lineVertexBuffer);
        rendererData.lineVertexBufferBase = new LineVertex[Renderer2DData::MAX_VERTICES];
        
        
        
        rendererData.whiteTexture = Texture::Create(TextureSpecification());
        uint32_t whiteTextureData = 0xffffffff;
        
        rendererData.whiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));
        
        
        
        uint32_t samplers[Renderer2DData::MAX_TEXTURE_SLOTS];
        for (uint32_t i = 0; i < Renderer2DData::MAX_TEXTURE_SLOTS; i++)
        {
            samplers[i] = i;
        }
        
        
        
        rendererData.quadShader = Shader::Create("assets/shaders/Renderer2D_quad.glsl");
        rendererData.circleShader = Shader::Create("assets/shaders/Renderer2D_circle.glsl");
        rendererData.lineShader = Shader::Create("assets/shaders/Renderer2D_line.glsl");
        
        // Set first texture slot to 0
        rendererData.textureSlots[0] = rendererData.whiteTexture;
        
        rendererData.quadVertexPositions[0] = {-0.5f, -0.5f, 0.0f, 1.0f };
        rendererData.quadVertexPositions[1] = {0.5f, -0.5f, 0.0f, 1.0f };
        rendererData.quadVertexPositions[2] = {0.5f, 0.5f, 0.0f, 1.0f };
        rendererData.quadVertexPositions[3] = {-0.5f, 0.5f, 0.0f, 1.0f };
        
        rendererData.cameraUniformBuffer = UniformBuffer::Create(sizeof(Renderer2DData::CameraData), 0);
    }
    
    void Renderer2D::Shutdown()
    {
        
        
        delete[] rendererData.quadVertexBufferBase;
    }
    
    void Renderer2D::BeginScene(const OrthographicCamera& camera)
    {
        
        
        rendererData.cameraBuffer.viewProjection = camera.GetViewProjectionMatrix();
        rendererData.cameraUniformBuffer->SetData(&rendererData.cameraBuffer, sizeof(Renderer2DData::CameraData));
        
        StartBatch();
    }
    
    void Renderer2D::BeginScene(const Camera& camera, const Math::Matrix4& transform)
    {
        
        
        rendererData.cameraBuffer.viewProjection = camera.GetProjectionMatrix() * Matrix4::Invert(transform);
        rendererData.cameraUniformBuffer->SetData(&rendererData.cameraBuffer, sizeof(Renderer2DData::CameraData));
        
        StartBatch();
    }
    
    void Renderer2D::BeginScene(const EditorCamera& camera)
    {
        
        
        rendererData.cameraBuffer.viewProjection = camera.GetViewProjectionMatrix();
        
        rendererData.cameraUniformBuffer->SetData(&rendererData.cameraBuffer, sizeof(Renderer2DData::CameraData));
        StartBatch();
    }
    
    void Renderer2D::EndScene()
    {
        
        
        Flush();
    }
    
    void Renderer2D::StartBatch()
    {
        rendererData.quadIndexCount = 0;
        rendererData.quadVertexBufferPtr = rendererData.quadVertexBufferBase;
        
        rendererData.circleIndexCount = 0;
        rendererData.circleVertexBufferPtr = rendererData.circleVertexBufferBase;
        
        rendererData.lineVertexCount = 0;
        rendererData.lineVertexBufferPtr = rendererData.lineVertexBufferBase;
        
        rendererData.textureSlotIndex = 1;
    }
    
    void Renderer2D::Flush()
    {
        if (rendererData.quadIndexCount)
        {
            uint32_t dataSize = (uint32_t)((uint8_t*)rendererData.quadVertexBufferPtr - (uint8_t*)rendererData.quadVertexBufferBase);
            rendererData.quadVertexBuffer->SetData(rendererData.quadVertexBufferBase, dataSize);
            
            // Bind textures
            for (uint32_t i = 0; i < rendererData.textureSlotIndex; i++)
                rendererData.textureSlots[i]->Bind(i);
            
            rendererData.quadShader->Bind();
            RenderCommand::DrawIndexed(rendererData.quadVertexArray, rendererData.quadIndexCount);
            rendererData.stats.drawCalls++;
        }
        
        if (rendererData.circleIndexCount)
        {
            uint32_t dataSize = (uint32_t)((uint8_t*)rendererData.circleVertexBufferPtr - (uint8_t*)rendererData.circleVertexBufferBase);
            rendererData.circleVertexBuffer->SetData(rendererData.circleVertexBufferBase, dataSize);
            
            rendererData.circleShader->Bind();
            RenderCommand::DrawIndexed(rendererData.circleVertexArray, rendererData.circleIndexCount);
            rendererData.stats.drawCalls++;
        }
        
        if (rendererData.lineVertexCount)
        {
            uint32_t dataSize = (uint32_t)((uint8_t*)rendererData.lineVertexBufferPtr - (uint8_t*)rendererData.lineVertexBufferBase);
            rendererData.lineVertexBuffer->SetData(rendererData.lineVertexBufferBase, dataSize);
            
            rendererData.lineShader->Bind();
            RenderCommand::SetLineWidth(rendererData.lineWidth);
            RenderCommand::DrawLines(rendererData.lineVertexArray, rendererData.lineVertexCount);
            rendererData.stats.drawCalls++;
        }
    }
    
    void Renderer2D::NextBatch()
    {
        Flush();
        StartBatch();
    }
    
    void Renderer2D::DrawQuad(const Math::Vector2& position, const Math::Vector2& size, const Math::Vector4& color)
    {
        DrawQuad({ position.x, position.y, 0.0f }, size, color);
    }
    
    void Renderer2D::DrawQuad(const Math::Vector3& position, const Math::Vector2& size, const Math::Vector4& color)
    {
        
        
        Math::Matrix4 transform = Matrix4::Translation(position)
                              * Matrix4::Scaled({ size.x, size.y, 1.0f });
        
        DrawQuad(transform, color);
    }
    
    void Renderer2D::DrawQuad(const Math::Vector2& position, const Math::Vector2& size, const SharedPtr<Texture>& texture, float tilingFactor, const Math::Vector4& tintColor)
    {
        DrawQuad({ position.x, position.y, 0.0f }, size, texture, tilingFactor, tintColor);
    }
    
    void Renderer2D::DrawQuad(const Math::Vector3& position, const Math::Vector2& size, const SharedPtr<Texture>& texture, float tilingFactor, const Math::Vector4& tintColor)
    {
        
        
        Math::Matrix4 transform = Matrix4::Translation(position)
                              * Matrix4::Scaled({ size.x, size.y, 1.0f });
        
        DrawQuad(transform, texture, tilingFactor, tintColor);
    }
    
    void Renderer2D::DrawQuad(const Math::Matrix4& transform, const Math::Vector4& color, int entityID)
    {
        
        
        constexpr size_t quadVertexCount = 4;
        const float textureIndex = 0.0f; // White Texture
        constexpr Math::Vector2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
        const float tilingFactor = 1.0f;
        
        if (rendererData.quadIndexCount >= Renderer2DData::MAX_INDICES)
            NextBatch();
        
        for (size_t i = 0; i < quadVertexCount; i++)
        {
            rendererData.quadVertexBufferPtr->position = transform * rendererData.quadVertexPositions[i];
            rendererData.quadVertexBufferPtr->color = color;
            rendererData.quadVertexBufferPtr->texCoord = textureCoords[i];
            rendererData.quadVertexBufferPtr->texIndex = textureIndex;
            rendererData.quadVertexBufferPtr->tilingFactor = tilingFactor;
            rendererData.quadVertexBufferPtr->EntityID = entityID;
            rendererData.quadVertexBufferPtr++;
        }
        
        rendererData.quadIndexCount += 6;
        
        rendererData.stats.quadCount++;
    }
    
    void Renderer2D::DrawQuad(const Math::Matrix4& transform, const SharedPtr<Texture>& texture, float tilingFactor, const Math::Vector4& tintColor, int entityID)
    {
        
        
        constexpr size_t quadVertexCount = 4;
        constexpr Math::Vector2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
        
        if (rendererData.quadIndexCount >= Renderer2DData::MAX_INDICES)
            NextBatch();
        
        float textureIndex = 0.0f;
        for (uint32_t i = 1; i < rendererData.textureSlotIndex; i++)
        {
            if (*rendererData.textureSlots[i] == *texture)
            {
                textureIndex = (float)i;
                break;
            }
        }
        
        if (textureIndex == 0.0f)
        {
            if (rendererData.textureSlotIndex >= Renderer2DData::MAX_TEXTURE_SLOTS)
                NextBatch();
            
            textureIndex = (float)rendererData.textureSlotIndex;
            rendererData.textureSlots[rendererData.textureSlotIndex] = texture;
            rendererData.textureSlotIndex++;
        }
        
        for (size_t i = 0; i < quadVertexCount; i++)
        {
            rendererData.quadVertexBufferPtr->position = transform * rendererData.quadVertexPositions[i];
            rendererData.quadVertexBufferPtr->color = tintColor;
            rendererData.quadVertexBufferPtr->texCoord = textureCoords[i];
            rendererData.quadVertexBufferPtr->texIndex = textureIndex;
            rendererData.quadVertexBufferPtr->tilingFactor = tilingFactor;
            rendererData.quadVertexBufferPtr->EntityID = entityID;
            rendererData.quadVertexBufferPtr++;
        }
        
        rendererData.quadIndexCount += 6;
        
        rendererData.stats.quadCount++;
    }
    
    void Renderer2D::DrawRotatedQuad(const Math::Vector2& position, const Math::Vector2& size, float rotation, const Math::Vector4& color)
    {
        DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, color);
    }
    
    void Renderer2D::DrawRotatedQuad(const Math::Vector3& position, const Math::Vector2& size, float rotation, const Math::Vector4& color)
    {
        
        
        Math::Matrix4 transform = Matrix4::Translation(position)
                              * Matrix4::Rotated(Math::ToRadians(rotation), { 0.0f, 0.0f, 1.0f })
                              * Matrix4::Scaled({ size.x, size.y, 1.0f });
        
        DrawQuad(transform, color);
    }
    
    void Renderer2D::DrawRotatedQuad(const Math::Vector2& position, const Math::Vector2& size, float rotation, const SharedPtr<Texture>& texture, float tilingFactor, const Math::Vector4& tintColor)
    {
        DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture, tilingFactor, tintColor);
    }
    
    void Renderer2D::DrawRotatedQuad(const Math::Vector3& position, const Math::Vector2& size, float rotation, const SharedPtr<Texture>& texture, float tilingFactor, const Math::Vector4& tintColor)
    {
        
        
        Math::Matrix4 transform = Matrix4::Translation(position)
                              * Matrix4::Rotated(Math::ToRadians(rotation), Vector3::forward)
                              * Matrix4::Scaled({ size.x, size.y, 1.0f });
        
        DrawQuad(transform, texture, tilingFactor, tintColor);
    }
    
    void Renderer2D::DrawCircle(const Math::Matrix4& transform, const Math::Vector4& color, float thickness /*= 1.0f*/, float fade /*= 0.005f*/, int entityID /*= -1*/)
    {
        
        
        // TODO: implement for circles
        // if (rendererData.quadIndexCount >= Renderer2DData::MaxIndices)
        // 	NextBatch();
        
        for (size_t i = 0; i < 4; i++)
        {
            rendererData.circleVertexBufferPtr->worldPosition = transform * rendererData.quadVertexPositions[i];
            rendererData.circleVertexBufferPtr->localPosition = rendererData.quadVertexPositions[i] * 2.0f;
            rendererData.circleVertexBufferPtr->color = color;
            rendererData.circleVertexBufferPtr->thickness = thickness;
            rendererData.circleVertexBufferPtr->fade = fade;
            rendererData.circleVertexBufferPtr->entityID = entityID;
            rendererData.circleVertexBufferPtr++;
        }
        
        rendererData.circleIndexCount += 6;
        
        rendererData.stats.quadCount++;
    }
    
    void Renderer2D::DrawLine(const Math::Vector3& p0, Math::Vector3& p1, const Math::Vector4& color, int entityID)
    {
        rendererData.lineVertexBufferPtr->position = p0;
        rendererData.lineVertexBufferPtr->color = color;
        rendererData.lineVertexBufferPtr->entityID = entityID;
        rendererData.lineVertexBufferPtr++;
        
        rendererData.lineVertexBufferPtr->position = p1;
        rendererData.lineVertexBufferPtr->color = color;
        rendererData.lineVertexBufferPtr->entityID = entityID;
        rendererData.lineVertexBufferPtr++;
        
        rendererData.lineVertexCount += 2;
    }
    
    void Renderer2D::DrawRect(const Math::Vector3& position, const Math::Vector2& size, const Math::Vector4& color, int entityID)
    {
        Math::Vector3 p0 = Math::Vector3(position.x - size.x * 0.5f, position.y - size.y * 0.5f, position.z);
        Math::Vector3 p1 = Math::Vector3(position.x + size.x * 0.5f, position.y - size.y * 0.5f, position.z);
        Math::Vector3 p2 = Math::Vector3(position.x + size.x * 0.5f, position.y + size.y * 0.5f, position.z);
        Math::Vector3 p3 = Math::Vector3(position.x - size.x * 0.5f, position.y + size.y * 0.5f, position.z);
        
        DrawLine(p0, p1, color, entityID);
        DrawLine(p1, p2, color, entityID);
        DrawLine(p2, p3, color, entityID);
        DrawLine(p3, p0, color, entityID);
    }
    
    void Renderer2D::DrawRect(const Math::Matrix4& transform, const Math::Vector4& color, int entityID)
    {
        Math::Vector3 lineVertices[4];
        for (size_t i = 0; i < 4; i++)
            lineVertices[i] = transform * rendererData.quadVertexPositions[i];
        
        DrawLine(lineVertices[0], lineVertices[1], color, entityID);
        DrawLine(lineVertices[1], lineVertices[2], color, entityID);
        DrawLine(lineVertices[2], lineVertices[3], color, entityID);
        DrawLine(lineVertices[3], lineVertices[0], color, entityID);
    }
    
    
    
    float Renderer2D::GetLineWidth()
    {
        return rendererData.lineWidth;
    }
    
    void Renderer2D::SetLineWidth(float width)
    {
        rendererData.lineWidth = width;
    }
    
    void Renderer2D::ResetStats()
    {
        memset(&rendererData.stats, 0, sizeof(Statistics));
    }
    
    Renderer2D::Statistics Renderer2D::GetStats()
    {
        return rendererData.stats;
    }
}}