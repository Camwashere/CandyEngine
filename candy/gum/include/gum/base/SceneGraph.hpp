#pragma once
#include "Root.hpp"
#include <queue>
#include "candy/event/Events.hpp"
#include <candy/graphics/camera/OrthographicCamera.hpp>
namespace Candy::Gum
{
  class GumContext;
  class SceneGraph
  {
  private:
    GumContext* context;
    Root root;
    bool blockCaptureEvents=false;
    std::queue<Node*> layoutQueue;
    std::queue<Node*> transformQueue;
    std::queue<Node*> boundsQueue;
    //Graphics::OrthographicCamera camera;
    Math::Vector2 sceneSize;
    Math::Vector2 mousePosition;
    Math::Vector2 windowSize;
    
  public:
    explicit SceneGraph(GumContext* context);
    
  private:
    void RenderNode(Node& node);
    
    
    void CalculateLayouts();
    void CalculateTransforms();
    void CalculateBounds();
    
    void CalculateLayoutsPostOrder(Node& node);
    void CalculateBoundsPostOrder(Node& node, Math::Vector2 parentPositionInScene);
    
    bool OnFrameBufferResize(Events::FrameBufferResizeEvent& event);
    bool OnWindowResize(Events::WindowResizeEvent& event);
    bool OnMouseMoved(Events::MouseMovedEvent& event);
    bool OnMousePressed(Events::MousePressedEvent& event);
    bool OnMouseReleased(Events::MouseReleasedEvent& event);
    bool OnKeyPressed(Events::KeyPressedEvent& event);
    bool OnKeyReleased(Events::KeyReleasedEvent& event);
    bool OnKeyTyped(Events::KeyTypedEvent& event);
    
  public:
    void OnCaptureEvent(Events::Event& event);
    void Update();
    void Render();
    
  public:
    Root& Root();
    [[nodiscard]] Math::Vector2 GetSceneSize()const;
    void SetSceneSize(Math::Vector2i size);
    void SetWindowSize(Math::Vector2i size);
    
    
  };
}