#include <gum/widget/Button.hpp>

namespace Candy::Gum
{
  Button::Button()
  {
    SetBackgroundFill(normalFill);
  }
  
  void Button::OnMouseEntered(MouseEnteredEvent& event)
  {
    SetBackgroundFill(hoveredFill);
  }
  void Button::OnMouseExited(MouseExitedEvent& event)
  {
    SetBackgroundFill(normalFill);
  }
  void Button::OnMousePressed(MousePressedEvent& event)
  {
    SetBackgroundFill(pressedFill);
  }
  void Button::OnMouseReleased(MouseReleasedEvent& event)
  {
    SetBackgroundFill(hoveredFill);
  }
  
  void Button::UpdateFill()
  {
    if (IsArmed())
    {
      SetBackgroundFill(pressedFill);
    }
    else if (IsHovered())
    {
      SetBackgroundFill(hoveredFill);
    }
    else
    {
      SetBackgroundFill(normalFill);
    }
    
    
    
  }
  void Button::SetHoveredFill(const Paint& color)
  {
    hoveredFill=color;
    UpdateFill();
  }
  void Button::SetNormalFill(const Paint& color)
  {
    normalFill=color;
    UpdateFill();
  }
  void Button::SetPressedFill(const Paint& color)
  {
    pressedFill=color;
    UpdateFill();
  }
  void Button::SetDisabledFill(const Paint& color)
  {
    disabledFill=color;
    UpdateFill();
  }
  
  [[nodiscard]] const Paint& Button::GetHoveredFill() const{return hoveredFill;}
  [[nodiscard]] const Paint& Button::GetNormalFill() const{return normalFill;}
  [[nodiscard]] const Paint& Button::GetPressedFill() const{return pressedFill;}
  [[nodiscard]] const Paint& Button::GetDisabledFill() const{return disabledFill;}
  
  
}