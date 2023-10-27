#pragma once
#include <candy/event/Events.hpp>
#include <gum/base/SceneGraph.hpp>
#include <gum/layout/BoxLayout.hpp>
#include <queue>
struct GLFWwindow;
namespace Candy::Gum
{
  class GumContext
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
    std::queue<SharedPtr<Events::Event>> captureEventQueue;
    
    
    Math::Vector2i windowSize;
    Math::Vector2 mousePositionWindow;
    
    Math::Vector2i contextSize;
    Math::Vector2 mousePositionContext;
    
  private:
    void WindowCallbackInit();
    void DispatchCaptureEvents();
  
  
  public:
    explicit GumContext(GLFWwindow* window);
    ~GumContext();
    
  public:
    void BeginScene();
    void EndScene();
    //void OnUpdate();
    
    friend class SceneGraph;
    
  };
  
}