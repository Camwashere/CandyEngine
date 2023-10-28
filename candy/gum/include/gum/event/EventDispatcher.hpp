#pragma once
#include <utility>

#include "EventType.hpp"
#include "internal/CallbackList.hpp"
#include "Event.hpp"
#include <any>
namespace Candy::Gum
{
  
  /*template<typename RETURN_TYPE, typename ...ARGS>
  class EventDispatcher
  {
  private:
    typedef std::function<RETURN_TYPE (ARGS...)> FunctionType;
    std::unordered_map<EventType, Internal::CallbackList<FunctionType>> callbackMap{};
  public:
    void AppendListener(EventType type, FunctionType func)
    {
      callbackMap[type].AppendCallback(func);
    }
    
    void Dispatch(EventType type, ARGS&&... args)
    {
      auto& list = callbackMap[type];
      list.Call(std::forward<ARGS>(args)...);
    }
  
  
  };*/
  
  template<typename EVENT>
  requires std::is_base_of_v<Event, EVENT>
  class EventDispatcher
  {
  private:
    
    typedef std::function<void (EVENT&)> FunctionType;
    Internal::CallbackList<FunctionType> callbacks;
    
  public:
    void AppendListener(FunctionType func)
    {
      callbacks.AppendCallback(func);
    }
    
    void Dispatch(EVENT& event)
    {
      callbacks.Call(event);
    }
    
  };
  
  
}