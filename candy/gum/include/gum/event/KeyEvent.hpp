#pragma once
#include <candy/base/KeyCodes.hpp>
#include <gum/event/InputEvent.hpp>

namespace Candy::Gum
{
  class KeyEvent : public InputEvent
  {
  protected:
    KeyCode code;
    
  protected:
    KeyEvent(EventType derivedKeyEventType, KeyCode keyCode) : InputEvent(std::move(derivedKeyEventType)), code(keyCode){}
    
  public:
    [[nodiscard]] KeyCode GetKeyCode() const{return code;}
    
    static EventType Type(){return EventType::Key;}
  };
  
  class KeyRawEvent : public KeyEvent
  {
  protected:
    KeyCode modifiers;
    
  protected:
    KeyRawEvent(EventType derivedKeyEventType, KeyCode keyCode, KeyCode modifiers) : KeyEvent(std::move(derivedKeyEventType), keyCode), modifiers(modifiers){}
    
    
  public:
    [[nodiscard]] KeyCode GetModifiers() const{return modifiers;}
    [[nodiscard]] bool IsModifierDown(KeyCode modifier) const{return (modifiers & modifier) != 0;}
    [[nodiscard]] bool IsShiftDown() const{return IsModifierDown(Key::LeftShift | Key::RightShift);}
    [[nodiscard]] bool IsControlDown() const{return IsModifierDown(Key::LeftControl | Key::RightControl);}
    [[nodiscard]] bool IsAltDown() const{return IsModifierDown(Key::LeftAlt | Key::RightAlt);}
    [[nodiscard]] bool IsSuperDown() const{return IsModifierDown(Key::LeftSuper | Key::RightSuper);}
    
  public:
    static EventType Type(){return EventType::KeyRaw;}
  };
  
  class KeyPressedEvent : public KeyRawEvent
  {
  public:
    KeyPressedEvent(KeyCode keyCode, KeyCode modifiers) : KeyRawEvent(Type(), keyCode, modifiers){}
    
  public:
    static EventType Type(){return EventType::KeyPressed;}
  };
  
  class KeyReleasedEvent : public KeyRawEvent
  {
  public:
    KeyReleasedEvent(KeyCode keyCode, KeyCode modifiers) : KeyRawEvent(Type(), keyCode, modifiers){}
    
  public:
    static EventType Type(){return EventType::KeyReleased;}
  };
  
  class KeyRepeatEvent : public KeyRawEvent
  {
  protected:
    int repeat;
    
  public:
    KeyRepeatEvent(KeyCode keyCode, KeyCode modifiers, int repeat) : KeyRawEvent(Type(), keyCode, modifiers), repeat(repeat){}
    
  public:
    [[nodiscard]] int GetRepeat() const{return repeat;}
    
  public:
    static EventType Type(){return EventType::KeyRepeat;}
  };
  
  class KeyTypedEvent : public KeyEvent
  {
  public:
    explicit KeyTypedEvent(KeyCode keyCode) : KeyEvent(Type(), keyCode){}
    
  public:
    static EventType Type(){return EventType::KeyTyped;}
  };
  
}