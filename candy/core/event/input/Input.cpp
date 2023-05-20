#include "Input.hpp"
#include <Candy/App.hpp>
#include "GLFW/glfw3.h"

namespace Candy
{
    bool Input::IsKeyPressed(KeyCode key)
    {
        return glfwGetKey(Application::Instance().MainWindowReference()->ref, key)==GLFW_PRESS;
    }
    bool Input::IsMouseButtonPressed(MouseCode button){return glfwGetMouseButton(Application::Instance().MainWindowReference()->ref, button)==GLFW_PRESS;}
    Math::Vector2 Input::GetMousePosition(){
        //double xPos;
        //double yPos;
        Math::Vector2 pos;
        glfwGetCursorPos(Application::Instance().MainWindowReference()->ref, (double*)&pos.x, (double*)&pos.y);
        return pos;
        //return Math::Vector2(xPos, yPos);
    }
    float Input::GetMouseX(){
        double posX;
        glfwGetCursorPos(Application::Instance().MainWindowReference()->ref, &posX, nullptr);
        return posX;
    }
    float Input::GetMouseY(){
        double posY;
        glfwGetCursorPos(Application::Instance().MainWindowReference()->ref, nullptr, &posY);
        return posY;
    }
}