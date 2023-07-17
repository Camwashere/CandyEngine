#include <candy/event/KeyEvent.hpp>


namespace Candy::Events{
        KeyEvent::KeyEvent(KeyCode keyCode, Events::EventType eventType) : Event(EventClass::KEYBOARD, eventType),
                                                                         keyCode(keyCode) {
            
        }
        
        KeyPressedEvent::KeyPressedEvent(KeyCode button, KeyCode repeat, KeyCode modifiers)
                : KeyEvent(button, EventType::KEY_PRESSED), repeat(repeat), modifiers(modifiers) {
            
        }
        
        KeyReleasedEvent::KeyReleasedEvent(KeyCode button) : KeyEvent(button, EventType::KEY_RELEASED) {
        
        }
        
        KeyTypedEvent::KeyTypedEvent(KeyCode button) : KeyEvent(button, EventType::KEY_TYPED){}
    
}