#pragma once
#include "Event.hpp"
namespace Candy::Events{
    class IEventListener {
    public:
        virtual void OnEvent(Event &event) = 0;
    };
}