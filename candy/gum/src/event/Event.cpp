#include <gum/event/Event.hpp>
#include <utility>

namespace Candy::Gum
{
    
    Event::Event(EventType type) : type(std::move(type))
    {
    }
}