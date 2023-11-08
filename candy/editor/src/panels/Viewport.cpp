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
#include <candy/ecs/TransformComponent.hpp>

namespace Candy
{
  using namespace Graphics;
  using namespace Math;
  using namespace ECS;
  
  Viewport::Viewport(EditorLayer* parentLayer) : parent(parentLayer), editorCamera(Vector3(0.0f, 1.0f, 3.27f), {3000.0f,1500.0f})
  {
    CANDY_CORE_ASSERT(parent != nullptr);
    gizmoType = ImGuizmo::OPERATION::TRANSLATE;
    
  }
  void Viewport::OnAttach()
  {
  
  }
  void Viewport::OnUpdate()
  {
    CANDY_PROFILE_FUNCTION();
    parent->activeScene->OnViewportResize((uint32_t)size.x, (uint32_t)size.y);
    
    
    editorCamera.SetViewportSize(size.x, size.y);
    editorCamera.OnUpdate();
    
    Renderer::UpdateCameraData(editorCamera.GetCamera3D(), editorCamera.GetCamera2D());
    Renderer::RenderScene(parent->activeScene);
    
    
    
    
    ImVec2 mousePos = ImGui::GetMousePos();
    mousePos.x -= bounds.min.x;
    mousePos.y -= bounds.min.y;
    Math::Vector2 viewSize = bounds.max - bounds.min;
    mousePos.y = viewSize.y - mousePos.y;
    //Math::Vector2u imageSize = Renderer::GetCurrentFrame().viewportData.selectionPixelBuffer->GetImageSize();
    Math::Vector2u imageSize = Renderer::GetViewportImageSize();
    float scaleX = (float)imageSize.width / viewSize.x;      // original image width / displayed width
    float scaleY = (float)imageSize.height / viewSize.y;      // original image height / displayed height
    
    int mouseX = static_cast<int>(mousePos.x * scaleX);
    int mouseY = static_cast<int>((viewSize.y - mousePos.y) * scaleY);
    
    if (mouseX >= 0 && mouseY >= 0 && mouseX < (int)imageSize.width && mouseY < (int)imageSize.height)
    {
      int pixelData = Renderer::ReadViewportPixelData(mouseX, mouseY);
      
      hoveredEntity = pixelData == -1 ? Entity() : Entity((entt::entity)pixelData, parent->activeScene.get());
    }
    OnOverlayRender();
  }
  
  void Viewport::OnEvent(Events::Event& event)
  {
    CANDY_PROFILE_FUNCTION();
    editorCamera.OnEvent(event);
    //orthographicCameraController.OnEvent(event);
  }
  void Viewport::OnRenderUI()
  {
    CANDY_PROFILE_FUNCTION();
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
    
    //Application::GetUILayer().BlockEvents(!isHovered);
    
    ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
    size = { viewportPanelSize.x, viewportPanelSize.y };
    
    ImGui::Image(Renderer::GetCurrentFrame().viewportDescriptor, ImVec2{size.x, size.y}, ImVec2{0, 0}, ImVec2{1, 1});
    
    if (ImGui::BeginDragDropTarget())
    {
      if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
      {
        const wchar_t *path = (const wchar_t *) payload->Data;
        parent->OpenScene(path);
      }
      ImGui::EndDragDropTarget();
    }
    
    //OnImGuizmo();
    ImGui::End();
    ImGui::PopStyleVar();
  }
  void Viewport::OnImGuizmo()
  {
    // Gizmos
    Entity selectedEntity = parent->scenePanel->GetSelectedEntity();
    if (selectedEntity && gizmoType != -1)
    {
      //bool is2D = parent->IsSelectedEntity2D();
      bool is2D = false;
      ImGuizmo::SetOrthographic(is2D);
      ImGuizmo::SetDrawlist();
      
      ImGuizmo::SetRect(bounds.min.x, bounds.min.y, bounds.max.x-bounds.min.x, bounds.max.y-bounds.min.y);
      
      // Editor camera
      Matrix4 cameraProjection = is2D? editorCamera.GetProjectionMatrix2D() : editorCamera.GetProjectionMatrix3D();
      Matrix4 cameraView = is2D? editorCamera.GetViewMatrix2D() : editorCamera.GetViewMatrix3D();
      
      // Entity transform
      auto& tc = selectedEntity.GetComponent<TransformComponent>();
      //bool local = tc.HasParent();
      
      
      
      Matrix4 worldTransform = tc.GetWorldTransform();
      Matrix4 localTransform = tc.GetLocalTransform();
      ImGuizmo::MODE mode = ImGuizmo::MODE::LOCAL;
      
      // Snapping
      //bool snap = Input::IsKeyPressed(Key::LeftControl);
      bool snap = false;
      float snapValue = 0.5f; // Snap to 0.5m for translation/scale
      // Snap to 45 degrees for rotation
      if (gizmoType == ImGuizmo::OPERATION::ROTATE)
        snapValue = 45.0f;
      
      float snapValues[3] = { snapValue, snapValue, snapValue };
      //cameraProjection[1, 1] *= -1;
      //cameraProjection[1, 1] *= -1;
      //cameraProjection[2, 2] *= 0.5f;
      //cameraProjection[2, 3] = cameraProjection[2, 2]+0.5f;
      
      
      ImGuizmo::Manipulate(cameraView.Data(), cameraProjection.Data(),
                           (ImGuizmo::OPERATION)gizmoType, mode, worldTransform.Data(),
                           localTransform.Data(), snap ? snapValues : nullptr);
      
      
      
      if (ImGuizmo::IsUsing())
      {
        
        Matrix4 local = worldTransform;
        Vector3 translation, scale;
        Quaternion rotation;
        if (Matrix4::DecomposeTransform(local, translation, rotation, scale))
        {
          tc.SetLocal(translation, rotation, scale);
        }
        else
        {
          CANDY_CORE_ERROR("Failed to decompose transform!");
        }
        
        
        
        
        
      }
    }
  }
  void Viewport::OnOverlayRender()
  {
    CANDY_PROFILE_FUNCTION();
    
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