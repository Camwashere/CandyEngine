#include <gum/GumInstance.hpp>
#include "CandyPch.hpp"
#include <candy/graphics/Renderer.hpp>
#include <gum/GumRenderer.hpp>
#include <gum/event/EventType.hpp>
namespace Candy::Gum
{
  using namespace Graphics;
  struct GumData
  {
    Version version=Version(0,0,1);
    GumConfig config;
    GumContext* currentContext=nullptr;
    
    bool initialized=false;
    
  };
  
  static GumData data;
  
  void GumInstance::GLFWCallbackInit()
  {
  
  }
  
  void GumInstance::Init()
  {
    CANDY_PROFILE_FUNCTION();
   CANDY_CORE_INFO("Initializing Gum");
   GumRenderer::Init();
   EventType::Init();
   data.initialized=true;
   CANDY_CORE_INFO("Initialized Gum");
  }
  
  bool GumInstance::IsInitialized()
  {
    return data.initialized;
  }
  
  void GumInstance::SetCurrentContext(GumContext* context)
  {
    data.currentContext = context;
  }
  GumContext& GumInstance::GetCurrentContext()
  {
    CANDY_CORE_ASSERT(data.currentContext, "GumInstance::GetCurrentContext: currentContext is nullptr");
    return *data.currentContext;
  }
  void GumInstance::Shutdown()
  {
  
  }
  void GumInstance::BeginPass()
  {
    CANDY_PROFILE_FUNCTION();
    Renderer::BeginGumPass();
    //Renderer::BeginEditorChain();
  }
  void GumInstance::EndPass()
  {
    Renderer::EndGumPass();
  }
  void GumInstance::Render()
  {
  
  }
  
  /*GumContext& GumInstance::GetContext()
  {
    return data.context;
  }*/
  Version GumInstance::GetVersion()
  {
    return data.version;
  }
}