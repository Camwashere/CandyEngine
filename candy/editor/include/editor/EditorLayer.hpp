#pragma once
#include <candy/app/Layer.hpp>
#include <candy/app/Project.hpp>
#include "panels/ContentBrowserPanel.hpp"
#include <candy/graphics/Material.hpp>
namespace Candy
{
  class EditorLayer : public Layer
  {
  private:
    Project* project;
    UniquePtr<ContentBrowserPanel> contentBrowserPanel;
    Candy::SharedPtr<Candy::Graphics::Shader> shader;
    Candy::SharedPtr<Candy::Graphics::VertexArray> vertexArray;
    Candy::Graphics::Material material;
    Color color;
  public:
    EditorLayer(Project* project);
    
    
    void OnAttach() override;
    void OnDetach() override;
    void OnUpdate() override;
    void OnRenderUI() override;
    void OnEvent(Events::Event& event) override;
  };
}