#pragma once
#include "camera/EditorCamera.hpp"
#include <candy/math/Matrix.hpp>
#include <candy/math/Vector.hpp>
#include <candy/graphics/Texture.hpp>
namespace Candy::ECS
{
  struct SpriteRendererComponent;
}
namespace Candy::Graphics
{
  
  class Renderer2D
  {
  private:
    static void StartBatch();
    static void NextBatch();
    static void ResetStats();
  public:
    struct Stats
    {
      uint32_t drawCalls = 0;
      uint32_t quadCount = 0;
      uint32_t vertexCount = 0;
      uint32_t indexCount = 0;
    };
    static void Init();
    static void Flush();
    static void RenderSelectionBuffer();
    static void BeginScene();
    static void EndScene();
    
    static void DrawQuad(const Math::Vector2& position, const Math::Vector2& size, const Math::Vector4& color);
    static void DrawQuad(const Math::Vector3& position, const Math::Vector2& size, const Math::Vector4& color, int entityID = -1);
    static void DrawQuad(const Math::Matrix4& transform, const Math::Vector4& color, int entityID = -1);
    static void DrawQuad(const Math::Matrix4& transform, const SharedPtr<Texture>& texture, float tilingFactor = 1.0f, const Math::Vector4& tintColor = Math::Vector4::one, int entityID = -1);
    
    static void DrawSprite(const Math::Matrix4& transform, ECS::SpriteRendererComponent& src, int entityID);
    
    static Stats GetStats();
    
  
  };
}