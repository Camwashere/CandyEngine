#pragma once
#include "DragBase.hpp"
namespace Candy::UI {
        class DragInt : public DragBase<int>
        {
        public:
            DragInt() : DragBase<int>(){
                SetFormat("%d");
            }
            DragInt(const String& name) : DragBase<int>(name){SetFormat("%d");}
            DragInt(const String& name, int* value, float stepValue=1.0f, int min=0, int max=0, const String& formatValue="%d", int sliderFlagsValue=0)
                    : DragBase<int>(name, value, stepValue, min, max, formatValue, sliderFlagsValue){}
        };
}

