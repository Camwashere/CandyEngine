#pragma once

#include "Layer.hpp"
#include "../../../include/Candy/Events.hpp"
namespace Candy {
    class UILayer : public Layer
    {
    private:
        bool blockEvents=true;
    
    public:
        UILayer();
        ~UILayer()=default;
        
        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnEvent(Events::Event& e)override;
        
        void Begin();
        void End();
        
        void BlockEvents(bool block){blockEvents=block;}
        void SetDarkThemeColors();
        
        uint32 GetActiveWidgetID()const;
        
    };
}


