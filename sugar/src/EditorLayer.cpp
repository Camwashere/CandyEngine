#include "EditorLayer.hpp"

namespace Candy
{
    EditorLayer::EditorLayer() : Layer("EditorLayer"), squareColor(0.2f, 0.3f, 0.8f, 1.0f)
    {}
    
    void EditorLayer::OnAttach()
    {
    
    }
    
    void EditorLayer::OnDetach()
    {
    
    }
    
    void EditorLayer::OnUpdate()
    {
    
    }
    
    void EditorLayer::OnRenderUI()
    {
    
    }
    
    void EditorLayer::OnEvent(Event &e)
    {
    
    }
    
    bool EditorLayer::OnKeyPressed(KeyPressedEvent &e)
    {
        return false;
    }
    
    bool EditorLayer::OnMouseButtonPressed(MousePressedEvent &e)
    {
        return false;
    }
    
    void EditorLayer::OnOverlayRender()
    {
    
    }
    
    void EditorLayer::NewProject()
    {
    
    }
    
    bool EditorLayer::OpenProject()
    {
        return false;
    }
    
    void EditorLayer::OpenProject(const std::filesystem::path &path)
    {
    
    }
    
    void EditorLayer::SaveProject()
    {
    
    }
    
    void EditorLayer::NewScene()
    {
    
    }
    
    void EditorLayer::OpenScene()
    {
    
    }
    
    void EditorLayer::OpenScene(const std::filesystem::path &path)
    {
    
    }
    
    void EditorLayer::SaveScene()
    {
    
    }
    
    void EditorLayer::SaveSceneAs()
    {
    
    }
    
    void EditorLayer::SerializeScene(SharedPtr<Scene> scene, const std::filesystem::path &path)
    {
    
    }
    
    void EditorLayer::OnScenePlay()
    {
    
    }
    
    void EditorLayer::OnSceneSimulate()
    {
    
    }
    
    void EditorLayer::OnSceneStop()
    {
    
    }
    
    void EditorLayer::OnScenePause()
    {
    
    }
    
    void EditorLayer::OnDuplicateEntity()
    {
    
    }
    
    void EditorLayer::UI_Toolbar()
    {
    
    }
}