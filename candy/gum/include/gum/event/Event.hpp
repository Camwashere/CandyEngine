#pragma once
#include <utility>

#include "EventType.hpp"
#include "EventTarget.hpp"
namespace Candy::Gum
{
  
  class Event
  {
  private:
    bool consumed=false;
    //EventType type;
    EventTarget target;
    EventTarget source;
    
  protected:
    Event()=default;
    
  public:
    [[nodiscard]] EventTarget GetTarget()const{return target;}
    [[nodiscard]] EventTarget GetSource()const{return source;}
    [[nodiscard]] EventType GetType()const{return Type();}
    void Consume(){consumed=true;}
    [[nodiscard]] bool IsConsumed()const{return consumed;}
    
    
  public:
    static EventType Type(){return EventType::None;}
    
  };
  
  
  class MouseEvent : public Event
  {
  protected:
    Math::Vector2 position;
    
  public:
    explicit MouseEvent(const Math::Vector2& pos) :  position(pos){}
    
  public:
    [[nodiscard]] Math::Vector2 GetLocalPosition() const{return position;}
    
  public:
    static EventType Type(){return EventType::Mouse;}
  };
  
  class MousePressedEvent : public MouseEvent
  {
  protected:
    MouseCode button;
  public:
    explicit MousePressedEvent(MouseCode code, const Math::Vector2& pos) : MouseEvent(pos), button(code){}
    
  public:
    static EventType Type(){return EventType::MousePressed;}
  };
  
  
  
  
}