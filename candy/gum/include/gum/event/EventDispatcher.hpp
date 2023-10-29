#pragma once
#include <utility>

#include "EventType.hpp"
#include "internal/CallbackList.hpp"
#include "Event.hpp"
#include <any>
#include <gum/event/EventHandler.hpp>
namespace Candy::Gum
{
  
  class EventDispatcher
  {
  private:
    std::unordered_map<EventType, std::vector<SharedPtr<EventHandlerBase>>> handlers{};
    
    
  public:
    template<typename EVENT>
    void AppendHandler(const EventHandler<EVENT>& handler)
    {
      static_assert(std::is_base_of<Event, EVENT>::value, "EVENT must derive from Event. Cannot append handler");
      handlers[EVENT::Type()].push_back(CreateSharedPtr<EventHandler<EVENT>>(handler));
    }
    
    
    void Dispatch(Event& event)
    {
      //CANDY_CORE_INFO("DISPATCHING EVENT: {0}", event.GetType().GetName());
      auto& handlerList = handlers[event.GetType()];
      //CANDY_CORE_INFO("Handler count: {0}", handlerList.size());
      for (auto& handler : handlerList)
      {
        handler->OnEvent(event);
      }
    }
  };
  
  
  
  
}