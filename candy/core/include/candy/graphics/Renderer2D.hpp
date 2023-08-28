#pragma once
#include "camera/EditorCamera.hpp"
#include <candy/math/Matrix.hpp>
#include <candy/math/Vector.hpp>
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
    static void DrawQuad(const Math::Vector3& position, const Math::Vector2& size, const Math::Vector4& color);
    static void DrawQuad(const Math::Matrix4& transform, const Math::Vector4& color, int entityID = -1);
    
    static Stats GetStats();
    
  
  };
}