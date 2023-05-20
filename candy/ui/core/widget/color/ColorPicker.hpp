#pragma once
#include "../base/WidgetBase.hpp"
namespace Candy::UI{
    class ColorPicker : public Widget<Color>
    {
    private:
        int colorEditFlags=0;
    public:
        ColorPicker() : Widget<Color>(){}
        ColorPicker(const String& name) : Widget<Color>(name){}
        ColorPicker(const String& name, Color* value, int color_edit_flags=0) : Widget<Color>(name, value), colorEditFlags(color_edit_flags){}

    public:
        void OnRender()override
        {
            ImGui::ColorPicker4(name.ToCharStr(), &(*value)[0], colorEditFlags);
        }

    public:
        void SetColorEditFlags(int value){colorEditFlags=value;}
        int GetColorEditFlags()const{return colorEditFlags;}
    };
}
