#pragma once
#include <gum/event/Event.hpp>
#include <utility>
#include <CandyPch.hpp>
namespace Candy::Gum
{
  class EventHandlerBase
  {
  public:
    virtual void OnEvent(Event& event)const = 0;
    virtual ~EventHandlerBase() = default;
  };
  
  template<typename EVENT>
  class EventHandler : public EventHandlerBase
  {
  private:
    std::function<void(EVENT&)> handle;
  public:
    static_assert(std::is_base_of<Event, EVENT>::value, "EVENT must derive from Event");
    
    explicit EventHandler(const std::function<void(EVENT&)>& functionHandle) : handle(functionHandle){}
    
    void OnEvent(Event& event)const override
    {
      
      if (EventType::IsDerived(event.GetType(), EVENT::Type()))
      {
        handle(static_cast<EVENT&>(event));
      }
      else
      {
        CANDY_CORE_ERROR("NOT DERIVED. Passed in event: {0}, Expected event: {1}", event.GetType().GetName(), EVENT::Type().GetName());
      }
    };
  
  };
}