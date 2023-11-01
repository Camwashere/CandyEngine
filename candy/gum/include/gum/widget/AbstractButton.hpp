#pragma once
#include <gum/widget/Widget.hpp>
namespace Candy::Gum
{
  class AbstractButton : public Widget
  {
  protected:
    bool armed=false;
    
  protected:
    virtual void OnMouseEntered(MouseEnteredEvent& event);
    virtual void OnMouseExited(MouseExitedEvent& event);
    virtual void OnMousePressed(MousePressedEvent& event);
    virtual void OnMouseReleased(MouseReleasedEvent& event);
  
  public:
    AbstractButton();
    virtual ~AbstractButton()=default;
  
  public:
    [[nodiscard]] bool IsArmed() const;
    
    
  };
}