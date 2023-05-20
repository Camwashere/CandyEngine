#pragma once

#include "Event.hpp"
#include "../../../include/Candy/Math.hpp"


namespace Candy::Events{
        class WindowEvent : public Event {
        protected:
            WindowEvent(EventType eventType);
        };
        
        class WindowResizeEvent : public WindowEvent {
        protected:
            int width, height;
        public:
            WindowResizeEvent(int w, int h);
            
            inline int GetWidth() const { return width; }
            inline int GetHeight() const { return height; }
            
            inline static EventType GetStaticType() { return EventType::WINDOW_RESIZE; }
            
        };
        class WindowCloseEvent : public WindowEvent
        {
        public:
            WindowCloseEvent();
            
            inline static EventType GetStaticType(){return EventType::WINDOW_CLOSE;}
        };
}

