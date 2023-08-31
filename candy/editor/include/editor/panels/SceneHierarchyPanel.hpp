#pragma once

#include <candy/ecs/Scene.hpp>
#include <candy/ecs/Entity.hpp>
namespace Candy
{
  class SceneHierarchyPanel
  {
  private:
    SharedPtr<ECS::Scene> context;
    ECS::Entity selectionContext;
    bool isSelection2D=false;
  private:
    template<typename T>
    void DisplayAddComponentEntry(const std::string& entryName);
    
    void DrawEntityNode(ECS::Entity entity);
    void DrawComponents(ECS::Entity entity);
  public:
    SceneHierarchyPanel() = default;
    explicit SceneHierarchyPanel(const SharedPtr<ECS::Scene>& scene);
    
    void SetContext(const SharedPtr<ECS::Scene>& scene);
    
    void OnRenderUI();
    
    [[nodiscard]] ECS::Entity GetSelectedEntity() const { return selectionContext; }
    void SetSelectedEntity(ECS::Entity entity);
    [[nodiscard]] bool IsSelectedEntity2D()const { return isSelection2D; }
    
    
  };
}