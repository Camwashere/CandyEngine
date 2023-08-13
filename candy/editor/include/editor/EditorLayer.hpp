#pragma once
#include <candy/app/Layer.hpp>
#include <candy/app/Project.hpp>
#include "candy/graphics/material/Material.hpp"
#include <candy/ecs/Scene.hpp>
#include <candy/graphics/camera/CameraController.hpp>
#include "panels/ContentBrowserPanel.hpp"
#include "panels/Viewport.hpp"
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
    Graphics::Mesh mesh;
    //Candy::SharedPtr<Candy::Graphics::Shader> shader;
    //Candy::SharedPtr<Candy::Graphics::VertexArray> vertexArray;
    Candy::SharedPtr<Candy::ECS::Scene> activeScene;
    //Candy::Graphics::CameraController cameraController;
    UniquePtr<ContentBrowserPanel> contentBrowserPanel;
    SharedPtr<Viewport> viewport;
    ECS::Entity testEntity;
    //std::vector<Object> objects;
    
    //std::vector<Math::Vector3> positions = {{0.0f, 0.0f, 0.0f}, {0.5f, 0.0f, 0.0f}, {0.0f, 0.5f, 0.0f}};
    
    //Candy::Graphics::Material material;
    //Color color;
  public:
    explicit EditorLayer(Project* project);
    
    
    void OnAttach() override;
    void OnDetach() override;
    void OnUpdate() override;
    void OnRenderUI() override;
    void OnEvent(Events::Event& event) override;
  };
}