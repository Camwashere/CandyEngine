#pragma once
#include <candy/app/Layer.hpp>
#include <candy/app/Project.hpp>
#include "candy/graphics/material/Material.hpp"
#include <candy/ecs/Scene.hpp>
#include <candy/graphics/camera/CameraController.hpp>
#include <candy/ui/Gizmo.hpp>
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
    SharedPtr<Gizmo> gizmo;
    SharedPtr<Candy::ECS::Scene> activeScene;
    std::filesystem::path activeScenePath;
    SharedPtr<SceneHierarchyPanel> scenePanel;
    UniquePtr<ContentBrowserPanel> contentBrowserPanel;
    SharedPtr<Viewport> viewport;
    DebugPanel debugPanel;
    
    
  private:
    bool OnMouseButtonPressed(Events::MousePressedEvent& event);
    bool OnKeyPressed(Events::KeyPressedEvent& event);
    void MenuBar();
    
    bool OpenProject();
    void SaveProject();
    
    void NewScene();
    void OpenScene();
    void OpenScene(const std::filesystem::path& path);
    void SaveScene();
    void SaveSceneAs();
    
    void SerializeScene(SharedPtr<ECS::Scene> scene, const std::filesystem::path& path);

  public:
    explicit EditorLayer();
    
    
    void OnAttach() override;
    void OnDetach() override;
    void OnUpdate() override;
    void OnRenderUI() override;
    void OnEvent(Events::Event& event) override;
    [[nodiscard]] bool IsSelectedEntity2D()const;
    
  private:
    friend class Viewport;
  };
}