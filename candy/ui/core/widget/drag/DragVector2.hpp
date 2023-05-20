#pragma once
#include "DragBaseN.hpp"
namespace Candy::UI{
    class DragVector2 : public DragBaseN<float, Math::Vector2>
    {
    public:
        DragVector2() : DragBaseN<float, Math::Vector2>(){
            SetFormat("%.3f");
        }
        DragVector2(const String& name) : DragBaseN<float, Math::Vector2>(name){SetFormat("%.3f");}
        DragVector2(const String& name, Math::Vector2* value, float stepValue=1.0f, float min=0.0f, float max=0.0f, const String& formatValue="%%.3f", int sliderFlagsValue=0)
                : DragBaseN<float, Math::Vector2>(name, value, stepValue, min, max, formatValue, sliderFlagsValue){}
    };
}
