#pragma once
#include "Base.hpp"
#include "Log.hpp"
#include <filesystem>


#ifdef CANDY_ENABLE_ASSERTS

// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
#define CANDY_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { CANDY##type##ERROR(msg, __VA_ARGS__); CANDY_DEBUGBREAK(); } }
#define CANDY_INTERNAL_ASSERT_WITH_MSG(type, check, ...) CANDY_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define CANDY_INTERNAL_ASSERT_NO_MSG(type, check) CANDY_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", CANDY_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define CANDY_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define CANDY_INTERNAL_ASSERT_GET_MACRO(...) CANDY_EXPAND_MACRO( CANDY_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, CANDY_INTERNAL_ASSERT_WITH_MSG, CANDY_INTERNAL_ASSERT_NO_MSG) )

// Currently accepts at least the condition and one additional parameter (the message) being optional
#define CANDY_ASSERT(...) CANDY_EXPAND_MACRO( CANDY_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#define CANDY_CORE_ASSERT(...) CANDY_EXPAND_MACRO( CANDY_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )





#else
#define CANDY_ASSERT(...)
#define CANDY_CORE_ASSERT(...)


#endif