#pragma once
#include "imgui.h"

namespace Candy::UI
{
    struct ScopedStyleColor
    {
    private:
        bool set=false;
        
    public:
        ScopedStyleColor()=default;
        ScopedStyleColor(ImGuiCol idx, ImVec4 color, bool predicate=true) : set(predicate)
        {
            if (predicate)
            {
                ImGui::PushStyleColor(idx, color);
            }
        }
        ~ScopedStyleColor()
        {
            if (set)
            {
                ImGui::PopStyleColor();
            }
        }
    };
}