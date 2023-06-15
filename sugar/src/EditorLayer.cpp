#include "EditorLayer.hpp"
#include "imgui_internal.h"
#include <Candy/CandyEngine.hpp>
namespace Candy
{
    using namespace Graphics;
    using namespace Math;
    using namespace ECS;
    using namespace Events;
    EditorLayer::EditorLayer() : Layer("EditorLayer"), cameraController(1280.0f/720.0f), squareColor(0.2f, 0.3f, 0.8f, 1.0f)
    {}
    
    void EditorLayer::OnAttach()
    {
        checkerboardTexture = Texture::Create("assets/textures/Checkerboard.png");
        iconPlay = Texture::Create("sugar/Resources/Icons/PlayButton.png");
        iconPause = Texture::Create("sugar/Resources/Icons/PauseButton.png");
        iconSimulate = Texture::Create("sugar/Resources/Icons/SimulateButton.png");
        iconStep = Texture::Create("sugar/Resources/Icons/StepButton.png");
        iconStop = Texture::Create("sugar/Resources/Icons/StopButton.png");
        
        
        FrameBufferSpecification fbSpec;
        fbSpec.attachments = { FrameBufferTextureFormat::RGBA8, FrameBufferTextureFormat::RED_INTEGER, FrameBufferTextureFormat::Depth };
        fbSpec.width = 1280;
        fbSpec.height = 720;
        framebuffer = FrameBuffer::Create(fbSpec);
        
        editorScene = CreateSharedPtr<Scene>();
        activeScene = editorScene;
        
        
        auto commandLineArgs = Application::Instance().GetAppData().commandLineArgs;
        if (commandLineArgs.Count > 1)
        {
            auto projectFilePath = commandLineArgs[1];
            OpenProject(projectFilePath);
        }
        else
        {
            // TODO(Yan): prompt the user to select a directory
            NewProject();
            
            // If no project is opened, close Sugar
            // NOTE: this is while we don't have a new project path
            if (!OpenProject())
            {
                Application::Close();
            }
            
            
        }
        
        editorCamera = EditorCamera(30.0f, 1.778f, 0.1f, 1000.0f);
        Renderer2D::SetLineWidth(4.0f);
        CANDY_CORE_INFO("ON ATTACH");
    }
    
    void EditorLayer::OnDetach()
    {
    
    }
    
    void EditorLayer::OnUpdate()
    {
        activeScene->OnViewportResize((uint32)viewportSize.x, (uint32)viewportSize.y);
        // Resize
        if (FrameBufferSpecification spec = framebuffer->GetSpecification();
                viewportSize.x > 0.0f && viewportSize.y > 0.0f && // zero sized framebuffer is invalid
                (spec.width != (uint32)viewportSize.x || spec.height != (uint32)viewportSize.y))
        {
            framebuffer->Resize((uint32_t)viewportSize.x, (uint32_t)viewportSize.y);
            cameraController.OnResize(viewportSize.x, viewportSize.y);
            editorCamera.SetViewportSize(viewportSize.x, viewportSize.y);
        }
        // Render
        Renderer2D::ResetStats();
        framebuffer->Bind();
        RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        RenderCommand::Clear();
        
        // Clear our entity ID attachment to -1
        framebuffer->ClearAttachment(1, -1);
        
        
        switch (sceneState)
        {
            case SceneState::Edit:
            {
                if (viewportFocused)
                {
                    cameraController.OnUpdate();
                }
                
                editorCamera.OnUpdate();
                
                
                activeScene->OnUpdateEditor(editorCamera);
                break;
            }
            case SceneState::Simulate:
            {
                editorCamera.OnUpdate();
                
                activeScene->OnUpdateSimulation(editorCamera);
                break;
            }
            case SceneState::Play:
            {
                activeScene->OnUpdateRuntime();
                break;
            }
            default:
                break;
        }
        
       
        
        Math::Vector2 mousePos = ImGui::GetMousePos();
        mousePos.x -= viewportBounds[0].x;
        mousePos.y -= viewportBounds[0].y;
        Math::Vector2 viewSize = viewportBounds[1] - viewportBounds[0];
        mousePos.y = viewSize.y - mousePos.y;
        int mouseX = (int)mousePos.x;
        int mouseY = (int)mousePos.y;
        
        
        
        if (mouseX >= 0 && mouseY >= 0 && mouseX < (int)viewSize.x && mouseY < (int)viewSize.y)
        {
            int pixelData = framebuffer->ReadPixel(1, mouseX, mouseY);
            hoveredEntity = pixelData == -1 ? Entity() : Entity((entt::entity)pixelData, activeScene.get());
        }
        
        
        
        OnOverlayRender();
        
        
        
        framebuffer->Unbind();
        
        
    
    }
    
