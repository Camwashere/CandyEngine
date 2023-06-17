cmake_minimum_required(VERSION 3.25)
project(CandyNoise)

set(CMAKE_CXX_STANDARD 23)

add_library(${PROJECT_NAME} PerlinNoise.hpp PerlinNoise.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC CandyMath)
target_include_directories(${PROJECT_NAME} PUBLIC ../math)