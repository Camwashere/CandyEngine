#pragma once

namespace Candy::Gum
{
  class Event;
  class EventDispatchChain;
  class EventDispatcher
  {
  public:
    virtual Event& DispatchEvent(Event& event, EventDispatchChain* tail)=0;
  };
  
  
}