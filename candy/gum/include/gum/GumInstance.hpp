#pragma once
#include <candy/utils/Version.hpp>
#include <filesystem>
#include "GumContext.hpp"
namespace Candy::Gum
{
  
  class GumConfig
  {
  private:
    std::filesystem::path filepath;
    size_t msaaSampleCount=1;
    
  public:
    bool Load(const std::filesystem::path& path);
    
  };
  class GumInstance
  {
  private:
    static void GLFWCallbackInit();
  public:
    static void SetCurrentContext(GumContext* context);
    static GumContext& GetCurrentContext();
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