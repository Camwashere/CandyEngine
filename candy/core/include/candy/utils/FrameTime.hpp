#pragma once
#include <chrono>
namespace Candy
{
  class FrameTime
  {
  private:
   
    float currentTime;
    float previousTime;
    float deltaTime;
    float fps;
    
    uint32_t frameCounter=0;
    std::chrono::high_resolution_clock::time_point startTimePoint;
    std::chrono::high_resolution_clock::time_point currentTimePoint;
    std::chrono::high_resolution_clock::time_point previousTimePoint;
    
  
  public:
    FrameTime();
  
  public:
    void Update();
  
  public:
    [[nodiscard]] float GetDeltaTime() const;
    
    [[nodiscard]] float GetCurrentTime() const;
    
    [[nodiscard]] float GetPreviousTime()const;
    [[nodiscard]] float GetFPS()const;
    
    
  };
}