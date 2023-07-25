#include <candy/utils/FrameTime.hpp>
#include <GLFW/glfw3.h>
namespace Candy
{
    FrameTime::FrameTime() : currentTime(0.0f), previousTime(0.0f), deltaTime(0.0f)
    {
    }
    
    void FrameTime::Update()
    {
        currentTime = (float)glfwGetTime();
        deltaTime = currentTime-previousTime;
        previousTime = currentTime;
    }
}