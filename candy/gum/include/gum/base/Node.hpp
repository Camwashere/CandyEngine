#pragma once
#include <candy/math/geometry/Bounds2D.hpp>
#include <candy/math/Matrix.hpp>
#include <candy/base/Base.hpp>
#include <gum/event/Event.hpp>
#include <gum/event/EventDispatcher.hpp>
#include <gum/event/WindowEvent.hpp>
#include <gum/event/KeyEvent.hpp>
#include <gum/event/MouseEvent.hpp>
namespace Candy::Gum
{
  
  class SceneGraph;
  class Node
  {
  private:
    static SceneGraph* SCENE_GRAPH_PTR;
  private:
    bool needsLayout=true;
    bool needsTransform=true;
    Math::Vector2 size;
    Math::Bounds2D boundsInSelf;
    Math::Bounds2D boundsInParent;
    Math::Bounds2D boundsInScene;
    Math::Vector2 minSize={0,0};
    Math::Vector2 prefSize;
    Math::Vector2 maxSize = {Math::Limit<float>::Max(), Math::Limit<float>::Max()};
    EventDispatcher captureEventDispatcher;
    EventDispatcher bubbleEventDispatcher;
    bool focused=false;
    bool hovered=false;
    
  protected:
    std::string name="Node";
    Node* parent=nullptr;
    
    bool enabled=true;
    Math::Vector2 layoutPosition;
    
    Math::Matrix3 transform;
    std::vector<SharedPtr<Node>> children;
    
  public:
    Node();
    virtual ~Node()=default;
    
  
    
  // Virtual functions
  protected:
    virtual void OnLayout();
    virtual void OnRender();
    virtual void OnBoundsCalculated();
    virtual void OnSetSize(Math::Vector2 oldValue, Math::Vector2 newValue);
    virtual void OnSetLayoutPosition(Math::Vector2 oldValue, Math::Vector2 newValue);
    
  public:
    template<typename EVENT>
    void AppendEventFilter(const std::function<void(EVENT&)>& functionHandle)
    {
      captureEventDispatcher.AppendHandler(EventHandler<EVENT>(functionHandle));
    }
    template<typename EVENT>
    void AppendEventHandler(const std::function<void(EVENT&)>& functionHandle)
    {
      bubbleEventDispatcher.AppendHandler(EventHandler<EVENT>(functionHandle));
    }
    template<typename EVENT>
    void AppendEventFilter(const EventHandler<EVENT>& handler)
    {
      captureEventDispatcher.AppendHandler(handler);
    }
    template<typename EVENT>
    void AppendEventHandler(const EventHandler<EVENT>& handler)
    {
      bubbleEventDispatcher.AppendHandler(handler);
    }
    [[nodiscard]]virtual bool Contains(Math::Vector2 localPoint)const=0;
    Node* FindContainingNode(Math::Vector2 localPoint);
    void OnCaptureEvent(Event& event);
    void OnBubbleEvent(Event& event);
    
  private:
    void CalculateTransform(Math::Vector2 sceneSize);
    void SetNeedsLayout(bool value);
    void SetNeedsTransform(bool value);
    

  public:
    void CalculateBounds(Math::Vector2 parentPositionInScene);
    void AddChild(SharedPtr<Node> child);
    void Layout();
    [[nodiscard]]bool Contains(float localX, float localY)const;
    void SetName(const std::string& value);
    [[nodiscard]] std::string GetName()const;
    void SetEnabled(bool enabled);
    void Enable();
    void Disable();
    void SetLayoutPosition(Math::Vector2 position);
    void SetSize(Math::Vector2 size);
    void SetSize(float width, float height);
    void SetWidth(float width);
    void SetHeight(float height);
    [[nodiscard]] Math::Vector2 GetSize()const;
    [[nodiscard]] Math::Vector2 GetLayoutPosition()const;
    [[nodiscard]] bool NeedsLayout()const;
    [[nodiscard]] bool NeedsTransform()const;
    [[nodiscard]] bool HasParent()const;
    Node* GetParent();
    [[nodiscard]] const Node* GetParent()const;
    [[nodiscard]] bool IsFocused()const;
    [[nodiscard]] bool IsEnabled()const;
    [[nodiscard]] bool IsLeaf()const;
    SceneGraph* GetSceneGraph();
    [[nodiscard]] Math::Bounds2D GetBoundsInSelf()const;
    [[nodiscard]] const Math::Bounds2D& GetBoundsInParent()const;
    [[nodiscard]] const Math::Bounds2D& GetBoundsInScene()const;
    [[nodiscard]] bool IsHovered() const;
    
    void SetMinSize(const Math::Vector2& value);
    void SetPrefSize(const Math::Vector2& value);
    void SetMaxSize(const Math::Vector2& value);
    [[nodiscard]] const Math::Vector2& GetMinSize()const;
    [[nodiscard]] const Math::Vector2& GetPrefSize()const;
    [[nodiscard]] const Math::Vector2& GetMaxSize()const;
    [[nodiscard]] const Math::Matrix3& GetTransform()const;
    
    
    friend class SceneGraph;
    
    
  };
}