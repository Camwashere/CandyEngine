cmake_minimum_required(VERSION 3.25)
project(CandyBase)

set(CMAKE_CXX_STANDARD 23)
set(SOURCE_BASE_FILES general/CandyAssert.hpp general/CandyConcepts.hpp general/CandyCoreBase.hpp
        primitive/PrimitiveTypes.hpp primitive/UUID.hpp primitive/UUID.cpp primitive/RawBuffer.hpp debug/Logger.hpp primitive/KeyCodes.hpp
        debug/Log.hpp debug/Log.cpp debug/Profiler.hpp primitive/MouseCodes.hpp general/PlatformDetection.hpp CandyBase.hpp)

find_package(fmt CONFIG REQUIRED)

add_library(${PROJECT_NAME} ${SOURCE_BASE_FILES})

target_link_libraries(${PROJECT_NAME} PUBLIC fmt::fmt-header-only)

