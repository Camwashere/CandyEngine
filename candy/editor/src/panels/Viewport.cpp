#include <editor/panels/Viewport.hpp>
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_vulkan.h"
#include <candy/app/Application.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <candy/graphics/RenderCommand.hpp>
#include <candy/graphics/PixelBuffer.hpp>
#include <candy/graphics/Renderer3D.hpp>
#include <imguizmo/ImGuizmo.h>
#include <editor/EditorLayer.hpp>

namespace Candy
{
  using namespace Graphics;
  using namespace Math;
  using namespace ECS;
  
  Viewport::Viewport(EditorLayer* parentLayer) : parent(parentLayer), cameraController(new Camera(Vector3(0.0f, 1.0f, 3.27f))), editorCamera(Vector3(0.0f, 1.0f, 3.27f))
  {
    CANDY_CORE_ASSERT(parent != nullptr);
    gizmoType = ImGuizmo::OPERATION::TRANSLATE;
  }
  void Viewport::OnAttach()
  {
  
  }
  void Viewport::OnUpdate()
  {
    parent->activeScene->OnViewportResize((uint32_t)size.x, (uint32_t)size.y);
    
    
    editorCamera.SetViewportSize(size.x, size.y);
    editorCamera.OnUpdate();
    parent->activeScene->OnUpdateEditor(editorCamera);
    
    
    
    
    ImVec2 mousePos = ImGui::GetMousePos();
    mousePos.x -= bounds.min.x;
    mousePos.y -= bounds.min.y;
    Math::Vector2 viewSize = bounds.max - bounds.min;
    mousePos.y = viewSize.y - mousePos.y;
    Math::Vector2u imageSize = Renderer::GetCurrentFrame().viewportData.selectionPixelBuffer->GetImageSize();
    float scaleX = (float)imageSize.width / viewSize.x;      // original image width / displayed width
    float scaleY = (float)imageSize.height / viewSize.y;      // original image height / displayed height
    
    int mouseX = static_cast<int>(mousePos.x * scaleX);
    int mouseY = static_cast<int>((viewSize.y - mousePos.y) * scaleY);
    
    if (mouseX >= 0 && mouseY >= 0 && mouseX < (int)imageSize.width && mouseY < (int)imageSize.height)
    {

      int pixelData = Renderer::GetCurrentFrame().viewportData.selectionPixelBuffer->ReadPixel(mouseX, mouseY);
      
      hoveredEntity = pixelData == -1 ? Entity() : Entity((entt::entity)pixelData, parent->activeScene.get());
    }
    OnOverlayRender();
  }
  
  void Viewport::OnEvent(Events::Event& event)
  {
    if (isHovered)
    {
      if (event.GetType() == Events::EventType::MOUSE_RELEASED)
      {
        Events::MouseReleasedEvent& e = (Events::MouseReleasedEvent&)event;
        if (e.GetButton() == Mouse::ButtonLeft)
        {
          Renderer3D::SetNeedsSelection();
        }
      }
    }
    editorCamera.OnEvent(event);
    
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
    
    ImGui::Image(Renderer::GetCurrentFrame().viewportData.viewportDescriptor, ImVec2{size.x, size.y}, ImVec2{0, 0}, ImVec2{1, 1});
    
    if (ImGui::BeginDragDropTarget())
    {
      if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
      {
        const wchar_t *path = (const wchar_t *) payload->Data;
        // OpenScene(path);
      }
      ImGui::EndDragDropTarget();
    }
    
    // Gizmos
    Entity selectedEntity = parent->scenePanel->GetSelectedEntity();
    if (selectedEntity && gizmoType != -1)
    {
      ImGuizmo::SetOrthographic(false);
      ImGuizmo::SetDrawlist();
      
      ImGuizmo::SetRect(bounds.min.x, bounds.min.y, bounds.max.x-bounds.min.x, bounds.max.y-bounds.min.y);
      
      // Editor camera
      Matrix4 cameraProjection = editorCamera.GetProjectionMatrix();
      Matrix4 cameraView = editorCamera.GetViewMatrix();
      
      // Entity transform
      auto& tc = selectedEntity.GetComponent<TransformComponent>();
      Matrix4 transform = tc.GetMatrix();
      
      // Snapping
      bool snap = Input::IsKeyPressed(Key::LeftControl);
      float snapValue = 0.5f; // Snap to 0.5m for translation/scale
      // Snap to 45 degrees for rotation
      if (gizmoType == ImGuizmo::OPERATION::ROTATE)
        snapValue = 45.0f;
      
      float snapValues[3] = { snapValue, snapValue, snapValue };
      cameraProjection[1, 1] *= -1;
      cameraProjection[2, 2] *= 0.5f;
      cameraProjection[2, 3] = cameraProjection[2, 2]+0.5f;
      
      ImGuizmo::Manipulate(&cameraView[0], &cameraProjection[0],
                           (ImGuizmo::OPERATION)gizmoType, ImGuizmo::LOCAL, &transform[0],
                           nullptr, snap ? snapValues : nullptr);
      
      if (ImGuizmo::IsUsing())
      {
        Vector3 translation, rotation, scale;
        Matrix4::DecomposeTransform(transform, translation, rotation, scale);
        
        Vector3 deltaRotation = rotation - tc.rotation;
        tc.position = translation;
        tc.rotation += deltaRotation;
        tc.scale = scale;
      }
    }
    ImGui::End();
    ImGui::PopStyleVar();
  }
  
  void Viewport::OnOverlayRender()
  {
    // Show colliders/debug rays etc
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