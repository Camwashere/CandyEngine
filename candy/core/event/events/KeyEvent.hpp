#pragma once

#include "Event.hpp"



namespace Candy::Events{
        class KeyEvent : public Event {
        protected:
            int32 keyCode;
            int32 count;
        
        public:
            KeyEvent(int32 keyCode, EventType eventType);
            
            inline int32 GetKeyCode() const { return keyCode; }
            
            inline int32 GetStaticType() {
                return (int32) EventType::KEY_PRESSED | (int32) EventType::KEY_RELEASED;
            }
        };
        
        class KeyPressedEvent : public KeyEvent {
        private:
            int32 repeat;
            int32 modifiers;
        
        public:
            KeyPressedEvent(int32 button, int32 repeat, int32 modifiers);
            
            inline int32 GetRepeat() const { return repeat; }
            
            inline int32 GetModifiers() const { return modifiers; }
            
            inline bool IsModifier(int32 modifier) const { return (bool) (modifiers & modifier); }
            
            inline bool IsRepeat()const{return repeat>0;}
            inline static EventType GetStaticType() { return EventType::KEY_PRESSED; }
        };
        
        class KeyReleasedEvent : public KeyEvent {
        public:
            KeyReleasedEvent(int32 button);
            
            inline static EventType GetStaticType() { return EventType::KEY_RELEASED; }
        };
        
        class KeyTypedEvent : public KeyEvent
        {
        public:
            KeyTypedEvent(int32 button);
            
            inline static EventType GetStaticType(){return EventType::KEY_TYPED;}
        };
    
}

