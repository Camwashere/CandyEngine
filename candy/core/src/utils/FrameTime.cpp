#include <candy/utils/FrameTime.hpp>
#include <chrono>
#include <GLFW/glfw3.h>
namespace Candy
{
  
  FrameTime::FrameTime() : startTimePoint(std::chrono::high_resolution_clock ::now()),
  currentTimePoint(std::chrono::high_resolution_clock::now()),
  previousTimePoint(std::chrono::high_resolution_clock::now()),
  currentTime(0.0f), previousTime(0.0f), deltaTime(0.0f)
  {
  
  
  }
  
  void FrameTime::Update()
  {
    previousTimePoint = currentTimePoint;
    currentTimePoint = std::chrono::high_resolution_clock::now();
    //glfwGetTime();
    currentTime = std::chrono::duration<float, std::chrono::seconds::period>(currentTimePoint - startTimePoint).count();
    previousTime = std::chrono::duration<float, std::chrono::seconds::period>(previousTimePoint - startTimePoint).count();
    //deltaTime = currentTime-previousTime;
    deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(currentTimePoint - previousTimePoint).count();
  }
  
  float FrameTime::GetDeltaTime() const {return deltaTime;}
  float FrameTime::GetCurrentTime() const {return currentTime;}
  float FrameTime::GetPreviousTime()const{return previousTime;}
}