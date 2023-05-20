#pragma once
#include "../base/WidgetBase.hpp"
namespace Candy::UI{
    class ColorEdit4 : public Widget<Color>
    {
    private:
        int colorEditFlags=0;
    public:
        ColorEdit4() : Widget<Color>(){}
        ColorEdit4(const String& name) : Widget<Color>(name){}
        ColorEdit4(const String& name, Color* value, int color_edit_flags=0) : Widget<Color>(name, value), colorEditFlags(color_edit_flags){}

    public:
        void OnRender()override
        {
            ImGui::ColorEdit4(name.ToCharStr(), &(*value)[0], colorEditFlags);
        }

    public:
        void SetColorEditFlags(int value){colorEditFlags=value;}
        int GetColorEditFlags()const{return colorEditFlags;}
    };
}

