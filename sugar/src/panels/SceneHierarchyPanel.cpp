#include "SceneHierarchyPanel.hpp"
#include <Candy/CandyEngine.hpp>
namespace Candy
{
    SceneHierarchyPanel::SceneHierarchyPanel(const SharedPtr<Scene>& scene)
    {
        SetContext(scene);
    }
    
    void SceneHierarchyPanel::SetContext(const SharedPtr<Scene> &scene)
    {
        context = scene;
        selectionContext={};
    }
    
    void SceneHierarchyPanel::OnRenderUI()
    {
        ImGui::Begin("Scene Hierarchy");
        if (context)
        {
        
        }
    }
}