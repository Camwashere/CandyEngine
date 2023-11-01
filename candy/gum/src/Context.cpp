#include <gum/Context.hpp>
#include <GLFW/glfw3.h>
#include <unordered_map>
#include "CandyPch.hpp"
#include <gum/render/Renderer.hpp>
#include <CandyEngine.hpp>
#include <candy/project/ProjectManager.hpp>
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
  
  
  static std::unordered_map<GLFWwindow*, Context*> contextMap;
  Context::Context(GLFWwindow* handle) : windowHandle(handle), sceneGraph(this)
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_INFO("Initializing Context");
    glfwGetWindowSize(windowHandle, &windowSize.x, &windowSize.y);
    Math::Vector2i frameBufferSize;
    glfwGetFramebufferSize(windowHandle, &frameBufferSize.x, &frameBufferSize.y);
    //contextSize.Set(static_cast<float>(frameBufferSize.x), static_cast<float>(frameBufferSize.y));
    sceneGraph.SetSceneSize({static_cast<float>(frameBufferSize.x), static_cast<float>(frameBufferSize.y)});
    sceneGraph.SetWindowSize(windowSize);
    contextMap[handle] = this;
    WindowCallbackInit();
    
    testObject = CreateSharedPtr<Button>();
    //Paint paint(Color{0.4f, 0.2f, 0.7f, 1.0f}, Graphics::Texture::Create(ProjectManager::GetAssetsDirectory() / "textures" / "statue.jpg"));
    testObject->SetNormalFill(Paint{Color{0.4f, 0.2f, 0.7f, 1.0f}, Graphics::Texture::Create(ProjectManager::GetAssetsDirectory() / "textures" / "statue.jpg")});
    
    testObject->SetPrefSize({200, 200});
    
    testObject->SetName("Btn 1");
    
    testObject2 = CreateSharedPtr<Button>();
    testObject2->SetNormalFill(Color{0.4f, 0.2f, 0.7f, 1.0f});
    //testObject2->SetFillColor(Color::blue);
    //testObject2->SetArcSize({0.2f, 0.8f});
    testObject2->SetPrefSize({250, 200});
    testObject2->SetName("Btn 2");
    
    testObject3 = CreateSharedPtr<Button>();
    testObject3->SetNormalFill(Color{0.4f, 0.2f, 0.7f, 1.0f});
    //testObject3->SetFillColor(Color::yellow);
    //testObject3->SetArcSize({0.8f, 0.2f});
    testObject3->SetPrefSize({300, 200});
    testObject3->SetName("Btn 3");
    
    testObject4 = CreateSharedPtr<Button>();
    testObject4->SetNormalFill(Color{0.4f, 0.2f, 0.7f, 1.0f});
    //testObject4->SetFillColor(Color::magenta);
    //testObject4->SetArcSize({0.4f, 0.7f});
    testObject4->SetPrefSize({150, 200});
    testObject4->SetName("Btn 4");
    
    
    testLayout = CreateSharedPtr<BoxLayout>();
    testLayout->AddChild(testObject);
    testLayout->AddChild(testObject2);
    testLayout->AddChild(testObject3);
    testLayout->AddChild(testObject4);
    testLayout->SetPrefSize({1000, 200});
    //testLayout->SetMaxSize({1500, 1500});
    testLayout->SetSpacing(100.0f);
    testLayout->SetBackgroundFill(Color::green);
    testLayout->SetName("Box Layout");
    sceneGraph.Root().AddChild(testLayout);
    CANDY_CORE_INFO("Initialized GumSystem Context");
  }
  void Context::BeginScene()
  {
    sceneGraph.FlushCaptureEventQueue();
  }
  void Context::EndScene()
  {
    sceneGraph.Update();
    Renderer::BeginScene(sceneGraph);
    sceneGraph.Render();
    Renderer::EndScene();
  }
  
  
  static int key_repeat_count[GLFW_KEY_LAST + 1] = { 0 };
  void Context::WindowCallbackInit()
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
      Context* context = contextMap[window];
      context->sceneGraph.SetWindowSize({width, height});
      //context->windowSize = {width, height};
      //context->sceneGraph.QueueWindowResized(width, height);
      
    });
    
    prevUserFramebufferSizeCallbacks[windowHandle] = glfwSetFramebufferSizeCallback(windowHandle, [](GLFWwindow* window, int width, int height)
    {
      auto iter = prevUserFramebufferSizeCallbacks.find(window);
      if (iter != prevUserFramebufferSizeCallbacks.end() && iter->second != nullptr)
      {
        iter->second(window, width, height);
      }
      
      // Add your own processing code here...
      Context* context = contextMap[window];
      context->sceneGraph.SetSceneSize({static_cast<float>(width), static_cast<float>(height)});
      //context->contextSize = {static_cast<float>(width), static_cast<float>(height)};
      //context->sceneGraph.QueueContextResized(width, height);
    });
    // Window Close
    prevUserWindowCloseCallbacks[windowHandle] = glfwSetWindowCloseCallback(windowHandle, [](GLFWwindow* window)
    {
      auto iter = prevUserWindowCloseCallbacks.find(window);
      if (iter != prevUserWindowCloseCallbacks.end() && iter->second != nullptr)
      {
        iter->second(window);
      }
    });
    
    prevUserKeyCallbacks[windowHandle] = glfwSetKeyCallback(windowHandle, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
      auto iter = prevUserKeyCallbacks.find(window);
      if (iter != prevUserKeyCallbacks.end() && iter->second != nullptr)
      {
        iter->second(window, key, scancode, action, mods);
      }
      
      Context* context = contextMap[window];
      switch (action)
      {
        case GLFW_PRESS:
        {
          key_repeat_count[key] = 1;
          context->sceneGraph.QueueKeyPressed(key, mods);
          break;
        }
        case GLFW_RELEASE:
        {
          key_repeat_count[key]=0;
          context->sceneGraph.QueueKeyReleased(key, mods);
          break;
        }
        case GLFW_REPEAT:
        {
          key_repeat_count[key]++;
          context->sceneGraph.QueueKeyRepeat(key, mods, key_repeat_count[key]);
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
      
      Context* context = contextMap[window];
      context->sceneGraph.QueueKeyTyped(keycode);
    });
    
    prevUserMouseButtonCallbacks[windowHandle] = glfwSetMouseButtonCallback(windowHandle, [](GLFWwindow* window, int button, int action, int mods)
    {
      auto iter = prevUserMouseButtonCallbacks.find(window);
      if (iter != prevUserMouseButtonCallbacks.end() && iter->second != nullptr)
      {
        iter->second(window, button, action, mods);
      }
      
      Context* context = contextMap[window];
      switch (action)
      {
        case GLFW_PRESS:
        {
          context->sceneGraph.QueueMousePressed(button);
          break;
        }
        case GLFW_RELEASE:
        {
          context->sceneGraph.QueueMouseReleased(button);
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
      Context* context = contextMap[window];
      //Math::Vector2 prevPos = context->mousePositionContext;
      //context->sceneGraph.previousMousePosition = context->sceneGraph.mousePosition;
      float xScaleFactor = static_cast<float>(context->sceneGraph.sceneSize.width) / static_cast<float>(context->windowSize.width);
      float yScaleFactor = static_cast<float>(context->sceneGraph.sceneSize.height) / static_cast<float>(context->windowSize.height);
      context->mousePositionWindow = {static_cast<float>(xPos), static_cast<float>(context->windowSize.height) - static_cast<float>(yPos)};
      Math::Vector2 contextMousePosition = {context->mousePositionWindow.x * xScaleFactor, context->mousePositionWindow.y * yScaleFactor};
      context->sceneGraph.SetMousePosition(contextMousePosition);
      //context->sceneGraph.mousePosition = context->mousePositionContext;
      //context->sceneGraph.QueueMouseMoved();
      
      
      //SharedPtr<Events::MouseMovedEvent> event = CreateSharedPtr<Events::MouseMovedEvent>(context->mousePositionContext.x, context->mousePositionContext.y);
      
      //context->captureEventQueue.push(event);
    });
  }
  Context::~Context()
  {
  
  }
}