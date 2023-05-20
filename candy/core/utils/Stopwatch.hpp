#pragma once
#include <chrono>
namespace Candy::Utils {
        
        
        class Stopwatch {
        private:
            std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
            std::chrono::time_point<std::chrono::high_resolution_clock> endTime;
        
        public:
            Stopwatch() = default;
        
        public:
            void Start();
            
            void Stop();
            
            long double ElapsedNanoseconds() const;
            
            long double ElapsedMicroseconds() const;
            
            long double ElapsedMilliseconds() const;
            
            long double ElapsedSeconds() const;
            
        };
    }