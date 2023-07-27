#include "TestLayer.hpp"
using namespace Candy;
using namespace Math;
using namespace Graphics;
using namespace Events;

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
TestLayer::TestLayer() : Layer("Test Layer")
{
  color = Color::purple;

  //Shader
  shader = Shader::Create("assets/shaders/temp/test.glsl");
  material.shader = shader.get();
  material.texture.Load("assets/textures/statue.jpg");
  material.textureImageView.Set(material.texture);


  //Buffers
  vertexArray = VertexArray::Create();
  
  BufferLayout layout;
  layout.AddElement(ShaderData::Type::Float3, "inPosition");
  layout.AddElement(ShaderData::Type::Float3, "inColor");
  layout.AddElement(ShaderData::Type::Float2, "inTexCoord");
  
  SharedPtr<VertexBuffer> vertexBuffer = VertexBuffer::Create(layout, vertices.size());
  
  
  uint64_t totalSize = layout.CalculateTotalComponentCount(vertices.size());
  float data[totalSize];
  for (int i=0, a=0; i<totalSize; i+=8, a++)
  {
    data[i] = vertices[a].x;
    data[i+1] = vertices[a].y;
    data[i+2] = vertices[a].z;
    
    data[i+3] = colors[a].x;
    data[i+4] = colors[a].y;
    data[i+5] = colors[a].z;
    
    data[i+6] = uvs[a].x;
    data[i+7] = uvs[a].y;
  }
  
  vertexBuffer->SetData(data);
  
  SharedPtr<IndexBuffer> indexBuffer = IndexBuffer::Create((uint32_t *) indices.data(), indices.size());
  
  vertexArray->AddVertexBuffer(vertexBuffer);
  vertexArray->SetIndexBuffer(indexBuffer);
  Renderer::Submit(&material);
  
  
}

void TestLayer::OnAttach()
{
  Layer::OnAttach();
}

void TestLayer::OnDetach()
{
  //CANDY_CORE_INFO("ON DETACH");
  vkDeviceWaitIdle(Vulkan::LogicalDevice());
  material.Destroy();
  //Vulkan::GetCurrentContext().CleanSwapChain();
  //vkDeviceWaitIdle(Vulkan::LogicalDevice());
  //textureImageView.Destroy();
  //texture.Destroy();
  //uniformBuffer->Destroy();
  //vkDestroyDescriptorSetLayout(Vulkan::LogicalDevice(), shader->GetDescriptorSetLayout(), nullptr);
  vertexArray->Clear();
  //CANDY_CORE_INFO("DETACHED TEST LAYER");
}

void TestLayer::OnEvent(Event &event)
{
  Layer::OnEvent(event);
}

void TestLayer::OnUpdate()
{
  
  static auto startTime = std::chrono::high_resolution_clock::now();
  
  auto currentTime = std::chrono::high_resolution_clock::now();
  float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
  
  Matrix4 model = Matrix4::Rotate(Matrix4::IDENTITY, time * Math::ToRadians(90.0f), Math::Vector3(0.0f, 0.0f, 1.0f));
  Matrix4 view = Matrix4::LookAt(Vector3(2.0f, 2.0f, 2.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f));
  Matrix4 proj = Matrix4::Perspective(Math::ToRadians(45.0f), Vulkan::GetContextSizeRatio(), 0.1f, 10.0f);
  
  proj[1,1] *= -1;

  Vulkan::GetCurrentContext().GetCurrentFrame().uniformBuffer->SetData(&color[0]);

  Renderer::BindDescriptorSets();

  vertexArray->Bind();
  shader->GetLayout().PushMatrix("model", model);
  shader->GetLayout().PushMatrix("view", view);
  shader->GetLayout().PushMatrix("proj", proj);
  
  Renderer::DrawIndexed(vertexArray);
}

void TestLayer::OnRenderUI()
{
  Layer::OnRenderUI();
}
