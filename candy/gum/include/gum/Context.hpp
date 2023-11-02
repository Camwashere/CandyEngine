#pragma once
#include <gum/base/SceneGraph.hpp>
#include <gum/layout/BoxLayout.hpp>
#include <queue>
#include <gum/widget/Button.hpp>
#include <gum/widget/Label.hpp>
struct GLFWwindow;
namespace Candy::Gum
{
  class Context
  {
  public:
    GLFWwindow* windowHandle=nullptr;
    bool blockEvents=false;
    SceneGraph sceneGraph;
    
    SharedPtr<Button> testObject;
    SharedPtr<Button> testObject2;
    SharedPtr<Button> testObject3;
    SharedPtr<Button> testObject4;
    SharedPtr<Label> testLabel;
    SharedPtr<BoxLayout> testLayout;
    
    Math::Vector2i windowSize;
    Math::Vector2 mousePositionWindow;
    
  
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