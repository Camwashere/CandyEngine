#include <gum/GumContext.hpp>
#include <GLFW/glfw3.h>
#include <unordered_map>
#include "CandyPch.hpp"
#include <gum/GumRenderer.hpp>
namespace Candy::Gum
{
  static std::unordered_map<GLFWwindow*, GLFWwindowsizefun> prevUserWindowSizeCallbacks;
  static std::unordered_map<GLFWwindow*, GLFWframebuffersizefun> prevUserFramebufferSizeCallbacks;
  static std::unordered_map<GLFWwindow*, GLFWwindowclosefun> prevUserWindowCloseCallbacks;
  static std::unordered_map<GLFWwindow*, GLFWkeyfun> prevUserKeyCallbacks;
  static std::unordered_map<GLFWwindow*, GLFWcharfun> prevUserCharCallbacks;
  static std::unordered_map<GLFWwindow*, GLFWmousebuttonfun> prevUserMouseButtonCallbacks;
  static std::unordered_map<GLFWwindow*, GLFWscrollfun> prevUserScrollCallbacks;
  static std::unordered_map<GLFWwindow*, GLFWcursorposfun> prevUserCursorPosCallbacks;
  static std::unordered_map<GLFWwindow*, GLFWwindowfocusfun> prevUserWindowFocusCallbacks;
  
  
  static std::unordered_map<GLFWwindow*, GumContext*> contextMap;
  GumContext::GumContext(GLFWwindow* handle) : windowHandle(handle), sceneGraph(this)
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_INFO("Initializing GumContext");
    glfwGetWindowSize(windowHandle, &windowSize.x, &windowSize.y);
    glfwGetFramebufferSize(windowHandle, &contextSize.x, &contextSize.y);
    sceneGraph.SetSceneSize(contextSize);
    sceneGraph.SetWindowSize(windowSize);
    contextMap[handle] = this;
    WindowCallbackInit();
    
