#pragma once


#include "panels/SceneHierarchyPanel.hpp"
#include "panels/ContentBrowserPanel.hpp"


namespace Candy {
    
    
    class EditorLayer : public Layer
    {
    private:
        Graphics::OrthographicCameraController cameraController;
        
        // Temp
        SharedPtr<Graphics::VertexArray> squareVA;
        SharedPtr<Graphics::Shader> flatColorShader;
        SharedPtr<Graphics::FrameBuffer> framebuffer;
        
        SharedPtr<ECS::Scene> activeScene;
        SharedPtr<ECS::Scene> editorScene;
        std::filesystem::path editorScenePath;
        ECS::Entity squareEntity;
        ECS::Entity cameraEntity;
        ECS::Entity secondCamera;
        
        ECS::Entity hoveredEntity;
        
        bool primaryCamera = true;
        
        Graphics::EditorCamera editorCamera;
        
        SharedPtr<Graphics::Texture> checkerboardTexture;
        
        bool viewportFocused = false, viewportHovered = false;
        Math::Vector2 viewportSize = { 0.0f, 0.0f };
        Math::Vector2 viewportBounds[2];
        
        Color squareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
        
        int gizmoType = -1;
        
        bool showPhysicsColliders = false;
        
        enum class SceneState
        {
            Edit = 0, Play = 1, Simulate = 2
        };
        SceneState sceneState = SceneState::Edit;
        
        // Panels
        SceneHierarchyPanel sceneHierarchyPanel;
        UniquePtr<ContentBrowserPanel> contentBrowserPanel;
        
        // Editor resources
        SharedPtr<Graphics::Texture> iconPlay, iconPause, iconStep, iconSimulate, iconStop;
    public:
        EditorLayer();
        ~EditorLayer() override = default;
        
        void OnAttach() override;
        void OnDetach() override;
        
        void OnUpdate() override;
        void OnRenderUI() override;
        void OnEvent(Events::Event& e) override;
    private:
        bool OnKeyPressed(Events::KeyPressedEvent& e);
        bool OnMouseButtonPressed(Events::MousePressedEvent& e);
        
        void OnOverlayRender();
        
        void NewProject();
        bool OpenProject();
        void OpenProject(const std::filesystem::path& path);
        void SaveProject();
        
        void NewScene();
        void OpenScene();
        void OpenScene(const std::filesystem::path& path);
        void SaveScene();
        void SaveSceneAs();
        
        void SerializeScene(SharedPtr<ECS::Scene> scene, const std::filesystem::path& path);
        
        void OnScenePlay();
        void OnSceneSimulate();
        void OnSceneStop();
        void OnScenePause();
        
        void OnDuplicateEntity();
        
        // UI Panels
        void UI_Toolbar();
    
    };
    
}