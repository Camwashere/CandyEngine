#include <gum/base/Root.hpp>
#include "CandyPch.hpp"
#include <gum/base/SceneGraph.hpp>
namespace Candy::Gum
{
  Root::Root()
  {
    CANDY_PROFILE_FUNCTION();
    name = "Root";
    transform = Math::Matrix3::IDENTITY;
    SetLayoutPosition({0, 0});
    
    Gum::EventHandler<Gum::ContextResizedEvent> contextResizeHandler([=, this](Gum::ContextResizedEvent& event)
    {
      CANDY_CORE_INFO("Root::ContextResizedEvent. Size: {}", event.GetSize());
      SetSize(event.GetSize());
    });
    AppendEventFilter(contextResizeHandler);
    
  }
  bool Root::Contains(Math::Vector2 scenePoint) const
  {
    CANDY_PROFILE_FUNCTION();
    return GetBoundsInScene().Contains(scenePoint);
    
  }
 
  
  
  
  
}