#pragma once

#include "Event.hpp"
#include <cstdint>
#include <candy/base/KeyCodes.hpp>

namespace Candy::Events{
    
        class KeyEvent : public Event {
        protected:
            KeyCode keyCode;
        
        public:
            KeyEvent(KeyCode keyCode, EventType eventType);
            
            [[nodiscard]] inline KeyCode GetKeyCode() const { return keyCode; }
            
            static inline KeyCode GetStaticType() {
                return (KeyCode) EventType::KEY_PRESSED | (KeyCode) EventType::KEY_RELEASED;
            }
        };
        
        class KeyPressedEvent : public KeyEvent {
        private:
            KeyCode repeat;
            KeyCode modifiers;
        
        public:
            KeyPressedEvent(KeyCode button, KeyCode repeat, KeyCode modifiers);
            
            [[nodiscard]] inline KeyCode GetRepeat() const { return repeat; }
            
            [[nodiscard]] inline KeyCode GetModifiers() const { return modifiers; }
            
            [[nodiscard]] inline bool IsModifier(KeyCode modifier) const { return (bool) (modifiers & modifier); }
            
            [[nodiscard]] inline bool IsRepeat()const{return repeat>0;}
            inline static EventType GetStaticType() { return EventType::KEY_PRESSED; }
        };
        
        class KeyReleasedEvent : public KeyEvent {
        public:
            explicit KeyReleasedEvent(KeyCode button);
            
            inline static EventType GetStaticType() { return EventType::KEY_RELEASED; }
        };
        
        class KeyTypedEvent : public KeyEvent
        {
        public:
            explicit KeyTypedEvent(KeyCode button);
            
            inline static EventType GetStaticType(){return EventType::KEY_TYPED;}
        };
    
}

