#pragma once
#include <utility>

#include "EventType.hpp"
#include "EventTarget.hpp"
namespace Candy::Gum
{
  class Node;
  class Event
  {
  private:
    bool consumed=false;
    EventType type=EventType::None;
    Node* source;
    
  protected:
    explicit Event(EventType type);
    
  public:
    
    void SetSource(Node* value){source=value;}
    [[nodiscard]] bool HasSource()const{return source != nullptr;}
    [[nodiscard]] Node* GetSource()const{return source;}
    [[nodiscard]] EventType GetType()const{return type;}
    void Consume(){consumed=true;}
    [[nodiscard]] bool IsConsumed()const{return consumed;}
  };
  
  
  
  
  
  
  
  
  
  
  
}