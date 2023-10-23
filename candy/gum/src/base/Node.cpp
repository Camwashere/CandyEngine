#include <gum/base/Node.hpp>
#include <CandyPch.hpp>
#include <gum/base/SceneGraph.hpp>
namespace Candy::Gum
{
  using namespace Math;
  
  Node::Node(SceneGraph& scene) : sceneGraph(&scene)
  {
  
  }
  
  void Node::Layout()
  {
    LayoutChildren();
    needsLayout = false;
  }
  void Node::OnRender()
  {
  
  }
  void Node::CalculateTransform(Math::Vector2 sceneSize)
  {
    // Convert rect size from framebuffer coordinates to shader coordinates
    Vector2 sizeInShaderCoordinates = ((GetSize()/sceneSize));
    
    // Adjust the position so that an object's lower left corner corresponds to positionInParent
    Vector2 positionInSceneOffset = boundsInScene.GetCenter();
    Vector2 positionInShaderCoordinates = ((positionInSceneOffset/sceneSize)*2.0f)-Vector2(1.0f);
    
    Math::Matrix3 translate = Matrix3::Translate(Matrix3::IDENTITY, positionInShaderCoordinates);
    Math::Matrix3 scale = Matrix3::Scale(Matrix3::IDENTITY, sizeInShaderCoordinates);
    transform = translate * scale;
    
    needsTransform=false;
    
  }
  void Node::AddChild(SharedPtr<Node> child)
  {
    CANDY_CORE_ASSERT(child != nullptr);
    CANDY_CORE_ASSERT(child->parent == nullptr);
    child->parent = this;
    children.push_back(child);
  }
  
  bool Node::Contains(float localX, float localY)const
  {
    return Contains({localX, localY});
  }
  
  
  
  void Node::OnCaptureEvent(Events::Event& event)
  {
    if (blockEvents || !enabled)
    {
      return;
    }
    switch(event.GetType())
    {
      case Events::EventType::MOUSE_MOVE:
      {
        break;
      }
      case Events::EventType::MOUSE_PRESSED:
      {
        OnCaptureMousePressedEvent(static_cast<Events::MousePressedEvent&>(event));
        break;
      }
      case Events::EventType::MOUSE_RELEASED:
      {
        break;
      }
      default:
        break;
    }
  }
  
  bool Node::OnCaptureMousePressedEvent(Events::MousePressedEvent& event)
  {
    Math::Vector2 pos = event.GetPosition();
    
    if (Contains(pos))
    {
      CANDY_CORE_INFO("Captured mouse press on: {0}, at: {1}", name, pos);
      if (IsLeaf())
      {
        GumMouseButtonPressedEvent gumEvent(this, event.GetPosition(), event.GetButton());
        
        OnEvent(gumEvent);
        return true;
        
      }
      
      for (auto& it : children)
      {
        bool captured = it->OnCaptureMousePressedEvent(event);
        if (captured)
        {
          return true;
        }
      }
    }
    return false;
  }
  void Node::OnEvent(GumEvent& event)
  {
    
    if (! event.IsConsumed())
    {
      switch(event.GetType())
      {
        case GumEventType::MousePressed:
        {
          OnMouseButtonPressed(static_cast<GumMouseButtonPressedEvent&>(event));
          break;
        }
        default:
          break;
      }
    }
    
    if (HasParent())
    {
      parent->OnEvent(event);
    }
    
  }
  void Node::OnMouseButtonPressed(GumMouseButtonPressedEvent& event)
  {
    CANDY_CORE_INFO("Mouse button pressed on: {0}, at local pos: {1}", name, event.GetLocalPosition());
    event.Consume();
  }
  
  void Node::CalculateBounds(Math::Vector2 parentPositionInScene)
  {
    boundsInSelf.SetSize(size);
    boundsInParent.SetSize(size);
    boundsInScene.SetSize(size);
    
    boundsInSelf.SetPosition({0, 0});
    boundsInParent.SetPosition(layoutPosition);
    boundsInScene.SetPosition(parentPositionInScene + layoutPosition);
  }
  void Node::SetEnabled(bool value)
  {
    enabled=value;
  }
  void Node::Enable()
  {
    SetEnabled(true);
  }
  void Node::Disable()
  {
    SetEnabled(false);
  }
  
  void Node::SetLayoutPosition(Math::Vector2 position)
  {
    layoutPosition = position;
  }
  void Node::SetSize(Math::Vector2 value)
  {
    size=value;
  }
  void Node::SetSize(float width, float height)
  {
    SetSize({width, height});
  }
  void Node::SetWidth(float width)
  {
    size.width = width;
  }
  void Node::SetHeight(float height)
  {
    size.height = height;
  }
  Math::Vector2 Node::GetSize()const
  {
    return size;
  }
  Math::Vector2 Node::GetLayoutPosition()const
  {
    return layoutPosition;
  }
  void Node::SetNeedsLayout(bool value)
  {
    needsLayout = value;
  }
  void Node::SetNeedsTransform(bool value)
  {
    needsTransform=value;
  }
  bool Node::NeedsLayout()const
  {
    return needsLayout;
  }
  bool Node::NeedsTransform()const
  {
    return needsTransform;
  }
  bool Node::HasParent()const
  {
    return parent != nullptr;
  }
  Node* Node::GetParent()
  {
    return parent;
  }
  const Node* Node::GetParent()const
  {
    return parent;
  }
  bool Node::IsEnabled()const
  {
    return enabled;
  }
  bool Node::IsLeaf()const
  {
    return children.empty();
  }
  Bounds2D Node::GetBoundsInSelf()const
  {
    return boundsInSelf;
  }
  
  const Bounds2D& Node::GetBoundsInParent()const
  {
    return boundsInParent;
  }
  const Math::Bounds2D& Node::GetBoundsInScene()const
  {
    return boundsInScene;
  }
  
  
  const LayoutGuide& Node::GetLayoutGuide()const
  {
    return layoutGuide;
  }
  const Math::Matrix3& Node::GetTransform()const
  {
    return transform;
  }
  
}