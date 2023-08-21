#include <editor/panels/DebugPanel.hpp>
#include "imgui/imgui.h"
#include <candy/app/Application.hpp>
namespace Candy
{
  void DebugPanel::OnRenderUI()
  {
    if (enabled)
    {
      ImGui::Begin("Debug");
      
      ImGui::Text("FPS: %f", Application::FPS());
      ImGui::End();
    }
    
  }
}