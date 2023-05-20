#include "KeyEvent.hpp"


namespace Candy::Events{
        KeyEvent::KeyEvent(int32 keyCode, Events::EventType eventType) : Event(EventClass::KEYBOARD, eventType),
                                                                         keyCode(keyCode) {
            
        }
        
        KeyPressedEvent::KeyPressedEvent(int32 button, int32 repeat, int32 modifiers)
                : KeyEvent(button, EventType::KEY_PRESSED), repeat(repeat), modifiers(modifiers) {
            
        }
        
        KeyReleasedEvent::KeyReleasedEvent(int32 button) : KeyEvent(button, EventType::KEY_RELEASED) {
        
        }
        
        KeyTypedEvent::KeyTypedEvent(int32 button) : KeyEvent(button, EventType::KEY_TYPED){}
    
}