#pragma once

#include "Event.hpp"
#include <candy/math/Vector.hpp>


namespace Candy::Events{
        class WindowEvent : public Event {
        protected:
            explicit WindowEvent(EventType eventType);
        };
        
        class WindowResizeEvent : public WindowEvent {
        protected:
            unsigned int width, height;
        public:
            WindowResizeEvent(unsigned int w, unsigned int h);
            
            [[nodiscard]] inline unsigned int GetWidth() const { return width; }
            [[nodiscard]] inline unsigned int GetHeight() const { return height; }
            
            inline static EventType GetStaticType() { return EventType::WINDOW_RESIZE; }
            
        };
        class WindowCloseEvent : public WindowEvent
        {
        public:
            WindowCloseEvent();
            
            inline static EventType GetStaticType(){return EventType::WINDOW_CLOSE;}
        };
        
        class FrameBufferResizeEvent : public WindowEvent
        {
        protected:
            Math::Vector2i size;
            
        public:
            FrameBufferResizeEvent(int width, int height);
            
            [[nodiscard]] inline int GetWidth()const{return size.x;}
            [[nodiscard]] inline int GetHeight()const{return size.y;}
            [[nodiscard]] inline const Math::Vector2i& GetSize()const{return size;}
            
            inline static EventType GetStaticType(){return EventType::FRAMEBUFFER_RESIZE;}
        };
}

