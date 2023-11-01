#pragma once
#include <utility>

#include "EventType.hpp"
#include "EventTarget.hpp"
#include <list>
namespace Candy::Gum
{
  class Node;
  
  
  class Event
  {
  private:
    bool consumed=false;
    EventType type=EventType::None;
    Node* source;
    std::list<Node*> eventDispatchChain;
    std::list<Node*>::iterator currentIter; // Add this line
    
    void BuildChain();
  protected:
    explicit Event(EventType type);
    
  public:
    void SetSource(Node* value);
    [[nodiscard]] bool HasSource()const{return source != nullptr;}
    [[nodiscard]] Node* GetSource()const{return source;}
    [[nodiscard]] EventType GetType()const{return type;}
    [[nodiscard]] std::string GetName()const{return type.GetName();}
    void Consume(){consumed=true;}
    [[nodiscard]] bool IsConsumed()const{return consumed;}
    [[nodiscard]] Node* GetTarget()const{ // Updated this line
      if (currentIter != eventDispatchChain.end()) {
        return *currentIter;
      } else {
        return nullptr;
      }
    }
    
    // Iteration functions
    void IncrementIter() {
      if (currentIter != eventDispatchChain.end()) {
        ++currentIter;
      }
    }
    
    void DecrementIter() {
      if (currentIter != eventDispatchChain.begin()) {
        --currentIter;
      }
    }
  };
  
  
  
  
  
  
  
  
  
  
  
}