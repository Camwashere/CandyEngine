#include <gum/event/GumEventHandler.hpp>

namespace Candy::Gum
{
  void GumCaptureEventHandler::OnCaptureEvent(Events::Event& event)
  {
    Events::EventDispatcher dispatcher(event);
    switch(event.GetType())
    {
      case Events::EventType::MOUSE_MOVE:
      {
        dispatcher.Dispatch<Events::MouseMovedEvent>(CANDY_BIND_EVENT_FUNCTION(GumCaptureEventHandler::OnCaptureMouseMoveEvent));
        break;
      }
      case Events::EventType::MOUSE_PRESSED:
      {
        dispatcher.Dispatch<Events::MousePressedEvent>(CANDY_BIND_EVENT_FUNCTION(GumCaptureEventHandler::OnCaptureMousePressedEvent));
        break;
      }
      case Events::EventType::MOUSE_RELEASED:
      {
        dispatcher.Dispatch<Events::MouseReleasedEvent>(CANDY_BIND_EVENT_FUNCTION(GumCaptureEventHandler::OnCaptureMouseReleasedEvent));
        break;
      }
      
    }
    
  }
  bool GumCaptureEventHandler::OnCaptureMouseMoveEvent(Events::MouseEvent& event)
  {
  
  }
  bool GumCaptureEventHandler::OnCaptureMousePressedEvent(Events::MousePressedEvent& event)
  {
  
  }
  bool GumCaptureEventHandler::OnCaptureMouseReleasedEvent(Events::MouseReleasedEvent& event)
  {
  
  }
  bool GumCaptureEventHandler::OnCaptureKeyEvent(Events::KeyEvent& event)
  {
  
  }
  bool GumCaptureEventHandler::OnCaptureWindowEvent(Events::WindowEvent& event)
  {
  
  }
}