#include <candy/graphics/Renderer3D.hpp>
#include <candy/graphics/RenderCommand.hpp>
#include <candy/graphics/Renderer.hpp>
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
    gridShader = Shader::Create("assets/shaders/renderer3D/Grid.glsl");
    shader = Shader::Create("assets/shaders/renderer3D/Mesh.glsl");
    selectionShader = Shader::Create("assets/shaders/renderer3D/SelectionMesh.glsl", Renderer::GetSelectionPass());
    material.SetShader(shader.get());
    material.SetTexture("texSampler", "assets/textures/statue.jpg");
    gridMaterial.SetShader(gridShader.get());
    selectionMaterial.SetShader(selectionShader.get());
    
  }
  
  void Renderer3D::RenderGrid()
  {
    instance->gridShader->Bind();
    instance->gridMaterial.Bind(0);
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
    instance->transforms.clear();
    instance->meshes.clear();
    instance->entities.clear();
    sceneData.viewMatrix = camera.GetViewMatrix();
    sceneData.projectionMatrix = camera.GetProjectionMatrix();
    RenderGrid();
    
    
  }
  void Renderer3D::SetNeedsSelection()
  {
    instance->needsSelection=true;
  }
  bool Renderer3D::NeedsSelection()
  {
    return instance->needsSelection;
  }
  void Renderer3D::EndScene()
  {
    CANDY_CORE_ASSERT(instance->transforms.size() == instance->meshes.size(), "Transforms and meshes are not the same size");
    instance->shader->Bind();
    instance->material.Bind(2);
    
    Renderer::GetCurrentFrame().storageBuffer->SetData(instance->transforms.data(), sizeof(Matrix4) * instance->transforms.size());
    
    DescriptorBuilder builder = DescriptorBuilder::Begin();
    VkDescriptorBufferInfo objectInfo;
    objectInfo.buffer = *Renderer::GetCurrentFrame().storageBuffer;
    objectInfo.offset=0;
    objectInfo.range=sizeof(Matrix4) * instance->transforms.size();
    builder.AddBufferWrite(0, &objectInfo, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC);
    builder.Write(Renderer::GetCurrentFrame().ObjectDescriptor());
    
    
    instance->shader->Commit();
    
    for (int i=0; i<instance->meshes.size(); i++)
    {
      instance->meshes[i].vertexArray->Bind();
      instance->shader->PushInt("objectIndex", i);
      RenderCommand::DrawIndexed(instance->meshes[i].vertexArray);
    }
    RenderSelectionBuffer();
    
    
  }
  void Renderer3D::RenderSelectionBuffer()
  {
    CANDY_CORE_ASSERT(instance->transforms.size() == instance->meshes.size(), "Transforms and meshes are not the same size");
    Renderer::BeginSelectionPass();
    instance->selectionShader->Bind();
    instance->selectionMaterial.Bind(2);
    
    /*Renderer::GetCurrentFrame().storageBuffer->SetData(instance->transforms.data(), sizeof(Matrix4) * instance->transforms.size());
    
    DescriptorBuilder builder = DescriptorBuilder::Begin();
    VkDescriptorBufferInfo objectInfo;
    objectInfo.buffer = *Renderer::GetCurrentFrame().storageBuffer;
    objectInfo.offset=0;
    objectInfo.range=sizeof(Matrix4) * instance->transforms.size();
    builder.AddBufferWrite(0, &objectInfo, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC);
    builder.Write(Renderer::GetCurrentFrame().ObjectDescriptor());*/
    
    
    instance->selectionShader->Commit();
    instance->selectionShader->PushInt("entityID", -1);
    for (int i=0; i<instance->meshes.size(); i++)
    {
      instance->meshes[i].vertexArray->Bind();
      instance->selectionShader->PushInt("objectIndex", i);
      instance->selectionShader->PushInt("entityID", static_cast<int>(instance->entities[i]));
      RenderCommand::DrawIndexed(instance->meshes[i].vertexArray);
    }
    //instance->needsSelection=false;
   
  }
  void Renderer3D::SubmitMesh(uint32_t entity, const Mesh& data, const Math::Matrix4& transform)
  {
    if (data.IsValid())
    {
      //CANDY_CORE_INFO("ENTITY SUBMITTED: {}", entity);
      //CANDY_CORE_INFO("INT ENTITY: {}", static_cast<int>(entity));
      instance->meshes.push_back(data);
      instance->transforms.push_back(transform);
      instance->entities.push_back(entity);
    }
  }
}