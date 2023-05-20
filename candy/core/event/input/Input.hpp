#pragma once
#include "../../../include/Candy/Math.hpp"

namespace Candy {
    
    class Input
    {
    public:
        static bool IsKeyPressed(KeyCode key);
        static bool IsMouseButtonPressed(MouseCode button);
        static Math::Vector2 GetMousePosition();
        static float GetMouseX();
        static float GetMouseY();
    };
    
}