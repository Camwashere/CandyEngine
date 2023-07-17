#pragma once
#include "candy/base/PlatformDetection.hpp"

#ifdef CANDY_PLATFORM_WINDOWS
  #ifndef NOMINMAX
    #define NOMINMAX
  #endif
#endif

#include <string>
#include <array>
#include <vector>
#include "candy/base/Base.hpp"
#include "candy/base/Log.hpp"
#include "candy/base/Instrumentor.hpp"
#include "candy/base/Assert.hpp"

#ifdef CANDY_PLATFORM_WINDOWS
  #include <Windows.h>
#endif
