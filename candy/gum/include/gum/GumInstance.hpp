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
  public:
    static void Init(const std::filesystem::path& iniConfigPath);
    static void Shutdown();
    static void NewFrame();
    static void EndFrame();
    static void Render();
    //static GumContext& GetContext();
    static Version GetVersion();
  };
}