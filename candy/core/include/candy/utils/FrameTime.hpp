#pragma once

namespace Candy
{
    class FrameTime
    {
    private:
        float currentTime;
        float previousTime;
        float deltaTime;
        
    public:
        FrameTime();
        
    public:
        void Update();
        
    public:
        [[nodiscard]] float GetDeltaTime()const{return deltaTime;}
        [[nodiscard]] float GetCurrentTime()const{return currentTime;}
        
    };
}