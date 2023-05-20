#pragma once

#include <Candy/CandyEngineBase.hpp>


namespace Candy::Events
    {
        enum class EventClass
        {
            KEYBOARD,
            MOUSE,
            WINDOW,
        };
        enum EventType
        {
            // Mouse
            MOUSE_PRESSED = BIT(0),
            MOUSE_RELEASED = BIT(1),
            MOUSE_SCROLL = BIT(2),
            MOUSE_MOVE = BIT(3),
            
            // Keyboard
            KEY_PRESSED = BIT(4),
            KEY_RELEASED = BIT(5),
            KEY_TYPED = BIT(6),
            
            // Window
            WINDOW_RESIZE = BIT(7),
            WINDOW_CLOSE = BIT(8)
        };
        
        class Event
        {
        private:
            friend class EventDispatcher;
        
        protected:
            const EventClass eventClass;
            EventType type;
            bool handled;
        
        protected:
            Event(EventClass eventClassValue, EventType eventType) : eventClass(eventClassValue), type(eventType),
                                                                     handled(false)
            {}
        
        public:
            inline void SetHandled(bool isHandled)
            { handled = isHandled; }
            
            inline bool IsHandled() const
            { return handled; }
            
            inline uint GetType() const
            { return (uint) type; }
            
            inline EventClass GetClass() const
            { return eventClass; }
            
            
        };
    }


