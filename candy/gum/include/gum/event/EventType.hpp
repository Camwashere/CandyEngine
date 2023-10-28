#pragma once
#include <cstdint>
#include <string>
#include <vector>
namespace Candy::Gum
{
  
  struct EventType
  {
    uint32_t type=0;
    uint32_t root=0;
    std::string name="None";
    
  private:
    static std::vector<EventType> registeredTypes;
    static EventType Register(const std::string& name, const EventType& root);
    static void InitEvents();
    static void InitInputEvents();
    static void InitMouseEvents();
    static void InitKeyEvents();
    static void InitWindowEvents();
    
  public:
    static void Init();
    static EventType GetType(uint32_t type);
    static bool IsDerived(const EventType& type, const EventType& parent);
    
  public:
    [[nodiscard]] EventType GetRoot()const;
    [[nodiscard]] bool IsDerived(const EventType& other)const;
    
    [[nodiscard]] bool operator==(const EventType& other)const;
    [[nodiscard]] bool operator!=(const EventType& other)const;
    [[nodiscard]] bool operator<(const EventType& other)const;
    [[nodiscard]] bool operator>(const EventType& other)const;
    [[nodiscard]] bool operator<=(const EventType& other)const;
    [[nodiscard]] bool operator>=(const EventType& other)const;
    
    EventType RegisterChild(const char* name)const;
    
    static EventType None;
    static EventType Any;
    static EventType Input;
    static EventType Mouse;
    static EventType Key;
    static EventType Window;
    
    static EventType MousePressed;
    static EventType MouseReleased;
    static EventType MouseMoved;
    static EventType MouseDragged;
    static EventType MouseEntered;
    static EventType MouseExited;
    
    static EventType KeyPressed;
    static EventType KeyReleased;
    static EventType KeyTyped;
    static EventType KeyRepeat;
  };
  
}

namespace std {
  template <typename T> struct hash;
  
  template<>
  struct hash<Candy::Gum::EventType>
  {
    std::size_t operator()(const Candy::Gum::EventType& eventType) const
    {
      return (std::uint64_t)eventType.type;
    }
  };
  
}