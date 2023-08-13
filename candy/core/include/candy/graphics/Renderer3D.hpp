#pragma once
#include <candy/graphics/shader/Shader.hpp>
#include <candy/graphics/VertexArray.hpp>
#include <candy/math/Matrix.hpp>
#include "model/Mesh.hpp"
#include <candy/graphics/camera/Camera.hpp>
#include "material/Material.hpp"
namespace Candy::Graphics
{
  class Renderer3D
  {
  private:
    SharedPtr<Shader> shader;
    SharedPtr<Shader> gridShader;
    Material material;
    Material gridMaterial;
    BufferLayout layout;
    std::vector<Math::Matrix4> transforms;
    static constexpr uint32_t MAX_OBJECTS=100;
    static Renderer3D* instance;
    
  private:
    void Initialize();
    static void RenderGrid();
    
  public:
    static BufferLayout GetBufferLayout();
    static void BeginScene(const Camera& camera);
    static void EndScene();
    static void Init();
    static void SubmitMesh(const Mesh& mesh, const Math::Matrix4& transform=Math::Matrix4::IDENTITY);
  
  };
}