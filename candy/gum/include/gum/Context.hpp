#pragma once
#include <gum/base/SceneGraph.hpp>
#include <gum/layout/BoxLayout.hpp>
#include <queue>

struct GLFWwindow;
namespace Candy::Gum
{
  class Context
  {
  public:
    GLFWwindow* windowHandle=nullptr;
    bool blockEvents=false;
    SceneGraph sceneGraph;
    SharedPtr<Rectangle> testObject;
    SharedPtr<Rectangle> testObject2;
    SharedPtr<Rectangle> testObject3;
    SharedPtr<Rectangle> testObject4;
    SharedPtr<BoxLayout> testLayout;
    //std::queue<SharedPtr<Events::Event>> captureEventQueue;
    
    
    Math::Vector2i windowSize;
    Math::Vector2 mousePositionWindow;
    
    //Math::Vector2 contextSize;
    //Math::Vector2 mousePositionContext;
  
  private:
    void WindowCallbackInit();
  
  
  public:
    explicit Context(GLFWwindow* window);
    ~Context();
  
  public:
    void BeginScene();
    void EndScene();
    
    friend class SceneGraph;
  };
}