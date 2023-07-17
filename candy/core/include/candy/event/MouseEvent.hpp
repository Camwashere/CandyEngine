#pragma once

#include "Event.hpp"
#include <candy/base/MouseCodes.hpp>
#include <candy/math/Vector.hpp>


namespace Candy::Events{
        
        class MouseEvent : public Event {
        protected:
            Math::Vector2 position;
        protected:
            MouseEvent(float x, float y, EventType eventType);
        
        public:
            [[nodiscard]] inline float GetX() const { return position.x; }
            
            [[nodiscard]] inline float GetY() const { return position.y; }
            
            [[nodiscard]] inline Math::Vector2 GetPosition() const { return position; }
            
            inline static MouseCode GetStaticType() {
                return (MouseCode) EventType::MOUSE_PRESSED | (MouseCode) EventType::MOUSE_RELEASED |
                       (MouseCode) EventType::MOUSE_MOVE;
            }
        };
        
        class MouseButtonEvent : public MouseEvent {
        protected:
            MouseCode button;
        
        protected:
            MouseButtonEvent(MouseCode button, float x, float y, EventType eventType);
        
        public:
            [[nodiscard]] inline MouseCode GetButton() const { return button; }
            
            inline static MouseCode GetStaticType() {
                return (MouseCode) EventType::MOUSE_PRESSED | (MouseCode) EventType::MOUSE_RELEASED;
            }
        };
        
        class MousePressedEvent : public MouseButtonEvent {
        public:
            MousePressedEvent(MouseCode button, float x, float y);
            
            inline static EventType GetStaticType() { return EventType::MOUSE_PRESSED; }
            
        };
        
        class MouseReleasedEvent : public MouseButtonEvent {
        public:
            MouseReleasedEvent(MouseCode button, float x, float y);
            
            inline static EventType GetStaticType() { return EventType::MOUSE_RELEASED; }
            
        };
        
        class MouseScrollEvent : public MouseEvent {
        public:
            MouseScrollEvent(float x, float y);
            
            [[nodiscard]] inline float GetOffsetX()const{return position.x;}
            [[nodiscard]] inline float GetOffsetY()const{return position.y;}
            [[nodiscard]] inline Math::Vector2 GetOffset()const{return position;}
            
            inline static EventType GetStaticType(){return EventType::MOUSE_SCROLL;}
        };
        
        class MouseMovedEvent : public MouseEvent {
        private:
            bool dragged;
        public:
            MouseMovedEvent(float x, float y, bool dragged=false);
            
            [[nodiscard]] inline bool IsDragged() const { return dragged; }
            
            inline static EventType GetStaticType() { return EventType::MOUSE_MOVE; }
        };
        
        
        
}

