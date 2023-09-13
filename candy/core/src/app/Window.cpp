#include <candy/app/Window.hpp>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <candy/app/Application.hpp>
#include <candy/graphics/Vulkan.hpp>
namespace Candy
{
    using namespace Graphics;
    using namespace Events;
    static std::uint8_t GLFW_WINDOW_COUNT=0;
    static void GLFWErrorCallback(int error, const char* description)
    {
        CANDY_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
    }
    
    
    
    
    Window::Window(WindowData data) : windowData(std::move(data)), fullscreen(false), graphicsContext(nullptr)
    {
        if (GLFW_WINDOW_COUNT==0)
        {
            int success = glfwInit();
            CANDY_CORE_ASSERT(success, "FAILED TO INITIALIZE GLFW");
            glfwSetErrorCallback(GLFWErrorCallback);
            Vulkan::Init();
        }
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        handle = glfwCreateWindow(windowData.GetWindowWidth(), windowData.GetWindowHeight(), windowData.title.c_str(), nullptr, nullptr);
        //VulkanInstance::Init(handle);
        
        ++GLFW_WINDOW_COUNT;
        graphicsContext = CreateUniquePtr<GraphicsContext>(handle);
       
        //renderer = new Renderer(graphicsContext);
        
        glfwSetWindowUserPointer(handle, &windowData);
        SetVSync(true);
        EventCallbackInit();
      
    }
    
    void Window::EventCallbackInit() const
    {
        // Window Resize
        glfwSetWindowSizeCallback(handle, [](GLFWwindow* window, int width, int height)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.windowSize.Set(width, height);
            
            WindowResizeEvent event(width, height);
            data.eventCallback(event);
        });
        
        // Framebuffer Resize
        glfwSetFramebufferSizeCallback(handle, [](GLFWwindow* window, int width, int height)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.frameBufferSize.Set(width, height);
            
            FrameBufferResizeEvent event(width, height);
            data.eventCallback(event);
        });
        
        // Window Close
        glfwSetWindowCloseCallback(handle, [](GLFWwindow* window)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            Events::WindowCloseEvent event;
            data.eventCallback(event);
        });
        
        glfwSetKeyCallback(handle, [](GLFWwindow* window, int key, int scancode, int action, int mods)
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
                default:
                    break;
            }
        });
        
        glfwSetCharCallback(handle, [](GLFWwindow* window, unsigned int keycode)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            
            KeyTypedEvent event(keycode);
            data.eventCallback(event);
        });
        
        glfwSetMouseButtonCallback(handle, [](GLFWwindow* window, int button, int action, int mods)
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
                default:
                    break;
            }
        });
        
        glfwSetScrollCallback(handle, [](GLFWwindow* window, double xOffset, double yOffset)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            MouseScrollEvent event((float)xOffset, (float)yOffset);
            data.eventCallback(event);
        });
        
        glfwSetCursorPosCallback(handle, [](GLFWwindow* window, double xPos, double yPos)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            
            data.mousePos.Set((float)xPos, (float)yPos);
            MouseMovedEvent event(data.mousePos.x, data.mousePos.y);
            data.eventCallback(event);
        });
        
    }
    
    Window::~Window()
    {
    
        
    }
    
    void Window::OnUpdate()
    {
        CANDY_PROFILE_FUNCTION();
        
        glfwPollEvents();
        Renderer::EndPass();
        graphicsContext->Present();
        graphicsContext->SwapBuffers();
        Renderer::BeginViewportPass();
        
    }
    
    void Window::Close() const
    {
        glfwDestroyWindow(handle);
        --GLFW_WINDOW_COUNT;
        if (GLFW_WINDOW_COUNT==0)
        {
          /*renderer->Shutdown();
          graphicsContext->Terminate();
          Vulkan::Shutdown();
          glfwTerminate();*/
          Application::Shutdown();
        }
    }
  void Window::OnWindowResize(Events::WindowResizeEvent& event)
  {
      windowData.windowSize.Set(event.GetWidth(), event.GetHeight());
  }
  
  void Window::OnFrameBufferResize(Events::FrameBufferResizeEvent& event)
  {
      graphicsContext->OnFrameBufferResize(event);
  }
    void Window::SetVSync(bool enabled)
    {
        if (enabled)
        {
            //glfwSwapInterval(1);
        }
        else
        {
            //glfwSwapInterval(0);
        }
        windowData.vsync = enabled;
    }
  
  void Window::Show() const
  {
      glfwShowWindow(handle);
  }
  void Window::Hide() const
  {
      glfwHideWindow(handle);
  }
  
  
}