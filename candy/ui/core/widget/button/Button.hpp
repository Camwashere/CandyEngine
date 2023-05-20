#pragma once
#include "../base/WidgetBase.hpp"
namespace Candy::UI{

    class Button : public WidgetBase
    {
    private:
        Math::Vector2 position;
        Math::Vector2 size;
        int buttonFlags=0;

        uint32 color=ImGuiCol_Button;
        uint32 hoveredColor=ImGuiCol_ButtonHovered;
        uint32 activeColor=ImGuiCol_ButtonActive;

        bool isHovered=false;
        bool isHeld=false;



    public:
        Button(const String& name) : WidgetBase(name), position(0, 0), size(50, 50){}
        Button(const String& name, const Math::Vector2& buttonPosition, const Math::Vector2& buttonSize, const Color& backgroundColor, const Color& buttonHoveredColor, const Color& buttonActiveColor)
            : WidgetBase(name), position(buttonPosition), size(buttonSize), color(backgroundColor.Pack()),hoveredColor(buttonHoveredColor.Pack()), activeColor(buttonActiveColor.Pack())
        {

        }

        void SetColor(const Color& value){color=value.Pack();}
        void SetHoveredColor(const Color& value){hoveredColor=value.Pack();}
        void SetActiveColor(const Color& value){activeColor=value.Pack();}


    public:
        void OnRender() override
        {

            ImGuiWindow* window = ImGui::GetCurrentWindow();
            if (window->SkipItems)
            {
                return;
            }

            const char* label = name.ToCharStr();

            ImGuiContext& g = *GImGui;
            const ImGuiStyle& style = g.Style;
            ImGui::PushID(id);
            const Math::Vector2 label_size = ImGui::CalcTextSize(label, NULL, true);

            Math::Vector2 cursorPos = window->DC.CursorPos;
            if ((buttonFlags & ImGuiButtonFlags_AlignTextBaseLine) && style.FramePadding.y < window->DC.CurrLineTextBaseOffset) // Try to vertically align buttons that are smaller/have no padding so that text baseline matches (bit hacky, since it shouldn't be a flag)
                cursorPos.y += window->DC.CurrLineTextBaseOffset - style.FramePadding.y;
            Math::Vector2 itemSize = ImGui::CalcItemSize(size, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

            const Shape::Rectangle bb(cursorPos, cursorPos + size);
            ImGui::ItemSize(itemSize, style.FramePadding.y);
            if (!ImGui::ItemAdd(bb, id))
            {
                return;
            }




            //bool hovered, held;
            bool pressed = ImGui::ButtonBehavior(bb, id, &isHovered, &isHeld, buttonFlags);

            // Render
            const ImU32 col = ImGui::GetColorU32((isHeld && isHovered) ? activeColor : isHovered ? hoveredColor : color);
            ImGui::RenderNavHighlight(bb, id);
            ImGui::RenderFrame(bb.min, bb.max, col, true, style.FrameRounding);

            if (g.LogEnabled)
            {
                ImGui::LogSetNextTextDecoration("[", "]");
            }
            ImGui::RenderTextClipped(bb.min + style.FramePadding, bb.max - style.FramePadding, label, NULL,
                                     reinterpret_cast<const ImVec2 *>(&label_size), style.ButtonTextAlign,
                                     reinterpret_cast<const ImRect *>(&bb));
            if (pressed)
            {
                std::cout << "Clicked" << std::endl;
            }


            IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags);

            ImGui::PopID();




        }
    };


}
