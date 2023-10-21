#include <gum/event/GumKeyEvent.hpp>
#include <gum/base/Node.hpp>
namespace Candy::Gum
{
  
  GumKeyEvent::GumKeyEvent(Node* source, GumEventType type, KeyCode key)
  : GumEvent(source, type), key(key)
  {
  
  }
  
  KeyCode GumKeyEvent::GetKey() const
  {
    return key;
  }
  
  GumKeyRawEvent::GumKeyRawEvent(Node* source, GumEventType type, KeyCode key, KeyCode modifiers)
  : GumKeyEvent(source, type, key), modifiers(modifiers)
  {
  
  }
  
  KeyCode GumKeyRawEvent::GetModifiers() const
  {
    return modifiers;
  }
  bool GumKeyRawEvent::IsModifierDown(KeyCode modifier) const
  {
    return (modifiers & modifier) != 0;
  }
  bool GumKeyRawEvent::IsShiftDown() const
  {
    return IsModifierDown(Key::LeftShift) || IsModifierDown(Key::RightShift);
  }
  bool GumKeyRawEvent::IsControlDown() const
  {
    return IsModifierDown(Key::LeftControl) || IsModifierDown(Key::RightControl);
  }
  bool GumKeyRawEvent::IsAltDown() const
  {
    return IsModifierDown(Key::LeftAlt) || IsModifierDown(Key::RightAlt);
  }
  bool GumKeyRawEvent::IsSuperDown() const
  {
    return IsModifierDown(Key::LeftSuper) || IsModifierDown(Key::RightSuper);
  }
  
  GumKeyPressedEvent::GumKeyPressedEvent(Node* source, KeyCode key, KeyCode modifiers)
  : GumKeyRawEvent(source, GumEventType::KeyPressed, key, modifiers)
  {
  
  }
  GumKeyReleasedEvent::GumKeyReleasedEvent(Node* source, KeyCode key, KeyCode modifiers)
  : GumKeyRawEvent(source, GumEventType::KeyReleased, key, modifiers)
  {
  
  }
  GumKeyRepeatEvent::GumKeyRepeatEvent(Node* source, KeyCode key, KeyCode modifiers)
  : GumKeyRawEvent(source, GumEventType::KeyRepeat, key, modifiers)
  {
  
  }
  
  GumKeyTypedEvent::GumKeyTypedEvent(Node* source, KeyCode key)
  : GumKeyEvent(source, GumEventType::KeyTyped, key)
  {
  
  }



}