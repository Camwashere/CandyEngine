#pragma once
#include "Root.hpp"
#include <queue>
#include <candy/graphics/camera/OrthographicCamera.hpp>
#include <gum/event/Event.hpp>

#include <candy/base/KeyCodes.hpp>
#include <candy/base/MouseCodes.hpp>
namespace Candy::Gum
{
  class Context;
  class SceneGraph
  {
  private:
    Context* context;
    Graphics::OrthographicCamera camera;
    Root root;
    bool blockCaptureEvents=false;
    std::queue<Node*> layoutQueue;
    std::queue<Node*> transformQueue;
    std::queue<Node*> boundsQueue;
    Node* focusedNode=nullptr;
    Math::Vector2 previousMousePosition;
    Math::Vector2 mousePosition;
    //Math::Vector2 sceneSize;
    std::list<Node*> hoveredNodes;
    Node* hoveredNode=nullptr;
    
    std::queue<SharedPtr<Event>> captureEventQueue;
    
  public:
    explicit SceneGraph(Context* context);
    
  private:
    void SetSceneSize(Math::Vector2 size);
    void SetWindowSize(Math::Vector2i size);
    void SetMousePosition(Math::Vector2 position);
    void SetFocusedNode(Node* node);
    
    void UpdateHovered();
    void UpdateHovered(Node& node, Math::Vector2 parentLocalPoint);
    void QueueEvent(SharedPtr<Event> event);
    void QueueMouseEntered(Node& node);
    void QueueMouseExited(Node& node);
    void QueueWindowResized(Math::Vector2i windowSize);
    void QueueContextResized();
    void QueueKeyPressed(KeyCode key, KeyCode mods);
    void QueueKeyReleased(KeyCode key, KeyCode mods);
    void QueueKeyRepeat(KeyCode key, KeyCode mods, int repeat);
    void QueueKeyTyped(KeyCode key);
    
    void QueueMousePressed(MouseCode button);
    void QueueMouseReleased(MouseCode button);
    void QueueMouseMoved();
    
    
    
  private:
    void RenderNode(Node& node);
    void CalculateLayouts();
    void CalculateTransforms();
    void CalculateBounds();
    
    void CalculateLayoutsPostOrder(Node& node);
    void CalculateBoundsPostOrder(Node& node, Math::Vector2 parentPositionInScene);
    
  public:
    void FlushCaptureEventQueue();
    void Update();
    void Render();
    
  public:
    const Graphics::OrthographicCamera& GetCamera()const;
    Root& Root();
    [[nodiscard]] Math::Vector2 GetSceneSize()const;
    friend class Context;
    
    
  };
}