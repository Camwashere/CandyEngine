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
    

    ImGui::End();
    ImGui::PopStyleVar();
  }
}