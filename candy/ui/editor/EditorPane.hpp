#pragma once
#include <Candy/CandyEngineCore.hpp>

namespace Candy::UI {
    class EditorLayout;
    class WidgetBase;
    
    class EditorPane
    {
    private:
        EditorLayout* parent;
        String name;
        Math::Direction2 direction;
        uint id;
        float sizePercent;
        std::vector<WidgetBase*> widgets;

    public:
        EditorPane(EditorLayout* parentLayout, const String& paneName, Math::Direction2 dockingDirection, float sizePercentage=0.25f);
        ~EditorPane();

    public:
        void Init();
        void OnRender();

    public:
        EditorLayout& GetParent();
        const String& GetName()const;
        Math::Direction2 GetDirection()const;
        uint GetID()const;
        float GetSizePercent()const;
        void AddWidget(WidgetBase* widget);
        void AddSpacer(int amount=1);


    };
}
