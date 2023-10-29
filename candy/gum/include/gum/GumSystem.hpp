#pragma once
#include <candy/utils/Version.hpp>
#include <gum/Context.hpp>
namespace Candy::Gum
{
  class GumConfig
  {
  private:
    std::filesystem::path filepath;
    size_t msaaSampleCount=1;
  };
  class GumSystem
  {
  private:
    static void GLFWCallbackInit();
  public:
    static void SetCurrentContext(Context* context);
    static Context& GetCurrentContext();
    static void Init();
    static bool IsInitialized();
    static void Shutdown();
    static void BeginPass();
    static void EndPass();
    static void Render();
    
    //static GumContext& GetContext();
    static Version GetVersion();
  };
}