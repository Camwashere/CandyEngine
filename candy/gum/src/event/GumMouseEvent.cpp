#include <gum/event/GumMouseEvent.hpp>
#include <gum/base/Node.hpp>
namespace Candy::Gum
{
  GumMouseEvent::GumMouseEvent(Node* sourceObj, GumEventType eventType, const Math::Vector2& eventPosition)
  : GumEvent(sourceObj, eventType), position(eventPosition)
  {
  
  }
  Math::Vector2 GumMouseEvent::GetLocalPosition() const
  {
    return position;
  }
  Math::Vector2 GumMouseEvent::GetParentRelativePosition()const
  {
    return Math::Vector2::zero;
  }
  Math::Vector2i GumMouseEvent::GetScreenPosition()const
  {
    return Math::Vector2i::zero;
  }
  Math::Vector2 GumMouseEvent::GetGlobalPosition()const
  {
    return Math::Vector2::zero;
  }
  
  GumMouseButtonEvent::GumMouseButtonEvent(Node* source, GumEventType type, const Math::Vector2& position, MouseCode button)
  : GumMouseEvent(source, type, position), button(button)
  {
  
  }
  MouseCode GumMouseButtonEvent::GetButton() const
  {
    return button;
  }
  GumMouseButtonPressedEvent::GumMouseButtonPressedEvent(Node* source, const Math::Vector2& position, MouseCode button)
  : GumMouseButtonEvent(source, GumEventType::MousePressed, position, button)
  {
  
  }
  
  GumMouseButtonReleasedEvent::GumMouseButtonReleasedEvent(Node* source, const Math::Vector2& position, MouseCode button)
  : GumMouseButtonEvent(source, GumEventType::MouseReleased, position, button)
  {
  
  }
  
  GumMouseMovedEvent::GumMouseMovedEvent(Node* source, const Math::Vector2& position)
  : GumMouseEvent(source, GumEventType::MouseMoved, position)
  {
  
  }
  GumMouseDraggedEvent::GumMouseDraggedEvent(Node* source, const Math::Vector2& position, MouseCode button)
  : GumMouseButtonEvent(source, GumEventType::MouseDragged, position, button)
  {
  
  }
  GumMouseEnteredEvent::GumMouseEnteredEvent(Node* source, const Math::Vector2& position)
  : GumMouseEvent(source, GumEventType::MouseEntered, position)
  {
  
  }
  GumMouseExitedEvent::GumMouseExitedEvent(Node* source, const Math::Vector2& position)
  : GumMouseEvent(source, GumEventType::MouseExited, position)
  {
  
  }
};



