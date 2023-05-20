#pragma once

#include <memory>

// Platform Detection
#ifdef _WIN32
    #ifdef _WIN64
        // Windows 64
        #define CANDY_PLATFORM_WINDOWS
    #else
        #error "x86 Builds Not Supported By Candy Engine"
    #endif
#elif defined(__APPLE__) || defined(__MACH__)
    #include <TargetConditionals.h>
    	#if TARGET_IPHONE_SIMULATOR == 1
    		#error "IOS simulator is not supported!"
    	#elif TARGET_OS_IPHONE == 1
    		#define CANDY_PLATFORM_IOS
    		#error "IOS is not supported!"
    	#elif TARGET_OS_MAC == 1
    		#define CANDY_PLATFORM_MACOS
    		#error "MacOS is not supported!"
    	#else
    		#error "Unknown Apple platform!"
        #endif

#elif defined(__ANDROID__)
   	#define CANDY_PLATFORM_ANDROID
   	#error "Android is not supported!"

#elif defined(__linux__)
   	#define CANDY_PLATFORM_LINUX
   	#error "Linux is not supported!"

#else
        /* Unknown compiler/platform */
        #error "Unknown platform!"
#endif
// End of platform detection


#ifdef CANDY_DEBUG
    #if defined(CANDY_PLATFORM_WINDOWS)
        #define CANDY_DEBUG_BREAK() __debugbreak()
    #elif defined(CANDY_PLATFORM_LINUX)
        #include <signal.h>
        #define CANDY_DEBUG_BREAK() raise(SIGTRAP)
    #else
        #error "Platform does not support debugbreak"
    #endif
    #define CANDY_ENABLE_ASSERTS
#else
#define CANDY_DEBUG_BREAK()
#endif

#define CANDY_EXPAND_MACRO(x) x
#define CANDY_STRINGIFY_MACRO(x) #x

#define BIT(x) (1<<x)

#define CANDY_BIND_EVENT_FUNCTION(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Candy
{
    template<typename T>
    using UniquePtr = std::unique_ptr<T>;
    
    template<typename T, typename... Args>
    constexpr UniquePtr<T> CreateUniquePtr(Args&&... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
    
    template<typename T>
    using SharedPtr = std::shared_ptr<T>;
    template<typename T, typename... Args>
    constexpr SharedPtr<T> CreateSharedPtr(Args&&... args)
    {
        //return std::shared_ptr<T>(new T(std::forward<Args...>(args...)));
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}

#include "CandyAssert.hpp"
