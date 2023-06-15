#include "GraphicsContext.hpp"


namespace Candy::Graphics {
    
    GraphicsContext::GraphicsContext(GLFWwindow *contextWindowHandle) : windowHandle(contextWindowHandle){
    
    
    }
    
    void GraphicsContext::Init() {
        glfwMakeContextCurrent(windowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        CANDY_CORE_ASSERT(status, "Failed to initialize GLAD");
        
        CANDY_CORE_INFO("OpenGL Info:");
        
        CANDY_CORE_INFO("  Vendor: {}", *glGetString(GL_VENDOR));
        CANDY_CORE_INFO("  Renderer: {0}", *glGetString(GL_RENDERER));
        CANDY_CORE_INFO("  Version: {0}", *glGetString(GL_VERSION));
        
        CANDY_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "Hazel requires at least OpenGL version 4.5!");
        
    }
    
    void GraphicsContext::SwapBuffers() {
        glfwSwapBuffers(windowHandle);
    }
    UniquePtr<GraphicsContext> GraphicsContext::Create(void *window) {
        return CreateUniquePtr<Graphics::GraphicsContext>(static_cast<GLFWwindow*>(window));
    }
}
