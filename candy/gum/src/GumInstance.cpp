#include <gum/GumInstance.hpp>
#include "CandyPch.hpp"
#include <candy/graphics/Renderer.hpp>
namespace Candy::Gum
{
  using namespace Graphics;
  struct GumData
  {
    Version version=Version(0,0,1);
    GumConfig config;
    //GumContext context;
    
  };
  
  static GumData data;
  void GumInstance::Init(const std::filesystem::path& iniConfigPath)
  {
    //bool loadedConfig = data.config.Load(iniConfigPath);
   // CANDY_CORE_ASSERT(loadedConfig, "Failed to load Gum config");
    
  }
  void GumInstance::Shutdown()
  {
  
  }
  void GumInstance::NewFrame()
  {
    Renderer::BeginUIPass();
  }
  void GumInstance::EndFrame()
  {
  
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