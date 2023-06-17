cmake_minimum_required(VERSION 3.25)
project(CandyEngineAll)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --enable-llvm")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23")

add_subdirectory(candy)
add_subdirectory(sugar)

add_executable(${PROJECT_NAME} sugar/src/SugarApp.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC Sugar)


