#pragma once
#include "DragBaseN.hpp"
namespace Candy::UI{
        class DragVector3 : public DragBaseN<float, Math::Vector3>
        {
        public:
            DragVector3() : DragBaseN<float, Math::Vector3>(){
                SetFormat("%.3f");
            }
            DragVector3(const String& name) : DragBaseN<float, Math::Vector3>(name){SetFormat("%.3f");}
            DragVector3(const String& name, Math::Vector3* value, float stepValue=1.0f, float min=0.0f, float max=0.0f, const String& formatValue="%.3f", int sliderFlagsValue=0)
                    : DragBaseN<float, Math::Vector3>(name, value, stepValue, min, max, formatValue, sliderFlagsValue){}
        };
}

