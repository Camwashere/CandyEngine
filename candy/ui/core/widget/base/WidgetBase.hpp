#pragma once
#include <Candy/CandyEngineCore.hpp>
#include "imgui.h"
#include "imgui_internal.h"
#include "../../base/UINode.hpp"

namespace Candy::UI{
    
    class WidgetBase : public UINode
    {
    
    protected:
        String name;
    public:
        WidgetBase(){}
        WidgetBase(const String& widgetName) : name(widgetName){}
        virtual ~WidgetBase(){}
    public:
        virtual void OnRender()=0;
        virtual void OnEvent(Events::Event &event) {  };
    public:
        void SetName(const String& widgetName){name=widgetName;}
        const String& GetName()const{return name;}
        
    };
    
    template<typename T>
    class Widget : public WidgetBase {
    protected:
        T *value=nullptr;
    public:
        Widget()=default;
        Widget(const String &widgetName) : WidgetBase(widgetName){}
        Widget(const String &widgetName, T *widgetValue) : WidgetBase(widgetName), value(widgetValue){}
        virtual ~Widget(){}
    public:
        virtual void OnRender() = 0;
        //virtual void OnEvent(Events::Event &event){};
    public:
        void SetValue(T *widgetValue) {value = widgetValue;}
        const T &GetValue() const{return *value;}
        T &GetRefValue(){return *value;}
    };
}