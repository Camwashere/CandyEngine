#pragma once
#include "../base/WidgetBase.hpp"
namespace Candy::UI {


    template<typename T, int TYPE_ID=Primitives::FindPrimitiveTypeID<T>()>
    class DragBase : public Widget<T>
    {
    protected:
        float step=1.0f;
        Math::Range<T> range;
        String format="%.3f";
        int sliderFlags=0;

    public:
        DragBase()=default;
        DragBase(const String& name) : Widget<T>(name){}
        DragBase(const String& name, T* value, float stepValue=1.0f, const T& min=nullptr, const T& max=nullptr, const String& formatValue="%.3f", int sliderFlagsValue=0) : Widget<T>(name, value),
                step(stepValue), range(min, max), format(formatValue), sliderFlags(sliderFlagsValue){}
        virtual ~DragBase(){}


    public:
        virtual void OnRender()override{
            ImGui::DragScalar(this->name.ToCharStr(), TYPE_ID, this->value, step, range.GetMinAsVoid(), range.GetMaxAsVoid(), format.ToCharStr(), sliderFlags);
        }

    public:
        void SetStep(float value){step=value;}
        void SetFormat(const String& value){format = value;}
        void SetSliderFlags(int value){sliderFlags=value;}

        float GetStep()const{return step;}
        String GetFormat()const{return format;}
        int GetSliderFlags()const{return sliderFlags;}
        int GetTypeID()const{return TYPE_ID;}


    };
}
