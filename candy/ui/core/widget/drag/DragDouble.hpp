#pragma once
#include "DragBase.hpp"
namespace Candy::UI {
        class DragDouble : public DragBase<double>
        {
        public:
            DragDouble() : DragBase<double>(){
                SetFormat("%.3f");
            }
            DragDouble(const String& name) : DragBase<double>(name){SetFormat("%.3f");}
            DragDouble(const String& name, double* value, float stepValue=1.0f, double min=0.0, double max=0.0, const String& formatValue="%.3f", int sliderFlagsValue=0)
                    : DragBase<double>(name, value, stepValue, min, max, formatValue, sliderFlagsValue){}
        };
}

