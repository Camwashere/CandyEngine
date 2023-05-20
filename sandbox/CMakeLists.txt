cmake_minimum_required(VERSION 3.25)
project(Sandbox)



set(SANDBOX_FILES ExampleLayer.hpp ChunkRenderer.hpp ChunkRenderer.cpp ExampleLayer.cpp)


add_library(${PROJECT_NAME} STATIC ${SANDBOX_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ../sandbox)
target_link_libraries(${PROJECT_NAME} PUBLIC Candy)