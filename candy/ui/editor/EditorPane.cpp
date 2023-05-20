#include "EditorPane.hpp"
#include "EditorLayout.hpp"
#include "imgui.h"
#include "imgui_internal.h"
#include "../core/widget/WidgetAll.hpp"
namespace Candy::UI {
        EditorPane::EditorPane(EditorLayout* parentLayout, const String& paneName, Math::Direction2 dockingDirection, float sizePercentage) : parent(parentLayout), name(paneName),
        direction(dockingDirection), sizePercent(sizePercentage)
        {

        }

        EditorPane::~EditorPane()
        {
            for (int i=0; i<widgets.size(); i++)
            {
                delete widgets[i];
            }
        }


        void EditorPane::Init()
        {
            id = ImGui::DockBuilderSplitNode(parent->GetID(), direction.ToImGuiDir(), sizePercent, nullptr, &parent->GetRefID());
            ImGui::DockBuilderDockWindow(name.ToCharStr(), id);
        }

        void EditorPane::OnRender()
        {
            ImGui::Begin(name.ToCharStr());
            for (int i=0; i<widgets.size(); i++)
            {
                widgets[i]->OnRender();
            }

            ImGui::End();

        }

        void EditorPane::AddWidget(WidgetBase* widget)
        {
            widgets.push_back(widget);
        }

        void EditorPane::AddSpacer(int amount)
        {
            widgets.push_back(new Spacer(amount));

        }

        EditorLayout& EditorPane::GetParent(){return *parent;}
        const String& EditorPane::GetName()const{return name;}
        Math::Direction2 EditorPane::GetDirection()const{return direction;}
        uint EditorPane::GetID()const{return id;}
        float EditorPane::GetSizePercent()const{return sizePercent;}
}