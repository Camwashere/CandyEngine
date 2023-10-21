#pragma once
#include <gum/event/GumEvent.hpp>
#include <candy/base/KeyCodes.hpp>
namespace Candy::Gum
{
  class GumKeyEvent : public GumEvent
  {
  protected:
    const KeyCode key;
    
  protected:
    GumKeyEvent(Node* source, GumEventType type, KeyCode key);
    
  public:
    [[nodiscard]] KeyCode GetKey() const;
    
  };
  class GumKeyRawEvent : public GumKeyEvent
  {
  protected:
    KeyCode modifiers;
    
  protected:
    GumKeyRawEvent(Node* source, GumEventType type, KeyCode key, KeyCode modifiers);
    
  public:
    [[nodiscard]] KeyCode GetModifiers() const;
    [[nodiscard]] bool IsModifierDown(KeyCode modifier) const;
    [[nodiscard]] bool IsShiftDown() const;
    [[nodiscard]] bool IsControlDown() const;
    [[nodiscard]] bool IsAltDown() const;
    [[nodiscard]] bool IsSuperDown() const;
  };
  class GumKeyPressedEvent : public GumKeyRawEvent
  {
  public:
    GumKeyPressedEvent(Node* source, KeyCode key, KeyCode modifiers);
  };
  
  class GumKeyReleasedEvent : public GumKeyRawEvent
  {
  
  public:
    GumKeyReleasedEvent(Node* source, KeyCode key, KeyCode modifiers);
    
  };
  
  class GumKeyRepeatEvent : public GumKeyRawEvent
  {
  public:
    GumKeyRepeatEvent(Node* source, KeyCode key, KeyCode modifiers);
  };
  
  class GumKeyTypedEvent : public GumKeyEvent
  {
  public:
    GumKeyTypedEvent(Node* source, KeyCode key);
  };
}