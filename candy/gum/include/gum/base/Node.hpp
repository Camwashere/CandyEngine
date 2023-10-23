#pragma once
#include <candy/math/geometry/Bounds2D.hpp>
#include <candy/math/Matrix.hpp>
#include <candy/event/Events.hpp>
#include <gum/event/GumEvent.hpp>
#include <gum/event/GumMouseEvent.hpp>
#include <gum/event/GumKeyEvent.hpp>
#include <gum/base/Layout.hpp>
namespace Candy::Gum
{
  class SceneGraph;
  class Node
  {
  private:
    bool needsLayout=true;
    bool needsTransform=true;
    Math::Vector2 size;
    Math::Bounds2D boundsInSelf;
    Math::Bounds2D boundsInParent;
    Math::Bounds2D boundsInScene;
    
  protected:
    std::string name;
    Node* parent=nullptr;
    const SceneGraph* sceneGraph=nullptr;
    bool enabled=true;
    bool blockEvents=false;
    Math::Vector2 layoutPosition;
    
    
    
    
    LayoutGuide layoutGuide;
    Math::Matrix3 transform;
    std::vector<SharedPtr<Node>> children;
    
  protected:
    explicit Node(SceneGraph& scene);
    
  // Virtual functions
  protected:
    void CalculateBounds(Math::Vector2 parentPositionInScene);
    virtual void LayoutChildren()=0;
    virtual void OnRender();
    
  public:
    [[nodiscard]]virtual bool Contains(Math::Vector2 localPoint)const=0;
    
    
    
    
  
  private:
    void CalculateTransform(Math::Vector2 sceneSize);
    void SetNeedsLayout(bool value);
    void SetNeedsTransform(bool value);
    void OnCaptureEvent(Events::Event& event);
    bool OnCaptureMousePressedEvent(Events::MousePressedEvent& event);
    
    
    void OnEvent(GumEvent& event);
    void OnMouseButtonPressed(GumMouseButtonPressedEvent& event);

  public:
    void AddChild(SharedPtr<Node> child);
    void Layout();
    [[nodiscard]]bool Contains(float localX, float localY)const;
    
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
    [[nodiscard]] bool IsEnabled()const;
    [[nodiscard]] bool IsLeaf()const;
    
    [[nodiscard]] Math::Bounds2D GetBoundsInSelf()const;
    [[nodiscard]] const Math::Bounds2D& GetBoundsInParent()const;
    [[nodiscard]] const Math::Bounds2D& GetBoundsInScene()const;
    
    
    
    [[nodiscard]] const LayoutGuide& GetLayoutGuide()const;
    [[nodiscard]] const Math::Matrix3& GetTransform()const;
    
    
    friend class SceneGraph;
    
    
  };
}