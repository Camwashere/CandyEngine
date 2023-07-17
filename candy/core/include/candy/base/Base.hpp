#pragma once
#include "PlatformDetection.hpp"
#include <memory>
#ifdef CANDY_DEBUG
#if defined(CANDY_PLATFORM_WINDOWS)
#define CANDY_DEBUGBREAK() __debugbreak()
#elif defined(CANDY_PLATFORM_LINUX)
#include <signal.h>
		#define CANDY_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
#endif
#define CANDY_ENABLE_ASSERTS
#else
#define CANDY_DEBUGBREAK()
#endif

#define CANDY_EXPAND_MACRO(x) x
#define CANDY_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

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