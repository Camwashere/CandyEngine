#pragma once

#include <Candy/CandyEngineBase.hpp>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
namespace Candy::Graphics {
    class GraphicsContext
    {
    private:
        GLFWwindow* windowHandle;
    public:
        GraphicsContext(GLFWwindow* contextWindowHandle);
        void Init();
        void SwapBuffers();
        
        static UniquePtr<GraphicsContext> Create(void* window);
    };
    
    
}

