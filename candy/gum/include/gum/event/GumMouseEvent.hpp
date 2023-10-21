#pragma once
#include "GumEvent.hpp"
#include <candy/base/MouseCodes.hpp>
#include <candy/math/Vector.hpp>
namespace Candy::Gum
{
  class GumMouseEvent : public GumEvent
  {
  protected:
    Math::Vector2 position;
    
  protected:
    GumMouseEvent(Node* source, GumEventType type, const Math::Vector2& position);
    
  public:
     /// @return The local position of the mouse event relative to the source object.
    [[nodiscard]] Math::Vector2 GetLocalPosition() const;
    [[nodiscard]] Math::Vector2 GetParentRelativePosition()const;
    [[nodiscard]] Math::Vector2i GetScreenPosition()const;
    [[nodiscard]] Math::Vector2 GetGlobalPosition()const;
    
  
  };
  
  class GumMouseButtonEvent : public GumMouseEvent
  {
  protected:
    MouseCode button;
    
  protected:
    GumMouseButtonEvent(Node* source, GumEventType type, const Math::Vector2& position, MouseCode button);
    
  public:
    [[nodiscard]] MouseCode GetButton() const;
    
  };
  
  class GumMouseButtonPressedEvent : public GumMouseButtonEvent
  {
  public:
    GumMouseButtonPressedEvent(Node* source, const Math::Vector2& position, MouseCode button);
  
  };
  
  class GumMouseButtonReleasedEvent : public GumMouseButtonEvent
  {
  public:
    GumMouseButtonReleasedEvent(Node* source, const Math::Vector2& position, MouseCode button);
    
  };
  
  
  
  class GumMouseMovedEvent : public GumMouseEvent
  {
  public:
    GumMouseMovedEvent(Node* source, const Math::Vector2& position);
    
  };
  
  
  
  class GumMouseDraggedEvent : public GumMouseButtonEvent
  {
  public:
    GumMouseDraggedEvent(Node* source, const Math::Vector2& position, MouseCode button);
  };
  
  class GumMouseEnteredEvent : public GumMouseEvent
  {
    GumMouseEnteredEvent(Node* source, const Math::Vector2& position);
  };
  
  class GumMouseExitedEvent : public GumMouseEvent
  {
    GumMouseExitedEvent(Node* source, const Math::Vector2& position);
  };
  

}