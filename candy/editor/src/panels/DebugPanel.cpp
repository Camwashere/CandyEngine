#include <editor/panels/DebugPanel.hpp>
#include "imgui/imgui.h"
#include <candy/app/Application.hpp>
#include <candy/graphics/Renderer3D.hpp>
#include <candy/graphics/Renderer2D.hpp>
namespace Candy
{
  using namespace Graphics;
  static void Renderer2DDebugInfo()
  {
    ImGui::SeparatorText("Renderer2D Stats");
    Renderer2D::Stats stats = Renderer2D::GetStats();
    ImGui::Text("Draw Calls: %d", stats.drawCalls);
    ImGui::Text("Quads: %d", stats.quadCount);
    ImGui::Text("Vertices: %d", stats.vertexCount);
    ImGui::Text("Indices: %d", stats.indexCount);
    ImGui::Text("Lines: %d", stats.lineCount);
    ImGui::Text("Characters: %d", stats.textCount);
  }
  void DebugPanel::OnRenderUI()
  {
    if (enabled)
    {
      ImGui::Begin("Debug");
      
      ImGui::Text("FPS: %d", (int)Application::AverageFPS());
      
      Renderer2DDebugInfo();
      
      
      ImGui::SeparatorText("Renderer3D Stats");
      
      const auto& stats = Renderer3D::GetStats();
      ImGui::Text("Draw Calls: %d", stats.drawCalls);
      ImGui::Text("Objects: %d", stats.objectCount);
      ImGui::Text("Vertices: %d", stats.vertexCount);
      ImGui::Text("Indices: %d", stats.indexCount);
      ImGui::Text("Triangles: %d", stats.triangleCount);
      
      ImGui::End();
    }
    
  }
  
  
}