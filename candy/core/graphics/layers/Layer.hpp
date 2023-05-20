#pragma once

#include <Candy/CandyEngineBase.hpp>


namespace Candy{
    class Window;
}
namespace Candy::Events
{
    class Event;
}

namespace Candy {
    
    class Layer {
    protected:
        bool isVisible;
        std::string name;
    
    protected:
    
    public:
        explicit Layer(const std::string& layerName, bool visible=true) : name(layerName), isVisible(visible){}
        virtual ~Layer()=default;
        
        inline bool IsVisible() const { return isVisible; }
        inline void SetVisible(bool visible) { isVisible = visible; }
        
        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnEvent(Events::Event& event){}
        virtual void OnUpdate(){}
        virtual void OnRenderUI(){}
        
        const std::string& GetName()const{return name;}
    };
}

