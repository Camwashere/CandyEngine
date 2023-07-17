#include <candy/utils/Stopwatch.hpp>

namespace Candy::Utils
{
    void Stopwatch::Start() {
        startTime = std::chrono::high_resolution_clock::now();
    }
    
    void Stopwatch::Stop() {
        endTime = std::chrono::high_resolution_clock::now();
    }
    
    long double Stopwatch::ElapsedNanoseconds() const {
        std::chrono::duration<long double, std::nano> d = endTime - startTime;
        return d.count();
    }
    
    long double Stopwatch::ElapsedMicroseconds() const {
        std::chrono::duration<long double, std::micro> d = endTime - startTime;
        return d.count();
    }
    
    long double Stopwatch::ElapsedMilliseconds() const {
        std::chrono::duration<long double, std::milli> d = endTime - startTime;
        return d.count();
    }
    
    long double Stopwatch::ElapsedSeconds() const {
        std::chrono::duration<long double> d = endTime - startTime;
        return d.count();
    }
}