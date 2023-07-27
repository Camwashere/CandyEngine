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
  texture.Load("assets/textures/statue.jpg");
  textureImageView.Set(texture);
  texture.CreateSampler();

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
  CreateDescriptorSets();
  Renderer::Submit(vertexArray, shader);
  
  
}
void TestLayer::CreateDescriptorSets()
{
  

  size_t sum=0;
  for (size_t i=0; i<FRAME_OVERLAP; i++)
  {
    VkDescriptorBufferInfo bufferInfo{};
    bufferInfo.buffer = *Vulkan::GetCurrentContext().GetFrame(i).uniformBuffer;
    //bufferInfo.buffer = *uniformBuffer;
    size_t offset=0;
    //size_t offset = Vulkan::PhysicalDevice().PadUniformBufferSize(sizeof(Color))*i;
    bufferInfo.offset = offset;
    bufferInfo.range = sizeof(Color);
    sum += bufferInfo.range + bufferInfo.offset;
    
    
    VkDescriptorImageInfo imageInfo{};
    imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    imageInfo.imageView = textureImageView;
    imageInfo.sampler = texture.GetSampler();
    DescriptorBuilder::Begin()
    .BindBuffer(0, &bufferInfo, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, ShaderData::StageToVulkan(ShaderData::Stage::Fragment))
    .BindImage(1, &imageInfo, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, ShaderData::StageToVulkan(ShaderData::Stage::Fragment))
    .Build(&Vulkan::GetCurrentContext().GetFrame(i).globalDescriptor);
  }

}
void TestLayer::OnAttach()
{
  Layer::OnAttach();
}

void TestLayer::OnDetach()
{
  //CANDY_CORE_INFO("ON DETACH");
  vkDeviceWaitIdle(Vulkan::LogicalDevice());
  //Vulkan::GetCurrentContext().CleanSwapChain();
  //vkDeviceWaitIdle(Vulkan::LogicalDevice());
  textureImageView.Destroy();
  texture.Destroy();
  //uniformBuffer->Destroy();
  vkDestroyDescriptorSetLayout(Vulkan::LogicalDevice(), shader->GetDescriptorSetLayout(), nullptr);
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
  
  ubo.model = Matrix4::Rotate(Matrix4::IDENTITY, time * Math::ToRadians(90.0f), Math::Vector3(0.0f, 0.0f, 1.0f));
  ubo.view = Matrix4::LookAt(Vector3(2.0f, 2.0f, 2.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f));
  ubo.proj = Matrix4::Perspective(Math::ToRadians(45.0f), Vulkan::GetContextSizeRatio(), 0.1f, 10.0f);
  
  ubo.proj[1,1] *= -1;
  size_t dataOffset = Vulkan::PhysicalDevice().PadUniformBufferSize(sizeof(Color))*Vulkan::GetCurrentContext().GetCurrentFrameIndex();
  Vulkan::GetCurrentContext().GetCurrentFrame().uniformBuffer->SetData(&color[0]);
  //uniformBuffer->SetData(&color[0]);
  Renderer::BindDescriptorSets();
  //uniformBuffer->SetData(&color[0]);
  vertexArray->Bind();
  
  Renderer::PushConstants(ShaderData::Stage::Vertex, sizeof(UniformBufferObject), &ubo);
  
  Renderer::DrawIndexed(vertexArray);
}

void TestLayer::OnRenderUI()
{
  Layer::OnRenderUI();
}
