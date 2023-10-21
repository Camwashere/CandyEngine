#include <gum/event/GumEvent.hpp>
#include <gum/base/Node.hpp>
namespace Candy::Gum
{
  GumEvent::GumEvent(Node* objectSource, GumEventType eventType) : source(objectSource), type(eventType),
  category(TypeToCategory(eventType)), consumed(false)
  {
  
  }
  
  GumEventCategory GumEvent::TypeToCategory(GumEventType type)
  {
    switch(type)
    {
      case GumEventType::MousePressed:
      case GumEventType::MouseReleased:
      case GumEventType::MouseMoved:
      case GumEventType::MouseDragged:
      case GumEventType::MouseEntered:
      case GumEventType::MouseExited:
        return GumEventCategory::MOUSE;
        
      case GumEventType::KeyPressed:
      case GumEventType::KeyReleased:
      case GumEventType::KeyTyped:
        return GumEventCategory::KEYBOARD;
        
      case GumEventType::ContextResized:
      case GumEventType::ContextClosed:
      case GumEventType::ContextMinimized:
        return GumEventCategory::CONTEXT;
        
      case GumEventType::ScrollStarted:
      case GumEventType::Scroll:
      case GumEventType::ScrollEnded:
        return GumEventCategory::SCROLL;
        
      default:
        return GumEventCategory::CUSTOM;
    }
  }
  
  Node& GumEvent::GetSource()
  {
    return *source;
  }
  GumEventCategory GumEvent::GetCategory()const
  {
    return category;
  }
  void GumEvent::Consume()
  {
    consumed = true;
  }
  bool GumEvent::IsConsumed() const
  {
    return consumed;
  }
  GumEventType GumEvent::GetType() const
  {
    return type;
  }
  
}