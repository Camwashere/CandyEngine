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
    material.shader = shader.get();
    material.texture.Load("assets/textures/statue.jpg");
    material.textureImageView.Set(material.texture);
    
    
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
    Matrix4 model = Matrix4::Rotate(Matrix4::IDENTITY, time * Math::ToRadians(90.0f), Math::Vector3(0.0f, 0.0f, 1.0f));
    Matrix4 view = Matrix4::LookAt(Vector3(2.0f, 2.0f, 2.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f));
    Matrix4 proj = Matrix4::Perspective(Math::ToRadians(45.0f), Vulkan::GetContextSizeRatio(), 0.1f, 10.0f);
    
    proj[1,1] *= -1;
    
    color.x = (Math::Sin(time) + 1.0f) / 2.0f;
    color.y = (Math::Cos(time) + 1.0f) / 2.0f;
    color.z = (Math::Sin(time) + 1.0f) / 2.0f;
    shader->SetColor("uColor", color);
    
    shader->PushMatrix("model", model);
    shader->PushMatrix("view", view);
    shader->PushMatrix("proj", proj);
    
    vertexArray->Bind();
    RenderCommand::DrawIndexed(vertexArray);
  }
  
  void EditorLayer::OnRenderUI()
  {
  
  }

  
  void EditorLayer::OnEvent(Events::Event &event)
  {
    Layer::OnEvent(event);
  }
}