#pragma once
#include "DragBase.hpp"
namespace Candy::UI {
    class DragFloat : public DragBase<float>
    {
    public:
        DragFloat() : DragBase<float>(){
            SetFormat("%.3f");
        }
        DragFloat(const String& name) : DragBase<float>(name){SetFormat("%.3f");}
        DragFloat(const String& name, float* value, float stepValue=1.0f, float min=0.0f, float max=0.0f, const String& formatValue="%.3f", int sliderFlagsValue=0)
            : DragBase<float>(name, value, stepValue, min, max, formatValue, sliderFlagsValue){}
    };
}

