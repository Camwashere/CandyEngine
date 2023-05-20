#pragma once

#include "Event.hpp"
#include "../../../include/Candy/Math.hpp"


namespace Candy::Events{
        
        class MouseEvent : public Event {
        protected:
            Math::Vector2 position;
        protected:
            MouseEvent(float x, float y, EventType eventType);
        
        public:
            inline const float GetX() const { return position.x; }
            
            inline const float GetY() const { return position.y; }
            
            inline const Math::Vector2 GetPosition() const { return position; }
            
            inline static int32 GetStaticType() {
                return (int32) EventType::MOUSE_PRESSED | (int32) EventType::MOUSE_RELEASED |
                       (int32) EventType::MOUSE_MOVE;
            }
        };
        
        class MouseButtonEvent : public MouseEvent {
        protected:
            int32 button;
        
        protected:
            MouseButtonEvent(int32 button, float x, float y, EventType eventType);
        
        public:
            inline const int32 GetButton() const { return button; }
            
            inline static int32 GetStaticType() {
                return (int32) EventType::MOUSE_PRESSED | (int32) EventType::MOUSE_RELEASED;
            }
        };
        
        class MousePressedEvent : public MouseButtonEvent {
        public:
            MousePressedEvent(int32 button, float x, float y);
            
            inline static EventType GetStaticType() { return EventType::MOUSE_PRESSED; }
            
        };
        
        class MouseReleasedEvent : public MouseButtonEvent {
        public:
            MouseReleasedEvent(int32 button, float x, float y);
            
            inline static EventType GetStaticType() { return EventType::MOUSE_RELEASED; }
            
        };
        
        class MouseScrollEvent : public MouseEvent {
        public:
            MouseScrollEvent(float x, float y);
            
            inline float GetOffsetX()const{return position.x;}
            inline float GetOffsetY()const{return position.y;}
            inline Math::Vector2 GetOffset()const{return position;}
            
            inline static EventType GetStaticType(){return EventType::MOUSE_SCROLL;}
        };
        
        class MouseMovedEvent : public MouseEvent {
        private:
            bool dragged;
        public:
            MouseMovedEvent(float x, float y, bool dragged=false);
            
            inline const bool IsDragged() const { return dragged; }
            
            inline static EventType GetStaticType() { return EventType::MOUSE_MOVE; }
        };
        
        
        
}

