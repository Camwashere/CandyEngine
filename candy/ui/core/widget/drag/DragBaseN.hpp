#pragma once
#include "../base/WidgetBase.hpp"
namespace Candy::UI {


        template<typename PRIMITIVE_VALUE_TYPE, typename CONTAINER_TYPE, int COMPONENT_COUNT=(sizeof(CONTAINER_TYPE)/sizeof(PRIMITIVE_VALUE_TYPE)), int TYPE_ID=Primitives::FindPrimitiveTypeID<PRIMITIVE_VALUE_TYPE>()>
        class DragBaseN : public Widget<CONTAINER_TYPE>
        {
        protected:
            float step=1.0f;
            Math::Range<PRIMITIVE_VALUE_TYPE> range;
            String format="%.3f";
            int sliderFlags=0;

        public:
            DragBaseN()=default;
            DragBaseN(const String& name) : Widget<CONTAINER_TYPE>(name){}
            DragBaseN(const String& name, CONTAINER_TYPE* value, float stepValue=1.0f, const PRIMITIVE_VALUE_TYPE& min=nullptr, const PRIMITIVE_VALUE_TYPE& max=nullptr, const String& formatValue="%.3f", int sliderFlagsValue=0)
            : Widget<CONTAINER_TYPE>(name, value), step(stepValue), range(min, max), format(formatValue), sliderFlags(sliderFlagsValue){}


        public:
            virtual void OnRender()override{
                ImGui::DragScalarN(this->name.ToCharStr(), TYPE_ID, static_cast<void*>(&(*this->value)[0]), COMPONENT_COUNT, step, range.GetMinAsVoid(), range.GetMaxAsVoid(), format.ToCharStr(), sliderFlags);
            }

        public:
            void SetStep(float value){step=value;}
            void SetFormat(const String& value){format = value;}
            void SetSliderFlags(int value){sliderFlags=value;}

            float GetStep()const{return step;}
            String GetFormat()const{return format;}
            int GetSliderFlags()const{return sliderFlags;}
            int GetTypeID()const{return TYPE_ID;}
            int GetComponentCount()const{return COMPONENT_COUNT;}


        };
}

