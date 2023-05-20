#include "MouseEvent.hpp"


namespace Candy::Events{
        
        MouseEvent::MouseEvent(float x, float y, EventType eventType) : Event(EventClass::MOUSE, eventType),
                                                                        position(x, y) {}
        
        MouseButtonEvent::MouseButtonEvent(int32 button, float x, float y, EventType eventType) : MouseEvent(x,
                                                                                                             y,
                                                                                                             eventType),
                                                                                                  button(button) {}
        
        MousePressedEvent::MousePressedEvent(int32 button, float x, float y) : MouseButtonEvent(button, x, y,
                                                                                                EventType::MOUSE_PRESSED) {}
        
        MouseReleasedEvent::MouseReleasedEvent(int32 button, float x, float y) : MouseButtonEvent(button, x, y,
                                                                                                  EventType::MOUSE_RELEASED) {}
        
        MouseScrollEvent::MouseScrollEvent(float x, float y) : MouseEvent(x, y, EventType::MOUSE_SCROLL){}
        
        MouseMovedEvent::MouseMovedEvent(float x, float y, bool dragged) : MouseEvent(x, y, EventType::MOUSE_MOVE),
                                                                           dragged(dragged) {
            
        }
}