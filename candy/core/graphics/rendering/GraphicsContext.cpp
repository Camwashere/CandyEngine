#include "GraphicsContext.hpp"

namespace Candy::Graphics {
    
    GraphicsContext::GraphicsContext(GLFWwindow *contextWindowHandle) : windowHandle(contextWindowHandle){
    
    
    }
    
    void GraphicsContext::Init() {
        glfwMakeContextCurrent(windowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        if (!status)
        {
            std::cerr << "Failed to initialize Glad!" << std::endl;
        }
        
    }
    
    void GraphicsContext::SwapBuffers() {
        glfwSwapBuffers(windowHandle);
    }
    UniquePtr<GraphicsContext> GraphicsContext::Create(void *window) {
        return CreateUniquePtr<Graphics::GraphicsContext>(static_cast<GLFWwindow*>(window));
    }
}
