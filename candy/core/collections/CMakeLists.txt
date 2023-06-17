cmake_minimum_required(VERSION 3.25)
project(CandyCollections)

set(CMAKE_CXX_STANDARD 23)

add_library(${PROJECT_NAME} Array2D.hpp Array3D.hpp HeapArray3D.hpp MultiArray.hpp)
target_link_libraries(${PROJECT_NAME} PUBLIC CandyMath)
target_include_directories(${PROJECT_NAME} PUBLIC ../math)