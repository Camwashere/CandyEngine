#pragma once
#include <gum/widget/Widget.hpp>
namespace Candy::Gum
{
  class Button : public Widget
  {
  protected:
    bool armed=false;
    Color hoveredColor=Color::blue;
    Color normalColor=Color::brown;
    Color pressedColor=Color::green;
    Color disabledColor=Color::grey;
    
  public:
    Button();
    
  public:
    [[nodiscard]] bool IsArmed() const;
    
  
  };
}