#pragma once
#include <gum/event/InputEvent.hpp>
#include <candy/math/Vector.hpp>
#include <candy/base/MouseCodes.hpp>
#include <utility>
namespace Candy::Gum
{
  class MouseEvent : public InputEvent
  {
  protected:
    const Math::Vector2 position;
    Math::Vector2 localPosition;
    
  protected:
    MouseEvent(EventType derivedMouseType, const Math::Vector2& pos) : InputEvent(std::move(derivedMouseType)), position(pos), localPosition(position){}
    
  
  public:
    void OffsetLocalPosition(const Math::Vector2& offset){localPosition+=offset;}
    void SetLocalPosition(const Math::Vector2& value){localPosition = value;}
    void ResetLocalPosition(){localPosition = position;}
    [[nodiscard]] Math::Vector2 GetLocalPosition()const{return localPosition;}
    [[nodiscard]] Math::Vector2 GetPosition() const{return position;}
    
  
  public:
    static EventType Type(){return EventType::Mouse;}
  };
  
  class MouseButtonEvent : public MouseEvent
  {
    protected:
      MouseCode button;
      
      MouseButtonEvent(EventType derivedButtonEventType, MouseCode buttonCode, const Math::Vector2& pos) : MouseEvent(std::move(derivedButtonEventType), pos), button(buttonCode){}
    
  
  public:
    [[nodiscard]] MouseCode GetButton() const{return button;}
    
  public:
    static EventType Type(){return EventType::MouseButton;}
  
  };
  
  class MousePressedEvent : public MouseButtonEvent
  {
  public:
    MousePressedEvent(MouseCode code, const Math::Vector2& pos) : MouseButtonEvent(Type(), code, pos){}
  
  public:
    static EventType Type(){return EventType::MousePressed;}
  };
  
  class MouseReleasedEvent : public MouseButtonEvent
  {
  public:
    MouseReleasedEvent(MouseCode code, const Math::Vector2& pos) : MouseButtonEvent(Type(), code, pos){}
    
    static EventType Type(){return EventType::MouseReleased;}
  };
  
  class MouseMovedEvent : public MouseEvent
  {
  protected:
    Math::Vector2 previousPosition;
  public:
    MouseMovedEvent(const Math::Vector2& prevPos, const Math::Vector2& newPos) : MouseEvent(Type(), newPos), previousPosition(prevPos){}
    
    [[nodiscard]] Math::Vector2 GetPreviousPosition() const{return previousPosition;}
    [[nodiscard]] Math::Vector2 GetDelta() const{return position-previousPosition;}
    static EventType Type(){return EventType::MouseMoved;}
  };
  
  class MouseDraggedEvent : public MouseEvent
  {
  public:
    explicit MouseDraggedEvent(const Math::Vector2& pos) : MouseEvent(Type(), pos){}
    
    static EventType Type(){return EventType::MouseDragged;}
  };
  
  class MouseEnteredEvent : public MouseEvent
  {
  public:
    explicit MouseEnteredEvent(const Math::Vector2& pos) : MouseEvent(Type(), pos){}
    
    static EventType Type(){return EventType::MouseEntered;}
  };
  
  class MouseExitedEvent : public MouseEvent
  {
  public:
    explicit MouseExitedEvent(const Math::Vector2& pos) : MouseEvent(Type(), pos){}
    
    static EventType Type(){return EventType::MouseExited;}
  };
}