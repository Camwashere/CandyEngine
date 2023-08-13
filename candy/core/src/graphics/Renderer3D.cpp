#include <candy/graphics/Renderer3D.hpp>
#include <candy/graphics/RenderCommand.hpp>
namespace Candy::Graphics
{
  using namespace Math;
  Renderer3D* Renderer3D::instance = nullptr;
  struct SceneData
  {
    Matrix4 viewMatrix{};
    Matrix4 projectionMatrix{};
  };
  static SceneData sceneData{};
  void Renderer3D::Initialize()
  {
    shader = Shader::Create("assets/shaders/renderer3D/Mesh.glsl");
    gridShader = Shader::Create("assets/shaders/renderer3D/Grid.glsl");
    transforms.resize(100);
    material.SetShader(shader.get());
    material.SetTexture("texSampler", "assets/textures/statue.jpg");
    gridMaterial.SetShader(gridShader.get());
  }
  
  void Renderer3D::RenderGrid()
  {
    instance->gridMaterial.Bind();
    //instance->gridShader->SetMatrix("model", transform);
    instance->gridShader->SetMatrix("proj", sceneData.projectionMatrix);
    instance->gridShader->SetMatrix("view", sceneData.viewMatrix);
    instance->gridShader->Commit();
    RenderCommand::DrawEmpty(6);
  }
  
  void Renderer3D::Init()
  {
    instance=new Renderer3D();
    instance->Initialize();
  }
  BufferLayout Renderer3D::GetBufferLayout()
  {
    return instance->shader->GetBufferLayout();
  }
  void Renderer3D::BeginScene(const Camera& camera)
  {
    
    sceneData.viewMatrix = camera.GetViewMatrix();
    sceneData.projectionMatrix = camera.GetProjectionMatrix();
    RenderGrid();
    /*instance->gridMaterial.Bind();
    instance->gridShader->SetMatrix("proj", sceneData.projectionMatrix);
    instance->gridShader->SetMatrix("view", sceneData.viewMatrix);*/
    
  }
  void Renderer3D::EndScene()
  {
  
  }
  void Renderer3D::SubmitMesh(const Mesh& mesh, const Math::Matrix4& transform)
  {
    /*CANDY_CORE_INFO("SUBMITTING MESH");
    instance->material.Bind();
    CANDY_CORE_INFO("BOUND MESH");
    instance->shader->SetMatrix("proj", sceneData.projectionMatrix);
    instance->shader->SetMatrix("view", sceneData.viewMatrix);
    instance->shader->SetMatrix("model", transform);
    CANDY_CORE_INFO("SET MATRICES");
    instance->shader->Commit();
    CANDY_CORE_INFO("COMMITTED MESH");
    mesh.vertexArray->Bind();
    CANDY_CORE_INFO("BOUND VERT ARRAY");
    
    RenderCommand::DrawIndexed(mesh.vertexArray);
    CANDY_CORE_INFO("DRAWN INDEXED");*/
    
  }
}