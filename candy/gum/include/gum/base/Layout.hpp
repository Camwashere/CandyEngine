#pragma once
#include <candy/math/Vector.hpp>
namespace Candy::Gum
{
  struct LayoutGuide
  {
    Math::Vector2 minPosition;
    Math::Vector2 minSize;
    
    Math::Vector2 prefPosition;
    Math::Vector2 prefSize;
    
    
    Math::Vector2 maxPosition;
    Math::Vector2 maxSize;
    
  };
}