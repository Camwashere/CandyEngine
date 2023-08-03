#include <editor/EditorLayer.hpp>
#include <CandyPch.hpp>
#include <candy/math/Vector.hpp>
#include <candy/math/Matrix.hpp>
#include <candy/graphics/Renderer.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <candy/graphics/RenderCommand.hpp>

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
    
    //layout.Flatten<std::vector<Vector3>, std::vector<Vector3>, std::vector<Vector2>>(vertices, colors, uvs);
    
    Vector2 b;
    Vector3 c;
    
    
    auto types = BufferLayout::Flatten(vertices, colors, uvs);
    for (auto t : types)
    {
      CANDY_CORE_INFO("Type: {0}", ShaderData::TypeToString(t));
    }
    
    
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
    //contentBrowserPanel = CreateUniquePtr<ContentBrowserPanel>(project->GetRootWorkingDirectory());
    //viewport = CreateUniquePtr<Viewport>();
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
    static auto startTime = std::chrono::high_resolution_clock::now();
    
    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
    
    Matrix4 model = Matrix4::Rotate(Matrix4::IDENTITY, time * Math::ToRadians(90.0f), Math::Vector3(0.0f, 0.0f, 1.0f));
    Matrix4 view = Matrix4::LookAt(Vector3(2.0f, 2.0f, 2.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f));
    Matrix4 proj = Matrix4::Perspective(Math::ToRadians(45.0f), Vulkan::GetContextSizeRatio(), 0.1f, 10.0f);
    
    proj[1,1] *= -1;
    
    //color.x = (Math::Sin(time) + 1.0f) / 2.0f;
    //color.y = (Math::Cos(time) + 1.0f) / 2.0f;
    //color.z = (Math::Sin(time) + 1.0f) / 2.0f;
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
  /*void EditorLayer::OnRenderUI()
  {
    // Note: Switch this to true to enable dockspace
    static bool dockspaceOpen = true;
    static bool opt_fullscreen_persistant = true;
    bool opt_fullscreen = opt_fullscreen_persistant;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_AutoHideTabBar;
    
    
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
    
  }*/
  
  void EditorLayer::OnEvent(Events::Event &event)
  {
    Layer::OnEvent(event);
  }
}