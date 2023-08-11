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
  
  Viewport::Viewport()
  {
  
  }
  void Viewport::OnAttach()
  {
  
  }
  void Viewport::OnUpdate()
  {
    
    
  
    
    
  }
  void Viewport::OnRenderUI()
  {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
    ImGui::Begin("Viewport");
    auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
    auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
    auto viewportOffset = ImGui::GetWindowPos();
    bounds.min = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
    bounds.max = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };
    
    
    isFocused = ImGui::IsWindowFocused();
    isHovered = ImGui::IsWindowHovered();
    
    //Application::Instance().GetUILayer().BlockEvents(!isHovered);
    
    ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
    size = { viewportPanelSize.x, viewportPanelSize.y };
    viewport.width = size.width;
    viewport.height = size.height;
    viewport.x = bounds.min.x;
    viewport.y = bounds.min.y;
   
    
   
    ImGui::Image(Renderer::GetCurrentFrame().gumDescriptor, ImVec2{size.x, size.y}, ImVec2{0, 0}, ImVec2{1, 1});
    

    ImGui::End();
    ImGui::PopStyleVar();
  }
}