#include <gum/base/SceneGraph.hpp>
#include <gum/Context.hpp>
#include <CandyPch.hpp>
#include <gum/render/Renderer.hpp>
#include "gum/GumSystem.hpp"
#include <gum/event/WindowEvent.hpp>
#include <gum/event/KeyEvent.hpp>
#include <gum/event/MouseEvent.hpp>
namespace Candy::Gum
{
  SceneGraph::SceneGraph(Context* gumContext) : context(gumContext)
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_ASSERT(context != nullptr);
    GumSystem::SetCurrentContext(context);
    Node::SCENE_GRAPH_PTR = this;
    SetFocusedNode(&root);
  }
  void SceneGraph::FlushCaptureEventQueue()
  {
    CANDY_PROFILE_FUNCTION();
    while (!captureEventQueue.empty())
    {
      auto event = captureEventQueue.front();
      captureEventQueue.pop();
      if (event)
      {
        root.OnCaptureEvent(*event);
        
      }
    }
  }
  void SceneGraph::Render()
  {
    CANDY_PROFILE_FUNCTION();
    RenderNode(root);
  }
  
  void SceneGraph::RenderNode(Node& node)
  {
    CANDY_PROFILE_FUNCTION();
    if (node.IsLeaf())
    {
      node.OnRender();
      return;
    }
    node.OnRender();
    for (const auto& child : node.children)
    {
      RenderNode(*child);
    }
    
  }
  void SceneGraph::Update()
  {
    CANDY_PROFILE_FUNCTION();
    layoutQueue.push(&root);
    transformQueue.push(&root);
    //boundsQueue.push(&root);
    CalculateLayouts();
    CalculateTransforms();
    CalculateBounds();
  }
  
  void SceneGraph::CalculateLayouts()
  {
    CANDY_PROFILE_FUNCTION();
    CalculateLayoutsPostOrder(root);
  }
  void SceneGraph::CalculateTransforms()
  {
    CANDY_PROFILE_FUNCTION();
    while (!transformQueue.empty())
    {
      // Get the dirty object from the front of the queue
      auto object = transformQueue.front();
      transformQueue.pop();
      if (object)
      {
        // Object still exists, proceed to process it
        // Process the dirty object here
        object->CalculateTransform(GetSceneSize());
        
        // Store the parent's prior dirty flags to update children if necessary
        object->SetNeedsTransform(false);
        
        // Enqueue the children if they are not already dirty
        for (const auto& child : object->children)
        {
          if (! child->NeedsTransform())
          {
            child->SetNeedsTransform(true);
            transformQueue.push(child.get());
          }
        }
      }
    }
  }
  void SceneGraph::CalculateBounds()
  {
    CANDY_PROFILE_FUNCTION();
    CalculateBoundsPostOrder(root, {0, 0});
  }
  void SceneGraph::CalculateLayoutsPostOrder(Node& node)
  {
    CANDY_PROFILE_FUNCTION();
    if (node.IsLeaf())
    {
      node.Layout();
      return;
    }
    for (const auto& child : node.children)
    {
      CalculateLayoutsPostOrder(*child);
    }
    node.Layout();
  }
  void SceneGraph::CalculateBoundsPostOrder(Node& node, Math::Vector2 parentPositionInScene)
  {
    CANDY_PROFILE_FUNCTION();
    if (node.IsLeaf())
    {
      node.CalculateBounds(parentPositionInScene);
      return;
    }
    Math::Vector2 posOffset = node.GetLayoutPosition() + parentPositionInScene;
    for (const auto& child : node.children)
    {
      CalculateBoundsPostOrder(*child, posOffset);
    }
    
    node.CalculateBounds(parentPositionInScene);
  }
  Root& SceneGraph::Root()
  {
    return root;
  }
  Math::Vector2 SceneGraph::GetSceneSize()const
  {
    return sceneSize;
  }
  void SceneGraph::SetSceneSize(Math::Vector2 size)
  {
    sceneSize = size;
    QueueContextResized();
    //root.SetSize(size);
  }
  void SceneGraph::SetWindowSize(Math::Vector2i size)
  {
    //windowSize.width = (float)size.width;
    //windowSize.height = (float)size.height;
    QueueWindowResized(size);
  }
  void SceneGraph::SetMousePosition(Math::Vector2 position)
  {
    previousMousePosition = mousePosition;
    mousePosition = position;
    UpdateHovered();
    QueueMouseMoved();
  }
  void SceneGraph::UpdateHovered()
  {
    hoveredNodes.clear();
    UpdateHovered(root, mousePosition);
  }
  void SceneGraph::UpdateHovered(Node& node, Math::Vector2 parentLocalPoint)
  {
    if (node.Contains(parentLocalPoint))
    {
      hoveredNodes.push_back(&node);
      if (!node.hovered)
      {
        node.hovered = true;
        QueueMouseEntered(node);
      }
    }
    else
    {
      if (node.hovered)
      {
        node.hovered = false;
        QueueMouseExited(node);
      }
    }
    Math::Vector2 localPoint = parentLocalPoint - node.GetLayoutPosition();
    for (auto& child : node.children)
    {
      UpdateHovered(*child, localPoint);
    }
  }
  void SceneGraph::QueueMouseEntered(Node& node)
  {
    SharedPtr<MouseEnteredEvent> event = CreateSharedPtr<MouseEnteredEvent>(mousePosition);
    event->SetSource(&node);
    
    QueueEvent(event);
    
  }
  void SceneGraph::QueueMouseExited(Node& node)
  {
    SharedPtr<MouseExitedEvent> event = CreateSharedPtr<MouseExitedEvent>(mousePosition);
    event->SetSource(&node);
    
    QueueEvent(event);
  }
  void SceneGraph::SetFocusedNode(Node* node)
  {
    if (focusedNode)
    {
      focusedNode->focused = false;
    }
    focusedNode = node;
    if (focusedNode)
    {
      focusedNode->focused = true;
    }
  }
  void SceneGraph::QueueEvent(SharedPtr<Event> event)
  {
    //event->SetSource(focusedNode);
    if (hoveredNodes.empty())
    {
      event->SetSource(&root);
    }
    else
    {
      event->SetSource(hoveredNodes.back());
    }
    captureEventQueue.push(std::move(event));
  }
  
  void SceneGraph::QueueWindowResized(Math::Vector2i windowSize)
  {
    QueueEvent(CreateSharedPtr<WindowResizedEvent>(Math::Vector2u{static_cast<unsigned int>(windowSize.width), static_cast<unsigned int>(windowSize.height)}));
  }
  void SceneGraph::QueueContextResized()
  {
    QueueEvent(CreateSharedPtr<ContextResizedEvent>(sceneSize));
  }
  void SceneGraph::QueueKeyPressed(KeyCode key, KeyCode mods)
  {
    QueueEvent(CreateSharedPtr<KeyPressedEvent>(key, mods));
  }
  void SceneGraph::QueueKeyReleased(KeyCode key, KeyCode mods)
  {
    QueueEvent(CreateSharedPtr<KeyReleasedEvent>(key, mods));
  }
  void SceneGraph::QueueKeyRepeat(KeyCode key, KeyCode mods, int repeat)
  {
    QueueEvent(CreateSharedPtr<KeyRepeatEvent>(key, mods, repeat));
  }
  void SceneGraph::QueueKeyTyped(KeyCode key)
  {
    QueueEvent(CreateSharedPtr<KeyTypedEvent>(key));
  }
  void SceneGraph::QueueMousePressed(MouseCode button)
  {
    QueueEvent(CreateSharedPtr<MousePressedEvent>(button, mousePosition));
  }
  void SceneGraph::QueueMouseReleased(MouseCode button)
  {
    //Node* containingNode = root.FindContainingNode(mousePosition);
    
    //SetFocusedNode(containingNode);
    QueueEvent(CreateSharedPtr<MouseReleasedEvent>(button, mousePosition));
  }
  void SceneGraph::QueueMouseMoved()
  {
    QueueEvent(CreateSharedPtr<MouseMovedEvent>(previousMousePosition, mousePosition));
  }
  

}