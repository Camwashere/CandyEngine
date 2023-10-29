#pragma once
#include <gum/event/Event.hpp>
#include <candy/math/Vector.hpp>
namespace Candy::Gum
{
  class WindowEvent : public Event
  {
  protected:
    explicit WindowEvent(EventType type) : Event(std::move(type)){}
  };
  
  class WindowResizedEvent : public Event
  {
  private:
    Math::Vector2u size;
    
  public:
    explicit WindowResizedEvent(Math::Vector2u size) : Event(Type()), size(size){}
    
  public:
    static EventType Type(){return EventType::WindowResized;}
    [[nodiscard]] Math::Vector2u GetSize()const{return size;}
    [[nodiscard]] uint32_t GetWidth()const{return size.x;}
    [[nodiscard]] uint32_t GetHeight()const{return size.y;}
  };
  
  class ContextResizedEvent : public WindowEvent
  {
  private:
    Math::Vector2 size;
    
  public:
    explicit ContextResizedEvent(Math::Vector2 size) : WindowEvent(Type()), size(size){}
    
  public:
    static EventType Type(){return EventType::ContextResized;}
    [[nodiscard]] Math::Vector2 GetSize()const{return size;}
    [[nodiscard]] float GetWidth()const{return size.x;}
    [[nodiscard]] float GetHeight()const{return size.y;}
    
  };
}