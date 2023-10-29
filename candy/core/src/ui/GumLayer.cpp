#include <candy/ui/GumLayer.hpp>
#include "CandyPch.hpp"
#include <candy/math/Vector.hpp>
#include <candy/graphics/RenderCommand.hpp>
#include "gum/GumSystem.hpp"
#include <gum/Context.hpp>
#include <candy/graphics/Vulkan.hpp>
namespace Candy
{
  //using namespace Graphics;
  using namespace Gum;
  GumLayer::GumLayer(Gum::Context* gumContext) : context(gumContext)
  {
    
  }
  
  void GumLayer::OnAttach()
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_INFO("GumSystem Version: {}", GumSystem::GetVersion());
    
    
  }
  
  void GumLayer::OnDetach()
  {
    CANDY_PROFILE_FUNCTION();
    GumSystem::Shutdown();
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
    //Renderer::BeginEditorChain();
    GumSystem::BeginPass();
    context->BeginScene();
    
    //Renderer::BeginUIPass();
  }
  
  void GumLayer::End()
  {
    CANDY_PROFILE_FUNCTION();
    context->EndScene();
    GumSystem::EndPass();
  }
}