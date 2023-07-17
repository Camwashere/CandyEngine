#pragma once
#include <spdlog/spdlog.h>
#include "spdlog/fmt/ostr.h"
#include "Base.hpp"
namespace Candy
{
  class Log
  {
  private:
    static SharedPtr<spdlog::logger> coreLogger;
    static SharedPtr<spdlog::logger> clientLogger;
  
  public:
    static void Init();
    static SharedPtr<spdlog::logger>& GetCoreLogger(){return coreLogger;}
    
    static SharedPtr<spdlog::logger>& GetClientLogger(){return clientLogger;}
  };
}

// Core log macros
#define CANDY_CORE_TRACE(...)    ::Candy::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CANDY_CORE_INFO(...)     ::Candy::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CANDY_CORE_WARN(...)     ::Candy::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CANDY_CORE_ERROR(...)    ::Candy::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CANDY_CORE_CRITICAL(...) ::Candy::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define CANDY_TRACE(...)         ::Candy::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CANDY_INFO(...)          ::Candy::Log::GetClientLogger()->info(__VA_ARGS__)
#define CANDY_WARN(...)          ::Candy::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CANDY_ERROR(...)         ::Candy::Log::GetClientLogger()->error(__VA_ARGS__)
#define CANDY_CRITICAL(...)      ::Candy::Log::GetClientLogger()->critical(__VA_ARGS__)