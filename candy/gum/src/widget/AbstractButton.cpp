#include <gum/widget/AbstractButton.hpp>

namespace Candy::Gum
{
  
  AbstractButton::AbstractButton()
  {
    AppendEventHandler<MouseEnteredEvent>([=, this](MouseEnteredEvent& event)
    {
      CANDY_CORE_INFO("AbstractButton::MouseEnteredEvent on {}. Position: {}", name, event.GetPosition());
      OnMouseEntered(event);
    });
    AppendEventHandler<MouseExitedEvent>([=, this](MouseExitedEvent& event)
    {
      CANDY_CORE_INFO("AbstractButton::MouseExitEvent on {}. Position: {}", name, event.GetPosition());
      OnMouseExited(event);
    });
    AppendEventHandler<MousePressedEvent>([=, this](MousePressedEvent& event)
    {
      CANDY_CORE_INFO("AbstractButton::MousePressedEvent on {}. Position: {}", name, event.GetPosition());
      armed = true;
      OnMousePressed(event);
    });
    AppendEventHandler<MouseReleasedEvent>([=, this](MouseReleasedEvent& event)
    {
      CANDY_CORE_INFO("AbstractButton::MouseReleasedEvent on {}. Position: {}", name, event.GetPosition());
      armed = false;
      OnMouseReleased(event);
    });
  }
  void AbstractButton::OnMouseEntered(MouseEnteredEvent& event)
  {
  
  }
  void AbstractButton::OnMouseExited(MouseExitedEvent& event)
  {
  
  }
  void AbstractButton::OnMousePressed(MousePressedEvent& event)
  {
  
  }
  void AbstractButton::OnMouseReleased(MouseReleasedEvent& event)
  {
  
  }
  
  bool AbstractButton::IsArmed() const
  {
    return armed;
  }
  
}