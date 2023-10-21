#include <gum/event/GumContextEvent.hpp>
#include <gum/base/Node.hpp>
namespace Candy::Gum
{
  GumContextEvent::GumContextEvent(Node* source, GumEventType type)
  : GumEvent(source, type)
  {
  
  }
  
  GumContextResizedEvent::GumContextResizedEvent(Node* source, uint32_t width, uint32_t height)
  : GumContextEvent(source, GumEventType::ContextResized), size(width, height)
  {
  
  }
  
  uint32_t GumContextResizedEvent::GetWidth()const
  {
    return size.x;
  }
  uint32_t GumContextResizedEvent::GetHeight()const
  {
    return size.y;
  }
  Math::Vector2u GumContextResizedEvent::GetSize()const
  {
    return size;
  }
  
  GumContextClosedEvent::GumContextClosedEvent(Node* source)
  : GumContextEvent(source, GumEventType::ContextClosed)
  {
  
  }
  
  GumContextMinimizedEvent::GumContextMinimizedEvent(Node* source)
  : GumContextEvent(source, GumEventType::ContextMinimized)
  {
  
  }
}