#pragma once
#include <chrono>

namespace Candy::Utils
{
    class Stopwatch
    {
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
        std::chrono::time_point<std::chrono::high_resolution_clock> endTime;
    
    public:
        Stopwatch() = default;
    
    public:
        void Start();
        
        void Stop();
        
        [[nodiscard]] long double ElapsedNanoseconds() const;
        
        [[nodiscard]] long double ElapsedMicroseconds() const;
        
        [[nodiscard]] long double ElapsedMilliseconds() const;
        
        [[nodiscard]] long double ElapsedSeconds() const;
    };
}