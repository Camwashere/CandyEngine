#pragma once
#include <candy/event/Event.hpp>
#include "GumEvent.hpp"
#include "candy/event/Events.hpp"

namespace Candy::Gum
{
  class GumEventHandler
  {
  public:
    virtual void OnEvent(GumEvent& event) = 0;
  };
  
  class GumCaptureEventHandler
  {
  protected:
    bool OnCaptureMouseMoveEvent(Events::MouseEvent& event);
    bool OnCaptureMousePressedEvent(Events::MousePressedEvent& event);
    bool OnCaptureMouseReleasedEvent(Events::MouseReleasedEvent& event);
    bool OnCaptureKeyEvent(Events::KeyEvent& event);
    bool OnCaptureWindowEvent(Events::WindowEvent& event);
  public:
    void OnCaptureEvent(Events::Event& event);
    
    
    
    
  };
}