#pragma once

#include <Candy/CandyEngine.hpp>
#include "panels/SceneHierarchyPanel.hpp"
#include "panels/ContentBrowserPanel.hpp"


namespace Candy {
    
    class EditorLayer : public Layer
    {
    private:
        //Hazel::OrthographicCameraController m_CameraController;
        
        // Temp
        SharedPtr<VertexArray> squareVA;
        SharedPtr<Shader> flatColorShader;
        SharedPtr<FrameBuffer> framebuffer;
        
        SharedPtr<Scene> activeScene;
        SharedPtr<Scene> editorScene;
        std::filesystem::path editorScenePath;
        Entity squareEntity;
        Entity cameraEntity;
        Entity secondCamera;
        
        Entity hoveredEntity;
        
        bool primaryCamera = true;
        
        //EditorCamera editorCamera;
        
        SharedPtr<Texture> checkerboardTexture;
        
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
        SharedPtr<Texture> iconPlay, iconPause, iconStep, iconSimulate, iconStop;
    public:
        EditorLayer();
        virtual ~EditorLayer() = default;
        
        virtual void OnAttach() override;
        virtual void OnDetach() override;
        
        void OnUpdate() override;
        virtual void OnRenderUI() override;
        void OnEvent(Event& e) override;
    private:
        bool OnKeyPressed(KeyPressedEvent& e);
        bool OnMouseButtonPressed(MousePressedEvent& e);
        
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
        
        void SerializeScene(SharedPtr<Scene> scene, const std::filesystem::path& path);
        
        void OnScenePlay();
        void OnSceneSimulate();
        void OnSceneStop();
        void OnScenePause();
        
        void OnDuplicateEntity();
        
        // UI Panels
        void UI_Toolbar();
    
    };
    
}