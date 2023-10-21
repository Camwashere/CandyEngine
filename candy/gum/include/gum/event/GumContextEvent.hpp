#pragma once
#include "GumEvent.hpp"
#include <candy/math/Vector.hpp>
namespace Candy::Gum
{
  class GumContextEvent : public GumEvent
  {
  protected:
    GumContextEvent(Node* source, GumEventType type);
  };
  
  class GumContextResizedEvent : public GumContextEvent
  {
  protected:
    Math::Vector2u size;
    
  public:
    GumContextResizedEvent(Node* source, uint32_t width, uint32_t height);
    
    [[nodiscard]] uint32_t GetWidth()const;
    [[nodiscard]] uint32_t GetHeight()const;
    [[nodiscard]] Math::Vector2u GetSize()const;
  };
  
  class GumContextClosedEvent : public GumContextEvent
  {
  public:
    explicit GumContextClosedEvent(Node* source);
  };
  
  class GumContextMinimizedEvent : public GumContextEvent
  {
  public:
    explicit GumContextMinimizedEvent(Node* source);
  };
}