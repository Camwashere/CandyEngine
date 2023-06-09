#pragma once
#include <Candy/ECS.hpp>
namespace Candy {
    
    class SceneHierarchyPanel
    {
    private:
        SharedPtr<ECS::Scene> context;
        ECS::Entity selectionContext;
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
        
        ECS::Entity GetSelectedEntity() const { return selectionContext; }
        void SetSelectedEntity(ECS::Entity entity);
    
    
    };
    
}