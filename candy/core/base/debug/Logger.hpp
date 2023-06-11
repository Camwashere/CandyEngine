#pragma once
#include "../primitive/PrimitiveTypes.hpp"
#include <iostream>
#include <utility>
#include <fmt/core.h>
#include <fmt/color.h>

namespace Candy
{
    enum class LogLevel : uint8
    {
        TRACE=0,
        INFO,
        WARN,
        ERROR,
        CRITICAL
    };
    class Logger
    {
    private:
        LogLevel logLevel;
        std::string name="Undefined Logger";
        
    private:
        
        template<typename...T>
        inline void Log(const fmt::format_string<T...>& formatStr, T&&... args)
        {
            fmt::print(formatStr, args...);
            fmt::print("{}",'\n');
            
        }
        
        template<typename S, typename...Args>
        inline void Log(const fmt::text_style& style, const S& formatStr, const Args&...args)
        {
            fmt::print(style, formatStr, args...);
            fmt::print("{}",'\n');
        }
        
    public:
        Logger() : logLevel(LogLevel::TRACE){}
        explicit Logger(std::string  loggerName) : logLevel(LogLevel::TRACE), name(std::move(loggerName)){}
        explicit Logger(LogLevel level) : logLevel(level){}
        
    public:
        template<typename...T>
        inline void Trace(fmt::format_string<T...> formatStr, T&&... args)
        {
            Log(std::move(formatStr), args...);
        }
        template<typename S, typename...Args>
        inline void Info(const S& formatStr, const Args&...args)
        {
            Log(fmt::fg(fmt::color::yellow), formatStr, args...);
        }
        template<typename S, typename...Args>
        inline void Warn(const S& formatStr, const Args&...args)
        {
            Log(fmt::fg(fmt::color::yellow), formatStr, args...);
        }
        template<typename S, typename...Args>
        inline void Error(const S& formatStr, const Args&...args)
        {
            Log((fmt::emphasis::bold | fmt::emphasis::underline) | fmt::fg(fmt::color::red), formatStr, args...);
        }
        template<typename S, typename...Args>
        inline void Critical(const S& formatStr, const Args&...args)
        {
            Log((fmt::emphasis::bold | fmt::emphasis::underline) | fmt::fg(fmt::color::rebecca_purple), formatStr, args...);
        }
        
        
        
        
        
        
        
    public:
        inline void SetLogLevel(LogLevel level){logLevel = level;}
        inline LogLevel GetLogLevel()const{return logLevel;}
        
        
        
        
    };
}