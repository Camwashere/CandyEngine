#include <gum/base/Node.hpp>
#include <CandyPch.hpp>
namespace Candy::Gum
{
  using namespace Math;
  
  Node::Node(SceneGraph& scene) : sceneGraph(&scene)
  {
  
  }
  
  void Node::Layout()
  {
    LayoutChildren();
  }
  void Node::OnRender()
  {
  
  }
  void Node::CalculateTransforms()
  {
    //Matrix3 scaleMatrix = Matrix3::Scale(Matrix3::IDENTITY, sizeInSceneCoordinates);
    Matrix3 translationMatrix = Matrix3::Translate(Matrix3::IDENTITY, position);
    localTransform = Matrix3::Translate(Matrix3::IDENTITY, position) * Matrix3::Scale(Matrix3::IDENTITY, size);
    if (parent)
    {
      localToParentTransform = parent->localTransform * localTransform;
      localToRootTransform = parent->localToRootTransform * localTransform;
    }
    else
    {
      localToParentTransform = localTransform;
      localToRootTransform = localToParentTransform;
    }
    
  }
  void Node::AddChild(SharedPtr<Node> child)
  {
    CANDY_CORE_ASSERT(child != nullptr);
    CANDY_CORE_ASSERT(child->parent == nullptr);
    child->parent = this;
    children.push_back(child);
  }
  /*void Node::SetLayoutSize(Math::Vector2 size)
  {
    layoutSize = size;
  }
  void Node::SetLayoutTranslation(Math::Vector2 value)
  {
    layoutTranslation = value;
  }*/
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
    Math::Vector2 position = event.GetPosition();
    
    if (Contains(position))
    {
      CANDY_CORE_INFO("Captured mouse press on: {0}, at: {1}", name, position);
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
  void Node::SetSize(Math::Vector2 value)
  {
    size=value;
    boundsInParent.SetSize(size);
    boundsInScene.SetSize(size);
  }
  void Node::SetSize(float width, float height)
  {
    SetSize({width, height});
  }
  Math::Vector2 Node::GetSize()const
  {
    return size;
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
  Bounds2D Node::GetLocalBounds()const
  {
    Math::Bounds2D localBounds{};
    localBounds.SetPosition({0, 0});
    localBounds.SetSize(size);
    return localBounds;
  }
  /*const Bounds2D& Node::GetLayoutBounds()const
  {
    return layoutBounds;
  }*/
  const Bounds2D& Node::GetBoundsInParent()const
  {
    return boundsInParent;
  }
  const Math::Bounds2D& Node::GetBoundsInScene()const
  {
    return boundsInScene;
  }
  /*const Vector2& Node::GetTranslation()const
  {
    return translation;
  }
  const Vector2& Node::GetScale()const
  {
    return scale;
  }
  float Node::GetRotation()const
  {
    return rotation;
  }
  
  const Vector2& Node::GetLayoutTranslation()const
  {
    return layoutTranslation;
  }
  const Math::Vector2& Node::GetLayoutSize()const
  {
    return layoutSize;
  }*/
  
  const LayoutGuide& Node::GetLayoutGuide()const
  {
    return layoutGuide;
  }
  const Math::Matrix3& Node::GetLocalTransform()const
  {
    return localTransform;
  }
  const Matrix3& Node::GetLocalToParentTransform()const
  {
    return localToParentTransform;
  }
  const Matrix3& Node::GetLocalToRootTransform()const
  {
    return localToRootTransform;
  }
}