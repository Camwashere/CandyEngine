#include <candy/event/Input.hpp>
#include <candy/app/Application.hpp>
#include <GLFW/glfw3.h>
namespace Candy
{
    bool Input::IsKeyPressed(KeyCode key)
    {
        return glfwGetKey(Application::GetMainWindowReference().handle, key)==GLFW_PRESS;
    }
    bool Input::IsMouseButtonPressed(MouseCode button)
    {
      return glfwGetMouseButton(Application::GetMainWindowReference().handle, button)==GLFW_PRESS;
    }
    
    Math::Vector2 Input::GetMousePosition()
    {
        double xPos;
        double yPos;
        
        glfwGetCursorPos(Application::GetMainWindowReference().handle, &xPos, &yPos);
        return {(float)xPos, (float)yPos};
    }
    float Input::GetMouseX(){
        double posX;
        glfwGetCursorPos(Application::GetMainWindowReference().handle, &posX, nullptr);
        return (float)posX;
    }
    float Input::GetMouseY(){
        double posY;
        glfwGetCursorPos(Application::GetMainWindowReference().handle, nullptr, &posY);
        return (float)posY;
    }
}