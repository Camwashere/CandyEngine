#include "Window.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include "stb_image.h"


namespace Candy {
    using namespace Math;
    using namespace Graphics;
    using namespace Events;
    
    static uint8 GLFW_WINDOW_COUNT=0;
    static void GLFWErrorCallback(int error, const char* description)
    {
        //ENGINE_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
    }
    Window *Window::instance;
    
    Window::Window(const std::string &name, int windowWidth, int windowHeight) : windowData(name,windowWidth,windowHeight){
        instance = this;
        Init();
    }
    
    Window::Window(const WindowData &data) : windowData(data){
        instance = this;
        Init();
    }
    
    Window::~Window() {
        Shutdown();
    }
    
    void Window::Init()
    {
        if (GLFW_WINDOW_COUNT==0)
        {
            int success = glfwInit();
            if (success)
            {
            
            }
            else
            {
                std::cerr << "Failed to initialize GLFW" << std::endl;
            }
            
            //ENGINE_CORE_ASSERT(success, "Could not initialize GLFW");
            //glfwSetErrorCallback(GLFWErrorCallback);
            
        }
        ref = glfwCreateWindow(windowData.width, windowData.height, windowData.title.c_str(), nullptr, nullptr);
        if (! ref)
        {
            std::cerr << "Failed to create window" << std::endl;
        }
        ++GLFW_WINDOW_COUNT;
        graphicsContext = GraphicsContext::Create(ref);
        graphicsContext->Init();
        glfwSetWindowUserPointer(ref, &windowData);
        SetVSync(true);
        
        glfwSetWindowSizeCallback(ref, [](GLFWwindow* window, int width, int height)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.width = width;
            data.height = height;
            WindowResizeEvent event(width, height);
            data.eventCallback(event);
        });
        glfwSetWindowCloseCallback(ref, [](GLFWwindow* window)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.eventCallback(event);
        });
        
        glfwSetKeyCallback(ref, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            
            switch (action)
            {
                case GLFW_PRESS:
                {
                    
                    KeyPressedEvent event(key, 0, mods);
                    data.eventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    data.eventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, 1, mods);
                    data.eventCallback(event);
                    break;
                }
            }
        });
        
        glfwSetCharCallback(ref, [](GLFWwindow* window, unsigned int keycode)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            
            KeyTypedEvent event(keycode);
            data.eventCallback(event);
        });
        
        glfwSetMouseButtonCallback(ref, [](GLFWwindow* window, int button, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            
            switch (action)
            {
                case GLFW_PRESS:
                {
                    MousePressedEvent event(button, data.mousePos.x, data.mousePos.y);
                    data.eventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseReleasedEvent event(button, data.mousePos.x, data.mousePos.y);
                    data.eventCallback(event);
                    break;
                }
                
            }
        });
        
        glfwSetScrollCallback(ref, [](GLFWwindow* window, double xOffset, double yOffset)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            MouseScrollEvent event((float)xOffset, (float)yOffset);
            data.eventCallback(event);
        });
        
        glfwSetCursorPosCallback(ref, [](GLFWwindow* window, double xPos, double yPos)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            
            data.mousePos.Set(xPos, yPos);
            MouseMovedEvent event(data.mousePos.x, data.mousePos.y);
            data.eventCallback(event);
        });
        
        
    }
    
    void Window::Shutdown() {
        glfwDestroyWindow(ref);
        --GLFW_WINDOW_COUNT;
        if (GLFW_WINDOW_COUNT==0)
        {
            glfwTerminate();
        }
    }
    
    void Window::OnUpdate() {
        glfwPollEvents();
        graphicsContext->SwapBuffers();
    }
    
    void Window::SetVSync(bool enabled) {
        if (enabled) {
            glfwSwapInterval(1);
        } else {
            glfwSwapInterval(0);
        }
        windowData.vsync = enabled;
    }
}
