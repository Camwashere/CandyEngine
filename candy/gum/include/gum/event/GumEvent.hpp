#pragma once
#include <candy/base/Base.hpp>

namespace Candy::Gum
{
  class GumContext;
  class Node;
  
  enum GumEventCategory
  {
    MOUSE=0,
    KEYBOARD,
    CONTEXT,
    SCROLL,
    CUSTOM,
  };
  enum GumEventType
  {
    // Mouse
    None=0,
    MousePressed,
    MouseReleased,
    MouseMoved,
    MouseDragged,
    MouseEntered,
    MouseExited,
    
    
    // Keyboard
    KeyPressed,
    KeyReleased,
    KeyTyped,
    KeyRepeat,
    
    // Window
    ContextResized,
    ContextClosed,
    ContextMinimized,
    
    ScrollStarted,
    Scroll,
    ScrollEnded,
  };
  
  
  class GumEvent
  {
  protected:
    Node* source;
    const GumEventType type;
    const GumEventCategory category;
    bool consumed;
    
  public:
    static GumEventCategory TypeToCategory(GumEventType type);
    
  public:
    GumEvent(Node* source, GumEventType type);
    
  public:
    Node& GetSource();
    [[nodiscard]] GumEventCategory GetCategory()const;
    void Consume();
    [[nodiscard]] bool IsConsumed() const;
    [[nodiscard]] GumEventType GetType() const;
  };
}