    testObject = CreateSharedPtr<Rectangle>(1000, 235, 1000, 1000);
    testObject->SetFillColor(Color::red);
    
    
    sceneGraph.Root().AddChild(testObject);
    //testObject->Disable();
    CANDY_CORE_INFO("Initialized Gum Context");
  }
  void GumContext::BeginScene()
  {
    DispatchCaptureEvents();
    
  }
  void GumContext::EndScene()
  {
    sceneGraph.Update();
    GumRenderer::BeginScene(sceneGraph);
    sceneGraph.Render();
    GumRenderer::EndScene();
  }
  
  
  void GumContext::DispatchCaptureEvents()
  {
    CANDY_PROFILE_FUNCTION();
    while (!captureEventQueue.empty())
    {
      Events::Event& event = *captureEventQueue.front();
      sceneGraph.OnCaptureEvent(event);
      //graph.PropagateCaptureEvent(event);
      captureEventQueue.pop();
    }
  }
  
  void GumContext::WindowCallbackInit()
  {
    CANDY_PROFILE_FUNCTION();
    
    prevUserWindowSizeCallbacks[windowHandle] = glfwSetWindowSizeCallback(windowHandle, [](GLFWwindow* window, int width, int height)
    {
      auto iter = prevUserWindowSizeCallbacks.find(window);
      if (iter != prevUserWindowSizeCallbacks.end() && iter->second != nullptr)
      {
        iter->second(window, width, height);
      }
      
      // Add your own processing code here...
      GumContext* context = contextMap[window];
      context->windowSize = {width, height};
      
    });
    
    prevUserFramebufferSizeCallbacks[windowHandle] = glfwSetFramebufferSizeCallback(windowHandle, [](GLFWwindow* window, int width, int height)
    {
      auto iter = prevUserFramebufferSizeCallbacks.find(window);
      if (iter != prevUserFramebufferSizeCallbacks.end() && iter->second != nullptr)
      {
        iter->second(window, width, height);
      }
      
      // Add your own processing code here...
      GumContext* context = contextMap[window];
      context->contextSize = {width, height};
      //context->graph.OnFrameBufferResize(width, height);
      SharedPtr<Events::FrameBufferResizeEvent> event = CreateSharedPtr<Events::FrameBufferResizeEvent>(width, height);
      context->captureEventQueue.push(event);
    });
    // Window Close
    prevUserWindowCloseCallbacks[windowHandle] = glfwSetWindowCloseCallback(windowHandle, [](GLFWwindow* window)
    {
      auto iter = prevUserWindowCloseCallbacks.find(window);
      if (iter != prevUserWindowCloseCallbacks.end() && iter->second != nullptr)
      {
        iter->second(window);
      }
      
      // Add your own processing code here...
      GumContext* context = contextMap[window];
      //Events::WindowCloseEvent event;
      //context->captureEventQueue.push(event);
    });
    
    prevUserKeyCallbacks[windowHandle] = glfwSetKeyCallback(windowHandle, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
      auto iter = prevUserKeyCallbacks.find(window);
      if (iter != prevUserKeyCallbacks.end() && iter->second != nullptr)
      {
        iter->second(window, key, scancode, action, mods);
      }
      
      // Add your own processing code here...
      GumContext* context = contextMap[window];
      switch (action)
      {
        case GLFW_PRESS:
        {
          Events::KeyPressedEvent event(key, 0, mods);
          //context->captureEventQueue.push(event);
          break;
        }
        case GLFW_RELEASE:
        {
          Events::KeyReleasedEvent event(key);
          //context->captureEventQueue.push(event);
          break;
        }
        case GLFW_REPEAT:
        {
          Events::KeyPressedEvent event(key, 1, mods);
          //context->captureEventQueue.push(event);
          break;
        }
        default:
          break;
      }
    });
    
    prevUserCharCallbacks[windowHandle] = glfwSetCharCallback(windowHandle, [](GLFWwindow* window, unsigned int keycode)
    {
      auto iter = prevUserCharCallbacks.find(window);
      if (iter != prevUserCharCallbacks.end() && iter->second != nullptr)
      {
        iter->second(window, keycode);
      }
      
      // Add your own processing code here...
      GumContext* context = contextMap[window];
      Events::KeyTypedEvent event(keycode);
      //context->captureEventQueue.push(event);
    });
    
    prevUserMouseButtonCallbacks[windowHandle] = glfwSetMouseButtonCallback(windowHandle, [](GLFWwindow* window, int button, int action, int mods)
    {
      auto iter = prevUserMouseButtonCallbacks.find(window);
      if (iter != prevUserMouseButtonCallbacks.end() && iter->second != nullptr)
      {
        iter->second(window, button, action, mods);
      }
      
      // Add your own processing code here...
      GumContext* context = contextMap[window];
      switch (action)
      {
        case GLFW_PRESS:
        {
          SharedPtr<Events::MousePressedEvent> event = CreateSharedPtr<Events::MousePressedEvent>(button, context->mousePositionContext.x, context->mousePositionContext.y);
          context->captureEventQueue.push(event);
          break;
        }
        case GLFW_RELEASE:
        {
          SharedPtr<Events::MouseReleasedEvent> event = CreateSharedPtr<Events::MouseReleasedEvent>(button, context->mousePositionContext.x, context->mousePositionContext.y);
          context->captureEventQueue.push(event);
          break;
        }
        default:
          break;
      }
      
      
    });
    
    prevUserScrollCallbacks[windowHandle] = glfwSetScrollCallback(windowHandle, [](GLFWwindow* window, double xOffset, double yOffset)
    {
      auto iter = prevUserScrollCallbacks.find(window);
      if (iter != prevUserScrollCallbacks.end() && iter->second != nullptr)
      {
        iter->second(window, xOffset, yOffset);
      }
      
      // Add your own processing code here...
    });
    
    prevUserCursorPosCallbacks[windowHandle] = glfwSetCursorPosCallback(windowHandle, [](GLFWwindow* window, double xPos, double yPos)
    {
      auto iter = prevUserCursorPosCallbacks.find(window);
      if (iter != prevUserCursorPosCallbacks.end() && iter->second != nullptr)
      {
        iter->second(window, xPos, yPos);
      }
      
      // Add your own processing code here...
      GumContext* context = contextMap[window];
      //glfwGetWindowSize(window, &context->windowSize.x, &context->windowSize.y);
      //glfwGetFramebufferSize(window, &context->contextSize.x, &context->contextSize.y);
      //CANDY_CORE_INFO("Context size: {0}, Window Size: {1}", context->contextSize, context->windowSize);
      float xScaleFactor = static_cast<float>(context->contextSize.width) / static_cast<float>(context->windowSize.width);
      float yScaleFactor = static_cast<float>(context->contextSize.height) / static_cast<float>(context->windowSize.height);
      context->mousePositionWindow = {static_cast<float>(xPos), static_cast<float>(context->windowSize.height) - static_cast<float>(yPos)};
      context->mousePositionContext = {context->mousePositionWindow.x * xScaleFactor, context->mousePositionWindow.y * yScaleFactor};
      
      
      
      SharedPtr<Events::MouseMovedEvent> event = CreateSharedPtr<Events::MouseMovedEvent>(context->mousePositionContext.x, context->mousePositionContext.y);
      
      context->captureEventQueue.push(event);
    });
  }
  GumContext::~GumContext()
  {
  
  }
  
  
}