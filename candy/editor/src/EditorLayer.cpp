#include <editor/EditorLayer.hpp>
#include <CandyPch.hpp>
#include <candy/math/Vector.hpp>
#include <candy/math/Matrix.hpp>
#include <candy/graphics/Renderer.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <candy/graphics/RenderCommand.hpp>
#include <candy/app/Application.hpp>
#include <candy/event/Events.hpp>
#include <imgui/imgui.h>
using namespace Candy::Math;
using namespace Candy::Graphics;
using namespace Candy::ECS;
using namespace Candy::Events;
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
  
  EditorLayer::EditorLayer(Project* proj) : project(proj)//, cameraController(new Camera(Vector3(0.0f, 0.0f, 3.27f)))
  {
    CANDY_ASSERT(project != nullptr);
    
    activeScene = Scene::Create("Test Scene");
    
    contentBrowserPanel = CreateUniquePtr<ContentBrowserPanel>("assets");
    viewport = CreateSharedPtr<Viewport>(activeScene.get());
    testEntity = activeScene->CreateEntity("Test Entity");
    mesh = Mesh::CreateCubeMesh();
    testEntity.AddComponent<MeshComponent>(&mesh);
    
    
    /*color = Color::purple;
    
    //Shader
    shader = Shader::Create("assets/shaders/temp/test.glsl");
    material.SetShader(shader.get());
    material.SetTexture("texSampler", "assets/textures/statue.jpg");
    
    
    for (const auto& p : positions)
    {
      Matrix4 transform = Matrix4::Translate(Matrix4::IDENTITY, p);
      objects.push_back({transform});
    }
  
    
    
    //Buffers
    vertexArray = VertexArray::Create();
    
    
    BufferLayout layout = shader->GetBufferLayout();
    
    
    SharedPtr<VertexBuffer> vertexBuffer = VertexBuffer::Create(layout, vertices.size());
    
    vertexBuffer->SetData<float>(vertices, colors, uvs);
    
    SharedPtr<IndexBuffer> indexBuffer = IndexBuffer::Create((uint32_t *) indices.data(), indices.size());
    
    vertexArray->AddVertexBuffer(vertexBuffer);
    vertexArray->SetIndexBuffer(indexBuffer);
    RenderCommand::SetClearColor(0.0f, 0.3f, 0.0f);*/
    //Renderer::Submit(&material);
    //color = Color::blue;
  }
  
  
  
  void EditorLayer::OnAttach()
  {
    if (testEntity.HasComponent<MeshComponent>())
    {
      CANDY_CORE_INFO("HAS MESH COMPONENT");
    }
    else
    {
      CANDY_CORE_INFO("HAS NO MESH COMPONENT");
    }
  
  }
  
  void EditorLayer::OnDetach()
  {
    //contentBrowserPanel->OnDetach();
  
  }
  
  void EditorLayer::OnUpdate()
  {
    Vector3 axis = {0.0f, 0.2f, 1.0f};
    float time = Application::CurrentTime();
    Matrix4 transform = Matrix4::Rotate(Matrix4::IDENTITY, time * Math::ToRadians(90.0f), axis);
    testEntity.GetTransform().rotation = axis * time * Math::ToRadians(90.0f);
    //testEntity.GetTransform().matrix = transform;
    //testEntity.GetTransform().rotation = axis * time * Math::ToRadians(90.0f);
    //testEntity.GetTransform().SetTransform(transform);
    viewport->OnUpdate();
    //RenderCommand::SetClearColor(color.Inverted());
    /*material.Bind();
    //cameraController.OnResize(Application::GetMainWindowReference().GetWidth(), Application::GetMainWindowReference().GetHeight());
    float time = Application::CurrentTime();
    
    for (int i=0; i<objects.size(); i++)
    {
      Math::Vector3 axis = {0.0f, 0.0f, 0.0f};
      axis[i] = 1.0f;
      objects[i].transform = Matrix4::Rotate(Matrix4::IDENTITY, (time*((float)i+1.0f)) * Math::ToRadians(90.0f), axis);
    }
    viewport->OnUpdate();
    //cameraController.OnUpdate();
    
    Renderer::GetCurrentFrame().storageBuffer->SetData(objects.data(), sizeof(Object) * objects.size());
    
    DescriptorBuilder builder = DescriptorBuilder::Begin();
    VkDescriptorBufferInfo objectInfo;
    objectInfo.buffer = *Vulkan::GetCurrentContext().GetCurrentFrame().storageBuffer;
    objectInfo.offset=0;
    objectInfo.range=sizeof(Object) * objects.size();
    builder.AddBufferWrite(0, &objectInfo, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC);
    builder.Write(Vulkan::GetCurrentContext().GetCurrentFrame().ObjectDescriptor());
    
    Matrix4 view = Matrix4::LookAt(Vector3(2.0f, 2.0f, 2.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f));
    Matrix4 proj = Matrix4::Perspective(Math::ToRadians(45.0f), Vulkan::GetContextSizeRatio(), 0.1f, 10.0f);
    
    proj[1,1] *= -1;
    
    color.x = (Math::Sin(time) + 1.0f) / 2.0f;
    color.y = (Math::Cos(time) + 1.0f) / 2.0f;
    color.z = (Math::Sin(time) + 1.0f) / 2.0f;
    
    float blend = (Math::Sin(time)+1.0f)/2.0f;
    
    
    shader->PushFloat("colorBlend", blend);
    
    //shader->SetMatrix("view", view);
    //shader->SetMatrix("proj", proj);
    shader->SetMatrix("view", viewport->cameraController.GetCamera().GetViewMatrix());
    shader->SetMatrix("proj", viewport->cameraController.GetCamera().GetProjectionMatrix());
    shader->SetColor("uColor", color);
    
    shader->Commit();
    
    
    vertexArray->Bind();
    for (int i=0; i<objects.size(); i++)
    {
      RenderCommand::DrawIndexed(vertexArray, objects.size(), i);
    }*/
    
  }
  
  void EditorLayer::OnRenderUI()
  {
    // Note: Switch this to true to enable dockspace
    static bool dockspaceOpen = true;
    static bool opt_fullscreen_persistant = true;
    bool opt_fullscreen = opt_fullscreen_persistant;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
    ImGuiWindowFlags_NoCollapse;
    
    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
      ImGuiViewport* view = ImGui::GetMainViewport();
      ImGui::SetNextWindowPos(view->Pos);
      ImGui::SetNextWindowSize(view->Size);
      ImGui::SetNextWindowViewport(view->ID);
      ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
      ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
      window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
      window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    
    // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
      window_flags |= ImGuiWindowFlags_NoBackground;
    
    // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
    // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
    // all active windows docked into it will lose their parent and become undocked.
    // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
    // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    
    
    ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
    ImGui::PopStyleVar();
    
    if (opt_fullscreen)
      ImGui::PopStyleVar(2);
    
    // DockSpace
    ImGuiIO& io = ImGui::GetIO();
    ImGuiStyle& style = ImGui::GetStyle();
    float minWinSizeX = style.WindowMinSize.x;
    style.WindowMinSize.x = 370.0f;
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
      ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
      ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }
    
    style.WindowMinSize.x = minWinSizeX;
    
    contentBrowserPanel->OnRenderUI();
    
    viewport->OnRenderUI();

    
    ImGui::End();
  }

  
  void EditorLayer::OnEvent(Events::Event &event)
  {
    viewport->OnEvent(event);
    //cameraController.OnEvent(event);
  }
}