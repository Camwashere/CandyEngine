#pragma once
#include "Logger.hpp"
#include "../general/CandyCoreBase.hpp"
namespace Candy
{
    class Log
    {
    private:
        inline static SharedPtr<Logger> coreLogger = CreateSharedPtr<Logger>();
        inline static SharedPtr<Logger> clientLogger = CreateSharedPtr<Logger>();
        
    public:
        static SharedPtr<Logger> GetCoreLogger(){return coreLogger;}
        static SharedPtr<Logger> GetClientLogger(){return clientLogger;}
    };
}

// Core log macros
#define CANDY_CORE_TRACE(...)    ::Candy::Log::GetCoreLogger()->Trace(__VA_ARGS__)
#define CANDY_CORE_INFO(...)     ::Candy::Log::GetCoreLogger()->Info(__VA_ARGS__)
#define CANDY_CORE_WARN(...)     ::Candy::Log::GetCoreLogger()->Warn(__VA_ARGS__)
#define CANDY_CORE_ERROR(...)    ::Candy::Log::GetCoreLogger()->Error(__VA_ARGS__)
#define CANDY_CORE_CRITICAL(...) ::Candy::Log::GetCoreLogger()->Critical(__VA_ARGS__)

// Client log macros
#define CANDY_TRACE(...)         ::Candy::Log::GetClientLogger()->Trace(__VA_ARGS__)
#define CANDY_INFO(...)          ::Candy::Log::GetClientLogger()->Info(__VA_ARGS__)
#define CANDY_WARN(...)          ::Candy::Log::GetClientLogger()->Warn(__VA_ARGS__)
#define CANDY_ERROR(...)         ::Candy::Log::GetClientLogger()->Error(__VA_ARGS__)
#define CANDY_CRITICAL(...)      ::Candy::Log::GetClientLogger()->Critical(__VA_ARGS__)