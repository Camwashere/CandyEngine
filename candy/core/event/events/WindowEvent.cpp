#include "WindowEvent.hpp"


namespace Candy::Events{
        WindowEvent::WindowEvent(EventType eventType) : Event(EventClass::WINDOW, eventType) {
        
        }
        
        WindowResizeEvent::WindowResizeEvent(int w, int h) : WindowEvent(
                EventType::WINDOW_RESIZE), width(w), height(h)  {
            
        }
        WindowCloseEvent::WindowCloseEvent() : WindowEvent(EventType::WINDOW_CLOSE){}
    
}