#pragma once

#include "Event.hpp"
#include <functional>

namespace Candy::Events{
        class EventDispatcher {
        private:
            Event &event;
        public:
            explicit EventDispatcher(Event &event) : event(event) {}
            
            template<typename T, typename F>
            bool Dispatch(const F& func) {
                if (event.GetType() == T::GetStaticType())
                {
                    event.handled |= func(static_cast<T&>(event));
                    return true;
                }
                return false;
            }
            
        };
}

