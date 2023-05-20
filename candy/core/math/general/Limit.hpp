#pragma once
#include <Candy/CandyEngineBase.hpp>

namespace Candy::Math
{
    template<typename T>
    struct Limit
    {
        static constexpr T Max(){return 0;}
        static constexpr T Min(){return 0;}
        static constexpr bool IsSpecialized(){return false;}
    
    };
    
    template<FloatingPoint T>
    struct Limit<T>
    {
        static constexpr T Max(){return FP_INFINITE;}
        static constexpr T Min(){return -FP_INFINITE;}
        static constexpr bool IsSpecialized(){return true;}
    };
    
    
    template<>
    struct Limit<uint8>
    {
        static constexpr uint8 Max(){return UINT8_MAX;}
        static constexpr uint8 Min(){return 0;}
        static constexpr bool IsSpecialized(){return true;}
    };
    
    template<>
    struct Limit<uint16>
    {
        static constexpr uint16 Max(){return UINT16_MAX;}
        static constexpr uint16 Min(){return 0;}
        static constexpr bool IsSpecialized(){return true;}
    };
    
    template<>
    struct Limit<uint32>
    {
        static constexpr uint32 Max(){return UINT32_MAX;}
        static constexpr uint32 Min(){return 0;}
        static constexpr bool IsSpecialized(){return true;}
    };
    template<>
    struct Limit<uint64>
    {
        static constexpr uint64 Max(){return UINT64_MAX;}
        static constexpr uint64 Min(){return 0;}
        static constexpr bool IsSpecialized(){return true;}
    };
    
    template<>
    struct Limit<int8>
    {
        static constexpr int8 Max(){return INT8_MAX;}
        static constexpr int8 Min(){return INT8_MIN;}
        static constexpr bool IsSpecialized(){return true;}
    };
    
    template<>
    struct Limit<int16>
    {
        static constexpr int16 Max(){return INT16_MAX;}
        static constexpr int16 Min(){return INT16_MIN;}
        static constexpr bool IsSpecialized(){return true;}
    };
    
    template<>
    struct Limit<int32>
    {
        static constexpr int32 Max(){return INT32_MAX;}
        static constexpr int32 Min(){return INT32_MIN;}
        static constexpr bool IsSpecialized(){return true;}
    };
    
    template<>
    struct Limit<int64>
    {
        static constexpr int64 Max(){return INT64_MAX;}
        static constexpr int64 Min(){return INT64_MIN;}
        static constexpr bool IsSpecialized(){return true;}
    };
    
    template<>
    struct Limit<bool>
    {
        static constexpr bool Max(){return true;}
        static constexpr bool Min(){return false;}
        static constexpr bool IsSpecialized(){return true;}
    };
    
    template<>
    struct Limit<char>
    {
        static constexpr char Max(){return CHAR_MAX;}
        static constexpr char Min(){return CHAR_MIN;}
        static constexpr bool IsSpecialized(){return true;}
    };
    
    
    
    
}