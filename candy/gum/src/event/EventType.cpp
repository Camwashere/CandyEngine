#include <gum/event/EventType.hpp>
#include <utility>

namespace Candy::Gum
{
  
  
  std::vector<EventType> EventType::registeredTypes{};
  EventType EventType::None;
  EventType EventType::Any;
  EventType EventType::Input;
  EventType EventType::Mouse;
  EventType EventType::Key;
  EventType EventType::Window;
  
  EventType EventType::MouseButton;
  EventType EventType::MousePressed;
  EventType EventType::MouseReleased;
  EventType EventType::MouseMoved;
  EventType EventType::MouseDragged;
  EventType EventType::MouseEntered;
  EventType EventType::MouseExited;
  
  EventType EventType::KeyRaw;
  EventType EventType::KeyPressed;
  EventType EventType::KeyReleased;
  EventType EventType::KeyRepeat;
  EventType EventType::KeyTyped;
  
  EventType EventType::WindowResized;
  EventType EventType::ContextResized;
  
  EventType::EventType(uint32_t type, uint32_t root, std::string  name) : type(type), root(root), name(std::move(name))
  {
  
  }
  
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
    EventType::MouseButton = EventType::Mouse.RegisterChild("Mouse Button");
    EventType::MousePressed = EventType::MouseButton.RegisterChild("Mouse Pressed");
    EventType::MouseReleased = EventType::MouseButton.RegisterChild("Mouse Released");
    
    EventType::MouseMoved = EventType::Mouse.RegisterChild("Mouse Moved");
    EventType::MouseDragged = EventType::Mouse.RegisterChild("Mouse Dragged");
    EventType::MouseEntered = EventType::Mouse.RegisterChild("Mouse Entered");
    EventType::MouseExited = EventType::Mouse.RegisterChild("Mouse Exited");
  }
  
  void EventType::InitKeyEvents()
  {
    EventType::Key = EventType::Input.RegisterChild("Key");
    EventType::KeyRaw = EventType::Key.RegisterChild("Key Raw");
    EventType::KeyPressed = EventType::KeyRaw.RegisterChild("Key Pressed");
    EventType::KeyReleased = EventType::KeyRaw.RegisterChild("Key Released");
    EventType::KeyRepeat = EventType::KeyRaw.RegisterChild("Key Repeat");
    EventType::KeyTyped = EventType::Key.RegisterChild("Key Typed");
    
  }
  void EventType::InitWindowEvents()
  {
    EventType::Window = EventType::Any.RegisterChild("Window");
    EventType::WindowResized = EventType::Window.RegisterChild("Window Resized");
    EventType::ContextResized = EventType::Window.RegisterChild("Context Resized");
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
  uint32_t EventType::GetTypeIndex()const
  {
    return type;
  }
  std::string EventType::GetName()const
  {
    return name;
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