#include <gum/widget/Button.hpp>

namespace Candy::Gum
{
  Button::Button()
  {
    EventHandler<MouseEnteredEvent> mouseEnteredEventHandler([=, this](MouseEnteredEvent& event)
    {
      CANDY_CORE_INFO("Button::MouseEnteredEvent. Position: {}", event.GetPosition());
      armed = true;
      SetBackgroundColor(hoveredColor);
    });
    EventHandler<MouseExitedEvent> mouseExitedEventHandler([=, this](MouseExitedEvent& event)
    {
      CANDY_CORE_INFO("Button::MouseExitEvent. Position: {}", event.GetPosition());
      armed = false;
      SetBackgroundColor(normalColor);
    });
    AppendEventHandler(mouseEnteredEventHandler);
    AppendEventHandler(mouseExitedEventHandler);
  }
  
  bool Button::IsArmed() const
  {
    return armed;
  }
}