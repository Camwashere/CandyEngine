#include "gum/GumSystem.hpp"
#include <gum/render/Renderer.hpp>
#include <candy/graphics/Renderer.hpp>
#include <gum/event/EventType.hpp>
namespace Candy::Gum
{
  //using namespace Graphics;
  struct GumData
  {
    Version version=Version(0,0,1);
    GumConfig config;
    Context* currentContext=nullptr;
    
    bool initialized=false;
    
  };
  
  static GumData data;
  
  void GumSystem::GLFWCallbackInit()
  {
    
  }
  
  void GumSystem::Init()
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_INFO("Initializing GumSystem");
    Renderer::Init();
    EventType::Init();
    data.initialized=true;
    CANDY_CORE_INFO("Initialized GumSystem");
  }
  
  bool GumSystem::IsInitialized()
  {
    return data.initialized;
  }
  
  void GumSystem::SetCurrentContext(Context* context)
  {
    data.currentContext = context;
  }
  Context& GumSystem::GetCurrentContext()
  {
    CANDY_CORE_ASSERT(data.currentContext, "GumSystem::GetCurrentContext: currentContext is nullptr");
    return *data.currentContext;
  }
  void GumSystem::Shutdown()
  {
    
  }
  void GumSystem::BeginPass()
  {
    CANDY_PROFILE_FUNCTION();
    Graphics::Renderer::BeginGumPass();
    //Renderer::BeginEditorChain();
  }
  void GumSystem::EndPass()
  {
    Graphics::Renderer::EndGumPass();
  }
  void GumSystem::Render()
  {
    
  }
  
  /*GumContext& GumSystem::GetContext()
  {
    return data.context;
  }*/
  Version GumSystem::GetVersion()
  {
    return data.version;
  }
}