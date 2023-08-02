#pragma once
#include <string>
#include <functional>
#include "candy/math/Vector.hpp"
namespace Candy::UI
{
  class Button
  {
  private:
    std::string text;
    Math::Vector2 position;
    Math::Vector2 size;
    std::function<void()> onClick;
    
  public:
    Button(std::string text, Math::Vector2 pos, Math::Vector2 size);
    
    
  };
}