#include <editor/panels/Viewport.hpp>
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_vulkan.h"
#include <candy/app/Application.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <candy/graphics/RenderCommand.hpp>

namespace Candy
{
  using namespace Graphics;
  using namespace Math;
  using namespace ECS;
  
  Viewport::Viewport(Scene* scene) : activeScene(scene), cameraController(new Camera(Vector3(0.0f, 1.0f, 3.27f)))
  {
    CANDY_CORE_ASSERT(activeScene != nullptr);
  }
  void Viewport::OnAttach()
  {
  
  }
  void Viewport::OnUpdate()
  {
    activeScene->OnViewportResize((uint32_t)size.x, (uint32_t)size.y);
    //const FrameBuffer& frameBuffer = Renderer::GetCurrentFrame().viewportFrameBuffer;
    cameraController.OnResize(Application::GetMainWindowReference().GetWidth(), Application::GetMainWindowReference().GetHeight());
    cameraController.OnUpdate();
    activeScene->OnUpdateEditor(cameraController.GetCamera());
    
    
    ImVec2 mousePos = ImGui::GetMousePos();
    mousePos.x -= bounds.min.x;
    mousePos.y -= bounds.min.y;
    Math::Vector2 viewSize = bounds.max - bounds.min;
    mousePos.y = viewSize.y - mousePos.y;
    int mouseX = (int)mousePos.x;
    int mouseY = (int)mousePos.y;
    if (mouseX >= 0 && mouseY >= 0 && mouseX < (int)viewSize.x && mouseY < (int)viewSize.y)
    {
      //int pixelData = frameBuffer->ReadPixel(1, mouseX, mouseY);
      int pixelData = 0;
      hoveredEntity = pixelData == -1 ? Entity() : Entity((entt::entity)pixelData, activeScene);
    }
    OnOverlayRender();
  }
  
  void Viewport::OnEvent(Events::Event& event)
  {
    cameraController.OnEvent(event);
  }
  void Viewport::OnRenderUI()
  {
    ImGuiWindowFlags flags = ImGuiWindowFlags_None;
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
    ImGui::Begin("Viewport", nullptr, flags);
    auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
    auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
    auto viewportOffset = ImGui::GetWindowPos();
    bounds.min = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
    bounds.max = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };
    
    
    isFocused = ImGui::IsWindowFocused();
    isHovered = ImGui::IsWindowHovered();
    
    Application::GetUILayer().BlockEvents(!isHovered);
    
    ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
    size = { viewportPanelSize.x, viewportPanelSize.y };
   
    
   
    ImGui::Image(Renderer::GetCurrentFrame().gumDescriptor, ImVec2{size.x, size.y}, ImVec2{0, 0}, ImVec2{1, 1});
    
    if (ImGui::BeginDragDropTarget())
    {
      if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
      {
        const wchar_t *path = (const wchar_t *) payload->Data;
        // OpenScene(path);
      }
      ImGui::EndDragDropTarget();
    }

    ImGui::End();
    ImGui::PopStyleVar();
  }
  
  void Viewport::OnOverlayRender()
  {
    /*if (m_SceneState == SceneState::Play)
    {
      Entity camera = m_ActiveScene->GetPrimaryCameraEntity();
      if (!camera)
        return;
      
      Renderer2D::BeginScene(camera.GetComponent<CameraComponent>().Camera, camera.GetComponent<TransformComponent>().GetTransform());
    }
    else
    {
      Renderer2D::BeginScene(m_EditorCamera);
    }
    
    if (m_ShowPhysicsColliders)
    {
      // Box Colliders
      {
        auto view = m_ActiveScene->GetAllEntitiesWith<TransformComponent, BoxCollider2DComponent>();
        for (auto entity : view)
        {
          auto [tc, bc2d] = view.get<TransformComponent, BoxCollider2DComponent>(entity);
          
          glm::vec3 translation = tc.Translation + glm::vec3(bc2d.Offset, 0.001f);
          glm::vec3 scale = tc.Scale * glm::vec3(bc2d.Size * 2.0f, 1.0f);
          
          glm::mat4 transform = glm::translate(glm::mat4(1.0f), tc.Translation)
                                * glm::rotate(glm::mat4(1.0f), tc.Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f))
                                * glm::translate(glm::mat4(1.0f), glm::vec3(bc2d.Offset, 0.001f))
                                * glm::scale(glm::mat4(1.0f), scale);
          
          Renderer2D::DrawRect(transform, glm::vec4(0, 1, 0, 1));
        }
      }
      
      // Circle Colliders
      {
        auto view = m_ActiveScene->GetAllEntitiesWith<TransformComponent, CircleCollider2DComponent>();
        for (auto entity : view)
        {
          auto [tc, cc2d] = view.get<TransformComponent, CircleCollider2DComponent>(entity);
          
          glm::vec3 translation = tc.Translation + glm::vec3(cc2d.Offset, 0.001f);
          glm::vec3 scale = tc.Scale * glm::vec3(cc2d.Radius * 2.0f);
          
          glm::mat4 transform = glm::translate(glm::mat4(1.0f), translation)
                                * glm::scale(glm::mat4(1.0f), scale);
          
          Renderer2D::DrawCircle(transform, glm::vec4(0, 1, 0, 1), 0.01f);
        }
      }
    }
    
    // Draw selected entity outline
    if (Entity selectedEntity = m_SceneHierarchyPanel.GetSelectedEntity())
    {
      const TransformComponent& transform = selectedEntity.GetComponent<TransformComponent>();
      Renderer2D::DrawRect(transform.GetTransform(), glm::vec4(1.0f, 0.5f, 0.0f, 1.0f));
    }
    
    Renderer2D::EndScene();*/
  }
  
  bool Viewport::IsHovered()const
  {
    return isHovered;
  }
  ECS::Entity Viewport::GetHoveredEntity()const
  {
    return hoveredEntity;
  }
}