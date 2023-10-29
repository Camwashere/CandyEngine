#pragma once
#include <gum/event/Event.hpp>
#include <utility>

namespace Candy::Gum
{
  class InputEvent : public Event
  {
  protected:
    explicit InputEvent(EventType type) : Event(std::move(type))
    {
    }
    
  public:
    [[nodiscard]] bool IsMouse() const
    {
      return GetType().IsDerived(EventType::Mouse);
    }
    
    [[nodiscard]] bool IsKey()const
    {
      return GetType().IsDerived(EventType::Key);
    }
  };
}