#pragma once
#include <candy/base/KeyCodes.hpp>
#include <candy/base/MouseCodes.hpp>
#include <candy/math/Vector.hpp>

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