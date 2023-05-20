#include "EditorLayout.hpp"
#include <candy/CandyEngine.hpp>
#include "EditorPane.hpp"
#include "imgui.h"
#include "imgui_internal.h"
namespace Candy{
    using namespace Math;
    namespace UI {
    EditorLayout::EditorLayout(const String& layoutName) : name(layoutName), needsInit(true)
    {
        windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        dockspaceFlags = ImGuiDockNodeFlags_PassthruCentralNode;

        if (dockspaceFlags & ImGuiDockNodeFlags_PassthruCentralNode) {
            windowFlags |= ImGuiWindowFlags_NoBackground;
        }

        viewport = ImGui::GetMainViewport();





    }

    void EditorLayout::Init()
    {
        needsInit=false;
        ImGui::DockBuilderRemoveNode(dockspaceID);
        ImGui::DockBuilderAddNode(dockspaceID, dockspaceFlags | ImGuiDockNodeFlags_DockSpace);
        ImGui::DockBuilderSetNodeSize(dockspaceID, viewport->Size);

        if (leftPane)
        {
            leftPane->Init();
        }
        if (rightPane)
        {
            rightPane->Init();
        }
        if (topPane)
        {
            topPane->Init();
        }
        if (bottomPane)
        {
            bottomPane->Init();
        }

        ImGui::DockBuilderFinish(dockspaceID);
    }
    
    void EditorLayout::OnRender()
    {
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, Vector2(0.0f, 0.0f));

        ImGui::Begin(name.ToCharStr(), nullptr, windowFlags);
        ImGui::PopStyleVar();
        ImGui::PopStyleVar(2);

        dockspaceID = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspaceID, Vector2(0.0f, 0.0f), dockspaceFlags);



        if (needsInit)
        {
            Init();

        }
        ImGui::End();



        if (leftPane)
        {
            leftPane->OnRender();
        }
        if (rightPane)
        {
            rightPane->OnRender();
        }
        if (topPane)
        {
            topPane->OnRender();
        }
        if (bottomPane)
        {
            bottomPane->OnRender();
        }


        /*ImGui::Begin("Right");
        ImGui::DragFloat3("Light Position", &light.position[0]);
        ImGui::ColorEdit3("Light Color", &light.color[0]);
        ImGui::DragFloat("Light Ambient", &light.ambientStrength, 0.01f, 0.0f, 1.0f);
        ImGui::Spacing();
        ImGui::DragFloat("Metallic", &material.metallic, 0.01f, 0.0f, 1.0f);
        ImGui::DragFloat("Specular", &material.specular, 0.01f, 0.0f, Math::MAX_FLOAT);
        ImGui::DragFloat("Roughness", &material.roughness, 0.1f, 0.0f, Math::MAX_FLOAT);
        ImGui::End();*/
    }

        void EditorLayout::SetLeftPane(const String& paneName, float size)
        {
            leftPane = new EditorPane(this, paneName, Math::Direction2::LEFT, size);
        }
        void EditorLayout::SetRightPane(const String& paneName, float size)
        {
            rightPane = new EditorPane(this, paneName, Math::Direction2::RIGHT, size);
        }
        void EditorLayout::SetTopPane(const String& paneName, float size)
        {
            topPane = new EditorPane(this, paneName, Math::Direction2::UP, size);
        }
        void EditorLayout::SetBottomPane(const String& paneName, float size)
        {
            bottomPane = new EditorPane(this, paneName, Math::Direction2::DOWN, size);
        }
}}