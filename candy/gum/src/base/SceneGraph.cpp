#include <gum/base/SceneGraph.hpp>
#include <gum/GumContext.hpp>
#include <CandyPch.hpp>
#include <gum/GumRenderer.hpp>
#include <gum/GumInstance.hpp>
namespace Candy::Gum
{
  SceneGraph::SceneGraph(GumContext* gumContext) : context(gumContext), root(*this)
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_ASSERT(context != nullptr);
    GumInstance::SetCurrentContext(context);
    
    
  }
  
  void SceneGraph::Render()
  {
    CANDY_PROFILE_FUNCTION();
    //GumRenderer::BeginScene();
    RenderNode(root);
    //GumRenderer::EndScene();
  }
  
  void SceneGraph::RenderNode(Node& node)
  {
    CANDY_PROFILE_FUNCTION();
    if (node.IsEnabled())
    {
      node.OnRender();
      
      for (const auto& child : node.children)
      {
        RenderNode(*child);
      }
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
    // Loop while there are dirty objects in the queue
    while (!layoutQueue.empty())
    {
      // Get the dirty object from the front of the queue
      auto object = layoutQueue.front();
      layoutQueue.pop();
      if (object)
      {
        // Object still exists, proceed to process it
        // Process the dirty object here
        object->Layout();
        
        // Store the parent's prior dirty flags to update children if necessary
        object->SetNeedsLayout(false);
        
        // Enqueue the children if they are not already dirty
        for (const auto& child : object->children)
        {
          if (! child->NeedsLayout())
          {
            child->SetNeedsLayout(true);
            layoutQueue.push(child.get());
          }
        }
      }
    }
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
        object->CalculateTransforms();
        
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
    CalculateBoundsPostOrder(root);
  }
  
  void SceneGraph::CalculateBoundsPostOrder(Node& node)
  {
    CANDY_PROFILE_FUNCTION();
    if (node.IsLeaf())
    {
      node.CalculateBounds();
      return;
    }
    for (const auto& child : node.children)
    {
      CalculateBoundsPostOrder(*child);
    }
    
    node.CalculateBounds();
  }
  Root& SceneGraph::Root()
  {
    return root;
  }
  Math::Vector2 SceneGraph::GetSceneSize()const
  {
    return sceneSize;
  }
  void SceneGraph::SetSceneSize(Math::Vector2i size)
  {
    sceneSize.width = (float)size.width;
    sceneSize.height = (float)size.height;
    
    root.SetSize(sceneSize);
  }
  void SceneGraph::SetWindowSize(Math::Vector2i size)
  {
    windowSize.width = (float)size.width;
    windowSize.height = (float)size.height;
  }
  void SceneGraph::OnCaptureEvent(Events::Event& event)
  {
    CANDY_PROFILE_FUNCTION();
    Events::EventDispatcher dispatcher(event);
    dispatcher.Dispatch<Events::FrameBufferResizeEvent>(CANDY_BIND_EVENT_FUNCTION(SceneGraph::OnFrameBufferResize));
    dispatcher.Dispatch<Events::WindowResizeEvent>(CANDY_BIND_EVENT_FUNCTION(SceneGraph::OnWindowResize));
    dispatcher.Dispatch<Events::MouseMovedEvent>(CANDY_BIND_EVENT_FUNCTION(SceneGraph::OnMouseMoved));
    dispatcher.Dispatch<Events::MousePressedEvent>(CANDY_BIND_EVENT_FUNCTION(SceneGraph::OnMousePressed));
    dispatcher.Dispatch<Events::MouseReleasedEvent>(CANDY_BIND_EVENT_FUNCTION(SceneGraph::OnMouseReleased));
    dispatcher.Dispatch<Events::KeyPressedEvent>(CANDY_BIND_EVENT_FUNCTION(SceneGraph::OnKeyPressed));
    dispatcher.Dispatch<Events::KeyReleasedEvent>(CANDY_BIND_EVENT_FUNCTION(SceneGraph::OnKeyReleased));
    dispatcher.Dispatch<Events::KeyTypedEvent>(CANDY_BIND_EVENT_FUNCTION(SceneGraph::OnKeyTyped));
    
    root.OnCaptureEvent(event);
  }
  
  
  
  bool SceneGraph::OnMouseMoved(Events::MouseMovedEvent& event)
  {
    mousePosition = event.GetPosition();
    return false;
  }
  bool SceneGraph::OnMousePressed(Events::MousePressedEvent& event)
  {
    mousePosition = event.GetPosition();
    return false;
  }
  bool SceneGraph::OnMouseReleased(Events::MouseReleasedEvent& event)
  {
    mousePosition = event.GetPosition();
    return false;
  }
  bool SceneGraph::OnKeyPressed(Events::KeyPressedEvent& event)
  {
    return false;
  }
  bool SceneGraph::OnKeyReleased(Events::KeyReleasedEvent& event)
  {
    return false;
  }
  bool SceneGraph::OnKeyTyped(Events::KeyTypedEvent& event)
  {
    return false;
  }
  bool SceneGraph::OnFrameBufferResize(Events::FrameBufferResizeEvent& event)
  {
    SetSceneSize(event.GetSize());
    return true;
  }
  bool SceneGraph::OnWindowResize(Events::WindowResizeEvent& event)
  {
    //root.SetSize(event.GetWidth(), event.GetHeight());
    SetWindowSize({(int)event.GetWidth(), (int)event.GetHeight()});
    return true;
  }
}