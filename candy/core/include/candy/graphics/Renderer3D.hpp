#pragma once
#include <candy/graphics/shader/Shader.hpp>
#include <candy/graphics/VertexArray.hpp>
#include <candy/math/Matrix.hpp>
#include "model/Mesh.hpp"
#include <candy/graphics/camera/Camera.hpp>
#include <candy/graphics/camera/EditorCamera.hpp>
#include "material/Material.hpp"

namespace Candy::Graphics
{
  struct Renderer3DStats
  {
    uint32_t drawCalls=0;
    uint32_t objects=0;
    uint32_t vertices=0;
    uint32_t indices=0;
    uint32_t triangles=0;
    
  };
  class Renderer3D
  {
  private:
    static Renderer3DStats stats;
  
  private:
    SharedPtr<Shader> shader;
    SharedPtr<Shader> gridShader;
    SharedPtr<Shader> selectionShader;
    Material material;
    std::vector<Mesh> meshes;
    
    std::vector<uint32_t> entities;
    std::vector<Math::Matrix4> transforms;
    static constexpr uint32_t MAX_OBJECTS=100;
    static Renderer3D* instance;
    
  private:
    void Initialize();
    static void ResetStats();
    static void RenderGrid();
    
  public:
    static BufferLayout GetBufferLayout();
    
    
    
    static void BeginScene();
    static void EndScene();
    static void Init();
    static void SubmitMesh(uint32_t entity, const Mesh& data, const Math::Matrix4& transform=Math::Matrix4::IDENTITY);
    static Renderer3DStats GetStats();
    static void RenderSelectionBuffer();
  
  };
}