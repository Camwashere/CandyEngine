#include <candy/event/WindowEvent.hpp>


namespace Candy::Events{
        WindowEvent::WindowEvent(EventType eventType) : Event(EventClass::WINDOW, eventType) {
        
        }
        
        WindowResizeEvent::WindowResizeEvent(unsigned int w, unsigned int h) : WindowEvent(
                EventType::WINDOW_RESIZE), width(w), height(h)  {
            
        }
        WindowCloseEvent::WindowCloseEvent() : WindowEvent(EventType::WINDOW_CLOSE){}
    
        FrameBufferResizeEvent::FrameBufferResizeEvent(int width, int height) : WindowEvent(EventType::FRAMEBUFFER_RESIZE), size(width, height)  {
        
        }
    
}