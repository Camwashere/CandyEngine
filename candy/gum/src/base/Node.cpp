#include <gum/base/Node.hpp>
#include <CandyPch.hpp>
#include <gum/base/SceneGraph.hpp>
namespace Candy::Gum
{
  using namespace Math;
  SceneGraph* Node::SCENE_GRAPH_PTR=nullptr;
  
  Node::Node()
  {
    /*AppendEventFilter<MousePressedEvent>([=, this](MousePressedEvent& event)
    {
      CANDY_CORE_INFO("Node::MousePressedEvent (capture) on {}. Position: {}", name, event.GetPosition());
      
    });
    AppendEventHandler<MousePressedEvent>([=, this](MousePressedEvent& event)
    {
      CANDY_CORE_INFO("Node::MousePressedEvent on {}. Position: {}", name, event.GetPosition());
      
    });*/
  }
  void Node::OnCaptureEvent(Event& event)
  {
    if (event.GetTarget() == nullptr)
    {
      return;
    }
    if (event.GetTarget() != this)
    {
      //CANDY_CORE_INFO("Target {} no equal on: {}, with event: {}", event.GetTarget()->name, name, event.GetName());
      return;
    }
    captureEventDispatcher.Dispatch(event);
    
    if (event.GetSource() == this)
    {
      OnBubbleEvent(event);
      return;
    }
    
    event.DecrementIter();
    for (auto& child : children)
    {
      child->OnCaptureEvent(event);
      if (event.IsConsumed())
      {
        return;
      }
    }
  }
  
  void Node::OnBubbleEvent(Event& event)
  {
    if (event.IsConsumed())
    {
      return;
    }
    bubbleEventDispatcher.Dispatch(event);
    if (parent == nullptr)
    {
      event.Consume();
      return;
    }
    parent->OnBubbleEvent(event);
  }
  void Node::Layout()
  {
    OnLayout();
    needsLayout = false;
  }
  Node* Node::FindContainingNode(Math::Vector2 parentLocalPoint)
  {
    if (Contains(parentLocalPoint))
    {
      Vector2 localPoint = parentLocalPoint - layoutPosition;
      CANDY_CORE_INFO("Node::Found:: Node: {}, Parent Position: {}, Local Point: {}", name, parentLocalPoint, localPoint);
      
      if (IsLeaf())
      {
        return this;
      }
      for (auto& child : children)
      {
        Node* result = child->FindContainingNode(localPoint);
        if (result != nullptr)
        {
          //return result->FindContainingNode
        }
      }
      //return this;
    }
    return nullptr;
    
    
  }
  void Node::OnRender()
  {
  
  }
  
  void Node::OnSetSize(Math::Vector2 oldValue, Math::Vector2 newValue)
  {
  
  }
  void Node::OnSetLayoutPosition(Math::Vector2 oldValue, Math::Vector2 newValue)
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
  
  
  
  
  
  
  
  void Node::CalculateBounds(Math::Vector2 parentPositionInScene)
  {
    boundsInSelf.SetFromOrigin({0, 0}, size);
    boundsInParent.SetFromOrigin(layoutPosition, size);
    boundsInScene.SetFromOrigin(parentPositionInScene + layoutPosition, size);
    
    OnBoundsCalculated();
  }
  void Node::OnBoundsCalculated()
  {
  
  }
  void Node::OnLayout()
  {
  
  }
  void Node::SetName(const std::string& value)
  {
    name = value;
  }
  std::string Node::GetName()const
  {
    return name;
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
    OnSetLayoutPosition(layoutPosition, position);
    layoutPosition = position;
    needsLayout=true;
  }
  void Node::SetSize(Math::Vector2 value)
  {
    OnSetSize(size, value);
    size=value;
    
  }
  void Node::SetSize(float width, float height)
  {
    SetSize({width, height});
  }
  void Node::SetWidth(float width)
  {
    SetSize({width, size.height});
  }
  void Node::SetHeight(float height)
  {
    SetSize({size.width, height});
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
  bool Node::IsFocused()const
  {
    return focused;
  }
  bool Node::IsEnabled()const
  {
    return enabled;
  }
  bool Node::IsLeaf()const
  {
    return children.empty();
  }
  SceneGraph* Node::GetSceneGraph()
  {
    return SCENE_GRAPH_PTR;
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
  
  void Node::SetMinSize(const Math::Vector2& value)
  {
    minSize = value;
    SetNeedsLayout(true);
  }
  void Node::SetPrefSize(const Math::Vector2& value)
  {
    prefSize = value;
    SetNeedsLayout(true);
  }
  void Node::SetMaxSize(const Math::Vector2& value)
  {
    maxSize = value;
    SetNeedsLayout(true);
  }
  const Math::Vector2& Node::GetMinSize()const
  {
    return minSize;
  }
  const Math::Vector2& Node::GetPrefSize()const
  {
    return prefSize;
  }
  const Math::Vector2& Node::GetMaxSize()const
  {
    return maxSize;
  }
  
  
  const Math::Matrix3& Node::GetTransform()const
  {
    return transform;
  }
  bool Node::IsHovered() const
  {
    return hovered;
  }
}