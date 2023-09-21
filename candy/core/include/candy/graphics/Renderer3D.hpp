#pragma once
#include <candy/graphics/shader/Shader.hpp>
#include <candy/graphics/VertexArray.hpp>
#include <candy/math/Matrix.hpp>
#include "model/Mesh.hpp"
#include "candy/graphics/camera/PerspectiveCamera.hpp"
#include <candy/graphics/camera/EditorCamera.hpp>
#include "material/Material.hpp"

namespace Candy::Graphics
{
  
  class Renderer3D
  {
  public:
    struct Stats
    {
      uint32_t drawCalls = 0;
      uint32_t objectCount = 0;
      uint32_t vertexCount = 0;
      uint32_t indexCount = 0;
      uint32_t triangleCount=0;
      
    };
    
    
  private:
    static void InitGrid();
    static void InitMesh();
    static void InitSelection();
    static void InitMaterial();
    static void ResetStats();
    static void RenderGrid();
    
    static void StartBatch();
    static void NextBatch();
    
  public:
    static inline bool skipFlush=false;
    static void Flush();
    static void FlushVertexData();
    static void BeginScene();
    static void EndScene();
    static void Init();
    static void SubmitMesh(uint32_t entity, uint32_t meshIndexCount, uint32_t meshVertexCount, const SharedPtr<Texture>& texture, const Math::Matrix4& transform=Math::Matrix4::IDENTITY);
    static void SubmitMesh(uint32_t entity, const MeshData& data, const SharedPtr<Texture>& texture, const Math::Matrix4& transform=Math::Matrix4::IDENTITY);
    static Renderer3D::Stats GetStats();
    static void RenderSelectionBuffer();
  
  };
}