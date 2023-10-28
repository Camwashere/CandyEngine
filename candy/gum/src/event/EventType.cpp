#include <gum/event/EventType.hpp>

namespace Candy::Gum
{
  
  
  std::vector<EventType> EventType::registeredTypes{};
  EventType EventType::None;
  EventType EventType::Any;
  EventType EventType::Input;
  EventType EventType::Mouse;
  EventType EventType::Key;
  EventType EventType::Window;
  
  EventType EventType::MousePressed;
  EventType EventType::MouseReleased;
  EventType EventType::MouseMoved;
  EventType EventType::MouseDragged;
  EventType EventType::MouseEntered;
  EventType EventType::MouseExited;
  
  
  EventType EventType::KeyPressed;
  EventType EventType::KeyReleased;
  EventType EventType::KeyTyped;
  EventType EventType::KeyRepeat;
  
  void EventType::InitEvents()
  {
    EventType::None = EventType(0, 0, "None");
    EventType::Any = EventType::None.RegisterChild("Any");
    InitInputEvents();
    InitWindowEvents();
    
  }
  void EventType::InitInputEvents()
  {
    EventType::Input = EventType::Any.RegisterChild("Input");
    InitMouseEvents();
    InitKeyEvents();
  }
  void EventType::InitMouseEvents()
  {
    EventType::Mouse = EventType::Input.RegisterChild("Mouse");
    EventType::MousePressed = EventType::Mouse.RegisterChild("Pressed");
    EventType::MouseReleased = EventType::Mouse.RegisterChild("Released");
    EventType::MouseMoved = EventType::Mouse.RegisterChild("Moved");
    EventType::MouseDragged = EventType::Mouse.RegisterChild("Dragged");
    EventType::MouseEntered = EventType::Mouse.RegisterChild("Entered");
    EventType::MouseExited = EventType::Mouse.RegisterChild("Exited");
  }
  
  void EventType::InitKeyEvents()
  {
    EventType::Key = EventType::Input.RegisterChild("Key");
    
    EventType::KeyPressed = EventType::Key.RegisterChild("Pressed");
    EventType::KeyReleased = EventType::Key.RegisterChild("Released");
    EventType::KeyTyped = EventType::Key.RegisterChild("Typed");
    EventType::KeyRepeat = EventType::Key.RegisterChild("Repeat");
    
  }
  void EventType::InitWindowEvents()
  {
    EventType::Window = EventType::Any.RegisterChild("Window");
  }
  
  void EventType::Init()
  {
    InitEvents();
  }
  EventType EventType::RegisterChild(const char* childName)const
  {
    return Register(childName, *this);
  }
  
  EventType EventType::GetType(uint32_t type)
  {
    return registeredTypes[type];
  }
  EventType EventType::Register(const std::string& name, const EventType& root)
  {
    uint32_t index = registeredTypes.size();
    EventType eventType(index, root.type, name);
    registeredTypes.push_back(eventType);
    return eventType;
  }
  
  bool EventType::IsDerived(const EventType& type, const EventType& parent)
  {
    if (type.type == 0)
    {
      return false;
    }
    if (type.type == parent.type)
    {
      return true;
    }
    if (type.root == parent.root)
    {
      return false;
    }
    return IsDerived(GetType(type.root), parent);
  }
  
  EventType EventType::GetRoot()const
  {
    return GetType(root);
  }
  
  bool EventType::IsDerived(const EventType& other)const
  {
    return EventType::IsDerived(*this, other);
  }
  
  bool EventType::operator==(const EventType& other)const
  {
    return type==other.type;
  }
  bool EventType::operator!=(const EventType& other)const
  {
    return type!=other.type;
  }
  
  bool EventType::operator<(const EventType& other)const
  {
    return type<other.type;
  }
  
  bool EventType::operator>(const EventType& other)const
  {
    return type>other.type;
  }
  
  bool EventType::operator<=(const EventType& other)const
  {
    return type<=other.type;
  }
  
  bool EventType::operator>=(const EventType& other)const
  {
    return type>=other.type;
  }
}