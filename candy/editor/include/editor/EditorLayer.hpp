#pragma once
#include <candy/app/Layer.hpp>
#include <candy/app/Project.hpp>
#include "candy/graphics/material/Material.hpp"

namespace Candy
{
  struct Object
  {
    Math::Matrix4 transform;
  };
  class EditorLayer : public Layer
  {
  private:
    Project* project;
    Candy::SharedPtr<Candy::Graphics::Shader> shader;
    Candy::SharedPtr<Candy::Graphics::VertexArray> vertexArray;
    std::vector<Object> objects;
    Object* objectSSBO;
    
    std::vector<Math::Vector3> positions = {{0.0f, 0.0f, 0.0f}, {0.5f, 0.0f, 0.0f}, {0.0f, 0.5f, 0.0f}};
    
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