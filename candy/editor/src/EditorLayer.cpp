#include <editor/EditorLayer.hpp>
#include <CandyPch.hpp>
#include <candy/math/Vector.hpp>
#include <candy/math/Matrix.hpp>
#include <candy/graphics/Renderer.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <candy/graphics/RenderCommand.hpp>
#include <candy/app/Application.hpp>

using namespace Candy::Math;
using namespace Candy::Graphics;
const std::vector<Vector3> vertices = {
  {-0.5f, -0.5f, 0.0f},
  {0.5f, -0.5f, 0.0f},
  {0.5f, 0.5f, 0.0f},
  {-0.5f, 0.5f, 0.0f},
  
  // SECOND SQUARE
  {-0.5f, -0.5f, -0.5f},
  {0.5f, -0.5f, -0.5f},
  {0.5f, 0.5f, -0.5f},
  {-0.5f, 0.5f, -0.5f}
};

const std::vector<Vector3> colors = {
  {1.0f, 0.0f, 0.0f},
  {0.0f, 1.0f, 0.0f},
  {0.0f, 0.0f, 1.0f},
  {1.0f, 1.0f, 1.0f},
  
  //SECOND SQUARE
  {1.0f, 0.0f, 0.0f},
  {0.0f, 1.0f, 0.0f},
  {0.0f, 0.0f, 1.0f},
  {1.0f, 1.0f, 1.0f}
};

const std::vector<Vector2> uvs = {
  {1.0f, 0.0f},
  {0.0f, 0.0f},
  {0.0f, 1.0f},
  {1.0f, 1.0f},
  
  //SECOND SQUARE
  {1.0f, 0.0f},
  {0.0f, 0.0f},
  {0.0f, 1.0f},
  {1.0f, 1.0f}
};



const std::vector<uint32_t> indices = {
  0, 1, 2, 2, 3, 0,
  //SECOND SQUARE
  4, 5, 6, 6, 7, 4
};
namespace Candy
{
  
  EditorLayer::EditorLayer(Project* proj) : project(proj)
  {
    CANDY_ASSERT(project != nullptr);
    color = Color::purple;
    
    //Shader
    shader = Shader::Create("assets/shaders/temp/test.glsl");
    material.SetShader(shader.get());
    material.SetTexture("texSampler", "assets/textures/statue.jpg");
    
    /*material.shader = shader.get();
    material.texture.Load("assets/textures/statue.jpg");
    material.textureImageView.Set(material.texture);*/
    
    
    
    for (const auto& p : positions)
    {
      Matrix4 transform = Matrix4::Translate(Matrix4::IDENTITY, p);
      objects.push_back({transform});
    }
    /*void* objectData;
    Vulkan::GetCurrentContext().GetFrame(0).storageBuffer->Bind(&objectData);
    objectSSBO = (Object*) objectData;
    for (int i=0; i<objects.size(); i++)
    {
      Object& object = objects[i];
      objectSSBO[i].transform = object.transform;
    }
    Vulkan::GetCurrentContext().GetFrame(0).storageBuffer->Unbind();*/
    
    
    
    
    //Buffers
    vertexArray = VertexArray::Create();
    
    
    BufferLayout layout = shader->GetBufferLayout();
    
    
    SharedPtr<VertexBuffer> vertexBuffer = VertexBuffer::Create(layout, vertices.size());
    
    vertexBuffer->SetData<float>(vertices, colors, uvs);
    
    SharedPtr<IndexBuffer> indexBuffer = IndexBuffer::Create((uint32_t *) indices.data(), indices.size());
    
    vertexArray->AddVertexBuffer(vertexBuffer);
    vertexArray->SetIndexBuffer(indexBuffer);
    Renderer::Submit(&material);
    color = Color::blue;
  }
  
  
  
  void EditorLayer::OnAttach()
  {
    Layer::OnAttach();
  }
  
  void EditorLayer::OnDetach()
  {
    //contentBrowserPanel->OnDetach();
  
  }
  
  void EditorLayer::OnUpdate()
  {
    float time = Application::CurrentTime();
    for (int i=0; i<objects.size(); i++)
    {
      Math::Vector3 axis = {0.0f, 0.0f, 0.0f};
      axis[i] = 1.0f;
      objects[i].transform = Matrix4::Rotate(Matrix4::IDENTITY, (time*((float)i+1.0f)) * Math::ToRadians(90.0f), axis);
    }
    
    /*void* objectData;
    Vulkan::GetCurrentContext().GetCurrentFrame().storageBuffer->Bind(&objectData);
    objectSSBO = (Object*) objectData;
    for (int i=0; i<objects.size(); i++)
    {
      Object& object = objects[i];
      objectSSBO[i].transform = object.transform;
    }
    Vulkan::GetCurrentContext().GetCurrentFrame().storageBuffer->Unbind();*/
    Renderer::GetCurrentFrame().storageBuffer->SetData(objects.data(), sizeof(Object) * objects.size());
    
    DescriptorBuilder builder = DescriptorBuilder::Begin();
    VkDescriptorBufferInfo objectInfo;
    objectInfo.buffer = *Vulkan::GetCurrentContext().GetCurrentFrame().storageBuffer;
    objectInfo.offset=0;
    objectInfo.range=sizeof(Object) * objects.size();
    builder.AddBufferWrite(0, &objectInfo, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC);
    builder.Write(Vulkan::GetCurrentContext().GetCurrentFrame().ObjectDescriptor());
    
    //Matrix4 model = Matrix4::Rotate(Matrix4::IDENTITY, time * Math::ToRadians(90.0f), Math::Vector3(0.0f, 0.0f, 1.0f));
    Matrix4 view = Matrix4::LookAt(Vector3(2.0f, 2.0f, 2.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f));
    Matrix4 proj = Matrix4::Perspective(Math::ToRadians(45.0f), Vulkan::GetContextSizeRatio(), 0.1f, 10.0f);
    
    proj[1,1] *= -1;
    
    color.x = (Math::Sin(time) + 1.0f) / 2.0f;
    color.y = (Math::Cos(time) + 1.0f) / 2.0f;
    color.z = (Math::Sin(time) + 1.0f) / 2.0f;
    
    float blend = (Math::Sin(time)+1.0f)/2.0f;
    //material.SetParameter("model", model);
    //material.SetParameter("view", view);
    //material.SetParameter("proj", proj);
    //material.SetParameter("uColor", color);
    
    shader->PushFloat("colorBlend", blend);
    
    //shader->SetMatrix("model", model);
    shader->SetMatrix("view", view);
    shader->SetMatrix("proj", proj);
    shader->SetColor("uColor", color);
    
    shader->Commit();
    //RenderCommand::BindDescriptorSets(shader->GetLayout().pipeline, {Vulkan::GetCurrentContext().GetCurrentFrame().globalDescriptor}, {0, 0});
    //shader->PushMatrix("model", model);
    //shader->PushMatrix("view", view);
    //shader->PushMatrix("proj", proj);
    //material.Bind();
    
    vertexArray->Bind();
    for (int i=0; i<objects.size(); i++)
    {
      RenderCommand::DrawIndexed(vertexArray, objects.size(), i);
    }
    
  }
  
  void EditorLayer::OnRenderUI()
  {
  
  }

  
  void EditorLayer::OnEvent(Events::Event &event)
  {
    Layer::OnEvent(event);
  }
}