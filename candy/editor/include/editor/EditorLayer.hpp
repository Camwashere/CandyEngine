#pragma once
#include <candy/app/Layer.hpp>
#include <candy/app/Project.hpp>
#include "candy/graphics/material/Material.hpp"
#include <candy/ecs/Scene.hpp>
#include <candy/graphics/camera/CameraController.hpp>
#include "panels/ContentBrowserPanel.hpp"
#include "panels/SceneHierarchyPanel.hpp"
#include "panels/Viewport.hpp"
#include "panels/DebugPanel.hpp"
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
    SharedPtr<Candy::ECS::Scene> activeScene;
    SharedPtr<SceneHierarchyPanel> scenePanel;
    UniquePtr<ContentBrowserPanel> contentBrowserPanel;
    SharedPtr<Viewport> viewport;
    DebugPanel debugPanel;
    ECS::Entity testEntity;
    ECS::Entity secondEntity;
    //bool selectionView=false;
    
  private:
    bool OnMouseButtonPressed(Events::MousePressedEvent& event);
    bool OnKeyPressed(Events::KeyPressedEvent& event);
    void MenuBar();
    bool OpenProject();
    void SaveProject();

  public:
    explicit EditorLayer(Project* project);
    
    
    void OnAttach() override;
    void OnDetach() override;
    void OnUpdate() override;
    void OnRenderUI() override;
    void OnEvent(Events::Event& event) override;
  };
}