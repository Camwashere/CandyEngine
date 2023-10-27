#pragma once
#include <cstdint>
#include <string>
namespace Candy::Gum
{
  struct EventType
  {
    uint32_t type;
    const char* name;
  };
  
  template<const EventType* type>
  class Event
  {
  
  };
}