    void EditorLayer::OnRenderUI()
    {
        // Note: Switch this to true to enable dockspace
        static bool dockspaceOpen = true;
        static bool opt_fullscreen_persistant = true;
        bool opt_fullscreen = opt_fullscreen_persistant;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
        
        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->Pos);
            ImGui::SetNextWindowSize(viewport->Size);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        
        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;
        
        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        
        
        ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
        ImGui::PopStyleVar();
        
        if (opt_fullscreen)
            ImGui::PopStyleVar(2);
        
        
        
        // DockSpace
        ImGuiIO& io = ImGui::GetIO();
        ImGuiStyle& style = ImGui::GetStyle();
        float minWinSizeX = style.WindowMinSize.x;
        style.WindowMinSize.x = 370.0f;
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }
        
        style.WindowMinSize.x = minWinSizeX;
        
        
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Open Project...", "Ctrl+O"))
                    OpenProject();
                
                ImGui::Separator();
                
                if (ImGui::MenuItem("New Scene", "Ctrl+N"))
                    NewScene();
                
                if (ImGui::MenuItem("Save Scene", "Ctrl+S"))
                    SaveScene();
                
                if (ImGui::MenuItem("Save Scene As...", "Ctrl+Shift+S"))
                    SaveSceneAs();
                
                ImGui::Separator();
                
                if (ImGui::MenuItem("Exit"))
                    Application::Close();
                
                ImGui::EndMenu();
            }
            
            if (ImGui::BeginMenu("Script"))
            {
                if (ImGui::MenuItem("Reload assembly", "Ctrl+R"))
                    //Scripting::ScriptEngine::ReloadAssembly();
                
                ImGui::EndMenu();
            }
            
            ImGui::EndMenuBar();
        }
        
        
        sceneHierarchyPanel.OnRenderUI();
        
        //TODO Content browser panel ui render is broken
        contentBrowserPanel->OnRenderUI();
        
        
        
        ImGui::Begin("Stats");
        
        auto stats = Renderer2D::GetStats();
        ImGui::Text("Renderer2D Stats:");
        ImGui::Text("Draw Calls: %d", stats.drawCalls);
        ImGui::Text("Quads: %d", stats.quadCount);
        ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
        ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
        
        ImGui::End();
        
        
        
        ImGui::Begin("Settings");
        ImGui::Checkbox("Show physics colliders", &showPhysicsColliders);
        ImGui::End();
        
        
        
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
        ImGui::Begin("Viewport");
        auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
        auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
        auto viewportOffset = ImGui::GetWindowPos();
        viewportBounds[0] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
        viewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };
        
        viewportFocused = ImGui::IsWindowFocused();
        viewportHovered = ImGui::IsWindowHovered();
        
        Application::Instance().GetUILayer()->BlockEvents(!viewportHovered);
        
        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        viewportSize = { viewportPanelSize.x, viewportPanelSize.y };
        
        uint64_t textureID = framebuffer->GetColorAttachmentRendererID();
        ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ viewportSize.x, viewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
        
        if (ImGui::BeginDragDropTarget())
        {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
            {
                const wchar_t* path = (const wchar_t*)payload->Data;
                OpenScene(path);
            }
            ImGui::EndDragDropTarget();
        }
        
        // Gizmos
        Entity selectedEntity = sceneHierarchyPanel.GetSelectedEntity();
        if (selectedEntity && gizmoType != -1)
        {
            //ImGuizmo::SetOrthographic(false);
            //ImGuizmo::SetDrawlist();
            
            //ImGuizmo::SetRect(viewportBounds[0].x, viewportBounds[0].y, viewportBounds[1].x - viewportBounds[0].x, viewportBounds[1].y - viewportBounds[0].y);
            
            // Camera
            
            // Editor camera
            const Math::Matrix4& cameraProjection = editorCamera.GetProjectionMatrix();
            Math::Matrix4 cameraView = editorCamera.GetViewMatrix();
            
            // Entity transform
            auto& tc = selectedEntity.GetComponent<TransformComponent>();
            Math::Matrix4 transform = tc.GetTransform();
            
            // Snapping
            /*bool snap = Input::IsKeyPressed(Key::LeftControl);
            float snapValue = 0.5f; // Snap to 0.5m for translation/scale
            // Snap to 45 degrees for rotation
            if (gizmoType == ImGuizmo::OPERATION::ROTATE)
                snapValue = 45.0f;
            
            float snapValues[3] = { snapValue, snapValue, snapValue };
            
            ImGuizmo::Manipulate(cameraView.ValuePtr(), cameraProjection.ValuePtr(),
                                 (ImGuizmo::OPERATION)gizmoType, ImGuizmo::LOCAL, &transform[0],
                                 nullptr, snap ? snapValues : nullptr);
            
            if (ImGuizmo::IsUsing())
            {
                Math::Vector3 position, rotation, scale;
                Math::Matrix4::DecomposeTransform(transform, position, rotation, scale);
                
                Math::Vector3 deltaRotation = rotation - tc.rotation;
                tc.position = position;
                tc.rotation += deltaRotation;
                tc.scale = scale;
            }*/
        }
        
        
        ImGui::End();
        ImGui::PopStyleVar();
        
        UI_Toolbar();
        
        ImGui::End();
    
    }
    
    void EditorLayer::OnEvent(Event &e)
    {
        cameraController.OnEvent(e);
        if (sceneState == SceneState::Edit)
        {
            editorCamera.OnEvent(e);
        }
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<KeyPressedEvent>(CANDY_BIND_EVENT_FUNCTION(EditorLayer::OnKeyPressed));
        dispatcher.Dispatch<MousePressedEvent>(CANDY_BIND_EVENT_FUNCTION(EditorLayer::OnMouseButtonPressed));
    
    }
    
    bool EditorLayer::OnKeyPressed(KeyPressedEvent &e)
    {
        // Shortcuts
        if (e.IsRepeat())
            return false;
        
        bool control = Input::IsKeyPressed(Key::LeftControl) || Input::IsKeyPressed(Key::RightControl);
        bool shift = Input::IsKeyPressed(Key::LeftShift) || Input::IsKeyPressed(Key::RightShift);
        
        switch (e.GetKeyCode())
        {
            case Key::N:
            {
                if (control)
                    NewScene();
                
                break;
            }
            case Key::O:
            {
                if (control)
                    OpenProject();
                
                break;
            }
            case Key::S:
            {
                if (control)
                {
                    if (shift)
                        SaveSceneAs();
                    else
                        SaveScene();
                }
                
                break;
            }
                
                // Scene Commands
            case Key::D:
            {
                if (control)
                    OnDuplicateEntity();
                
                break;
            }
                
            
        }
        
        return false;
    }
    
    bool EditorLayer::OnMouseButtonPressed(MousePressedEvent &e)
    {
        if (e.GetButton() == Mouse::ButtonLeft)
        {
            /*if (viewportHovered && !ImGuizmo::IsOver() && !Input::IsKeyPressed(Key::LeftAlt))
                sceneHierarchyPanel.SetSelectedEntity(hoveredEntity);*/
        }
        return false;
    }
    
    void EditorLayer::OnOverlayRender()
    {
        if (sceneState == SceneState::Play)
        {
            Entity camera = activeScene->GetPrimaryCameraEntity();
            if (!camera)
                return;
            
            Renderer2D::BeginScene(camera.GetComponent<CameraComponent>().camera, camera.GetComponent<TransformComponent>().GetTransform());
        }
        else
        {
            Renderer2D::BeginScene(editorCamera);
        }
        
        if (showPhysicsColliders)
        {
        
        
        
        }
        
        // Draw selected entity outline
        if (Entity selectedEntity = sceneHierarchyPanel.GetSelectedEntity())
        {
            const TransformComponent& transform = selectedEntity.GetComponent<TransformComponent>();
            Renderer2D::DrawRect(transform.GetTransform(), Math::Vector4(1.0f, 0.5f, 0.0f, 1.0f));
        }
        
        Renderer2D::EndScene();
    }
    
    void EditorLayer::NewProject()
    {
        Project::New();
    }
    
    bool EditorLayer::OpenProject()
    {
        std::string filepath = FileDialogs::OpenFile("Candy Project (*.cproj)\0*.cproj\0");
        if (filepath.empty())
        {
            CANDY_CORE_WARN("Filepath: {} is empty", filepath);
            return false;
        }
        OpenProject(filepath);
        return true;
    }
    
    void EditorLayer::OpenProject(const std::filesystem::path &path)
    {
        if (Project::Load(path))
        {
            //TODO Fix Scripting Engine Init
            //Scripting::ScriptEngine::Init();
            auto startScenePath = Project::GetAssetFilePath(Project::GetActive()->GetConfig().startScene);
            OpenScene(startScenePath);
            contentBrowserPanel = CreateUniquePtr<ContentBrowserPanel>();
        }
    
    }
    
    void EditorLayer::SaveProject()
    {
        //Project::SaveActive();
    }
    
    void EditorLayer::NewScene()
    {
        activeScene = CreateSharedPtr<Scene>();
        sceneHierarchyPanel.SetContext(activeScene);
        
        editorScenePath = std::filesystem::path();
    
    }
    
    void EditorLayer::OpenScene()
    {
        std::string filepath = FileDialogs::OpenFile("Candy Scene (*.candy)\0*.candy\0");
        if (!filepath.empty())
            OpenScene(filepath);
    
    }
    
    void EditorLayer::OpenScene(const std::filesystem::path &path)
    {
        if (sceneState != SceneState::Edit)
        {
            OnSceneStop();
        }
        
        if (path.extension().string() != ".candy")
        {
            CANDY_WARN("Could not load {0} - not a scene file", path.string());
            return;
        }
        
        SharedPtr<Scene> newScene = CreateSharedPtr<Scene>();
        SceneSerializer serializer(newScene);
        if (serializer.Deserialize(path.string()))
        {
            editorScene = newScene;
            sceneHierarchyPanel.SetContext(editorScene);
            
            activeScene = editorScene;
            editorScenePath = path;
        }
    
    }
    
    void EditorLayer::SaveScene()
    {
        if (!editorScenePath.empty())
        {
            SerializeScene(activeScene, editorScenePath);
        }
        else
        {
            SaveSceneAs();
            
        }
    }
    
    void EditorLayer::SaveSceneAs()
    {
        std::string filepath = FileDialogs::SaveFile("Candy Scene (*.candy)\0*.candy\0");
        if (!filepath.empty())
        {
            SerializeScene(activeScene, filepath);
            editorScenePath = filepath;
        }
    
    }
    
    void EditorLayer::SerializeScene(SharedPtr<Scene> scene, const std::filesystem::path &path)
    {
        SceneSerializer serializer(scene);
        serializer.Serialize(path.string());
    }
    
    void EditorLayer::OnScenePlay()
    {
        if (sceneState == SceneState::Simulate)
            OnSceneStop();
        
        sceneState = SceneState::Play;
        
        activeScene = Scene::Copy(editorScene);
        activeScene->OnRuntimeStart();
        
        sceneHierarchyPanel.SetContext(activeScene);
    
    }
    
    void EditorLayer::OnSceneSimulate()
    {
        if (sceneState == SceneState::Play)
            OnSceneStop();
        
        sceneState = SceneState::Simulate;
        
        activeScene = Scene::Copy(editorScene);
        activeScene->OnSimulationStart();
        
        sceneHierarchyPanel.SetContext(activeScene);
    }
    
    void EditorLayer::OnSceneStop()
    {/*
        CANDY_CORE_ASSERT(sceneState == SceneState::Play || sceneState == SceneState::Simulate);
        
        if (sceneState == SceneState::Play)
            activeScene->OnRuntimeStop();
        else if (sceneState == SceneState::Simulate)
            activeScene->OnSimulationStop();
        
        sceneState = SceneState::Edit;
        
        activeScene = editorScene;
        
        sceneHierarchyPanel.SetContext(activeScene);*/
    
    }
    
    void EditorLayer::OnScenePause()
    {
        if (sceneState == SceneState::Edit)
            return;
        
        activeScene->SetPaused(true);
    }
    
    void EditorLayer::OnDuplicateEntity()
    {
        /*if (sceneState != SceneState::Edit)
            return;
        
        Entity selectedEntity = sceneHierarchyPanel.GetSelectedEntity();
        if (selectedEntity)
        {
            Entity newEntity = editorScene->DuplicateEntity(selectedEntity);
            sceneHierarchyPanel.SetSelectedEntity(newEntity);
        }*/
    
    }
    
    void EditorLayer::UI_Toolbar()
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 2));
        ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(0, 0));
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
        auto& colors = ImGui::GetStyle().Colors;
        const auto& buttonHovered = colors[ImGuiCol_ButtonHovered];
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(buttonHovered.x, buttonHovered.y, buttonHovered.z, 0.5f));
        const auto& buttonActive = colors[ImGuiCol_ButtonActive];
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(buttonActive.x, buttonActive.y, buttonActive.z, 0.5f));
        
        ImGui::Begin("##toolbar", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
        
        bool toolbarEnabled = (bool)activeScene;
        
        ImVec4 tintColor = ImVec4(1, 1, 1, 1);
        if (!toolbarEnabled)
            tintColor.w = 0.5f;
        
        float size = ImGui::GetWindowHeight() - 4.0f;
        ImGui::SetCursorPosX((ImGui::GetWindowContentRegionMax().x * 0.5f) - (size * 0.5f));
        
        bool hasPlayButton = sceneState == SceneState::Edit || sceneState == SceneState::Play;
        bool hasSimulateButton = sceneState == SceneState::Edit || sceneState == SceneState::Simulate;
        bool hasPauseButton = sceneState != SceneState::Edit;
        
        if (hasPlayButton)
        {
            SharedPtr<Texture> icon = (sceneState == SceneState::Edit || sceneState == SceneState::Simulate) ? iconPlay : iconStop;
            if (ImGui::ImageButton((ImTextureID)(uint64_t)icon->GetRendererID(), ImVec2(size, size), ImVec2(0, 0), ImVec2(1, 1), 0, ImVec4(0.0f, 0.0f, 0.0f, 0.0f), tintColor) && toolbarEnabled)
            {
                if (sceneState == SceneState::Edit || sceneState == SceneState::Simulate)
                    OnScenePlay();
                else if (sceneState == SceneState::Play)
                    OnSceneStop();
            }
        }
        
        if (hasSimulateButton)
        {
            if (hasPlayButton)
                ImGui::SameLine();
            
            SharedPtr<Texture> icon = (sceneState == SceneState::Edit || sceneState == SceneState::Play) ? iconSimulate : iconStop;
            if (ImGui::ImageButton((ImTextureID)(uint64_t)icon->GetRendererID(), ImVec2(size, size), ImVec2(0, 0), ImVec2(1, 1), 0, ImVec4(0.0f, 0.0f, 0.0f, 0.0f), tintColor) && toolbarEnabled)
            {
                if (sceneState == SceneState::Edit || sceneState == SceneState::Play)
                    OnSceneSimulate();
                else if (sceneState == SceneState::Simulate)
                    OnSceneStop();
            }
        }
        if (hasPauseButton)
        {
            bool isPaused = activeScene->IsPaused();
            ImGui::SameLine();
            {
                SharedPtr<Texture> icon = iconPause;
                if (ImGui::ImageButton((ImTextureID)(uint64_t)icon->GetRendererID(), ImVec2(size, size), ImVec2(0, 0), ImVec2(1, 1), 0, ImVec4(0.0f, 0.0f, 0.0f, 0.0f), tintColor) && toolbarEnabled)
                {
                    activeScene->SetPaused(!isPaused);
                }
            }
            
            // Step button
            if (isPaused)
            {
                ImGui::SameLine();
                {
                    SharedPtr<Texture> icon = iconStep;
                    isPaused = activeScene->IsPaused();
                    if (ImGui::ImageButton((ImTextureID)(uint64_t)icon->GetRendererID(), ImVec2(size, size), ImVec2(0, 0), ImVec2(1, 1), 0, ImVec4(0.0f, 0.0f, 0.0f, 0.0f), tintColor) && toolbarEnabled)
                    {
                        activeScene->Step();
                    }
                }
            }
        }
        ImGui::PopStyleVar(2);
        ImGui::PopStyleColor(3);
        ImGui::End();
    
    }
}