#pragma once
#include <candy/app/Layer.hpp>
#include <candy/app/Project.hpp>
#include "candy/graphics/material/Material.hpp"

namespace Candy
{
  class EditorLayer : public Layer
  {
  private:
    Project* project;
    Candy::SharedPtr<Candy::Graphics::Shader> shader;
    Candy::SharedPtr<Candy::Graphics::VertexArray> vertexArray;
    Candy::Graphics::Material material;
    Color color;
  public:
    explicit EditorLayer(Project* project);
    
    
    void OnAttach() override;
    void OnDetach() override;
    void OnUpdate() override;
    void OnRenderUI() override;
    void OnEvent(Events::Event& event) override;
  };
}