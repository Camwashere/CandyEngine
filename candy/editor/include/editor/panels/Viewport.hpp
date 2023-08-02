#pragma once
#include <vulkan/vulkan.h>
#include <candy/math/Vector.hpp>
#include <candy/math/Rectangle.hpp>
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
    void OnUpdate();
    void OnRenderUI();
    
  };
}