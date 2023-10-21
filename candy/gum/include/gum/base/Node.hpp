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
    
  protected:
    std::string name;
    Node* parent=nullptr;
    const SceneGraph* sceneGraph=nullptr;
    bool enabled=true;
    bool blockEvents=false;
    
    Math::Vector2 position;
    Math::Vector2 size;
    //Math::Bounds2D layoutBounds;
    Math::Bounds2D boundsInParent;
    Math::Bounds2D boundsInScene;
    
    
    
    LayoutGuide layoutGuide;
    
    // Transform
    //Math::Vector2 translation;
    //Math::Vector2 scale=Math::Vector2::one;
    //float rotation=0.0f;
    Math::Matrix3 localTransform;
    Math::Matrix3 localToParentTransform;
    Math::Matrix3 localToRootTransform;
    
    std::vector<SharedPtr<Node>> children;
    
  protected:
    explicit Node(SceneGraph& scene);
    
  // Virtual functions
  protected:
    virtual void CalculateBounds()=0;
    virtual void LayoutChildren()=0;
    virtual void OnRender();
    
  public:
    [[nodiscard]]virtual bool Contains(Math::Vector2 localPoint)const=0;
    
    
    
    
  
  private:
    void CalculateTransforms();
    void SetNeedsLayout(bool value);
    void SetNeedsTransform(bool value);
    void OnCaptureEvent(Events::Event& event);
    bool OnCaptureMousePressedEvent(Events::MousePressedEvent& event);
    
    
    void OnEvent(GumEvent& event);
    void OnMouseButtonPressed(GumMouseButtonPressedEvent& event);

  public:
    void AddChild(SharedPtr<Node> child);
    //void SetLayoutSize(Math::Vector2 size);
    //void SetLayoutTranslation(Math::Vector2 translation);
    void Layout();
    [[nodiscard]]bool Contains(float localX, float localY)const;
    
    void SetEnabled(bool enabled);
    void Enable();
    void Disable();
    void SetSize(Math::Vector2 size);
    void SetSize(float width, float height);
    Math::Vector2 GetSize()const;
    [[nodiscard]] bool NeedsLayout()const;
    [[nodiscard]] bool NeedsTransform()const;
    [[nodiscard]] bool HasParent()const;
    Node* GetParent();
    [[nodiscard]] const Node* GetParent()const;
    [[nodiscard]] bool IsEnabled()const;
    [[nodiscard]] bool IsLeaf()const;
    
    [[nodiscard]] Math::Bounds2D GetLocalBounds()const;
    //[[nodiscard]] const Math::Bounds2D& GetLayoutBounds()const;
    [[nodiscard]] const Math::Bounds2D& GetBoundsInParent()const;
    [[nodiscard]] const Math::Bounds2D& GetBoundsInScene()const;
    
    /*[[nodiscard]] const Math::Vector2& GetTranslation()const;
    [[nodiscard]] const Math::Vector2& GetScale()const;
    [[nodiscard]] float GetRotation()const;
    
    [[nodiscard]] const Math::Vector2& GetLayoutTranslation()const;
    [[nodiscard]] const Math::Vector2& GetLayoutSize()const;*/
    
    [[nodiscard]] const LayoutGuide& GetLayoutGuide()const;
    
    [[nodiscard]] const Math::Matrix3& GetLocalTransform()const;
    
    [[nodiscard]] const Math::Matrix3& GetLocalToParentTransform()const;
    [[nodiscard]] const Math::Matrix3& GetLocalToRootTransform()const;
    
    friend class SceneGraph;
    
    
  };
}