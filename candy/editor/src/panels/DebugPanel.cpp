#include <editor/panels/DebugPanel.hpp>
#include "imgui/imgui.h"
#include <candy/app/Application.hpp>
#include <candy/graphics/Renderer3D.hpp>
#include <candy/graphics/Renderer2D.hpp>
#include <gum/base/Node.hpp>
#include <gum/GumContext.hpp>
#include <gum/GumInstance.hpp>
#include <gum/shape/Rectangle.hpp>
namespace Candy
{
  using namespace Graphics;
  static void Renderer2DDebugInfo()
  {
    CANDY_PROFILE_FUNCTION();
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
    CANDY_PROFILE_FUNCTION();
    if (enabled)
    {
      SharedPtr<Gum::Rectangle> rect = Gum::GumInstance::GetCurrentContext().testObject;
      Math::Vector2 shapePos = rect->GetPosition();
      Math::Vector2 shapeSize = rect->GetSize();
      Math::Vector2 arcSize = rect->GetArcSize();
      float strokeWidth = rect->GetStrokeWidth();
      Color fillColor = rect->GetFillColor();
      Color strokeColor = rect->GetStrokeColor();
      
      ImGui::Begin("Debug");
      ImGui::DragFloat2("Shape Position", &shapePos.x, 1.f);
      ImGui::DragFloat2("Shape Size", &shapeSize.x, 1.f, 0.0f, FLT_MAX);
      ImGui::DragFloat2("Arc size", &arcSize.x, 0.5f, 0.0f, FLT_MAX);
      ImGui::DragFloat("Stroke Width", &strokeWidth, 0.05f, 0.0f, FLT_MAX);
      ImGui::ColorEdit4("Fill Color", &fillColor.r);
      ImGui::ColorEdit4("Stroke Color", &strokeColor.r);
      
      ImGui::SeparatorText("Application Stats");
      
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
      
      rect->SetPosition(shapePos);
      rect->SetSize(shapeSize);
      rect->SetArcSize(arcSize);
      rect->SetStrokeWidth(strokeWidth);
      rect->SetFillColor(fillColor);
      rect->SetStrokeColor(strokeColor);
      
    }
    
  }
  
  
}