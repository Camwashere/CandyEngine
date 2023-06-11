#pragma once
#include <Candy/Math.hpp>
#include "camera/CameraAll.hpp"
#include "data/texture/Texture.hpp"
namespace Candy::Graphics
{
    class Renderer2D
    {
    private:
        static void StartBatch();
        static void NextBatch();
        
    public:
        static void Init();
        static void Shutdown();
        
        static void BeginScene(const Camera& camera, const Math::Matrix4& transform);
        static void BeginScene(const EditorCamera& camera);
        static void BeginScene(const OrthographicCamera& camera); // TODO: Remove
        static void EndScene();
        static void Flush();
        
        // Primitives
        static void DrawQuad(const Math::Vector2& position, const Math::Vector2& size, const Math::Vector4& color);
        static void DrawQuad(const Math::Vector3& position, const Math::Vector2& size, const Math::Vector4& color);
        static void DrawQuad(const Math::Vector2& position, const Math::Vector2& size, const SharedPtr<Texture>& texture, float tilingFactor = 1.0f, const Math::Vector4& tintColor = Math::Vector4(1.0f));
        static void DrawQuad(const Math::Vector3& position, const Math::Vector2& size, const SharedPtr<Texture>& texture, float tilingFactor = 1.0f, const Math::Vector4& tintColor = Math::Vector4(1.0f));
        
        static void DrawQuad(const Math::Matrix4& transform, const Math::Vector4& color, int entityID = -1);
        static void DrawQuad(const Math::Matrix4& transform, const SharedPtr<Texture>& texture, float tilingFactor = 1.0f, const Math::Vector4& tintColor = Math::Vector4(1.0f), int entityID = -1);
        
        static void DrawRotatedQuad(const Math::Vector2& position, const Math::Vector2& size, float rotation, const Math::Vector4& color);
        static void DrawRotatedQuad(const Math::Vector3& position, const Math::Vector2& size, float rotation, const Math::Vector4& color);
        static void DrawRotatedQuad(const Math::Vector2& position, const Math::Vector2& size, float rotation, const SharedPtr<Texture>& texture, float tilingFactor = 1.0f, const Math::Vector4& tintColor = Math::Vector4(1.0f));
        static void DrawRotatedQuad(const Math::Vector3& position, const Math::Vector2& size, float rotation, const SharedPtr<Texture>& texture, float tilingFactor = 1.0f, const Math::Vector4& tintColor = Math::Vector4(1.0f));
        
        static void DrawCircle(const Math::Matrix4& transform, const Math::Vector4& color, float thickness = 1.0f, float fade = 0.005f, int entityID = -1);
        
        static void DrawLine(const Math::Vector3& p0, Math::Vector3& p1, const Math::Vector4& color, int entityID = -1);
        
        static void DrawRect(const Math::Vector3& position, const Math::Vector2& size, const Math::Vector4& color, int entityID = -1);
        static void DrawRect(const Math::Matrix4& transform, const Math::Vector4& color, int entityID = -1);
        
        
        
        static float GetLineWidth();
        static void SetLineWidth(float width);
        
        // Stats
        struct Statistics
        {
            uint32_t drawCalls = 0;
            uint32_t quadCount = 0;
            
            uint32_t GetTotalVertexCount() const { return quadCount * 4; }
            uint32_t GetTotalIndexCount() const { return quadCount * 6; }
        };
        static void ResetStats();
        static Statistics GetStats();
    };
}