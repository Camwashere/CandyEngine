#pragma once
#include "DragBaseN.hpp"
namespace Candy::UI{
        class DragVector4 : public DragBaseN<float, Math::Vector4>
        {
        public:
            DragVector4() : DragBaseN<float, Math::Vector4>(){
                SetFormat("%.3f");
            }
            DragVector4(const String& name) : DragBaseN<float, Math::Vector4>(name){SetFormat("%.3f");}
            DragVector4(const String& name, Math::Vector4* value, float stepValue=1.0f, float min=0.0f, float max=0.0f, const String& formatValue="%%.3f", int sliderFlagsValue=0)
                    : DragBaseN<float, Math::Vector4>(name, value, stepValue, min, max, formatValue, sliderFlagsValue){}
        };
}
