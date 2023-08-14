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

namespace Candy
{
  
  EditorLayer::EditorLayer(Project* proj) : project(proj)
  {
    CANDY_ASSERT(project != nullptr);
    
    activeScene = Scene::Create("Test Scene");
    
    contentBrowserPanel = CreateUniquePtr<ContentBrowserPanel>("assets");
    scenePanel = CreateSharedPtr<SceneHierarchyPanel>(activeScene);
    viewport = CreateSharedPtr<Viewport>(activeScene.get());
    testEntity = activeScene->CreateEntity("Test Entity");
    secondEntity = activeScene->CreateEntity("Second Entity");
    
    testEntity.AddComponent<MeshComponent>(Mesh::CreateCubeMesh());
    secondEntity.AddComponent<MeshComponent>(Mesh::CreateTriangularPrismMesh());
    
    testEntity.GetTransform().position = {0.0f, 2.0f, 0.0f};
    
    secondEntity.GetTransform().position = {4.0f, 2.0f, 0.0f};
    
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
  
  
  }
  
  void EditorLayer::OnUpdate()
  {
    /*Vector3 axis = {0.0f, 0.2f, 1.0f};
    Vector3 axis2 = {0.6f, 0.8f, 0.0f};
    float time = Application::CurrentTime();
    testEntity.GetTransform().rotation = axis * time * Math::ToRadians(90.0f);
    secondEntity.GetTransform().rotation = axis2 * time * Math::ToRadians(90.0f);*/
    viewport->OnUpdate();
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
    
    scenePanel->OnRenderUI();
    contentBrowserPanel->OnRenderUI();
    viewport->OnRenderUI();

    
    ImGui::End();
  }

  
  void EditorLayer::OnEvent(Events::Event &event)
  {
    viewport->OnEvent(event);
    
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<Events::KeyPressedEvent>(CANDY_BIND_EVENT_FUNCTION(EditorLayer::OnKeyPressed));
    dispatcher.Dispatch<Events::MousePressedEvent>(CANDY_BIND_EVENT_FUNCTION(EditorLayer::OnMouseButtonPressed));
  }
  
  bool EditorLayer::OnMouseButtonPressed(Events::MousePressedEvent& event)
  {
    if (event.GetButton() == Mouse::ButtonLeft)
    {
      if (viewport->IsHovered() && !Input::IsKeyPressed(Key::LeftAlt))
      {
        scenePanel->SetSelectedEntity(viewport->GetHoveredEntity());
      }
    }
    return false;
  }
  bool EditorLayer::OnKeyPressed(Events::KeyPressedEvent& event)
  {
    // Shortcuts
    if (event.IsRepeat())
    {
      return false;
    }
    
    bool control = Input::IsKeyPressed(Key::LeftControl) || Input::IsKeyPressed(Key::RightControl);
    bool shift = Input::IsKeyPressed(Key::LeftShift) || Input::IsKeyPressed(Key::RightShift);
    
    
    return false;
  }
}