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
  
  void RenderRect(const SharedPtr<Gum::Rectangle>& rect, float step = 1.f)
  {
    //Math::Vector2 shapePos = rect->GetPosition();
    //Math::Vector2 shapeSize = rect->GetSize();
    Math::Vector2 arcSize = rect->GetArcSize();
    float strokeWidth = rect->GetStrokeWidth();
    Color fillColor = rect->GetFillColor();
    Color strokeColor = rect->GetStrokeColor();
    
    Math::Vector2 minSize = rect->GetMinSize();
    Math::Vector2 maxSize = rect->GetMaxSize();
    Math::Vector2 prefSize = rect->GetPrefSize();
    
    ImGui::Begin(rect->GetName().c_str());
    ImGui::DragFloat("Step", &step, 0.01f, 0.0f, FLT_MAX);
    //ImGui::DragFloat2("Shape Position", &shapePos.x, step, 0.0f, FLT_MAX);
    //ImGui::DragFloat2("Shape Size", &shapeSize.x, step, 0.0f, FLT_MAX);
    ImGui::DragFloat2("Arc size", &arcSize.x, 0.05f, 0.0f, 1.0f);
    ImGui::DragFloat("Stroke Width", &strokeWidth, step, 0.0f, FLT_MAX);
    ImGui::ColorEdit4("Fill Color", &fillColor.r);
    ImGui::ColorEdit4("Stroke Color", &strokeColor.r);
    
    ImGui::DragFloat2("Min Size", &minSize.x, step, 0.0f, FLT_MAX);
    ImGui::DragFloat2("Max Size", &maxSize.x, step, 0.0f, FLT_MAX);
    ImGui::DragFloat2("Pref Size", &prefSize.x, step, 0.0f, FLT_MAX);
    
    ImGui::End();
    
    //rect->SetPosition(shapePos);
    //rect->SetSize(shapeSize);
    rect->SetArcSize(arcSize);
    rect->SetStrokeWidth(strokeWidth);
    rect->SetFillColor(fillColor);
    rect->SetStrokeColor(strokeColor);
    rect->SetMinSize(minSize);
    rect->SetMaxSize(maxSize);
    rect->SetPrefSize(prefSize);
    
    
  }
  
  void RenderLayout(const SharedPtr<Gum::BoxLayout>& layout, float step=100.f)
  {
    ImGui::Begin("Layout");
    ImGui::SeparatorText(layout->GetName().c_str());
    float spacing = layout->GetSpacing();
    Math::Vector2 layoutPos = layout->GetLayoutPosition();
    Math::Vector2 minSize = layout->GetMinSize();
    Math::Vector2 maxSize = layout->GetMaxSize();
    Math::Vector2 prefSize = layout->GetPrefSize();
    Color backgroundColor = layout->GetBackgroundColor();
    
    ImGui::DragFloat("Spacing", &spacing, 1.0f, 0.0f, FLT_MAX);
    ImGui::DragFloat2("Layout Pos", &layoutPos.x, step, 0.0f, FLT_MAX);
    ImGui::DragFloat2("Min Size", &minSize.x, step, 0.0f, FLT_MAX);
    ImGui::DragFloat2("Max Size", &maxSize.x, step, 0.0f, FLT_MAX);
    ImGui::DragFloat2("Pref Size", &prefSize.x, step, 0.0f, FLT_MAX);
    ImGui::ColorEdit4("Background Color", &backgroundColor.r);
    
    layout->SetSpacing(spacing);
    layout->SetLayoutPosition(layoutPos);
    layout->SetMinSize(minSize);
    layout->SetMaxSize(maxSize);
    layout->SetPrefSize(prefSize);
    layout->SetBackgroundColor(backgroundColor);
    
    ImGui::End();
  }
  void DebugPanel::OnRenderUI()
  {
    CANDY_PROFILE_FUNCTION();
    if (enabled)
    {
      Gum::Root& root = Gum::GumInstance::GetCurrentContext().sceneGraph.Root();
      Color backgroundColor = root.GetBackgroundColor();
      
      SharedPtr<Gum::Rectangle> rect = Gum::GumInstance::GetCurrentContext().testObject;
      SharedPtr<Gum::Rectangle> rect1 = Gum::GumInstance::GetCurrentContext().testObject2;
      SharedPtr<Gum::Rectangle> rect2 = Gum::GumInstance::GetCurrentContext().testObject3;
      SharedPtr<Gum::Rectangle> rect3 = Gum::GumInstance::GetCurrentContext().testObject4;
      
      SharedPtr<Gum::BoxLayout> layout = Gum::GumInstance::GetCurrentContext().testLayout;
     /* Math::Vector2 shapePos = rect->GetPosition();
      Math::Vector2 shapeSize = rect->GetSize();
      Math::Vector2 arcSize = rect->GetArcSize();
      float strokeWidth = rect->GetStrokeWidth();
      Color fillColor = rect->GetFillColor();
      Color strokeColor = rect->GetStrokeColor();*/
      
      ImGui::Begin("Debug");
      ImGui::SeparatorText("Root");
      ImGui::ColorEdit4("Background Color", &backgroundColor.r);
      
      
      RenderRect(rect);
      RenderRect(rect1);
      RenderRect(rect2);
      RenderRect(rect3);
      RenderLayout(layout);
      /*ImGui::SeparatorText("Rectangle");
      ImGui::DragFloat("Step", &step, 0.01f, 0.0f, FLT_MAX);
      ImGui::DragFloat2("Shape Position", &shapePos.x, step, 0.0f, FLT_MAX);
      ImGui::DragFloat2("Shape Size", &shapeSize.x, step, 0.0f, FLT_MAX);
      ImGui::DragFloat2("Arc size", &arcSize.x, 0.05f, 0.0f, 1.0f);
      ImGui::DragFloat("Stroke Width", &strokeWidth, step, 0.0f, FLT_MAX);
      ImGui::ColorEdit4("Fill Color", &fillColor.r);
      ImGui::ColorEdit4("Stroke Color", &strokeColor.r);*/
      
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
      
      root.SetBackgroundColor(backgroundColor);
      /*rect->SetPosition(shapePos);
      rect->SetSize(shapeSize);
      rect->SetArcSize(arcSize);
      rect->SetStrokeWidth(strokeWidth);
      rect->SetFillColor(fillColor);
      rect->SetStrokeColor(strokeColor);*/
      
    }
    
  }
  
  
}