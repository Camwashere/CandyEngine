#include <candy/ui/GumLayer.hpp>
#include "CandyPch.hpp"
#include <candy/math/Vector.hpp>
#include <candy/graphics/RenderCommand.hpp>
#include <gum/GumInstance.hpp>
#include <candy/graphics/Vulkan.hpp>
namespace Candy
{
  using namespace Graphics;
  using namespace Gum;
  GumLayer::GumLayer()
  {
    
  }
  
  void GumLayer::OnAttach()
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_INFO("Gum Version: {}", GumInstance::GetVersion());
    
    
  }
  
  void GumLayer::OnDetach()
  {
    CANDY_PROFILE_FUNCTION();
    GumInstance::Shutdown();
  }
  
  void GumLayer::OnEvent(Events::Event &e)
  {
    CANDY_PROFILE_FUNCTION();
    if (blockEvents)
    {
      e.SetHandled(e.IsHandled() | (e.GetClass()==Events::EventClass::MOUSE));
      e.SetHandled(e.IsHandled() | (e.GetClass()==Events::EventClass::KEYBOARD));
    }
  }
  void GumLayer::BlockEvents(bool block)
  {
    blockEvents = block;
  }
  void GumLayer::Begin()
  {
    CANDY_PROFILE_FUNCTION();
    GumInstance::NewFrame();
    Renderer::BeginUIPass();
  }
  
  void GumLayer::End()
  {
    CANDY_PROFILE_FUNCTION();
    
    // Rendering
    GumInstance::EndFrame();
    
    
    
    
  }
}