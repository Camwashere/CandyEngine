#pragma once

namespace Candy::Gum
{
  enum class EventTargetPolicy
  {
    Normal=0,
    PassThrough,
    Block,
  };
  class EventTarget
  {
  private:
    EventTargetPolicy capturePolicy = EventTargetPolicy::Normal;
    EventTargetPolicy bubblePolicy = EventTargetPolicy::Normal;
    
  public:
  
  
  
  };
}