#pragma once
#include <vulkan/vulkan.h>
#include <candy/math/Vector.hpp>
#include <candy/math/Rectangle.hpp>
#include <candy/event/Events.hpp>
namespace Candy
{
  class Viewport
  {
  private:
    bool isFocused=false;
    bool isHovered=false;
    VkViewport viewport;
    
    Math::Rectangle bounds;
    Math::Vector2 size;
    
  public:
    Viewport();
    
  public:
    void OnAttach();
    void OnUpdate();
    void OnEvent(Events::Event& event);
    void OnRenderUI();
    
  };
}